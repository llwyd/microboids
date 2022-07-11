#include "fsm.h"

#define ENTER_CRITICAL { asm("CPSID IF"); }
#define EXIT_CRITICAL  { asm("CPSIE IF"); }

extern void FSM_Init( fsm_t * state, fsm_events_t * fsm_event )
{
    fsm_event->read_index = 0U;
    fsm_event->write_index = 0U;
    fsm_event->fill = 0U;

    FSM_Dispatch( state, signal_Enter );
}

extern void FSM_Dispatch( fsm_t * state, signal s )
{
    state_func previous = state->state;
    fsm_status_t status = state->state( state, s );

    while ( status == fsm_Transition )
    {
        previous( state, signal_Exit );
        previous = state->state;
        status = state->state( state, signal_Enter );
    }
}

extern void FSM_FlushEvents( fsm_events_t * fsm_event )
{
    if( fsm_event->fill > 0U )
    {
        ENTER_CRITICAL;
        fsm_event->read_index = fsm_event->write_index;
        fsm_event->fill = 0U;
        EXIT_CRITICAL;
    }
}

extern void FSM_AddEvent( fsm_events_t * fsm_event, signal s )
{
    if( fsm_event->fill < BUFFER_SIZE )
    {
        ENTER_CRITICAL;
        fsm_event->event[ fsm_event->write_index++ ] = s;
        fsm_event->fill++;
        fsm_event->write_index = ( fsm_event->write_index & ( BUFFER_SIZE - 1U ) );
        EXIT_CRITICAL;
    }
}

extern bool FSM_EventsAvailable( fsm_events_t * fsm_event )
{
    return ( fsm_event->fill > 0U );
}

extern signal FSM_GetLatestEvent( fsm_events_t * fsm_event )
{
    signal s;

    ENTER_CRITICAL;
    s = fsm_event->event[ fsm_event->read_index++ ];
    fsm_event->fill--;
    fsm_event->read_index = ( fsm_event->read_index & ( BUFFER_SIZE - 1U ) );
    EXIT_CRITICAL;

    return s;
}

