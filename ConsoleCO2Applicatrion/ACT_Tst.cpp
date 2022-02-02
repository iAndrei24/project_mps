
#include "Tst.h"
#include "ACT.h"
#include "ACT_Tst.h"


extern moduleState_t ACT_State;
extern actuatorValue_t ACT_Mode;
extern sensorValue_t DBG_SENSOR_VALUE;
extern uint8_t DBG_Achitation;

bool ACT_Init_T0(void)
{
	/* Precondition */
	ACT_State = DEFAULT;

	/* Test Run */
	(void)ACT_Init();

	/* Test results */
	return TST_CHECK_EQUAL(ACT_State, INIT, ((char*)"ACT_Init_Check_Module_State"));

}

bool ACT_SetValue_T0(void)
{
	/* Precondition */
	ACT_State = INIT;

	/* Test Run */
	(void)ACT_SetValue(ALARM_ERROR);

	/* Test results */
	return TST_CHECK_EQUAL(ACT_Mode, ALARM_ERROR, ((char*)"ACT_SetValue_Check_ERROR"));

}

bool ACT_SetValue_T1(void)
{
	/* Precondition */
	ACT_State = INIT;

	/* Test Run */
	(void)ACT_SetValue(ALARM_DEFAULT);

	/* Test results */
	return TST_CHECK_EQUAL(ACT_Mode, ALARM_DEFAULT, ((char*)"ACT_SetValue_Check_DEFAULT"));

}

bool ACT_SetValue_T2(void)
{
	/* Precondition */
	ACT_State = INIT;

	/* Test Run */
	(void)ACT_SetValue(ALARM_WARNING);

	/* Test results */
	return TST_CHECK_EQUAL(ACT_Mode, ALARM_WARNING, ((char*)"ACT_SetValue_Check_WARNING"));

}

bool ACT_SetValue_T3(void)
{
	/* Precondition */
	ACT_State = INIT;

	/* Test Run */
	(void)ACT_SetValue(ALARM_EMERGENCY);

	/* Test results */
	return TST_CHECK_EQUAL(ACT_Mode, ALARM_EMERGENCY, ((char*)"ACT_SetValue_Check_EMERGENCY"));

}

bool ACT_SetValue_T4(void)
{
	/* Precondition */
	functionState_t func_state = FUNCTION_NOK;
	ACT_State = INIT;

	/* Test Run */
	func_state = ACT_SetValue(ALARM_EMERGENCY);

	/* Test results */
	return TST_CHECK_EQUAL(func_state, FUNCTION_OK, ((char*)"ACT_SetValue_Check_FUNC_OK_RET"));

}

bool ACT_SetValue_T5(void)
{
	/* Precondition */
	functionState_t func_state = FUNCTION_OK;
	ACT_State = DEFAULT;
	/* Test Run */
	func_state = ACT_SetValue(ALARM_EMERGENCY);
	ACT_State = INIT;

	/* Test results */
	return TST_CHECK_EQUAL(func_state, FUNCTION_NO_INIT, ((char*)"ACT_SetValue_Check_FUNC_NOK_RET"));

}

bool ACT_SetValue_T6(void)
{
	/* Precondition */
	ACT_State = INIT;
	DBG_Achitation = 1u;

	/* Test Run */
	(void)ACT_SetValue(ALARM_WARNING);

	/* Test results */
	return TST_CHECK_EQUAL(DBG_Achitation, ZERO, ((char*)"ACT_SetValue_Check_WARNING_ACH"));

}