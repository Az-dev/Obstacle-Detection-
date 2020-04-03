/*
 * Car_SOS.c
 *
 * Created: 4/1/2020 10:52:26 AM
 *  Author: Az
 */
 /*-INCLUDES ----------------------------------------------------------------------------------------------------------*/
 #include "Car_SOS.h"
 #include "../../SL/SOS/SOS.h"
 #include "../../SL/SOS/SOS_PB_Cfg.h"
 #include "../Steering/Steering.h"
 #include "../../ECUAL/Us/Us.h"
 #include "../../ECUAL/SwDelay/SwDelay.h" 
 #include "../../ECUAL/SwICU/SwICU_Cfg.h"
 #include "../../RTE/SharedResource/SharedResource.h"
 /*- GLOBALS ----------------------------------------------------------------------------------------------------------*/
 #define NO_OF_TRIALS 2 /* Say 2 for example*/ 
 uint8_t genm_sysState;              /* A variable that is used to store system state */
 uint8_t genm_recordErrorState;      /* A variable used to store system state at which the error_state occurred */
 uint8_t no_of_trials = NO_OF_TRIALS;
 uint8_t error_state = 0;
 /*- FUNCTION DEFINITIONS ---------------------------------------------------------------------------------------------*/
 /*--------------- System Tasks -------------*/
 /*
 *	Description: A task that is responsible for initializing System -excluding SOS_Init()-
 *
 *	@param void
 *
 *	@param void
 */
 static void InitTask(void)
 {
    /* check current state */
    if(INITIALIZE == genm_sysState)
    {

       /* 1 - Initialize Ultrasonic and SwICU ----*/
       uint8_t au8_UsInitErrorState = Us_Init();
       uint8_t au8_IcuInitErrorState = Icu_Init(&Icu_config);
       uint8_t au8_IcuConfEdgeErrorState = Icu_ConfigEdge(ICU_CH2,ICU_RISE_TO_FALL);       
       /* 2- Initialize Steering ----*/
       uint8_t au8_SteeringInitErrorState = Steering_Init();
       /* After this : Check Error_state returned by each function */
       if(( E_NOK != au8_UsInitErrorState ) && ( E_NOK != au8_IcuInitErrorState ) && ( E_NOK != au8_SteeringInitErrorState ) && ( E_NOK != au8_IcuConfEdgeErrorState ))
       {
          /* update System state machine to the next state */
          genm_sysState = TRIGGER_MEASUREMENT;          
       }
       else
       {
          /* Record the current error_state state */
          genm_recordErrorState = INITIALIZE;
          /* Go into a time out state to take a time out procedure */
          genm_sysState = TIME_OUT;
          /*NOte : we could add in the future a reporting mechanism for Error states variables*/
       }
    }
 }

 /*
 *	Description: A task that is responsible for triggering distance/InputCapture measurement process.
 *
 *	@param void
 *
 *	@param void
 */
 static void TriggerMeasurement(void)
 {
    /* check current state */
    if(TRIGGER_MEASUREMENT == genm_sysState)
    {
       /*-- Triggering Ultrasonic ---*/
       uint8_t au8_UsTriggerErrorState = Us_Trigger();
       /* After this : Check Error_state returned by each function */
       if(E_NOK != au8_UsTriggerErrorState)
       {
          /* update System state machine to the next state */
          genm_sysState = CALC_MEASUREMENT;          
       }
       else
       {
          /* Record the current error_state state */
          genm_recordErrorState = TRIGGER_MEASUREMENT;
          /* Go into a time out state to take a time out procedure */
          genm_sysState = TIME_OUT;
          /*NOte : we could add in the future a reporting mechanism for Error states variables*/
       }
    }
 }

 /*
 *	Description: A task that is responsible for calculating distance.
 *
 *	@param void
 *
 *	@param void
 */
 static void CalculateMeasurement(void)
 {
    /* check current state */
    if(CALC_MEASUREMENT == genm_sysState)
    {
       /* Trigger Measurement calculation */
       uint8_t au8_UsCalcErrorState = Us_CalcDistance();
       /* After this : Check Error_state returned by each function */
       if(E_NOK != au8_UsCalcErrorState)
       {
          /* update System state machine to the next state */
          genm_sysState = STEERING_ACTION;          
       }
       else
       {
          /* Record the current Error_state state */
          genm_recordErrorState = CALC_MEASUREMENT;
          /* Go into a time out state to take a time out procedure */
          genm_sysState = TIME_OUT;
          /*NOte : we could add in the future a reporting mechanism for Error states variables*/
       }
    }
 }

 /*
 *	Description: A task that is responsible for Initiating an steering action -speed & direction for the motors-.
 *
 *	@param void
 *
 *	@param void
 */
 static void SteeringAction(void)
 {
    /* check current state */
    if(STEERING_ACTION == genm_sysState)
    {
       static uint32_t su32_distance; 
       /*-- 1 - Get Distance Value --*/
       uint8_t au8_getDistErrorState = Get_DistanceVal(&su32_distance);
       /*-- 2 - Take a steering action based on the distance value and Distance Boundary values --*/
       uint8_t au8_SteeringErrorState = 0;       
       if(su32_distance < (uint32_t)DOWN_BOUNDARY_DISTANCE)
       {
          /* Move BackWard & Turn left */
          //Steering_SteerCar(CAR_FORWARD, 50);
          //softwareDelayMs(30);          
          au8_SteeringErrorState = Steering_SteerCar(CAR_LEFT, 40);
          //softwareDelayMs(7);          
       }
       else if((su32_distance >= (uint32_t)DOWN_BOUNDARY_DISTANCE) && (su32_distance <= (uint32_t)UP_BOUNDARY_DISTANCE))
       {
          /* Turn left */
          au8_SteeringErrorState = Steering_SteerCar(CAR_RIGHT, 50);
          //softwareDelayMs(5);          
       }
       else
       {
          /* Move Straight forward */
          au8_SteeringErrorState = Steering_SteerCar(CAR_BACKWARD, 35);
          //softwareDelayMs(10);          
       }

       /* After this : Check Error_state returned by each function */
       if((E_NOK != au8_SteeringErrorState) && (DISTANCE_GET_FAIL != au8_getDistErrorState))
       {
          /* update System state machine to the next state */
          genm_sysState = TRIGGER_MEASUREMENT;          
       }
       else
       {
          /* Record the current error_state state */
          genm_recordErrorState = STEERING_ACTION;
          /* Go into a time out state to take a time out procedure */
          genm_sysState = TIME_OUT;
          /*NOte : we could add in the future a reporting mechanism for Error states variables*/
       }
    }
 }

 /*
 *  Description : A task that is responsible taking a time out procedure for a stuck system task.
 *
 *  @param void
 *
 *  @return void
 */
