#ifndef __UTIL_H_
#define __UTIL_H_

typedef enum {false, true} bool;

#define SET(X, Y, Z) ( (X) |=  ( (Y) << (Z) ) )
#define CLR(X, Y, Z) ( (X) &= ~( (Y) << (Z) ) )
#define TOG(X, Y, Z) ( (X) ^=  ( (Y) << (Z) ) )

#endif /* __UTIL_H_ */
