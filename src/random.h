#ifndef RANDOM_H_
#define RANDOM_H_

#include <stdint.h>

typedef struct
{
    uint32_t seed;
}
random_t;

extern void Random_Init(random_t * const rng);
extern void Random_SetSeed(random_t* const rng, uint32_t seed);
extern uint32_t Random_Next(random_t * const rng);

#endif /* RANDOM_H_ */
