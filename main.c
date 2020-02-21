/*
 * CarProject.c
 *
 * Created: 2/17/2020 10:23:28 AM
 * Author : Az
 */ 
/*- INCLUDES -------------------------------------------------------------------------------------------------------------------*/
#include "Test/Test.h"
#include "APP/CarSM/CarSM.h"
/*- Main FUNCTION DEFINITION ---------------------------------------------------------------------------------------------------*/
int main(void)
{
   /* TimerTest(); ---> test passed*/
   /* DioTest();  ----> test passed */
   /* HwPwmTest(); ---> bypassed    */
   /* MotorTest(); ---> test passed and approved HwPWM */ 
   /* IcuTest();   ---> Finallly passed */
   //UsTest();
   //IcuWithUsTest(); /*--> Fully passed :xD */
   /*------------------- START CAR APPLICATION  ------------------------*/
   Car_SM_Init();
   Car_SM_Update();
   /*------------------- END CAR APPLICATION   ------------------------*/
    
}

