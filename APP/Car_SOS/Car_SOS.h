/*
 * Car_SOS.h
 *
 * Created: 4/1/2020 10:52:09 AM
 *  Author: Az
 */ 


#ifndef CAR_SOS_H_
#define CAR_SOS_H_
/*-INCLUDES ----------------------------------------------------------------------------------------------------------*/
#include "../../Helpers/std_types.h"
/*- DEFINES & TYPEDEFS -----------------------------------------------------------------------------------------------*/
/*----- System States -----*/
#define INITIALIZE          0
#define TRIGGER_MEASUREMENT 1
#define CALC_MEASUREMENT    2
#define STEERING_ACTION     3
#define TIME_OUT		       4
#define RESET               5
/*--- Distance Boundaries (measured in cm) ----*/
#define UP_BOUNDARY_DISTANCE   35
#define DOWN_BOUNDARY_DISTANCE 25
/* FUNCTION PROTOTYPES ----------------------------------------------------------------------------------------------*/
/*
*  Description : The main function on Car_SOS
*
*  @param void 
*
*  @return void 
*/
extern void Car_SOS(void);

#endif /* CAR_SOS_H_ */