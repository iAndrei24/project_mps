
#include "Tst.h"
#include "CTRL.h"
#include "CTRL_Tst.h"

extern moduleState_t CTRL_State;
extern moduleState_t SEN_State;
extern moduleState_t ACT_State;

extern actuatorValue_t ACT_Mode;
extern sensorValue_t DBG_SENSOR_VALUE;

bool CTRL_Init_T0(void)
{
	/* Precondition */
	CTRL_State = DEFAULT;

	/* Test Run */
	(void)CTRL_Init();

	/* Test results */
	return TST_CHECK_EQUAL(CTRL_State, INIT, ((char*)"CTRL_Init_Check_Module_State"));

}


bool CTRL_Main_T0(void)
{
	/* Precondition */
	DBG_SENSOR_VALUE = ZERO;
	CTRL_State = INIT;
	SEN_State = INIT;
	ACT_State = INIT;

	/* Test Run */
	(void)CTRL_Main();
	(void)CTRL_Main();
	(void)CTRL_Main();

	/* Test results */
	return TST_CHECK_EQUAL(ACT_Mode, ALARM_ERROR, ((char*)"CTRL_Main_ERROR_CASE"));

}

bool CTRL_Main_T1(void)
{
	/* Precondition */
	DBG_SENSOR_VALUE = 50;
	CTRL_State = INIT;
	SEN_State = INIT;
	ACT_State = INIT;

	/* Test Run */
	(void)CTRL_Main();

	/* Test results */
	return TST_CHECK_EQUAL(ACT_Mode, ALARM_EMERGENCY, ((char*)"CTRL_Main_EMERGENCY_CASE"));

}


bool CTRL_Main_T2(void)
{
	/* Precondition */
	DBG_SENSOR_VALUE = 24;
	CTRL_State = INIT;
	SEN_State = INIT;
	ACT_State = INIT;

	/* Test Run */
	(void)CTRL_Main();

	/* Test results */
	return TST_CHECK_EQUAL(ACT_Mode, ALARM_WARNING, ((char*)"CTRL_Main_WARNING_CASE"));

}

bool CTRL_Main_T3(void)
{
	/* Precondition */
	DBG_SENSOR_VALUE = 14;
	CTRL_State = INIT;
	SEN_State = INIT;
	ACT_State = INIT;

	/* Test Run */
	(void)CTRL_Main();

	/* Test results */
	return TST_CHECK_EQUAL(ACT_Mode, ALARM_DEFAULT, ((char*)"CTRL_Main_DEFAULT_CASE"));

}