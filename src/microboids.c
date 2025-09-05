#include "m0_util.h"
#include "util.h"
#include "clock.h"
#include "i2c.h"
#include "gpio.h"
#include "state.h"
#include "events.h"
#include "fifo_base.h"
#include "timer.h"
#include "bird.h"
#include "life.h"
#include "display.h"
#include "random.h"
#include "systick.h"
#include "watchdog.h"
#include <stdbool.h>

#define MODESELECT_PIN ( 7U )
#define I2C_SCL ( 11U )
#define I2C_SDA ( 12U )

#define CORE_CLOCK ( 64000000U )
#define SYSTICK_1MS ( ( CORE_CLOCK / 1000U ) - 1U )

_Static_assert( LCD_COLUMNS == DISPLAY_COLUMNS, "Mismatch of column size" );
_Static_assert( LCD_ROWS == DISPLAY_ROWS, "Mismatch of row size" );
_Static_assert( LCD_PAGES == DISPLAY_PAGES, "Mismatch of pages" );
_Static_assert( LCD_FULL_ROWS == DISPLAY_FULL_ROWS, "Mismatch of full row size" );
_Static_assert( sizeof( uint8_t ) == 1U, "uint8_t > 1 byte" );

DEFINE_STATE(Life);

#define EVENTS(EVNT) \
    EVNT(Timer) \

GENERATE_EVENTS(EVENTS);

static volatile gpio_t * gpio_a = ( gpio_t *) GPIOA_BASE;
static volatile gpio_t * gpio_b = ( gpio_t *) GPIOB_BASE;
static event_fifo_t events;

typedef struct
{
    state_t state;
    void (*tick)(void);
    uint8_t (*(*get)(void))[LCD_COLUMNS];
}
microboids_state_t;

/* This goes into an uninitialised region so that upon the user
 * pressing the reset button, the GOL will start again using
 * the last seed in memory
 */
static random_t random_seed __attribute__((section(".no_init")));

void  __attribute__((interrupt("IRQ"))) _tim2( void )
{
    if(!FIFO_IsFull((fifo_base_t*)&events))
    {
        FIFO_Enqueue( &events, EVENT(Timer));
    }
    Timer_ClearInterrupt();
}

static void Init ( microboids_state_t * const state )
{
    Clock_Set64MHz();
    SysTick_Init( SYSTICK_1MS );
    
    /* Globally Enable Interrupts */
    asm("CPSIE IF"); 


    GPIO_Init();
    GPIO_ConfigureInput(gpio_b, MODESELECT_PIN);

    GPIO_SetAlt(gpio_a, I2C_SCL, 0x6);
    GPIO_SetAlt(gpio_a, I2C_SDA, 0x6);

    GPIO_SetOpenDrain(gpio_a, I2C_SCL);
    GPIO_SetOpenDrain(gpio_a, I2C_SDA);

    GPIO_SetSpeed(gpio_a, I2C_SCL);
    GPIO_SetSpeed(gpio_a, I2C_SDA);
    
    /* microcontroller starts faster than the power on for LCD
     * so need brief delay on startup */
    SysTick_Delay(60U);
    
    Events_Init(&events);
    Random_Init(&random_seed);
    I2C_Init();
    Display_Init();
    Timer_Init();

    state->state.state = STATE(Life);
    
    if(!GPIO_ReadInput(gpio_b, MODESELECT_PIN))
    {
        Bird_Init( Random_Next(&random_seed) );
        state->tick = Bird_Tick;
        state->get = Bird_GetBuffer;
    }
    else
    {
        Timer_UpdatePeriod(4U);
        Life_Init( Random_Next(&random_seed) );
        state->tick = Life_Tick;
        state->get = Life_GetBuffer;
    }
    Watchdog_Init();
}

/* Only state of the program */
static state_ret_t State_Life( state_t * this, event_t s )
{
    state_ret_t ret;
    microboids_state_t * state = (microboids_state_t *)this;

    switch( s )
    {
        case EVENT(Timer):
        {
            state->tick();
            const uint8_t (*buffer)[LCD_COLUMNS] = state->get();
            Display_Update(buffer);
            ret = HANDLED();
            break;
        }
        case EVENT(Enter):
        {
            const uint8_t (*buffer)[LCD_COLUMNS] = state->get();
            Display_Update(buffer);
            Timer_Start();
            ret = HANDLED();
            break;
        }
        case EVENT(Exit):
        default:
        {
            ASSERT(false);
            ret = NO_PARENT(this);
        }
        break;
    }

    return ret;
}

/* Main Event Loop */
static void Loop( void )
{
    microboids_state_t life;    
    Init(&life);

    event_t sig = EVENT(None);

    FIFO_Enqueue(&events, EVENT(Enter));
    
    while( 1 )
    {
        while( FIFO_IsEmpty( (fifo_base_t*)&events ) )
        {
            asm("wfi"); 
        }
        sig = FIFO_Dequeue( &events );
        STATEMACHINE_Dispatch( &life.state, sig );
        Watchdog_Kick();
    }
}

int main ( void )
{
    Loop();

    return 0;
}

