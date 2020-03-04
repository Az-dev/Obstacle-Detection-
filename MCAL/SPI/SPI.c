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
volatile uint8_t gu8_transmissionComplete = 0;
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
      SPCR |= (str_SpiCfg->SPI_En|str_SpiCfg->SPI_INT_En|str_SpiCfg->SPI_MS_Sel|str_SpiCfg->SPI_CK_mode|str_SpiCfg->SPI_freq_mode|str_SpiCfg->SPI_Dord);
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
*  @param  uint8_t * Data_byte  (input param)
*
*  @return EnumSPIError
*/
EnumSPIError_t SPI_WriteByte(uint8_t *Data_byte)
{
   /* Define error state*/
   uint8_t au8_errorState = 0;  
   if(NULL != Data_byte)
   {
      /* Write Data */
      SPDR = *Data_byte;
      /* Report success */
      au8_errorState = BYTE_WRITE_SUCCESS;     
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
*  @param  uint8_t * Data_byte (output param)
*
*  @return EnumSPIError
*/
EnumSPIError_t SPI_ReadByte(uint8_t *Data_byte)
{
   /* Define error state*/
   uint8_t au8_errorState = 0;
   if(NULL != Data_byte)
   {
      /* Read Data from SPDR*/
      *Data_byte = SPDR;        
      /* Report success */
      au8_errorState = BYTE_WRITE_SUCCESS;
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
*  Description : Returns status of Transmission complete software flag
*
*  @param void
*  @return EnumSPIError_t
*/
EnumSPIError_t SPI_GetTransmissionStatus(void)
{
   /* Define error state */
   uint8_t au8_errorState = 0;
   /* Check transmission status flag */
   if(gu8_transmissionComplete == 1)
   {
      /* Report transmission success */
      au8_errorState = SPI_TRANSMISSION_SUCCESS;
      /* Reset Transmission Flag */
      gu8_transmissionComplete = 0;
   }
   else
   {
      /* Report transmission fail */
      au8_errorState = SPI_TRANSMISSION_FAIL;      
   }
   return au8_errorState;
}

/*--------------------------------------------- ISR CONTROL ------------------------------------------------------*/
ISR_SPI()
{ 
   /* Raise transmission complete flag */
   gu8_transmissionComplete = 1;
}
