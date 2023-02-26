#ifndef	__EEPROM_H__
#define __EEPROM_H__

#include "stm32f10x.h"                  // Device header
#include "SOFT_SPI.h"
#include "USART.h"
#include "Delay.h"

#define GD25QX_PageSize                  256
#define GD25QX_PerWritePageSize          256

//GD25QX  √¸¡Ó
#define DUMMY                            0xFF
#define GD25QX_JEDEC_ID                  0x9F
#define GD25QX_WRITE_ENABLE              0x06
#define GD25QX_WRITE_DISABLE             0x04
#define GD25QX_READ_STATUS_REGISTER      0x05
#define GD25QX_READ_STATUS_REGISTER1     0x35
#define GD25QX_WRITE_STATUS_REGISTER     0x01
#define GD25QX_READ_DATA                 0x03
#define GD25QX_FAST_READ                 0x0B
#define GD25QX_PAGE_PROGRAM              0x02
#define GD25QX_BLOCK_ERASE			     0xD8 
#define GD25QX_SECTOR_ERASE              0x20
#define GD25QX_CHIP_ERASE		         0xC7 
#define GD25QX_ManufactDeviceID   	     0x90
#define GD25QX_POWER_DOWN                0xB9
#define GD25QX_RELEASE_POWER_DOWN        0xAB
#define GD25QX_DEVICE_ID                 0xAB
#define GD25QX_ENABLE_RESET              0x66
#define GD25QX_RESET                     0x99

void GD25Q16_Init();
void GD25Q16_RESET();
void GD25Q16_WAKE_UP(); 
void GD25Q16_Power_Down();
void GD25Q16_Write_ENABLE();
uint8_t GD25Q16_SendByte(uint8_t Byte); 
uint32_t GD25Q16_ReadID();
void GD25Q16_WaitForWrite();
void GD25Q16_Chip_Erase();
void GD25Q16_Sector_Erase(uint32_t Addr);
void GD25Q16_Read_Data(uint32_t Addr,uint8_t *Data,uint32_t Num);
void GD25Q16_Page_Program(uint32_t Addr,uint8_t *Data,uint32_t Num);
void GD25Q16_Buff_Write(uint32_t Addr,uint8_t *Data,uint32_t Num);

#endif	/*__EEPROM_H__*/

