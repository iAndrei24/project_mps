
    /* CO2Detection.cpp */

#include "CO2Detection.h"

/* Function used offer the nessesary inputs for this funtionality to work.
 *
 */
CO2Detection::CO2Detection(samplingTolerance_t noLimitErrors, pinNo_t alarmPin_Err, pinNo_t alarmPin_Wa, pinNo_t alarmPin_Em, pinNo_t ventilationPin, pinNo_t sensorPin)
{
    
    noOfToleratedErrors = ZERO;
    noErrors = noLimitErrors;

    alarm_error_pin = alarmPin_Err;
    alarm_warning_pin = alarmPin_Wa;
    alarm_emergency_pin = alarmPin_Em;
    ventilation_pin = ventilationPin;
    sensor_pin = sensorPin;
}

/* Function used to prepare the CO2Detection workflow.
 *
 */
functionState_t CO2Detection::CO2Detection_Init(void)
{
    functionState_t func_state = FUNCTION_OK;

    noOfToleratedErrors = ZERO;

    func_state = (functionState_t)(func_state | PIN_MODE_SET(this.alarm_error_pin, LOGIC_OUTPUT));
    func_state = (functionState_t)(func_state | PIN_MODE_SET(this.alarm_warning_pin, LOGIC_OUTPUT));
    func_state = (functionState_t)(func_state | PIN_MODE_SET(this.alarm_emergency_pin, LOGIC_OUTPUT));
    func_state = (functionState_t)(func_state | PIN_MODE_SET(this.ventilation_pin, LOGIC_OUTPUT));

    func_state = (functionState_t)(func_state | PIN_MODE_SET(this.sensor_pin, LOGIC_INPUT));

    return func_state;
}

/* Function used to write the workflow of an CO2Detection as per requirements.
 *
 */
functionState_t CO2Detection::CO2Detection_Main(void)
{
    functionState_t func_state = FUNCTION_OK;

    co2Value_t sensor_value = ZERO;

    /* 2. Toate valorile citite trebuie sa fie într-un interval predefinit. Valorile în afara intervalului sunt ignorate. */
    /* 10. Cantitatea de CO2 este citită cu ajutorul unui senzor. */
    func_state = (functionState_t)(func_state | getCO2Value(&sensor_value));

    if((FUNCTION_OK != func_state) && (INVALID_VALUE == sensor_value))
    {
        /* 3. Cand <X> citiri succesive ale unui senzor generează valori în afara intervalului predefinit un led,ce corespunde senzorului respectiv, își schimba culoarea în <color> (se genereaza ERROR). */
        noOfToleratedErrors++;

        if(noErrors <= noOfToleratedErrors)
        {
            func_state = (functionState_t)(func_state | setCO2Alarm(ALARM_ERROR));
        }
    }
    else
    {
        noOfToleratedErrors = ZERO;

        /* 4. În funcție de valorile citite se pot genera semnale WARNING sau ALARM. */
        if((WARNING_LOWER_LIMIT <= sensor_value) && (WARNING_UPPER_LIMIT > sensor_value))
        {
            /* 5. Cand un semnal WARNING este generat un led își schimba culoarea in <color>. */
            /* 12. Atunci cand cantitatea de CO2 este este mai mare decat <procent>%, un semnal WARNING este generat. */
            func_state = (functionState_t)(func_state | setCO2Alarm(ALARM_WARNING));
        }
        else if((EMERGENCY_LOWER_LIMIT <= sensor_value) && (EMERGENCY_UPPER_LIMIT > sensor_value))
        {
            /* 8. Cand un semnal ALARMĂ este generat un led își schimba culoarea in <color>. */
            /* 14. Atunci cand cantitatea de CO2 este este mai mare decat 0.3%, un semnal ALARMĂ este generat */
            func_state = (functionState_t)(func_state | setCO2Alarm(ALARM_EMERGENCY));
        }
        else
        {
            /* 6. Un WARNING persista pana cand este achitat de pilot sau dispar condițiile care l-au generat. */
            /* 7. După achitare un nou WARNING va fi generat doar dacă a existat cel puțin o citire pentru care nu s-a generat WARNING sau ALARM. */
            /* 9. Un ALARM persista pana cand dispar condițiile care l-au generat.  */
            func_state = (functionState_t)(func_state | setCO2Alarm(ALARM_OFF));

            /* 13. Dacă semnalul WARNING este achitat atunci se porneste instalatia de ventilatie. */
            /* 15. După apariția semnalului ALARM se porneste instalatia de ventilatie. */
            /* 16. Instalatia de ventilatie se oprește dacă cantitatea de CO2 este mai mica decat <procent>% */
            func_state = (functionState_t)(func_state | setCO2Ventilation(VENTILATION_ON));
        }
    }

    return func_state;
}

