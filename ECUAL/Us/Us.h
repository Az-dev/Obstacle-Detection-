/*
 * Us.h
 *
 * Created: 2/18/2020 11:10:15 PM
 *  Author: Az
 */ 


#ifndef US_H_
#define US_H_

/*- INCLUDES -----------------------------------------------------------------------------------------------------------------------*/
#include "../../Helpers/std_types.h"
#include "../../Helpers/common_macros.h"
#include "../../MCAL/DIO/DIO.h"
#include "../SwDelay/SwDelay.h"
#include "../SwICU/SwICU.h"

/*- FUNCTION PROTOTYPES -----------------------------------------------------------------------------------------------------------*/

/*
*  Description  :  Description  :  Configures Us Triggering and Echo pins.
*
*  @param void
*
*  @return ERROR_STATUS
*/
ERROR_STATUS Us_Init(void);

/*
*  Description : This function send the  pulse, to trigger pin of the UltraSonic.
*                    
*  @param void
*
*  @return ERROR_STATUS
*/
ERROR_STATUS Us_Trigger(void);

/*
*  Description : This function calculate the distance based on input capture value
*
*
*  @param void
*
*  @return ERROR_STATUS
*/
ERROR_STATUS Us_CalcDistance(void);





#endif /* US_H_ */