#include "buffer.h" 

#define BUFFER_SIZE ( 8U )

typedef struct
{
    unsigned char read_index;
    unsigned char write_index;
    unsigned char fill;
    void ( *fn[ BUFFER_SIZE ] ) ( void );
} task_buffer_t;

volatile task_buffer_t task;

void Task_Init( void )
{
    task.read_index = 0U;
    task.write_index = 0U;
    task.fill = 0U;
}

void Task_Add( void ( *fn)( void ) )
{ 
    /* Enter critical Section */
    asm("CPSID IF");
   
    if( task.fill < BUFFER_SIZE )
    {
        task.fn[task.write_index++] = fn;
        task.fill++;
        task.write_index %= BUFFER_SIZE;
    } 
 
    /* Exit critical Section */
    asm("CPSIE IF");
}

void Task_Get( void )
{ 
    /* Enter critical Section */
    asm("CPSID IF");
   
    if( task.fill > 0 )
    {
        task.fn[task.read_index++]();
        task.fill--;
        task.read_index %= BUFFER_SIZE;
    } 
 
    /* Exit critical Section */
    asm("CPSIE IF");
}

