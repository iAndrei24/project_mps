
/* Proj_Spec.h */

#ifndef PROJECT_SPECIFIC_H_
#define PROJECT_SPECIFIC_H_

#include <stdio.h>

#define INV_VALUE (0xAAAA)
#define ZERO (0U)

typedef enum BASIC_STATES
{
    E_OK = 0,
    E_NOK = 1,
    E_ON = 1,
    E_OFF = 0

}basicStates_t;

typedef signed char sint8_t;
typedef unsigned char uint8_t;

typedef signed short int sint16_t;
typedef unsigned short int uint16_t;

typedef signed long int sint32_t;
typedef unsigned long int uint32_t;

#endif /* PROJECT_SPECIFIC_H_ */