#include "MPU6050.h"

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

void MPU6050_Init()
{
    IIC_Init();
	MPU6050_WriteReg(MPU6050_PWR_MGMT_1,0x01);		//��Դ����Ĵ���1  ѡ��X��������ʱ��
	MPU6050_WriteReg(MPU6050_PWR_MGMT_2,0x00);		//��Դ����Ĵ���2  6���������
	MPU6050_WriteReg(MPU6050_SMPLRT_DIV,0x07);		//�����ʷ�Ƶ
	MPU6050_WriteReg(MPU6050_CONFIG,0x06);			//��ͨ�˲�Ƶ��
	MPU6050_WriteReg(MPU6050_GYRO_CONFIG,0x18);		//������
	MPU6050_WriteReg(MPU6050_ACCEL_CONFIG,0x18);	//���ٶȼ�
}

uint8_t MPU6050_GetID()
{
	return MPU6050_ReadReg(MPU6050_WHO_AM_I);
}

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


