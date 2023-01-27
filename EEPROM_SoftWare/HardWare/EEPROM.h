#ifndef	__EEPROM_H__
#define __EEPROM_H__

#include "stm32f10x.h"                  // Device header
#include "I2C.h"

#define EEPROM_ADDR         0xA0

void EEPROM_Init();
void EEPROM_Byte_Write(uint8_t Addr,uint8_t Byte);
void EEPROM_Page_Write(uint8_t Addr,uint8_t *Byte,uint8_t Num);
uint8_t EEPROM_Random_Read(uint8_t Addr);
void EEPROM_Sequential_Read(uint8_t Addr,uint8_t *Byte,uint8_t Num);

#endif	/*__EEPROM_H__*/

