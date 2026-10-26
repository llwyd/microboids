#include "random.h"
#include "crc.h"
#include "id.h"
#include "life_assert.h"

static uint32_t GenerateRandom(uint32_t x)
{
    /* Xorshift */
    x ^= x << 13;
	x ^= x >> 17;
	x ^= x << 5;

    return x;
}

static uint32_t InitialValue(void)
{
    volatile uint32_t * chip_id = (uint32_t *)UNIQUE_ID_BASE;
    uint32_t initial_seed = 0u;
    for(uint32_t idx = 0u; idx < UNIQUE_ID_WORDS; idx++)
    {
        initial_seed = CRC_Next(*(chip_id++));
    }
    
    ASSERT(initial_seed != 0u);
    return initial_seed;
}

extern void Random_Init(random_t * const rng)
{
    if(rng->seed == 0U)
    {
        rng->seed = InitialValue();
        rng->seed = GenerateRandom(rng->seed);
    }
    else
    {
        rng->seed = GenerateRandom(rng->seed);
    }
}

extern uint32_t Random_Next(random_t * const rng)
{
    rng->seed = GenerateRandom(rng->seed);
    return rng->seed;
}

extern void Random_SetSeed(random_t* const rng, uint32_t seed)
{
    rng->seed = seed;
}

