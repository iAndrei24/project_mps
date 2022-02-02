#pragma once
/* Project_Cfg.h */

#ifndef PROJECT_CFG_H_
#define PROJECT_CFG_H_

//#define TEST_UNIT_MODE
//#define TEST_VALIDATION_MODE

#define ERROR_LIMIT (3U)

#define WARNING_LOWER_LIMIT (20U)
#define WARNING_UPPER_LIMIT (30U)

#define EMERGENCY_LOWER_LIMIT (30U)
#define EMERGENCY_UPPER_LIMIT (500U)

#define SENSOR_LOWER_LIMIT (9U)
#define SENSOR_UPPER_LIMIT (501U)

typedef enum FUNCTION_STATE
{
    FUNCTION_OK = E_OK,
    FUNCTION_NOK = E_NOK,
    FUNCTION_NO_INIT

} functionState_t;

typedef enum MODULE_STATE
{
    INIT,
    DEFAULT

} moduleState_t;

typedef uint16_t sensorValue_t;

typedef enum ACTUATOR_ACTION
{
    ALARM_WARNING,
    ALARM_EMERGENCY,
    ALARM_ERROR,
    ALARM_DEFAULT

} actuatorValue_t;

#endif /* PROJECT_CFG_H_ */