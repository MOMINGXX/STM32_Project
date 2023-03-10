#ifndef __MP3_TF_16P_H__
#define __MP3_TF_16P_H__

#include "USART.h"

#define Next_Song  					0x01
#define Last_Song  					0x02
#define Specify_Music  				0x03		//指定曲目 1-2999 
#define Add_Volume 					0x04
#define Reduce_Volume 				0x05
#define Specify_Volume  			0x06		//音量  0-30
#define Specify 					0x07		//指定	EQ0/1/2/3/4/5
#define Ring_Specify_play 			0x08		//环指定曲目播放
#define Specify_play  				0x09		//指定播放 1/2/3/4/5(U/SD/AUX/SLEEP/FLASH)
#define Sleep  						0x0A		//睡眠
#define Module_Reset  				0x0C		//模块复位
#define Play  						0x0D
#define Suspended  					0x0E		//暂停
#define Specify_Folder 		    	0x0F		//指定文件夹  1-10(需要自己设定) 
#define Full_Loop 					0x11		//全部循环播放	[1:循环播放][0:停止循环播放] 
#define Designated_MP3_Folder  		0x12		//指定MP3文件夹	0--9999 
#define Call_Waiting  				0x13		//插播广告		0--9999 
#define Designated_15Folder  		0x14		//支持15文件夹
#define Stop_Slots  				0x15		//停止插播，播放背景
#define Stop_Song  					0x16		//指定文件夹循环播放 
#define Specify_Folder_play 		0x17		//指定文件夹循环播放
#define Random_Broadcast 			0x18		//随机播放
#define Loop 						0x19		//循环播放 
#define Start_Close_DAC  			0x1A		//开启和关闭 DAC

void Uart_SendCMD(uint8_t CMD ,uint8_t feedback ,uint16_t dat);
void Uart_SendFolder(uint8_t CMD,uint8_t feedback,uint8_t Folder,uint8_t dat);

#endif 
