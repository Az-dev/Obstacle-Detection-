/*
 * Us.c
 *
 * Created: 2/18/2020 11:09:55 PM
 *  Author: Az
 */
/*- INCLUDES -----------------------------------------------------------------------------------------------------------------------*/
#include "Us.h"
#include "Us_Cfg.h"

/*- FUNCTION DEFINITIONS ----------------------------------------------------------------------------------------------------------*/
/*
*  Description  :  Configures Us Triggering and Echo pins 
* 
*  @param void
*
*  @return ERROR_STATUS
*/
ERROR_STATUS Us_Init(void)
{
   /*---- 1 - Triggering pin config ----*/
   strDioCfg_t Us_trigger_config = 
   {
      ULTRA_EN_GPIO,
      ULTRA_ENABLE_BIT,
      OUTPUT
   };
   DIO_init(&Us_trigger_config);
   /*---- 2 - Echo pin config  ----*/   
   strDioCfg_t Us_echo_config =
   {
      ULTRA_OUT_GPIO,
      ULTRA_OUT_BIT,
      INPUT
   };
   DIO_init(&Us_echo_config);  
   /*--- Return Success ---*/
   return E_OK;  
}

/*
*  Description : This function send the  pulse, to trigger pin of the UltraSonic.
*
*  @param void
*
*  @return ERROR_STATUS
*/
ERROR_STATUS Us_Trigger(void)
{
   /*- Providing a trigger pulse ----------------*/
   DIO_Write(ULTRA_EN_GPIO,ULTRA_ENABLE_BIT,HIGH);
   softwareDelayMs(5);
   DIO_Write(ULTRA_EN_GPIO,ULTRA_ENABLE_BIT,LOW);
   /*--- Return Success ---*/
   return E_OK;
}


/*
*  Description : This function calculate the distance based on input capture value
*
*
*  @param void
*
*  @return ERROR_STATUS
*/
ERROR_STATUS Us_CalcDistance(void)
{
   /*- 1 - Get Input Capture Value Stored in RTE ---> GetInputCaptureVal()*/
   /*- 2 - Calculate the distance -based on the brought input capture value -*/
   /*- 3 - Update Distance Value Stored in RTE ---> Update/SetDistanceVal()*/
   /*---- Set the new measured distance ----*/
   //*Distance = ((gu32_Icu_Time * 68) / 1000);
   return E_OK;   
}
