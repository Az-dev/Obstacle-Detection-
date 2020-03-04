 /*-INCLUDES ------------------------------------------------------------------------------------------------------*/
#include "usart.h"
#include "../../interrupt.h"

/*- GLOBAL VARIALBLES ---------------------------------------------------------------------------------------------*/
volatile uint8_t ch  = 0;
/*- FUNCTION DEFINITIONS ------------------------------------------------------------------------------------------*/
/*
*  Description : Initializes USART.
*
*  @param const gstr_usart_init_t USART_InitCfg
*  @return EnumUSARTError_t
*/
EnumUSARTError_t Usart_Init(const gstr_usart_init_t * USART_InitCfg)
{
   /* Define error state */
   uint8_t au8_errrorState = 0;
   /* Check Null pointer */
   if(NULL != USART_InitCfg)
   {
      /*----------------- initializing (UCSRC) -----------------*/
      UCSRC |= (USART_InitCfg->usart_mode_sel|USART_InitCfg->stop_bit_sel|USART_InitCfg->reg_sel_mode|0x06); /*0x06 becuase we want UCSZ0:1 to be set to 1 1 ---> in order to obtain 8-bit width character*/
      //UCSRC |= 0x85; /*works fine*/
      /*----------------- initializing (UCSRB) -----------------*/
      UCSRB |= ((USART_InitCfg->interrupt_mode_sel | USART_InitCfg->usart_dir_sel) & (~(0x04)) & (~(0x03)));
      //UCSRB  |= 0xB8;
      /*----------------- initializing (UCSRA) -----------------*/
      //UCSRA &= ~(0x1C); /* Check that FE & DOR & PE is set to zero*/
      UCSRA |= (USART_InitCfg->double_speed_select & ~(0x1C));
      /*------------------ initialize baude rate ---------------*/
      UBRRL = BAUDE_RATE;
      /*------------------ Character size select  ---------------*/      
      /*---- setting it to 8-bit -----*/
      //UCSRC |= 0x05;
      //UCSRB &= ~(0x04); /* ----> check this if it will work or not */
      /*----- clear RXB8 and TXB8 ----*/
      //UCSRB &= ~(0x03);
      /* Report success */
      au8_errrorState = INIT_USART_CONFIG_OK; 
   }
   else
   {
      /* Report Fail */
      au8_errrorState = INVALID_USART_INPUT_PARAMS;
   }
   return au8_errrorState;   
}

/*
*  Description : Read a character from RXB.
*
*  @param volatile uint8_t * data_byte (output param)
*  @return EnumUSARTError_t
*/
EnumUSARTError_t UsartReadRx(volatile uint8_t * data_byte)
{
   /* Define error state */
   uint8_t au8_errorState = 0;
   /* Check Null pointer */
   if(NULL != data_byte)
   {
      *data_byte = UDR;      
      /* Report success*/
      au8_errorState = USART_BYTE_READ_SUCCESS;      
   }
   else
   {
      /* Report Fail */
      au8_errorState = INVALID_USART_INPUT_PARAMS;
   } 
   return au8_errorState;
}

/*
*  Description : Write a character to TXB
*
*  @param volatile uint8_t * data_byte  (input param)
*  @return EnumUSARTError_t
*/
EnumUSARTError_t UsartWriteTx(volatile uint8_t * data_byte)
{
   /* Define error state */
   uint8_t au8_errorState = 0;
   /* Check NULL pointer */
   if(NULL != data_byte)
   {
      /* Write value  to UDR */
      UDR = * data_byte;
      /* Report Success */
      au8_errorState = USART_BYTE_WRITE_SUCCESS;
   }
   else
   {
      /* Report Fail */
      au8_errorState = INVALID_USART_INPUT_PARAMS;     
   }
   return au8_errorState;  
}

/*
*  Description : Resets UDR .
*
*  @param void
*
*  @return EnumUSARTError_t
*/
EnumUSARTError_t ResetUDR(void)
{
   /* Define error state */
   uint8_t au8_errorState = 0;
   /*Reset UDR*/
   UDR = 0;
   /* Check for failure*/
   if(0 == UDR)
   {
      /* Report Success*/
      au8_errorState = UDR_RESET_SUCCESS;     
   }
   else
   {
      /* Report Fail */
      au8_errorState = UDR_RESET_FAIL; 
   }
   return au8_errorState;
}


/*--------------------------------------------------- Interrupt handlers  -----------------------------------------*/
/*
* USART on successful character receive completion interrupt handler 
*/
ISR_USART_RX()
{
   /* on successful character reception : you can read the new character */  
   UsartReadRx(&ch);
   /* Test Purpose */ 
   TCNT2 = UDR;  
}

/*
* USART when data register is empty
*/
ISR_USART_UDRE()
{
   /* if data register is empty : you can write a new character. */   
   UsartWriteTx(&ch);
   /* Reset UDER flag */
   UCSRA |= 0x20;
   /* Disable UDER */
   UCSRB &= ~(DATA_REGISTER_EMPTY_EN); 
   
            
}

ISR_USART_TX()
{
   /* if data register is empty : you can write a new character. */
   UsartWriteTx(&ch);   
}