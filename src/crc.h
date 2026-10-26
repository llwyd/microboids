#ifndef CRC_H_
#define CRC_H_

#include "m0_util.h"
#include "util.h"

extern void CRC_Init(void);
extern uint32_t CRC_Next(uint32_t input);

#endif /* CRC_H_ */
