/*- INCLUDES ----------------------------------------------------------------------------------------------------------------------------------------*/
#include "Timer.h"


/*- GLOBAL VARIABLES --------------------------------------------------------------------------------------------------------------------------*/
/*---- Timers prescalers ----*/
volatile static uint8_t gu8_t0Prescaler   = 0;
volatile static uint16_t gu16_t1Prescaler = 0;
volatile static uint8_t gu8_t2Prescaler   = 0;

volatile uint32_t gu32_overflowTimes = 0;
volatile uint8_t gu8_excuteFlag = 0;  /* Initial condition '0' not to execute*/
/*- FUNCTIONS DEFINITIONS ----------------------------------------------------------------------------------------------------------------------------*/
/**
 * Description: Initiates timer module. 
 * 
 * @param   strTimerConfig_t*  Timer_cfg
 * 
 * @return 	ERROR_STATUS						
 */
ERROR_STATUS Timer_Init(strTimerConfig_t * Timer_cfg)
{
   /* Define error state */
   uint8_t au8_errorState = 0;
   /* Check Timer_cfg value*/
   if(Timer_cfg != NULL)
   {
      switch(Timer_cfg->u16_timer_ch)
      {
         case TIMER_0:
            /* Initializing timer0 working mode */
            TCCR0 |= (uint8_t)(Timer_cfg->u16_mode);
            /* Set Timer0 prescaler */
            gu8_t0Prescaler = (uint8_t)(Timer_cfg->u16_prescal);                                
         break;
         case TIMER_1:
            /* Initializing timer1 working mode */
            TCCR1 |= Timer_cfg->u16_mode;
            //TCCR1 |= 0xA000;  /*COM1A1/COM1B1 = 1 & COM1A0/COM1B0 = 0  -----> Clear OC1A/OC1B on compare match when up-counting. Set OC1A/OC1B on compare match when down counting.*/
            /* Set Timer1 prescaler */
            gu16_t1Prescaler = (Timer_cfg->u16_prescal);            
         break;
         case TIMER_2:
            /* Initializing timer2 working mode */
            TCCR2 |= (uint8_t)(Timer_cfg->u16_mode);
            /* Set Timer2 prescaler */
            gu8_t2Prescaler = (uint8_t)(Timer_cfg->u16_prescal);           
         break;        
      }
      /*-- Setting Interrupt Procedure --*/
      /* 1 - set Global interrupt bit*/
      sei();      
      /* 2 - set TOIE2 */
      TIMSK |= Timer_cfg->u16_interruptMask;
      /* Success */      
      au8_errorState = E_OK;
   }
   else
   {
      /* Return Fail */
      au8_errorState = E_NOK; 
   }
   
   return au8_errorState;  
}

/**
 * Description : This function starts the given timer. 
 * 	
 *	@param   uint8_t    Timer_CH_NO
 * @param   uint16_t   Timer_Count
 * 			
 * @return  ERROR_STATUS	
 */
ERROR_STATUS Timer_Start(uint8_t Timer_CH_NO, uint16_t Timer_Count)
{
   switch(Timer_CH_NO)
   {
      case TIMER_0:
         /* Initialize TCNT0 */
         TCNT0 = (uint8_t)Timer_Count;
         /* Sets the prescalar for timer0 */
         TCCR0 |= gu8_t0Prescaler;                 
      break;
      case TIMER_1:
         /* Initialize TCNT0 */
         TCNT1 = (uint8_t)Timer_Count;
         /* Sets the prescalar for timer1 */
         //TCCR1 |= en_mode;
         TCCR1B |= gu16_t1Prescaler;         
      break;
      case TIMER_2:
         /* Initialize TCNT0 */
         TCNT2 = (uint8_t)Timer_Count;
         /* Sets the prescalar for timer2 */
         TCCR2 |= gu8_t2Prescaler;         
      break;
   }
   return E_OK;
}

/**
 * Description: This function stops the given timer. 
 * 	
 * @param   uint8_t  Timer_CH_NO
 * 			
 * @return  ERROR_STATUS							
 */
