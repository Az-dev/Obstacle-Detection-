/*
 * SharedResource.c
 *
 * Created: 3/30/2020 9:08:51 PM
 *  Author: Az
 */ 
 /*- INCLUDES --------------------------------------------------------------------------------------------------------*/
 #include "SharedResource.h"
/*- GLOBALS ----------------------------------------------------------------------------------------------------------*/
 static uint32_t gu32_distance = 0;
 static uint16_t gu16_inputCaptureVal = 0;
 /*- FUNCTIONS DEFINITIONS -------------------------------------------------------------------------------------------*/
 /*
 *   Description : Sets/Updates Input Capture Value.
 *
 *   @param uint16_t val
 *   @return EnmRTEError_t
 */
 EnmRTEError_t Set_IC_Val(uint16_t val)
 {
    uint8_t au8_errorState = 0;
    /* Sets/Updates Input Capture value*/
    gu16_inputCaptureVal = val;    
    /* report success */
    au8_errorState = IC_SET_SUCCESS;

    return au8_errorState;
 }

 /*
 *   Description : Sets/Updates Distance measured value.
 *
 *   @param uint32_t val
 *   @return EnmRTEError_t
 */
 EnmRTEError_t Set_DistanceVal(uint32_t val)
 {
    /* Sets/Updates Distance value*/
    uint8_t au8_errorState = 0;
    /* Sets/Updates Input Capture value*/
    gu32_distance = val;
    /* report success */
    au8_errorState = DISTANCE_SET_SUCCESS;

    return au8_errorState;
 }

 /*
 *   Description : Gets Input Capture Value.
 *
 *   @param uint16_t * val (output param)
 *   @return EnmRTEError_t
 */
 EnmRTEError_t Get_IC_Val(uint16_t * val)
 {
    uint8_t au8_errorState = 0;   
    if(NULL != val)
    {
       /* Get Input Capture value*/
       *val = gu16_inputCaptureVal;
      /* Report Success */
      au8_errorState = IC_GET_SUCCESS;
    }
    else
    {
      /* Report Fail */
      au8_errorState = IC_GET_FAIL;
    }

    return au8_errorState;
 }

 /*
 *   Description : Gets Measured Distance value.
 *
 *   @param uint32_t * val (output param)
 *   @return EnmRTEError_t
 */
 EnmRTEError_t Get_DistanceVal(uint32_t * val)
 {
    uint8_t au8_errorState = 0;
    if(NULL != val)
    {
       /* Get Distance value*/
       *val = gu32_distance;
       /* Report Success */
       au8_errorState = DISTANCE_GET_SUCCESS;
    }
    else
    {
       /* Report Fail */
       au8_errorState = DISTANCE_GET_FAIL;
    }

    return au8_errorState;
 }