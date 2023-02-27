#include "MPU6050.h"

/****
	* @brief    六轴传感器 写数据			  
	* @param   	RegAddress  寄存器地址
    * @param   	Data        写入的数据
	* @return   无    	
	* Sample usage:MPU6050_WriteReg(MPU6050_PWR_MGMT_1,0x01);
    */
void MPU6050_WriteReg(uint8_t RegAddress,uint8_t Data)
{
    IIC_Start();
    IIC_SendByte(MPU6050_ADDR);
	IIC_ReceiveAck();
    IIC_SendByte(RegAddress);
    IIC_ReceiveAck();
    IIC_SendByte(Data);
    IIC_ReceiveAck();
    IIC_Stop();
}

/****
	* @brief    六轴传感器 读取数据		  
	* @param   	RegAddress  寄存器地址
	* @return   Data        读取的数据   	
	* Sample usage:MPU6050_ReadReg(MPU6050_PWR_MGMT_1);
    */
uint8_t MPU6050_ReadReg(uint8_t RegAddress)
{
    uint8_t Data = 0;
    IIC_Start();
    IIC_SendByte(MPU6050_ADDR);
	IIC_ReceiveAck();
    IIC_SendByte(RegAddress);
    IIC_ReceiveAck();

    IIC_Start();
    IIC_SendByte(MPU6050_ADDR | 0x01);
    IIC_ReceiveAck();
    Data = IIC_ReceiveByte();
    IIC_SendAck(1);
    IIC_Stop();
    return Data;    
}

/****
	* @brief    六轴传感器 初始化		  
	* @param   	无
	* @return   无	
	* Sample usage:MPU6050_Init();
    */
void MPU6050_Init()
{
    IIC_Init();
	MPU6050_WriteReg(MPU6050_PWR_MGMT_1,0x01);		//电源管理寄存器1  解除休眠状态 选用X轴陀螺仪时钟
	MPU6050_WriteReg(MPU6050_PWR_MGMT_2,0x00);		//电源管理寄存器2  6轴均不待机
	MPU6050_WriteReg(MPU6050_SMPLRT_DIV,0x07);		//采样率分频       陀螺仪125hz
	MPU6050_WriteReg(MPU6050_CONFIG,0x06);			//低通滤波频率
	MPU6050_WriteReg(MPU6050_GYRO_CONFIG,0x18);		//陀螺仪
	MPU6050_WriteReg(MPU6050_ACCEL_CONFIG,0x18);	//加速度计
}

/****
	* @brief    六轴传感器 ID		  
	* @param   	无
	* @return   ID号          0X68
	* Sample usage:MPU6050_GetID();
    */
uint8_t MPU6050_GetID()
{
	return MPU6050_ReadReg(MPU6050_WHO_AM_I);
}

/****
	* @brief    六轴传感器 读取数据		  
	* @param   	Data    结构体地址
	* @return   无
	* Sample usage:MPU6050_GetData(&Data);
    */
void MPU6050_GetData(MPU6050_Data *Data)
{
	Data->ACCEL_XOUT = MPU6050_ReadReg(MPU6050_ACCEL_XOUT_H) << 8;
    Data->ACCEL_XOUT |= MPU6050_ReadReg(MPU6050_ACCEL_XOUT_L);

    Data->ACCEL_YOUT = MPU6050_ReadReg(MPU6050_ACCEL_YOUT_H) << 8;
    Data->ACCEL_YOUT |= MPU6050_ReadReg(MPU6050_ACCEL_YOUT_L);

    Data->ACCEL_ZOUT = MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_H) << 8;
    Data->ACCEL_ZOUT |= MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_L);

    Data->GYRO_XOUT = MPU6050_ReadReg(MPU6050_GYRO_XOUT_H) << 8;
    Data->GYRO_XOUT |= MPU6050_ReadReg(MPU6050_GYRO_XOUT_L);

    Data->GYRO_YOUT = MPU6050_ReadReg(MPU6050_GYRO_YOUT_H) << 8;
    Data->GYRO_YOUT |= MPU6050_ReadReg(MPU6050_GYRO_YOUT_L);

    Data->GYRO_ZOUT = MPU6050_ReadReg(MPU6050_GYRO_ZOUT_H) << 8;
    Data->GYRO_ZOUT |= MPU6050_ReadReg(MPU6050_GYRO_ZOUT_L);
}


