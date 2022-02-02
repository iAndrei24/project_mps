
/* SEN.h */

#ifndef SENSOR_H_
#define SENSOR_H_

#include "Proj_Spec.h"
#include "Proj_Cfg.h"

extern functionState_t SEN_Init(void);
extern functionState_t SEN_GetValue(sensorValue_t* value);


#endif /* SENSOR_H_ */