/*
 * TMU.c
 *
 * Created: 2/24/2020 4:14:52 PM
 *  Author: Az
 */ 
/*- INCLUDES -------------------------------------------------------------------------------------------------------*/
#include "../../MCAL/Timer/Timer.h"
#include "../../MCAL/Timer/Timer_Cfg.h"
#include "TMU.h"
/*- GLOBAL VARIABLES -----------------------------------------------------------------------------------------------*/
static strTask_t garrTaskTMUBuffer[TMU_BUFFER_SIZE];  
static sint16_t gindex = TMU_BUFFER_SIZE;
volatile uint16_t gu16_preloader = 0;    /* this variable is (volatile,not static) as it must be shown to TIMER's ISR*/
/*- FUNCITONS DEFINITIONS ------------------------------------------------------------------------------------------*/
/*
*  Description : Initializes the given timer channel with the given resolution.
*
*  @param  const strTMU_Cfg_t *  strTMU_Init
*
*  @return EnmTMUError_t
*/
EnmTMUError_t TMU_Init(const strTMU_Cfg_t * strTMU_Init)
{
   /* Define Error state */
   uint8_t au8_errorState;
   /* Check pointer value */ 
   if(NULL != strTMU_Init)
   {
      /* Initializes the given timer */
      switch(strTMU_Init->timer_channel)
      {
         case TIMER_0:
            /* Initialize timer0 */
            Timer_Init(&gstrTimer0TmuConfig);
            /* Calculate the value to be set to the timer according to the prescaler set in configuration */
            switch(gstrTimer0TmuConfig.u16_prescal)
            {
               case T0_PRESCALER_64:;
                  /* not used currently*/
               break;
               case T0_PRESCALER_256:;
                  /* not used currently*/
               break;
               case T0_PRESCALER_1024:
                  gu16_preloader = (uint16_t)(((double)INVERSE_TICK_TIME_PRESCALE_1024 / MILLI_SECONDS) * strTMU_Init->resolution);
                  Timer_SetValue(TIMER_0 , (T0_OV_VAL - gu16_preloader));
               break;               
            }            
         break;
         case TIMER_1:
            /*Initialize timer1*/
            Timer_Init(&gstrTimer1TmuConfig);
            /* Calculate the value to be set to the timer according to the prescaler set in configuration */
            switch(gstrTimer1TmuConfig.u16_prescal)
            {
               case T1_PRESCALER_64:;
                  /* not used currently*/
               break;
               case T1_PRESCALER_256:;
                  /* not used currently*/
               break;
               case T1_PRESCALER_1024:
                  gu16_preloader = (uint16_t)(((double)INVERSE_TICK_TIME_PRESCALE_1024 / MILLI_SECONDS) * strTMU_Init->resolution);
                  Timer_SetValue(TIMER_1 , (T1_OV_VAL - gu16_preloader));
               break;
            }
         break;
         case TIMER_2:
            /*Initialize timer2*/
            Timer_Init(&gstrTimer2TmuConfig);
            /* Calculate the value to be set to the timer according to the prescaler set in configuration */
            switch(gstrTimer2TmuConfig.u16_prescal)
            {
               case T2_PRESCALER_64:;
                  /* not used currently*/
               break;
               case T2_PRESCALER_256:;
                  /* not used currently*/
               break;
               case T2_PRESCALER_1024:
                  gu16_preloader = (uint16_t)(((double)INVERSE_TICK_TIME_PRESCALE_1024 / MILLI_SECONDS) * strTMU_Init->resolution);
                  Timer_SetValue(TIMER_2 , (T2_OV_VAL - gu16_preloader));
               break;
            }
         break;
      }
      au8_errorState = INIT_OK;      
   }else{
      au8_errorState = INIT_NOK;
   }   
   /* Return error state */
   return au8_errorState;
}


/*
*
*
*
*/
EnmTMUError_t TMU_DeInit();

/*
*
*
*
*/
EnmTMUError_t TMU_Dispatch()
{
   /* Check if the buffer not empty */
   if(0 < gindex)
   {
      uint16_t au16_iter = (uint16_t)gindex;
      /* Search for the Task of the given function within TMU buffer*/
      for(;au16_iter >= 0; au16_iter--)
      {
           
      }      
   }else{
      /* return error code array is empty */;
   }   
}

/*
*  Description : Adds a Task instance to TMU tasks Buffer.
*
*  @param uint16_t duration
*  @param void (* fn)(void)
*  uint8_t work_mode                //States whether the task to be add will be PERIODIC or ONESHOOT
*
*  @param EnmTMUError_t
*/
EnmTMUError_t TMU_Start_Timer(uint16_t duration , void (* fn)(void) , uint8_t work_mode)
{
   /*---- Enable Interrupt ----*/
   /*---- Add Task to TMU Buffer ----*/
   if(0 <= gindex)
   {
      /* Create a new task */
      strTask_t austr_Task = 
      {
         fn,         
         duration,
         //uint8_t ready_flag;
         work_mode
      };      
      /* Append the task to TMU buffer */
      garrTaskTMUBuffer[TMU_BUFFER_SIZE - gindex] = austr_Task;      
      /* Decrement gindex */
      gindex--;
   }else{
      /* return error code buffer is full*/
   }
}

/*
*  Description : Removes a task form TMU queue.
*
*  @param @param void (* call_back)(void)
*
*  @return EnmTMUError_t
*/
EnmTMUError_t TMU_Stop_Timer(void (* call_back)(void))
{
   /* Check if the buffer not empty */
   if(0 < gindex)
   {
      uint16_t au16_iter = (uint16_t)gindex;
      /* Search for the Task of the given function within TMU buffer*/
      for(;au16_iter >= 0; au16_iter--)
      {
         if(garrTaskTMUBuffer[au16_iter].fn == call_back)
         {
            /* Then remove the Task */
            garrTaskTMUBuffer[au16_iter] = garrTaskTMUBuffer[au16_iter];
            /* Increment the size */
            au16_iter++;           
         }           
      }      
   }else{
      /* return error code array is empty */
   }
}
