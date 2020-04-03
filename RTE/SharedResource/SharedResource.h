/*
 * SharedResource.h
 *
 * Created: 3/30/2020 9:09:46 PM
 *  Author: Az
 */
#ifndef SHAREDRESOURCE_H_
#define SHAREDRESOURCE_H_
/*- INCLUDES ----------------------------------------------------------------------------------------------------------*/
#include "../../Helpers/std_types.h"
/*- TYPEDEFS ----------------------------------------------------------------------------------------------------------*/
typedef enum EnmRTEError
{
   RTE_UNDEFINED_ERROR = 0,
   IC_SET_SUCCESS = 1,
   IC_SET_FAIL = 2,
   IC_GET_SUCCESS = 3,
   IC_GET_FAIL = 4,
   DISTANCE_SET_SUCCESS = 5,
   DISTANCE_SET_FAIL = 6,
   DISTANCE_GET_SUCCESS = 7,
   DISTANCE_GET_FAIL = 8,
}EnmRTEError_t;
/*- FUNCTIONS PROTOTYPES -----------------------------------------------------------------------------------------------*/
/*
 *   Description : Sets/Updates Input Capture Value.
 *
 *   @param uint16_t val
 *   @return EnmRTEError_t
 */
 extern EnmRTEError_t Set_IC_Val(uint16_t val);

 /*
 *   Description : Sets/Updates Distance measured value.
 *
 *   @param uint32_t val
 *   @return EnmRTEError_t
 */
 extern EnmRTEError_t Set_DistanceVal(uint32_t val);

 /*
 *   Description : Gets Input Capture Value.
 *
 *   @param uint16_t * val (output param)
 *   @return EnmRTEError_t
 */
 extern EnmRTEError_t Get_IC_Val(uint16_t * val);

 /*
 *   Description : Gets Measured Distance value.
 *
 *   @param uint32_t * val (output param)
 *   @return EnmRTEError_t
 */
 extern EnmRTEError_t Get_DistanceVal(uint32_t * val);

#endif /* SHAREDRESOURCE_H_ */