ERROR_STATUS Timer_Stop(uint8_t Timer_CH_NO)
{
   switch(Timer_CH_NO)
   {
      case TIMER_0:
         TCCR0 &= T0_NO_CLOCK;         
      break;
      case TIMER_1:
         TCCR1B &= T1_NO_CLOCK;       
      break;
      case TIMER_2:
         TCCR2 &= T2_NO_CLOCK;     
      break;
   }
   return E_OK;
}

/**
 * Description: This function is used to set the value of timer counter for a timer. 
 * 	
 * @param   uint8_t     Timer_CH_NO
 * @param 	uint16_t *  Timer_value 	(I/O paramter)		
 * 
 * @return	ERROR_STATUS						
 */
ERROR_STATUS Timer_SetValue(uint8_t Timer_CH_NO, uint16_t Timer_value)
{
   switch(Timer_CH_NO)
   {
      case TIMER_0:
         TCNT0 = (uint8_t)Timer_value;         
      break;
      case TIMER_1:
         TCNT1 = Timer_value;
      break;
      case TIMER_2:
         TCNT2 = (uint8_t)Timer_value;
      break;      
   }
   return E_OK;
}

/**
 * Description: This function is used to return the value of timer counter for a timer. 
 * 	
 * @param   uint8_t     Timer_CH_NO
 * @param 	uint16_t *  Timer_value 	(I/O paramter)		
 * 
 * @return	ERROR_STATUS						
 */
ERROR_STATUS Timer_GetValue(uint8_t Timer_CH_NO, uint16_t* Timer_value)
{
   if(Timer_value != NULL)
   {
      switch(Timer_CH_NO)
      {
         case TIMER_0:
            *Timer_value = TCNT0;
         break;
         case TIMER_1:
            *Timer_value = TCNT1;
         break;
         case TIMER_2:
            *Timer_value = TCNT2;
         break;
      }
      return E_OK;
   }else{
      return E_NOK;
   }   
}

/**
 * Description: This function is used to return if the flag of the timer is raised or not.
 * 
 * @param   uint8_t   Timer_CH_NO
 * @param   uint8_t * Timer_status
 *			
 * @return ERROR_STATUS	 						
 */
ERROR_STATUS Timer_GetStatus(uint8_t Timer_CH_NO, uint8_t * Timer_status)
{
   if(Timer_status != NULL)
   {
      switch(Timer_CH_NO)
      {
         case TIMER_0:
            //(*Timer_status) = (uint8_t)BIT_IS_SET(TIFR,BIT0);            
         break;
         case TIMER_1:
            //(*Timer_status) = (uint8_t)BIT_IS_SET(TIFR,BIT2);
         break;
         case TIMER_2:
            //(*Timer_status) = (uint8_t)BIT_IS_SET(TIFR,BIT6);
         break;         
      }
      return E_OK;
   }
   else
   {
      return E_NOK;
   }
}

/************************************************ Timers ISRs Control **********************************************************/
ISR_TIMER0_OVF(){
   /*---- TMU Over Flow Procedure ----*/
   /* 1 - Increment Global over flow times counter --*/
   gu32_overflowTimes++;
   /* 2 - Rise execute flag */
   gu8_excuteFlag = 1;
   /* 3 - Reload TCNT ---*/   
   Timer_SetValue(TIMER_0 , (T0_OV_VAL - gu16_preloader));   
     
}

ISR_TIMER1_OVF(){
   /*---- TMU Over Flow Procedure ----*/
   /* 1 - Increment Global over flow times counter --*/
   gu32_overflowTimes++; 
   /* 2 - Rise execute flag */
   gu8_excuteFlag = 1; 
   /* 3 - Reload TCNT ---*/   
   Timer_SetValue(TIMER_1 , (T1_OV_VAL - gu16_preloader));     
}

ISR_TIMER2_OVF(){
   /*---- TMU Over Flow Procedure ----*/
   /* 1 - Increment Global over flow times counter --*/
   gu32_overflowTimes++;
   /* 2 - Rise execute flag or tick flag */
   gu8_excuteFlag = 1;
   /* 3 - Reload TCNT ---*/   
   Timer_SetValue(TIMER_2 , (T2_OV_VAL - gu16_preloader));   
     
}



ISR_TIMER0_COMP(){
   /*set pins*/
   //gpioPinWrite(GPIOD,(BIT4|BIT5),HIGH);
}

