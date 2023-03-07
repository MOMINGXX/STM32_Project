#ifndef __MPU6050_H__
#define __MPU6050_H__

#include "stm32f10x.h"                  // Device header
#include "USER_I2C.h"
#include "NRF24L01.h"
#include "LED.h"
#include "nmswj.h"
#include "math.h"

#define MPU6050_ADDR    		0xD0
#define	MPU6050_SMPLRT_DIV		0x19	//陀螺仪采样率，典型值：0x07(125Hz)
#define	MPU6050_CONFIG			0x1A	//低通滤波频率，典型值：0x06(5Hz)
#define	MPU6050_GYRO_CONFIG		0x1B	//陀螺仪自检及测量范围，典型值：0x18(不自检，2000deg/s)
#define	MPU6050_ACCEL_CONFIG	0x1C	//加速计自检、测量范围及高通滤波频率，典型值：0x01(不自检，2G，5Hz)
#define	MPU6050_ACCEL_XOUT_H	0x3B
#define	MPU6050_ACCEL_XOUT_L	0x3C
#define	MPU6050_ACCEL_YOUT_H	0x3D
#define	MPU6050_ACCEL_YOUT_L	0x3E
#define	MPU6050_ACCEL_ZOUT_H	0x3F
#define	MPU6050_ACCEL_ZOUT_L	0x40
#define	MPU6050_TEMP_OUT_H		0x41
#define	MPU6050_TEMP_OUT_L		0x42
#define	MPU6050_GYRO_XOUT_H		0x43
#define	MPU6050_GYRO_XOUT_L		0x44	
#define	MPU6050_GYRO_YOUT_H		0x45
#define	MPU6050_GYRO_YOUT_L		0x46
#define	MPU6050_GYRO_ZOUT_H		0x47
#define	MPU6050_GYRO_ZOUT_L		0x48
#define	MPU6050_TMP_H	        0x1B
#define	MPU6050_TMP_L	        0x1C
#define	MPU6050_PWR_MGMT_1		0x6B	//电源管理，典型值：0x00(正常启用)
#define	MPU6050_PWR_MGMT_2		0x6C	//电源管理，典型值：0x00(正常启用)
#define	MPU6050_WHO_AM_I		0x75	//IIC地址寄存器(默认数值0x68，只读)

typedef struct 
{
    int16_t ACCEL_XOUT;
    int16_t ACCEL_YOUT;
    int16_t ACCEL_ZOUT;
    int16_t GYRO_XOUT;
    int16_t GYRO_YOUT;
    int16_t GYRO_ZOUT;
    float Temperature;
}MPU6050_Data;

extern float Pitch;
extern float Roll;						//四元数解算出的欧拉角

void MPU6050_Dispose();
void MPU6050_Init();
uint8_t MPU6050_GetID();
void MPU6050_WriteReg(uint8_t RegAddress,uint8_t Data);
void IMUupdate(float gx, float gy, float gz, float ax, float ay, float az);
uint8_t MPU6050_ReadReg(uint8_t RegAddress);
void MPU6050_GetData(MPU6050_Data *Data);
void MPU6050_SendData();

#endif

