
#include "Tst.h"
#include "CTRL_Tst.h"
#include "ACT_Tst.h"
#include "SEN_Tst.h"

moduleState_t TST_State = DEFAULT;

bool (*TestList[NO_OF_TESTS])(void) =
{
	/* &getValue_branch_one_test*/
	&CTRL_Init_T0,
	&CTRL_Main_T0,
	&CTRL_Main_T1,
	&CTRL_Main_T2,
	&CTRL_Main_T3,
	&ACT_Init_T0,
	&ACT_SetValue_T0,
	&ACT_SetValue_T1,
	&ACT_SetValue_T2,
	&ACT_SetValue_T3,
	&ACT_SetValue_T4,
	&ACT_SetValue_T5,
	&ACT_SetValue_T6,
	&SEN_Init_T0,
	&SEN_GetValue_T0,
	&SEN_GetValue_T1,
	&SEN_GetValue_T2,
	&SEN_GetValue_T3
};

bool TST_CHECK_EQUAL(int given_value, int compare_value, char* test_name)
{
	bool func_state = false;

	if (given_value == compare_value)
	{
		printf("%s: Passed!\n", test_name);
		func_state = true;

	}
	else
	{
		printf("%s: Failed!\n", test_name);
		func_state = false;
	}

	return func_state;
}

bool TST_CHECK_NEQUAL(int given_value, int compare_value, char* test_name)
{
	bool func_state = false;

	if (given_value != compare_value)
	{
		printf("%s: Passed!\n", test_name);
		func_state = true;

	}
	else
	{
		printf("%s: Failed!\n", test_name);
		func_state = false;
	}

	return func_state;
}

functionState_t TST_Init(void)
{
	functionState_t func_state = FUNCTION_OK;

	(void)func_state;
	TST_State = INIT;
	printf("\nStarting testing procedure...\n");
	printf("Preparing %d tests...\n", NO_OF_TESTS);
	printf("\n");

	return func_state;
}

functionState_t TST_Main(void)
{
	functionState_t func_state = FUNCTION_OK;
	int passed_tests = 0u;
	
	printf("##################################\n");
	printf("#### Start project testing... ####\n");
	printf("##################################\n\n");

	printf("List of tests:\n");
	for (unsigned int index = 0u; index < NO_OF_TESTS; index++)
	{
		if (TestList[index]())
		{
			passed_tests++;

		}else{ /* Do nothing */ }
	}
	TST_State = DEFAULT;

	printf("------------------------------\n");
	printf(">> Test report: %d/%d\n\n", passed_tests, NO_OF_TESTS);

	return func_state;
}