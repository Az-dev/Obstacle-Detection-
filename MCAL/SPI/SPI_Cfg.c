/*
 * SPI_Cfg.c
 *
 * Created: 3/2/2020 2:47:40 PM
 *  Author: Az
 */ 
/*- INCLUDES ------------------------------------------------------------------------------------------------------*/
#include "SPI.h"
/*- STRUCTS ------------------------------------------------------------------------------------------------------*/
/*--- SPI configuration struct (Master) Interrupt-mode ---*/
str_SPI_Cfg_t gstr_MasterCfg = 
{
   SPI_EN,
   SPIE_EN,
   DORD_HIGH,
   MSTR_SEL,
   CLK_POL_PHA_MODE_0,
   Fosc_128,
   SPI_2X_DIS
};

/*--- SPI configuration struct (Slave) Interrupt-mode ---*/
str_SPI_Cfg_t gstr_SlaveCfg =
{
   SPI_EN,
   SPIE_EN,
   DORD_HIGH,
   SLV_SEL,
   CLK_POL_PHA_MODE_0,
   Fosc_128,
   SPI_2X_DIS
};
