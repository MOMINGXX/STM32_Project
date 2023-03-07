#ifndef __NRF24L01_H__
#define __NRF24L01_H__

#include "stm32f10x.h"                  // Device header
#include "SOFT_SPI.h"
#include "USART.h"
#include "Delay.h"

/* 这两个数据要完全一致才能够通信 */
#define NRF24L01_TX_ADR_WIDTH 	   5  	//发射地址宽度
#define NRF24L01_TX_PLOAD_WIDTH    20   //发射数据通道有效数据宽度0~32Byte 

#define NRF24L01_RX_ADR_WIDTH      5
#define NRF24L01_RX_PLOAD_WIDTH    20

#define NRF24L01_CHANAL            25	//频道选择 

#define NRF24L01_R_REGISTER        0x00    // 读寄存器。5位存储器映射地址
#define NRF24L01_W_REGISTER        0x20    // 写寄存器。5位存储器映射地址，仅可在断电或待机模式下执行
#define NRF24L01_R_RX_PAYLOAD      0x61    // 读取RX负载。1-32个字节。读操作将始终从字节0开始。有效载荷将在读取后从FIFO中删除。 用于RX模式
#define NRF24L01_W_TX_PAYLOAD      0xA0    // 写入TX负载。1-32字节。写操作始终从字节0开始。用于TX模式
#define NRF24L01_FLUSH_TX          0xE1    // 刷新TX FIFO，用于TX模式
#define NRF24L01_FLUSH_RX          0xE2    // 刷新RX FIFO，用于RX模式，在传输确认期间不应执行（确认包不会完成）。
#define NRF24L01_REUSE_TX_PL       0xE3    // 用于PTX设备。重用最后发送的有效负载。 只要CE为高，就会重复发送数据包。在执行W_TX_PAYLOAD或FLUSH TX之前，TX有效负载重用处于活动状态。 在包传输期间，不得激活或停用TX有效载荷重用
#define NOP                        0xFF    // 没有操作。 可能用于读取STATUS寄存器

#define NRF24L01_CONFIG            0x00    // 配置寄存器
#define NRF24L01_EN_AA             0x01    // 启用“自动确认”功能，禁用此功能以与nRF2401兼容
#define NRF24L01_EN_RXADDR         0x02    // 启用RX地址
#define NRF24L01_SETUP_AW          0x03    // 地址宽度的设置（所有数据管道通用）
#define NRF24L01_SETUP_RETR        0x04    // 自动重传的设置
#define NRF24L01_RF_CH             0x05    // 射频频道
#define NRF24L01_RF_SETUP          0x06    // 射频设置寄存器
#define NRF24L01_STATUS            0x07    // 状态寄存器（与MOSI引脚上施加的SPI指令字并行，STATUS寄存器在MISO引脚上串行移出）
#define NRF24L01_OBSERVE_TX        0x08    // 传输观察寄存器
#define NRF24L01_CD                0x09    // 载波检测
#define NRF24L01_RX_ADDR_P0        0x0A    // 接收地址数据管道0。最大长度为5个字节。
#define NRF24L01_RX_ADDR_P1        0x0B    // 接收地址数据管道1。最大长度为5个字节。
#define NRF24L01_RX_ADDR_P2        0x0C    // 接收地址数据管道2。只有最低字节可以设置，高位字节等于RX_ADDR_P1[39:8]
#define NRF24L01_RX_ADDR_P3        0x0D    // 接收地址数据管道3。只有最低字节可以设置，高位字节等于RX_ADDR_P1[39:8]
#define NRF24L01_RX_ADDR_P4        0x0E    // 接收地址数据管道4。只有最低字节可以设置，高位字节等于RX_ADDR_P1[39:8]
#define NRF24L01_RX_ADDR_P5        0x0F    // 接收地址数据管道5。只有最低字节可以设置，高位字节等于RX_ADDR_P1[39:8]
#define NRF24L01_TX_ADDR           0x10    // 发送地址。仅用于PTX设备。如果这是启用了增强型ShockBurstTM的PTX设备，则将RX_ADDR_P0设置为等于此地址以处理自动确认。
#define NRF24L01_RX_PW_P0          0x11    // 数据管道0中的RX有效负载中的字节数（1到32个字节）
#define NRF24L01_RX_PW_P1          0x12    // 数据管道1中的RX有效负载中的字节数（1到32个字节）
#define NRF24L01_RX_PW_P2          0x13    // 数据管道2中的RX有效负载中的字节数（1到32个字节）
#define NRF24L01_RX_PW_P3          0x14    // 数据管道3中的RX有效负载中的字节数（1到32个字节）
#define NRF24L01_RX_PW_P4          0x15    // 数据管道4中的RX有效负载中的字节数（1到32个字节）
#define NRF24L01_RX_PW_P5          0x16    // 数据管道1中的RX有效负载中的字节数（1到32个字节）
#define NRF24L01_FIFO_STATUS       0x17    // FIFO状态寄存器
#define NRF24L01_MAX_RT            0x10    //达到最大重发次数中断标志位
#define NRF24L01_TX_DS		       0x20    //发送完成中断标志位	  
#define NRF24L01_RX_DR		       0x40    //接收到数据中断标志位

//SPI
#define NRF24L01_SPIx                       SPI2
#define NRF24L01_SPIx_CLK                   RCC_APB1Periph_SPI2
#define NRF24L01_SPIx_APBxClockCMD          RCC_APB1PeriphClockCmd

//GPIO
#define NRF24L01_GPIO_CLK                   RCC_APB2Periph_GPIOB
#define NRF24L01_GPIO_APBxClockCMD          RCC_APB2PeriphClockCmd

#define NRF24L01_GPIO_PORT                  GPIOB
#define NRF24L01_CE_GPIO_PIN                GPIO_Pin_6
#define NRF24L01_IRQ_GPIO_PIN               GPIO_Pin_8
//#define NRF24L01_CSN_GPIO_PIN               GPIO_Pin_12
//#define NRF24L01_SCK_GPIO_PIN               GPIO_Pin_13
//#define NRF24L01_MISO_GPIO_PIN              GPIO_Pin_14
//#define NRF24L01_MOSI_GPIO_PIN              GPIO_Pin_15

/* extern uint8_t NRF24L01_RX_BUF[NRF24L01_RX_PLOAD_WIDTH];		//接收数据缓存
extern uint8_t NRF24L01_TX_BUF[NRF24L01_TX_PLOAD_WIDTH];		//发射数据缓存 */

void NRF24L01_Init(void);  // GPIO初始化
void NRF24L01_RX_Mode();
void NRF24L01_TX_Mode();
uint8_t NRF24L01_Check();
uint8_t NRF24L01_TxPacket(uint8_t *TxBuff);
uint8_t NRF24L01_RxPacket(uint8_t *RxBuff);
void NRF24L01_Check_detection();

#endif

