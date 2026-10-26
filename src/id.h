#ifndef _UNIQUE_ID_H_
#define _UNIQUE_ID_H_

#include "m0_util.h"
#include "util.h"

#define UNIQUE_ID_BASE ( 0x1FFF7590 )
#define UNIQUE_ID_WORDS (96u / 32u)

_Static_assert(UNIQUE_ID_WORDS == 3u, "UNIQUE ID Incorrect size");

typedef uint32_t unique_id_t;

#endif /* _UNIQUE_ID_H_ */
