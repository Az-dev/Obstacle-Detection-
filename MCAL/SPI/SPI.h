/*
 * SPI.h
 *
 * Created: 3/2/2020 2:46:49 PM
 *  Author: Az
 */ 


#ifndef SPI_H_
#define SPI_H_
/*- INCLUDES --------------------------------------------------------------------------------------------------------*/
#include "../../std_types.h"
/*- DEFINES ---------------------------------------------------------------------------------------------------------*/
/*--- 1 - SPCR (SPI Control Register) configuration ---*/
/* SPI Enable/Disable */
#define SPI_EN  0X40
#define SPI_DIS 0X00

/* SPI Interrupt Enable/Disable */
#define SPIE_EN   0x80
#define SPIE_DIS  0x00

/* SPI Data Order Select : if is set --> "LSB" is transmitted first , else "MSB" is transmitted first */
#define DORD_HIGH 0X20
#define DORD_LOW  0X00

/* SPI Master/Slave select */
#define MSTR_SEL 0x10
#define SLV_SEL  0x00

/* SPI (CPOL,CPHA) Mode Select */
#define CLK_POL_PHA_MODE_0 0x00
#define CLK_POL_PHA_MODE_1 0x04
#define CLK_POL_PHA_MODE_2 0x08
#define CLK_POL_PHA_MODE_3 0x0C

/* SPI (SCK) frequency select */
#define  Fosc_4   0x00
#define  Fosc_16  0x01
#define  Fosc_64  0x02
#define  Fosc_128 0x03   

/*--- 2 - SPSR (SPI Status Register) configuration ---*/
/* Enable/Disable 2x speed */
#define SPI_2X_EN    0x01
#define SPI_2X_DIS   0x00

/* Setting Interrupt flag */
#define SPIF_SET    0X80

/*- TYPEDEFS --------------------------------------------------------------------------------------------------------*/
/*--- SPI configuration struct ---*/
typedef struct str_SPI_Cfg
{
   uint8_t SPI_En;
   uint8_t SPI_INT_En;
   uint8_t SPI_Dord;
   uint8_t SPI_MS_Sel;
   uint8_t SPI_CK_mode;
   uint8_t SPI_freq_mode;
   uint8_t SPI_2X_En;  
}str_SPI_Cfg_t;
/*--- SPI Error Enum ----*/
typedef enum EnumSPIError
{
   INIT_CONFIG_OK = 0,
   INVALID_INPUT_PARAMS = 1,
   BYTE_WRITE_SUCCESS = 2,
   BYTE_WRITE_FAIL = 3,
   
}EnumSPIError_t; 

/*- FUNCITON PROTOTYPES --------------------------------------------------------------------------------------------*/
/*
*  Description : Initializes SPI module.
*
*  @param  str_SPI_Cfg_t * str_SpiCfg
*
*  @return EnumSPIError
*/
extern EnumSPIError_t SPI_Init(str_SPI_Cfg_t * str_SpiCfg);

/*
*  Description : Writes a Byte to SPDR (SPI Data Register).
*
*  @param  uint8_t * Data_byte
*
*  @return EnumSPIError
*/
extern EnumSPIError_t SPI_WriteByte(uint8_t * Data_byte);

/*
*  Description : Reads a Byte from SPDR (SPI Data Register).
*
*  @param  uint8_t * Data_byte
*
*  @return EnumSPIError
*/
extern EnumSPIError_t SPI_ReadByte(uint8_t * Data_byte);

#endif /* SPI_H_ */