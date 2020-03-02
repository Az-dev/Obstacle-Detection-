/*
 * SPI.c
 *
 * Created: 3/2/2020 2:46:36 PM
 *  Author: Az
 */ 
/*- INCLUDES -------------------------------------------------------------------------------------------------------*/
#include "SPI.h"
#include "../../interrupt.h"
#include "../../registers.h"
/*- GLOBAL VARIABLES ----------------------------------------------------------------------------------------------*/
static volatile uint8_t gu8_transmissionComplete = 0; /* 0 : not ready to read*/
static uint8_t gu8_firstWriteOperation = 1;           /* initialized to 1 to refer to the first write operation */
static volatile uint8_t gu8_writeOperationLock = 1;   /* initialized to 1 : to lock write operation */
/*- FUNCTION DEFINITIONS ------------------------------------------------------------------------------------------*/
/*
*  Description : Initializes SPI module.
*
*  @param  str_SPI_Cfg_t * str_SpiCfg
*
*  @return EnumSPIError
*/
EnumSPIError_t SPI_Init(str_SPI_Cfg_t * str_SpiCfg)
{
   /* Define error status*/
   uint8_t au8_errorState = 0;
   if(NULL != str_SpiCfg)
   {
      /*---- Configuring (SPCR) ----*/
      SPCR |= (str_SpiCfg->SPI_En|str_SpiCfg->SPI_INT_En|str_SpiCfg->SPI_MS_Sel|str_SpiCfg->SPI_freq_mode|str_SpiCfg->SPI_CK_mode|str_SpiCfg->SPI_Dord);
      /*---- Configuring (SPSR) ----*/
      SPSR |= (str_SpiCfg->SPI_2X_En);
      /*---- report success ----*/
      au8_errorState = INIT_CONFIG_OK;      
   }else{
      /*---- report Fail----*/
      au8_errorState = INVALID_INPUT_PARAMS;
   }
   /*---- Return Error State ----*/
   return au8_errorState;      
}

/*
*  Description : Writes a Byte to SPDR (SPI Data Register).
*
*  @param  uint8_t * Data_byte
*
*  @return EnumSPIError
*/
EnumSPIError_t SPI_WriteByte(uint8_t * Data_byte)
{
   /* Define error state*/
   uint8_t au8_errorState = 0;  
   if(NULL != Data_byte)
   {
      /* Check if this is the first write operation or not*/
      if(gu8_firstWriteOperation == 1)
      {
         /* Write Data */
         SPDR = *Data_byte;
         /* Reset first write operation flag */
         gu8_firstWriteOperation = 0;         
         /* Report success */
         au8_errorState = BYTE_WRITE_SUCCESS;
      }
      else
      {
         /* this is not the first write operation : then check gu8_writeOperationLock flag before writing again */
         if(gu8_writeOperationLock == 0)
         {
            /* Write Data */
            SPDR = *Data_byte;
            /* Lock write again*/
            gu8_writeOperationLock = 1;               
            /* Report success */
            au8_errorState = BYTE_WRITE_SUCCESS;            
         }
         else
         {
            /* Report fail */
            au8_errorState = BYTE_WRITE_FAIL;
            
         }
         
      }      
   }
   else
   {
      /* Report fail */
      au8_errorState = INVALID_INPUT_PARAMS;
   }
   /* Return au8_errorState */
   return au8_errorState;
}

/*
*  Description : Reads a Byte from SPDR (SPI Data Register).
*
*  @param  uint8_t * Data_byte
*
*  @return EnumSPIError
*/
EnumSPIError_t SPI_ReadByte(uint8_t * Data_byte)
{
   /* Define error state*/
   uint8_t au8_errorState = 0;
   if(NULL != Data_byte)
   {
      if(gu8_transmissionComplete == 1)
      {
         /* Read Data from SPDR*/
         *Data_byte = SPDR;
         /* Unlock write operation */
         gu8_writeOperationLock = 0;
         /* reset gu8_transmissionComplete flag*/
         gu8_transmissionComplete = 0;
      }      
      /* Report success */
      au8_errorState = BYTE_WRITE_SUCCESS;
      }else{
      /* Report fail */
      au8_errorState = INVALID_INPUT_PARAMS;
   }
   /* Return au8_errorState */
   return au8_errorState;
}

/*--------------------------------------------- ISR CONTROL ------------------------------------------------------*/
ISR_SPI()
{
   /*--- Rise Transmission complete Flag ---*/
   gu8_transmissionComplete = 1;   
}
