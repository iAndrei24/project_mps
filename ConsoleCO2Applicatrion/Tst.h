
/* Tst.h */

#ifndef TEST_H_
#define TEST_H_

#include "Proj_Spec.h"
#include "Proj_Cfg.h"

#define NO_OF_TESTS (18U)

extern moduleState_t TST_State;

extern functionState_t TST_Init(void);
extern functionState_t TST_Main(void);

extern bool TST_CHECK_EQUAL(int given_value, int compare_value, char* test_name);
extern bool TST_CHECK_NEQUAL(int given_value, int compare_value, char* test_name);


#endif /* TEST_H_ */