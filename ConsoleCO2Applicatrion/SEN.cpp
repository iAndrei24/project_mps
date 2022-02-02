
#include "SEN.h"

extern moduleState_t TST_State;

moduleState_t SEN_State = DEFAULT;
extern sensorValue_t DBG_SENSOR_VALUE;

functionState_t SEN_Init(void)
{
	functionState_t func_state = FUNCTION_OK;

	SEN_State = INIT;
	(TST_State == INIT) ? (int)TST_State : printf(">CO2 Sensor initialized\n");

	(void)func_state;

	return func_state;
}

functionState_t SEN_GetValue(sensorValue_t* value)
{
	functionState_t func_state = FUNCTION_OK;

	if (INIT != SEN_State)
	{
		func_state = FUNCTION_NO_INIT;

	}
	else
	{
		*value = DBG_SENSOR_VALUE;

		if ((SENSOR_LOWER_LIMIT <= *value) && (SENSOR_UPPER_LIMIT >= *value))
		{
			(TST_State == INIT) ? (int)TST_State : printf(">Valid sensor value detected.\n");
		}
		else
		{
			func_state = FUNCTION_NOK;
			(TST_State == INIT) ? (int)TST_State : printf(">Invalid sensor value detected.\n");
			*value = INV_VALUE;
		}

	}

	return func_state;
}