
    /* Project_Cfg.h */

#ifndef PROJECT_CFG_H_
#define PROJECT_CFG_H_

#define ALARM_PIN_ERROR (2U)
#define ALARM_PIN_WARNING (3U)
#define ALARM_PIN_EMERGENCY (4U)
#define SENSOR_PIN (5U)
#define VENTILATION_PIN (6U)

#define SAMPLING_TIME (1000U)
#define NO_TOLERATED_ERR (3U)

typedef enum TOLERANCE_LIMITS
{
    LOWER_LIMIT = 200,
    UPPER_LIMIT = 1000,
    WARNING_LOWER_LIMIT = 200,
    WARNING_UPPER_LIMIT = 600,
    EMERGENCY_LOWER_LIMIT = 600,
    EMERGENCY_UPPER_LIMIT = 1000

}toleranceLimit_t;

typedef unsigned short int co2Value_t;
typedef unsigned int samplingTime_t;
typedef unsigned int samplingTolerance_t;
typedef unsigned char pinNo_t;


#define PIN_DIGITAL_WRITE(PIN, LOGICAL_STATE) DEFAULT_VALUE/* digitalWrite(PIN, LOGICAL_STATE) */
#define PIN_DIGITAL_READ(PIN) DEFAULT_VALUE/* digitalRead(PIN) */

#define PIN_ANALOG_WRITE(PIN, VALUE) DEFAULT_VALUE/* analogWrite(PIN, VALUE) */
#define PIN_ANALOG_READ(PIN) DEFAULT_VALUE/* analogRead(PIN) */

#define PIN_MODE_SET(PIN, PIN_MODE) DEFAULT_VALUE/* PinMode(PIN, PIN_MODE) */

#define LOGIC_HIGH  DEFAULT_VALUE/* HIGH */
#define LOGIC_LOW   DEFAULT_VALUE/* LOW */

#define LOGIC_OUTPUT DEFAULT_VALUE /* OUTPUT */
#define LOGIC_INPUT  DEFAULT_VALUE /* INPUT */


#endif /* PROJECT_CFG_H_ */