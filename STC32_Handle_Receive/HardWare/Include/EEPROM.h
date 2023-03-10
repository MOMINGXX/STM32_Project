#ifndef	__EEPROM_H__
#define __EEPROM_H__

#include "I2C.h"

#define AT24C02_ADDR        0xAE
#define AT24C02_PageSize    8

void AT24C02_Byte_Write(uint8_t Write_Addr,uint8_t Byte);
void AT24C02_Page_Write(uint8_t Write_Addr,uint8_t *Byte,uint8_t Num);
void AT24C02_Buffer_Write(uint8_t Write_Addr,uint8_t *Byte,uint8_t Num);
uint8_t AT24C02_Random_Read(uint8_t Write_Addr);
void AT24C02_Sequential_Read(uint8_t Write_Addr,uint8_t *Byte,uint16_t Num);

#endif	/*__EEPROM_H__*/

