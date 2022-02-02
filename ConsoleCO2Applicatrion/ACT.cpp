
#include "ACT.h"

extern moduleState_t TST_State;

moduleState_t ACT_State = DEFAULT;
actuatorValue_t ACT_Mode = ALARM_DEFAULT;
extern sensorValue_t DBG_SENSOR_VALUE;
extern uint8_t DBG_Achitation;

functionState_t ACT_Init(void)
{
	functionState_t func_state = FUNCTION_OK;

	ACT_State = INIT;
    (TST_State == INIT) ? (int)TST_State : printf(">Actuators initialized\n");

	(void)func_state;

	return func_state;
}

functionState_t ACT_SetValue(actuatorValue_t value)
{
	functionState_t func_state = FUNCTION_OK;

	if (INIT != ACT_State)
	{
		func_state = FUNCTION_NO_INIT;

	}
	else
	{
        switch (value)
        {
            case ALARM_ERROR:
            {
                (TST_State == INIT) ? (int)TST_State : printf("> Error: chengeing light from green to red and wait for mentenance.\n");
                ACT_Mode = ALARM_ERROR;
                break;
            }
            case ALARM_WARNING:
            {
                (TST_State == INIT) ? (int)TST_State : printf("> Warning: chengeing light from green to red and wait for achitation.\n");

                if (ZERO != DBG_Achitation)
                {
                    DBG_Achitation = ZERO;
                    (TST_State == INIT) ? (int)TST_State : printf("> Warning: signal was confirmed, starting ventilation.\n");

                }
                else { /* Do nothing */ }

                ACT_Mode = ALARM_WARNING;
                break;
            }
            case ALARM_EMERGENCY:
            {
                (TST_State == INIT) ? (int)TST_State : printf("> Emergency: chengeing light from green to red and start the ventilation.\n");
                ACT_Mode = ALARM_EMERGENCY;
                break;
            }
            default:
            {
                (TST_State == INIT) ? (int)TST_State : printf("> No alarm, no action.\n");
                ACT_Mode = ALARM_DEFAULT;
                break;
            }

        }

	}

	return func_state;
}