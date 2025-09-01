#ifndef EVENTS_H_
#define EVENTS_H_

#include <stdint.h>
#include <stdbool.h>
#include <state.h>
#include "assert_bp.h"
#include "fifo_base.h"

#define FIFO_LEN (32U)

typedef struct
{
    char * name;
    bool (*event_fn)(void);
    event_t event;
}
event_callback_t;

typedef struct
{
    fifo_base_t base;
    event_t queue[FIFO_LEN];
    event_t in;
    event_t out;
} event_fifo_t;

extern void Events_Init(event_fifo_t * fifo);

#endif /* EVENTS_H_ */
