
#include "CTRL.h"
#include "SEN.h"
#include "ACT.h"

extern moduleState_t TST_State;

moduleState_t CTRL_State = DEFAULT;

actuatorValue_t checkAlarms(sensorValue_t value)
{
	actuatorValue_t actuatorValue = ALARM_DEFAULT;
	static uint8_t errorNo = ZERO;

	if ((INV_VALUE == value) && (ALARM_DEFAULT == actuatorValue))
	{
		errorNo++;

		if (ERROR_LIMIT <= errorNo)
		{
			actuatorValue = ALARM_ERROR;
			(TST_State == INIT) ? (int)TST_State : printf("\n> Error alarm type activated <\n");
			
		}
		else { /* Do nothing */ }
	}
	else
	{
		errorNo = ZERO;
	}

	if (((WARNING_LOWER_LIMIT <= value) && (WARNING_UPPER_LIMIT > value)) && (ALARM_DEFAULT == actuatorValue))
	{
		actuatorValue = ALARM_WARNING;
		(TST_State == INIT) ? (int)TST_State : printf("\n> Warning alarm type activated <\n");

	}
	else { /* Do nothing */ }

	if (((EMERGENCY_LOWER_LIMIT <= value) && (EMERGENCY_UPPER_LIMIT >= value)) && (ALARM_DEFAULT == actuatorValue))
	{
		actuatorValue = ALARM_EMERGENCY;
		(TST_State == INIT) ? (int)TST_State : printf("\n> Emergency alarm type activated <\n");

	}
	else { /* Do nothing */ }

	return actuatorValue;
}

functionState_t CTRL_Init(void)
{
	functionState_t func_state = FUNCTION_OK;

	CTRL_State = INIT;
	(TST_State == INIT) ? (int)TST_State : printf(">CO2 Controll initialized\n");

	(void)func_state;

	return func_state;
}

functionState_t CTRL_Main(void)
{
	functionState_t func_state = FUNCTION_OK;
	static uint8_t CTRL_Main_CNT = ZERO;

	sensorValue_t sensor_value = ZERO;
	actuatorValue_t actoator_value = ALARM_DEFAULT;

	(TST_State == INIT) ? (int)TST_State : printf(">CO2 Controll cyclic activity no: %d\n", CTRL_Main_CNT++);

	if (INIT != CTRL_State)
	{
		func_state = FUNCTION_NO_INIT;

	}
	else
	{

		func_state = SEN_GetValue(&sensor_value);

		(TST_State == INIT) ? (int)TST_State : printf("[CO2 Concentration: %d(*1000)\n", sensor_value);

		actoator_value = checkAlarms(sensor_value);

		func_state = ACT_SetValue(actoator_value);

	}

	return func_state;
}