/* Function used to switch on the alarms.
 * Note: Alarm is controled digitally, in case want an default <color> this can be done hardware or software.
 */
functionState_t CO2Detection::setCO2Alarm(alarmState_t state)
{
    functionState_t func_state = FUNCTION_OK;

    switch(state)
    {
        case ALARM_ERROR:
        {
            func_state = (functionState_t)(func_state | PIN_DIGITAL_WRITE(this.alarm_error_pin, LOGIC_HIGH));
            func_state = (functionState_t)(func_state | PIN_DIGITAL_WRITE(this.alarm_warning_pin, ALARM_OFF));
            func_state = (functionState_t)(func_state | PIN_DIGITAL_WRITE(this.alarm_emergency_pin, ALARM_OFF));
            break;
        }
        case ALARM_WARNING:
        {
            func_state = (functionState_t)(func_state | PIN_DIGITAL_WRITE(this.alarm_error_pin, ALARM_OFF));
            func_state = (functionState_t)(func_state | PIN_DIGITAL_WRITE(this.alarm_warning_pin, LOGIC_HIGH));
            func_state = (functionState_t)(func_state | PIN_DIGITAL_WRITE(this.alarm_emergency_pin, ALARM_OFF));
            break;
        }
        case ALARM_EMERGENCY:
        {
            func_state = (functionState_t)(func_state | PIN_DIGITAL_WRITE(this.alarm_error_pin, ALARM_OFF));
            func_state = (functionState_t)(func_state | PIN_DIGITAL_WRITE(this.alarm_warning_pin, ALARM_OFF));
            func_state = (functionState_t)(func_state | PIN_DIGITAL_WRITE(this.alarm_emergency_pin, LOGIC_HIGH));
            break;
        }
        default:
        {
            func_state = (functionState_t)(func_state | PIN_DIGITAL_WRITE(this.alarm_error_pin, ALARM_OFF));
            func_state = (functionState_t)(func_state | PIN_DIGITAL_WRITE(this.alarm_warning_pin, ALARM_OFF));
            func_state = (functionState_t)(func_state | PIN_DIGITAL_WRITE(this.alarm_emergency_pin, ALARM_OFF));
            break;
        }
    }

    return func_state;
}

/* Function used to switch on the ventilation.
 * Note: Ventialation is controled digitally.
 */
functionState_t CO2Detection::setCO2Ventilation(ventilationState_t state)
{
    functionState_t func_state = FUNCTION_OK;

    func_state = (functionState_t)(func_state | PIN_DIGITAL_WRITE(this.ventilation_pin, state));

    return func_state;
}

/* Function used to obtain the CO2 Value from the sensor.
 * Note: Sensor must be analogic, else you need to change implementation to match.
 */
functionState_t CO2Detection::getCO2Value(co2Value_t* value)
{
    functionState_t func_state = FUNCTION_OK;

    *value = PIN_ANALOG_READ(this.sensor_pin);

    if((LOWER_LIMIT<(*value)) && (UPPER_LIMIT>(*value)))
    {
        func_state = FUNCTION_OK;
    }
    else
    {
        func_state = FUNCTION_NOK;
        (*value) = INVALID_VALUE;
    }

    return func_state;
}