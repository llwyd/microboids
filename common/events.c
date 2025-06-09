#include "events.h"

static void Enqueue( fifo_base_t * const fifo );
static void Dequeue( fifo_base_t * const fifo );
static void Flush( fifo_base_t * const fifo );

extern void Events_Init(event_fifo_t * fifo)
{
    static const fifo_vfunc_t vfunc =
    {
        .enq = Enqueue,
        .deq = Dequeue,
        .flush = Flush,
    };
    FIFO_Init( (fifo_base_t *)fifo, FIFO_LEN );
    
    fifo->base.vfunc = &vfunc;
    fifo->in = 0x0;
    fifo->out = 0x0;
//    memset(fifo->queue, 0x00, FIFO_LEN * sizeof(fifo->in));
}

static void Enqueue( fifo_base_t * const base )
{
    ASSERT(base != NULL );
    ENQUEUE_BOILERPLATE( event_fifo_t, base );
}

static void Dequeue( fifo_base_t * const base )
{
    ASSERT(base != NULL );
    DEQUEUE_BOILERPLATE( event_fifo_t, base );
}

static void Flush( fifo_base_t * const base )
{
    ASSERT(base != NULL );
    FLUSH_BOILERPLATE( event_fifo_t, base );
}