static void TimeOut(void)
{
   if(genm_sysState == TIME_OUT && no_of_trials != 0)
   {
      /* retry procedure : By forcing the state again*/
      genm_sysState = genm_recordErrorState;
      /* Decrement no of trials */
      no_of_trials--;
       
   }
   else /* Time out trials is up , so reset */
   {
      /* Reinitialize number of trials */
      no_of_trials = NO_OF_TRIALS;
      /* Go into Reset state*/
      genm_sysState = RESET;
   }
}

/*
*  Description : A task that is responsible for executing the reset procedure of the system.
*
*  @param void 
*
*  @return void
*/
static void Reset(void)
{
   if(RESET == genm_sysState)
   {
      /* Reset system state*/
      genm_sysState = INITIALIZE;
      /* reset procedure whether firing watch dog or any mechanism of rest*/
   }
}

/*
*  Description : The main function on Car_SOS
*
*  @param void
*
*  @return void
*/
void Car_SOS(void)
{
   /* Initialize State */
   genm_sysState = INITIALIZE;
   /* Initialize SOS */
   SOS_Init(&gstrSOSConfig);
   /* Add system tasks */
   SOS_AddTask(1,InitTask,PERIODIC,0);         /* Debug Point : there is a bug when using ONESHOOT*/
   SOS_AddTask(1,TriggerMeasurement,PERIODIC,1);
   SOS_AddTask(13,CalculateMeasurement,PERIODIC,2);
   SOS_AddTask(1,SteeringAction,PERIODIC,3);
   SOS_AddTask(1,TimeOut,PERIODIC,4);
   SOS_AddTask(1,Reset,PERIODIC,5);
   /* Start SOS */
   SOS_TimerStart();
   while(1)
   {
      SOS_Dispatch();
   }
}