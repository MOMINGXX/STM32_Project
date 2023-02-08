#ifndef	__EEPROM_H__
#define __EEPROM_H__

#include "stm32f10x.h"                  // Device header
#include "USART.h"
#include "Delay.h"

#define GD25QX_PageSize                  256
#define GD25QX_PerWritePageSize          256

//GD25QX  命令
#define DUMMY                            0x00
#define GD25QX_JEDEC_ID                  0x9F
#define GD25QX_WRITE_ENABLE              0x06
#define GD25QX_WRITE_DISABLE             0x04
#define GD25QX_READ_STATUS_REGISTER      0x05
#define GD25QX_READ_STATUS_REGISTER1     0x35
#define GD25QX_WRITE_STATUS_REGISTER     0x01
#define GD25QX_READ_DATA                 0x03
#define GD25QX_FAST_READ                 0x0B
#define GD25QX_PAGE_PROGRAM              0x02
#define GD25QX_BLOCK_ERASE1			     0x52       //32KB
#define GD25QX_BLOCK_ERASE2			     0xD8       //64KB
#define GD25QX_SECTOR_ERASE              0x20
#define GD25QX_CHIP_ERASE		         0xC7 
#define GD25QX_ManufactDeviceID   	     0x90
#define GD25QX_POWER_DOWN                0xB9
#define GD25QX_RELEASE_POWER_DOWN        0xAB
#define GD25QX_DEVICE_ID                 0xAB
#define GD25QX_ENABLE_RESET              0x66
#define GD25QX_RESET                     0x99

		
//SPI   
#define GD25Q16_SPI                      SPI1
#define GD25Q16_SPI_CLK                  RCC_APB2Periph_SPI1
#define GD25Q16_SPI_APBxCLKCMD           RCC_APB2PeriphClockCmd

//SPI GPIO
#define GD25Q16_SPI_GPIO_CLK             RCC_APB2Periph_GPIOA
#define GD25Q16_SPI_GPIO_APBxCLKCMD      RCC_APB2PeriphClockCmd
		
#define GD25Q16_SPI_CS_GPIO_PIN          GPIO_Pin_4
#define GD25Q16_SPI_CS_GPIO_PORT         GPIOA
		
#define GD25Q16_SPI_SCK_GPIO_PIN         GPIO_Pin_5
#define GD25Q16_SPI_SCK_GPIO_PORT        GPIOA
	
#define GD25Q16_SPI_MISO_GPIO_PIN        GPIO_Pin_6
#define GD25Q16_SPI_MISO_GPIO_PORT       GPIOA
		
#define GD25Q16_SPI_MOSI_GPIO_PIN        GPIO_Pin_7
#define GD25Q16_SPI_MOSI_GPIO_PORT       GPIOA

/*等待超时时间*/
#define SPIT_FLAG_TIMEOUT                ((uint32_t)0x1000)
#define SPIT_LONG_TIMEOUT                ((uint32_t)(10 * SPIT_FLAG_TIMEOUT))

//#define W25QX_ERROR(fmt,arg...)          printf("W25QX_ERROR:>"fmt"\n",##arg)
#define W25QX_ERROR(n)         			  printf("W25QX_ERRO: 等待超时! ERROR_CODE:> "#n"\n")
		
#define GD25Q16_SPI_CS(x)        		  GPIO_WriteBit(GD25Q16_SPI_CS_GPIO_PORT ,GD25Q16_SPI_CS_GPIO_PIN,(BitAction)(x))
//#define GD25Q16_SPI_CSLOW				  GPIO_ResetBits(GD25Q16_SPI_CS_GPIO_PORT ,GD25Q16_SPI_CS_GPIO_PIN )
//#define GD25Q16_SPI_CSHIGH				GPIO_SetBits(GD25Q16_SPI_CS_GPIO_PORT ,GD25Q16_SPI_CS_GPIO_PIN)

void GD25Q16_Init();
uint32_t GD25Q16_Read_JEDEC_ID();
uint8_t GD25Q16_Read_Device_ID();
uint16_t GD25Q16_Read_Manufacture_ID();

void GD25Q16_Chip_Erase();
void GD25Q16_Sector_Erase(uint32_t Addr);
void GD25Q16_Block_Erase(uint32_t Addr);

uint8_t GD25Q16_Send_Byte(uint8_t Byte);
void GD25Q16_Read_Data(uint32_t Addr,uint8_t *Data,uint32_t Num);
void GD25Q16_Page_Program(uint32_t Addr,uint8_t *Data,uint32_t Num);
void GD25Q16_Buff_Write(uint32_t Addr,uint8_t *Data,uint32_t Num);

void GD25Q16_Power_Down();

#endif	/*__EEPROM_H__*/

