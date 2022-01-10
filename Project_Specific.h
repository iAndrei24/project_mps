
    /* Project_Specific.h */

#ifndef PROJECT_SPECIFIC_H_
#define PROJECT_SPECIFIC_H_

#define INVALID_VALUE (255U)
#define DEFAULT_VALUE (255U)

typedef enum BASIC_NUMBERS
{
    ZERO = 0,
    ONE,
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE
}basicNumbers_t;

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