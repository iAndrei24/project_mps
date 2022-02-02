
#include "Tst.h"
#include "VLD_Tst.h"
#include "CTRL.h"

extern sensorValue_t DBG_SENSOR_VALUE;
extern uint8_t DBG_Achitation;
extern actuatorValue_t ACT_Mode;
extern moduleState_t CTRL_State;
extern moduleState_t SEN_State;
extern moduleState_t ACT_State;

bool VLD_InvalidRead_To_Error(void)
{
	printf("\nValidation test 1: VLD_InvalidRead_To_Error\n");
	printf("______________________________________________\n");
	/* Precondition */
	printf("Step 0: [Inject sensor fault] Prepare the sistem condition for error. \n");
	DBG_SENSOR_VALUE = ZERO;
	CTRL_State = INIT;
	SEN_State = INIT;
	ACT_State = INIT;

	/* Test Run */
	printf("Step 1: [Fault in progress] Keep sensor fault for three cycles in order to rise an sensor error.\n");
	(void)CTRL_Main();
	(void)CTRL_Main();
	(void)CTRL_Main();

	/* Test results */
	printf("Step 2: [Fault result] Check the actuators as result to rise an sensor error.\n");
	return TST_CHECK_EQUAL(ACT_Mode, ALARM_ERROR, ((char*)"VLD_INVALID_READ_T0_ERROR"));

}

bool VLD_WarningRead_To_Warning(void)
{
	printf("\nValidation test 2: VLD_WarningRead_To_Warning\n");
	printf("______________________________________________\n");
	/* Precondition */
	printf("Step 0: [Inject warning fault] Prepare the sistem condition for warning alarm. \n");
	DBG_SENSOR_VALUE = 24;
	CTRL_State = INIT;
	SEN_State = INIT;
	ACT_State = INIT;

	/* Test Run */
	printf("Step 1: [Fault in progress] Keep sensor warning range in order to rise an warning alarm.\n");
	(void)CTRL_Main();

	/* Test results */
	printf("Step 2: [Fault result] Check the actuators as result to rise an warning alarm.\n");
	(void)TST_CHECK_EQUAL(ACT_Mode, ALARM_EMERGENCY, ((char*)"VLD_T0_WARNING"));

	printf("Step 3: [Fault result] Make a warning achitation and check if ventialation is started as reaction fot the warning.\n");
	DBG_Achitation = 1u;
	(void)CTRL_Main();
	return TST_CHECK_EQUAL(DBG_Achitation, ZERO, ((char*)"VLD_T0_WARNING_N_VENT"));

}


bool VLD_EmergencyRead_To_Emergency(void)
{
	printf("\nValidation test 3: VLD_EmergencyRead_To_Emergency\n");
	printf("______________________________________________\n");
	/* Precondition */
	printf("Step 0: [Inject emergency fault] Prepare the sistem condition for emergency alarm. \n");
	DBG_SENSOR_VALUE = 70;
	CTRL_State = INIT;
	SEN_State = INIT;
	ACT_State = INIT;

	/* Test Run */
	printf("Step 1: [Fault in progress] Keep sensor fault in order to rise an emergency alarm.\n");
	(void)CTRL_Main();

	/* Test results */
	printf("Step 2: [Fault result] Check the actuators as result to rise an emergency alarm.\n");
	return TST_CHECK_EQUAL(ACT_Mode, ALARM_EMERGENCY, ((char*)"VLD_T0_EMERGENCY"));

}