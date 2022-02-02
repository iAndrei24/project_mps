
/* ACT.h */

#ifndef ACTUATOR_H_
#define ACTUATOR_H_

#include "Proj_Spec.h"
#include "Proj_Cfg.h"

extern functionState_t ACT_Init(void);
extern functionState_t ACT_SetValue(actuatorValue_t value);


#endif /* ACTUATOR_H_ */