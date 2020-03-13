/*
 * CarProject.c
 *
 * Created: 2/17/2020 10:23:28 AM
 * Author : Az
 */ 
/*- INCLUDES -------------------------------------------------------------------------------------------------------------------*/
#include "Test/Test.h"
#include "APP/CarSM/CarSM.h"
#include "APP/BCM_BasedApp/BCM_Based.h"
/*- Main FUNCTION DEFINITION ---------------------------------------------------------------------------------------------------*/
int main(void)
{
   /*------------------- START TMU APPLICATION  ------------------------*/
   //TmuTest();
   /*------------------- END TMU APPLICATION   ------------------------*/   
   
   /*------------------- START CAR APPLICATION  ------------------------*/
   //Car_SM_Init();
   //Car_SM_Update();
   /*------------------- END CAR APPLICATION   ------------------------*/
    
   /*---------------------- Start test ----------------------------*/
   //TimerTest(); /* ---> test passed*/
   /* DioTest();  ----> test passed */
   /* HwPwmTest(); ---> bypassed    */
   /* MotorTest(); ---> test passed and approved HwPWM */
   /* IcuTest();   ---> Finallly passed */
   //UsTest();
   //IcuWithUsTest(); /*--> Fully passed :xD */
   //masterSpi();  //---->success
   //slaveSpi();  //-----> success
   //myUsartFullDuplexInterruptTest(); // ----> test passed for both transmission and reciption
   /*---------------------- End test ------------------------------*/   
   
   /*--------------------- Start BCM test -----------------------------*/
   //BCM_Transmit();  /* Burn its hex on master */
   //BCM_Receive();   /* Burn its hex on slave */
   /*--------------------- End BCM test -------------------------------*/
   
   
       
}

