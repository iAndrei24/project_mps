
    /* CO2Detection_Tests.cpp */

#include "CO2Detection.h"
#include "Test.h"


/* Test Groups CO2Detection_Init START*/

/* Testing that the function it's okay with normal inputs */
/* Result mut be FUNCTION_OK */
TEST(CO2Detection_Init,FUNCTION_OK_Case)
{
    /* Initializare */
    functionState_t function_state_test = FUNCTION_NOK;

    /* Check inputs */
    CO2Detection CO2_Handler(NO_TOLERATED_ERR, ALARM_PIN_ERROR, ALARM_PIN_WARNING, ALARM_PIN_EMERGENCY, VENTILATION_PIN, SENSOR_PIN);

    /* Run Test */
    function_state_test = CO2_Handler.CO2Detection_Init(); 

    /* Check Results */
    CHECK_EQUAL(FUNCTION_OK, function_state_test);


    /* Deinitializare */

}


/* Testing that the function it's not okay with wrong inputs */
/* Result mut be FUNCTION_NOK */
TEST(CO2Detection_Init,FUNCTION_NOK_Case)
{
    /* Initializare */
    functionState_t function_state_test = FUNCTION_OK;

    /* Check inputs */
    CO2Detection CO2_Handler(700u, ALARM_PIN_ERROR, ALARM_PIN_WARNING, ALARM_PIN_EMERGENCY, VENTILATION_PIN, SENSOR_PIN);

    /* Run Test */
    function_state_test = CO2_Handler.CO2Detection_Init(); 

    /* Check Results */
    CHECK_EQUAL(FUNCTION_NOK, function_state_test);


    /* Deinitializare */

}

/* Test Groups CO2Detection_Init END*/

/* Test Groups CO2Detection_Main START*/

/* Testing that sensor malfunction it's detected */
/* Result mut be ERROR ALARM */
TEST(CO2Detection_Main,SENSOR_ERROR)
{
    /* Initializare */
    functionState_t function_state_test = FUNCTION_NOK;
    co2Value_t global_test_sensor_value = 200u;

    /* Check inputs */
    CO2Detection CO2_Handler(NO_TOLERATED_ERR, ALARM_PIN_ERROR, ALARM_PIN_WARNING, ALARM_PIN_EMERGENCY, VENTILATION_PIN, SENSOR_PIN);
    global_test_sensor_value = 10000u;

    /* Run Test */
    function_state_test = CO2_Handler.CO2Detection_Main(); 
    function_state_test = CO2_Handler.CO2Detection_Main(); 
    function_state_test = CO2_Handler.CO2Detection_Main(); 

    /* Check Results */
    CHECK_EQUAL(FUNCTION_OK, function_state_test);
    CHECK_EQUAL(LOGIC_HIGH, PIN_DIGITAL_READ(this.alarm_error_pin));


    /* Deinitializare */
    global_test_sensor_value = 200u;

}


/* Testing that sensor warning it's detected */
/* Result mut be ERROR WARNING */
TEST(CO2Detection_Main,SENSOR_WARNING)
{
    /* Initializare */
    functionState_t function_state_test = FUNCTION_NOK;
    co2Value_t global_test_sensor_value = 200u;

    /* Check inputs */
    CO2Detection CO2_Handler(NO_TOLERATED_ERR, ALARM_PIN_ERROR, ALARM_PIN_WARNING, ALARM_PIN_EMERGENCY, VENTILATION_PIN, SENSOR_PIN);
    global_test_sensor_value = 250u;

    /* Run Test */
    function_state_test = CO2_Handler.CO2Detection_Main(); 

    /* Check Results */
    CHECK_EQUAL(FUNCTION_OK, function_state_test);
    CHECK_EQUAL(LOGIC_HIGH, PIN_DIGITAL_READ(this.alarm_warning_pin));


    /* Deinitializare */
    global_test_sensor_value = 200u;

}

/* Testing that sensor emergency it's detected */
/* Result mut be ERROR EMERGENCY & VENTILATION*/
TEST(CO2Detection_Main,SENSOR_EMERGENCY)
{
    /* Initializare */
    functionState_t function_state_test = FUNCTION_NOK;
    co2Value_t global_test_sensor_value = 200u;

    /* Check inputs */
    CO2Detection CO2_Handler(NO_TOLERATED_ERR, ALARM_PIN_ERROR, ALARM_PIN_WARNING, ALARM_PIN_EMERGENCY, VENTILATION_PIN, SENSOR_PIN);
    global_test_sensor_value = 700u;

    /* Run Test */
    function_state_test = CO2_Handler.CO2Detection_Main(); 

    /* Check Results */
    CHECK_EQUAL(FUNCTION_OK, function_state_test);
    CHECK_EQUAL(LOGIC_HIGH, PIN_DIGITAL_READ(this.alarm_emergency_pin));
    CHECK_EQUAL(LOGIC_HIGH, PIN_DIGITAL_READ(this.ventilation_pin));


    /* Deinitializare */
    global_test_sensor_value = 200u;

}

/* Testing that no error it's detected */
/* Result mut be no error*/
TEST(CO2Detection_Main,SENSOR_EMERGENCY)
{
    /* Initializare */
    functionState_t function_state_test = FUNCTION_NOK;
    co2Value_t global_test_sensor_value = 200u;

    /* Check inputs */
    CO2Detection CO2_Handler(NO_TOLERATED_ERR, ALARM_PIN_ERROR, ALARM_PIN_WARNING, ALARM_PIN_EMERGENCY, VENTILATION_PIN, SENSOR_PIN);
    global_test_sensor_value = 200u;

    /* Run Test */
    function_state_test = CO2_Handler.CO2Detection_Main(); 
    function_state_test = CO2_Handler.CO2Detection_Main(); 
    function_state_test = CO2_Handler.CO2Detection_Main(); 
    function_state_test = CO2_Handler.CO2Detection_Main(); 

    /* Check Results */
    CHECK_EQUAL(FUNCTION_OK, function_state_test);
    CHECK_EQUAL(LOGIC_LOW, PIN_DIGITAL_READ(this.alarm_error_pin));
    CHECK_EQUAL(LOGIC_LOW, PIN_DIGITAL_READ(this.alarm_warning_pin));
    CHECK_EQUAL(LOGIC_LOW, PIN_DIGITAL_READ(this.alarm_emergency_pin));
    CHECK_EQUAL(LOGIC_LOW, PIN_DIGITAL_READ(this.ventilation_pin));


    /* Deinitializare */
    global_test_sensor_value = 200u;

}

/* Test Groups CO2Detection_Main END*/