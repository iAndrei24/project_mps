
#include "Tst.h"
#include "SEN.h"
#include "SEN_Tst.h"


extern moduleState_t SEN_State;
extern actuatorValue_t SEN_Mode;
extern sensorValue_t DBG_SENSOR_VALUE;

bool SEN_Init_T0(void)
{
	/* Precondition */
	SEN_State = DEFAULT;

	/* Test Run */
	(void)SEN_Init();

	/* Test results */
	return TST_CHECK_EQUAL(SEN_State, INIT, ((char*)"SEN_Init_Check_Module_State"));

}

bool SEN_GetValue_T0(void)
{
	/* Precondition */
	SEN_State = DEFAULT;
	functionState_t func_state = FUNCTION_OK;
	sensorValue_t value = 0;

	/* Test Run */
	func_state = SEN_GetValue(&value);

	/* Test results */
	return TST_CHECK_EQUAL(func_state, FUNCTION_NO_INIT, ((char*)"SEN_GetValue_Check_NOK_RET"));

}

bool SEN_GetValue_T1(void)
{
	/* Precondition */
	SEN_State = INIT;
	functionState_t func_state = FUNCTION_NOK;
	sensorValue_t value = 0;

	/* Test Run */
	func_state = SEN_GetValue(&value);

	/* Test results */
	return TST_CHECK_EQUAL(func_state, FUNCTION_OK, ((char*)"SEN_GetValue_Check_OK_RET"));

}

bool SEN_GetValue_T2(void)
{
	/* Precondition */
	SEN_State = INIT;
	functionState_t func_state = FUNCTION_NOK;
	sensorValue_t value = 0;
	DBG_SENSOR_VALUE = 14;

	/* Test Run */
	func_state = SEN_GetValue(&value);

	/* Test results */
	return TST_CHECK_EQUAL(value, DBG_SENSOR_VALUE, ((char*)"SEN_GetValue_Check_INRANGE"));

}

bool SEN_GetValue_T3(void)
{
	/* Precondition */
	SEN_State = INIT;
	functionState_t func_state = FUNCTION_NOK;
	sensorValue_t value = 0;
	DBG_SENSOR_VALUE = 0;

	/* Test Run */
	func_state = SEN_GetValue(&value);

	/* Test results */
	return TST_CHECK_EQUAL(value, INV_VALUE, ((char*)"SEN_GetValue_Check_OUTRANGE"));

}