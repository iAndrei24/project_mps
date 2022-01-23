
    /* CO2Detection.h */

#ifndef CO2DETECTION_H_
#define CO2DETECTION_H_

#include "Project_Cfg.h"
#include "Project_Specific.h"

typedef enum FUNCTION_STATE
{
    FUNCTION_OK = E_OK,
    FUNCTION_NOK = E_NOK
} functionState_t;

typedef enum ALARM_STATE
{
    ALARM_OFF = LOGIC_LOW,
    ALARM_ERROR = 1,
    ALARM_WARNING = 2,
    ALARM_EMERGENCY = 3,
} alarmState_t;

typedef enum VENTILATION_STATE
{
    VENTILATION_OFF = LOGIC_LOW,
    VENTILATION_ON = LOGIC_HIGH
} ventilationState_t;

class CO2Detection
{
    private:
    samplingTolerance_t noOfToleratedErrors;
    samplingTolerance_t noErrors;

    pinNo_t alarm_error_pin, 
            alarm_warning_pin, 
            alarm_emergency_pin, 
            ventilation_pin, 
            sensor_pin;
    
    functionState_t setCO2Alarm(alarmState_t state);
    functionState_t setCO2Ventilation(ventilationState_t state);

    public:
    CO2Detection(samplingTolerance_t noLimitErrors, pinNo_t alarmPin_Err, pinNo_t alarmPin_Wa, pinNo_t alarmPin_Em, pinNo_t ventilationPin, pinNo_t sensorPin);
    functionState_t CO2Detection_Init(void);
    functionState_t CO2Detection_Main(void);
    functionState_t getCO2Value(co2Value_t* value);

};

#endif /* CO2DETECTION_H_ */