/*
 * SOS.h
 *
 * Created: 2/24/2020 4:15:10 PM
 *  Author: Az
 */ 


#ifndef SOS_H_
#define SOS_H_
/*- INCLUDES ------------------------------------------------------------------------------------------------------*/
#include "../../std_types.h"
#include "SOS_PREB_Cfg.h"
/*- DEFINES -------------------------------------------------------------------------------------------------------*/
#define PERIODIC 0
#define ONESHOOT 1

/*---- TIMER CHANNEL ----*/
#define  TIMER_0  0
#define  TIMER_1  1
#define  TIMER_2  2
/*- TYPEDEFS ------------------------------------------------------------------------------------------------------*/
/*------- Error Enum -------*/
typedef enum EnmSOSError
{
   INIT_OK  = 0,
   INIT_NOK = 1,
   BUFFER_FULL = 3,
   BUFFER_EMPTY = 4,
   INVALID_TASK_PARAM = 5,   
}EnmSOSError_t;
/*------- Task Struct ------*/
typedef struct strTask
{
   void (* fn)(void) ;
   uint16_t counter;       /* represents the time interval after which task must be executed */
   uint16_t priority; 
   uint8_t work_mode;
   uint16_t tick_counts;  /* Internal tick counter for a task */
}strTask_t;

/*------- configuration Struct -----*/ 
typedef struct strSOS_Cfg
{
   uint8_t timer_channel; 
   uint16_t resolution;
}strSOS_Cfg_t;

/*- FUNCIONS PROTOYPES --------------------------------------------------------------------------------------------*/
/*
*  Description : Initialized the given timer channel with the given resolution.   
*  
*  @param const strSOS_Cfg_t *  strSOS_Init
*
*  @return EnmSOSError_t
*/
extern EnmSOSError_t SOS_Init(const strSOS_Cfg_t * strSOS_Init);

/*
*
*
*
*/
extern EnmSOSError_t SOS_DeInit();

/*
*  Description : Iterate on the tasks to decide on the task to be executed.
*
*  @param void
*
*  @return EnmSOSError_t
*/
extern EnmSOSError_t SOS_Dispatch(void);

/*
*  Description : Adds a Task instance to SOS tasks Buffer.
*
*  @param uint16_t duration
*  @param void (* task_fn)(void)                // A function-pointer to task function
*  @param uint8_t work_mode                //States whether the task to be add will be PERIODIC or ONESHOOT
*  @param uint16_t priority
*
*  @return EnmSOSError_t
*/
extern EnmSOSError_t SOS_Start_Timer(uint16_t duration , void (* task_fn)(void)  , uint8_t work_mode ,uint16_t priority);

/*
*  Description : Removes a task form SOS queue.
*
*  @param void (* task_fn)(void)
*
*  @return EnmSOSError_t
*/
extern EnmSOSError_t SOS_Stop_Timer(void (* task_fn)(void));

#endif /* SOS_H_ */