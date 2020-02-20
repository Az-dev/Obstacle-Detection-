/*
 * Timer_Cfg.c
 *
 * Created: 2/17/2020 10:46:08 AM
 *  Author: Az
 */ 

/*- INCLUDES ----------------------------------------------------------------------------------------------------------------------------------------*/
#include "Timer.h"
/*- DEFINES -----------------------------------------------------------------------------------------------------------------------------------------*/
/*
#define T0_PWM_GPIO	(GPIOD)
#define T0_PWM_BIT	(BIT0)

#define T1_PWM_GPIO	(GPIOD)
#define T1_PWM_BIT	(BIT1)

#define T2_PWM_GPIO (GPIOD)
#define T2_PWM_BIT	(BIT2)
*/
/*- GLOBAL VARIABLES -------------------------------------------------------------------------------------------------------------------------------*/

/* configuring timer 0 to work as SW_PWM */
/*
strTimerConfig_t gstrTimer0Config =
{
   T0_NORMAL_MODE,
   T0_OC0_CLEAR,
   T0_PRESCALER_1024,
   //gu8_preloader,
   //(gu8_preloader + u16_duty_ticks),
   (T0_INTERRUPT_CMP|T0_INTERRUPT_NORMAL)   
};
*/


/* configuring timer 2 to be used as a counter within SwICU */
strTimerConfig_t gstrTimerConfig = 
{
   TIMER_2,
   T2_NORMAL_MODE,
   T2_OC2_CLEAR,
   T2_PRESCALER_1024,      
   //0,
   //0,
   //0,
   T2_INTERRUPT_NORMAL   
};


