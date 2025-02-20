/* Conway's game of life for the Trinket m0+ and a small lcd display
 * T.L. 2022
 * */

/* ATSAMD21E18 */

#include "util.h"
#include "clock.h"
#include "i2c.h"
#include "gpio.h"
#include "state.h"
#include "events.h"
#include "fifo_base.h"
#include "timer.h"
#include "bird.h"
#include "display.h"
#include "random.h"
#include "systick.h"
#include <stdbool.h>

#define LED_PIN ( 7U )
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

#define SIGNALS(SIG) \
    SIG(Timer) \

GENERATE_SIGNALS(SIGNALS);

static volatile gpio_t * gpio_a = ( gpio_t *) GPIOA_BASE;
static volatile gpio_t * gpio_b = ( gpio_t *) GPIOB_BASE;
static event_fifo_t events;

/* This goes into an uninitialised region so that upon the user
 * pressing the reset button, the GOL will start again using
 * the last seed in memory
 */
static random_t random_seed __attribute__((section(".no_init")));

void  __attribute__((interrupt("IRQ"))) _tim2( void )
{
    FIFO_Enqueue( &events, EVENT(Timer));
    Timer_ClearInterrupt();
}

static void UpdateLCD( void )
{
    const uint8_t (*buffer)[LCD_COLUMNS] = Bird_GetBuffer();
    Display_Update( buffer );
}

static void Init ( void )
{
    Clock_Set64MHz();
    SysTick_Init( SYSTICK_1MS );
    
    /* Globally Enable Interrupts */
    asm("CPSIE IF"); 

    /* microcontroller starts faster than the power on for LCD
     * so need brief delay on startup */
    SysTick_Delay(60U);

    GPIO_Init();
    GPIO_ConfigureOutput(gpio_b, LED_PIN);
    GPIO_SetOutput(gpio_b, LED_PIN);

    GPIO_SetAlt(gpio_a, I2C_SCL, 0x6);
    GPIO_SetAlt(gpio_a, I2C_SDA, 0x6);

    GPIO_SetOpenDrain(gpio_a, I2C_SCL);
    GPIO_SetOpenDrain(gpio_a, I2C_SDA);

    GPIO_SetSpeed(gpio_a, I2C_SCL);
    GPIO_SetSpeed(gpio_a, I2C_SDA);
    
    Events_Init(&events);
    Random_Init(&random_seed);
    I2C_Init();
    Display_Init();
    Timer_Init();
    Bird_Init( &UpdateLCD, Random_Next(&random_seed) );
}

/* Only state of the program */
static state_ret_t State_Life( state_t * this, event_t s )
{
    state_ret_t ret;

    switch( s )
    {
        case EVENT(Timer):
        {
            Bird_Tick();
            ret = HANDLED();
            break;
        }
        case EVENT(Enter):
        {
            GPIO_ClearOutput(gpio_b, LED_PIN);
            Timer_Start();
            ret = HANDLED();
            break;
        }
        case EVENT(Exit):
        default:
        {
            GPIO_SetOutput(gpio_b, LED_PIN);
            ret = HANDLED();
        }
        break;
    }

    return ret;
}

/* Main Event Loop */
static void Loop( void )
{
    state_t life;
    life.state = STATE(Life);
    event_t sig = EVENT(None);

    FIFO_Enqueue(&events, EVENT(Enter));
    
    while( 1 )
    {
        while( FIFO_IsEmpty( (fifo_base_t*)&events ) )
        {
            asm("wfi"); 
        }
        sig = FIFO_Dequeue( &events );
        STATEMACHINE_FlatDispatch( &life, sig );
    }
}

int main ( void )
{
    Init();
    Loop();

    return 0;
}

