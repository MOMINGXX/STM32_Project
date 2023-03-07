#include "MODEDATA.h"
#include "bmp.h"

uint8_t Mode = 2;
uint8_t Mode_TxBuf[5] = " 0 ";  //模式选项缓存
uint8_t KEY_NUM;

void OLED_Move(uint8_t Mode,uint8_t Direction)
{
    OLED_WriteCommand(0x2E);        //关闭滚动
	OLED_WriteCommand(Direction);   //水平垂直或者右滚动 29/2a
	OLED_WriteCommand(0x00);        //虚拟字节
	OLED_WriteCommand(0x00);        //起始页 0
	OLED_WriteCommand(0x07);        //滚动时间间隔
	OLED_WriteCommand(0x07);        //终止页 7
	OLED_WriteCommand(0x00);        //虚拟字节
	OLED_WriteCommand(0xFF);        //虚拟字节
	if(Mode==1)
	{
		OLED_ShowString(1,1,"Bluetooth mode !");  //蓝牙
	}
	if(Mode==2)
	{
		OLED_ShowString(1,1,"Rocker mode !");  //遥感
	}
	if(Mode==3)
	{
		OLED_ShowString(1,1,"MP3PLAY mode !");  //播放
	}
	OLED_WriteCommand(0x2F);        //开启滚动
	Delay_ms(300);
}



void OLED_Mode(Mode_Init Mode)
{
    switch(Mode)
    {
        case BLUETOOTH_MODE:
        OLED_ShowString(1,1," Bluetooth mode");  //蓝牙
        OLED_DrawBMP(40,2,88,8,BMP_LY);
        break;
        case ROCKER_MODE:
        OLED_ShowString(1,1,"  Rocker mode  ");  //遥感
        OLED_DrawBMP(40,2,88,8,BMP_YK);
        break;
        case PLAY_MODE:
        OLED_ShowString(1,1," MP3PLAY  mode ");  //播放
        OLED_DrawBMP(40,2,88,8,BMP_MP3);
        break;
        case GRAVITY_MODE:
        OLED_ShowString(1,1," Gravity  mode ");  //GRAVITY
        OLED_DrawBMP(40,2,88,8,BMP_ZL);
        break;
        case KEY_MODE:
        OLED_ShowString(1,1,"   KEY  mode   ");  //按键
        OLED_DrawBMP(40,2,88,8,BMP_KY);
        break;
        case AVOID_MODE:
        OLED_ShowString(1,1,"  AVOID  mode  ");  //bz
        OLED_DrawBMP(40,2,88,8,BMP_BZ);
        break;
        case WS2812_MODE:
        OLED_ShowString(1,1,"  WS2812 mode  ");  //ws2812
        OLED_DrawBMP(40,2,88,8,BMP_CD);
        break;
        default:
            break;
    }
}

void KEY_SCAN()
{
    KEY_NUM = Key_GetNumber();
}

static void OLED_Show_ROCKERValue()
{
    ROCKER_Value Value;
    ROCKER_COORDINATE(&Value);
    OLED_ShowString(2,1,"LX:");
    OLED_ShowString(2,9,"RX:");
    OLED_ShowString(3,1,"LY:");
    OLED_ShowString(3,9,"RY:");
    OLED_ShowString(4,1,"Battery:");
    OLED_ShowNum(2,4,Value.ROCKER_LX_Value,3);
    OLED_ShowNum(2,12,Value.ROCKER_RX_Value,3);
    OLED_ShowNum(3,4,Value.ROCKER_LY_Value,3);
    OLED_ShowNum(3,12,Value.ROCKER_RY_Value,3);
    OLED_ShowNum(4,10,Value.Electricity,3);
}

static void OLED_Show_MPU6050Value()
{
    MPU6050_Data Data;
    MPU6050_GetData(&Data);
    //OLED_ShowSignedNum(4,1,Data.Temperature,5);
    OLED_ShowSignedNum(2,1,Data.ACCEL_XOUT,5);
    OLED_ShowSignedNum(3,1,Data.ACCEL_YOUT,5);
    OLED_ShowSignedNum(4,1,Data.ACCEL_ZOUT,5);
    OLED_ShowSignedNum(2,9,Data.GYRO_XOUT,5);
    OLED_ShowSignedNum(3,9,Data.GYRO_YOUT,5);
    OLED_ShowSignedNum(4,9,Data.GYRO_ZOUT,5);
}

void Mode_Option()
{
    ROCKER_Driction();
    OLED_Mode(Mode);
    if(L_DIR == L_DOWN)       //s
    {
        Mode++;
        OLED_Clear();
        OLED_Mode(Mode);
        while(1)
        {
            ROCKER_Driction();
            if(L_DIR == L_MIDDLE)
            {
                break;
            }
        }
    }
    if(L_DIR == L_ON)     //x
    {
        Mode--;
        OLED_Clear();
        OLED_Mode(Mode);
        while(1)
        {
            ROCKER_Driction();
            if(L_DIR == L_MIDDLE)
            {
                break;
            }
        }
    }
    if(Mode > 7) Mode = 7;
    if(Mode < 1) Mode = 1;
    if(BLUETOOTH_MODE == Mode)
    {
        if(DETERMIN == KEY_NUM)
        {
            OLED_Clear();
            OLED_ShowString(1,1,"Bluetooth mode !");
            while(1)
            {
                NRF24L01_TX_Mode();
                Mode_TxBuf[0] = 'L';
                Mode_TxBuf[1] = 'Y';
                while(NRF24L01_TxPacket(Mode_TxBuf) == NRF24L01_TX_DS);
                ROCKER_Driction();
                if(L_DIR == L_ON && R_DIR == R_ON)      //左右摇杆向上
                {
                    OLED_Clear();
                    break;
                }
            }
        }
    }
    else if(ROCKER_MODE == Mode)
    {
        if(DETERMIN == KEY_NUM)
        {
            OLED_Clear();
            OLED_ShowString(1,1,"Rocker mode !   ");
            while(1)
            {
                KEY_SCAN();
                ROCKERData_Send();
                OLED_Show_ROCKERValue();
                if(RETURN == KEY_NUM)
                {
                    OLED_Clear();
                    break;
                }
            }
        }
    }
    else if(PLAY_MODE == Mode)
    {
        if(DETERMIN == KEY_NUM)
        {
            OLED_Clear();
            OLED_ShowString(1,1,"MP3 PLAY mode !");
            while(1)
            {
                KEY_SCAN();
                Key_Send(KEY_NUM); 
                if(RETURN == KEY_NUM)
                {
                    OLED_Clear();
                    break;
                } 
            }
        }
    }
    else if(GRAVITY_MODE == Mode)
    {
        if(DETERMIN == KEY_NUM)
        {
            OLED_Clear();
            OLED_ShowString(1,1,"GRAVITY mode !");     
            while(1)
            {
                ROCKER_Driction();
                ROCKERData_Send();
                MPU6050_SendData();
                if(L_DIR == L_ON && R_DIR == R_ON)      //左右摇杆向上
                {
                    OLED_Clear();
                    break;
                }  
            }        
        }
    }
    else if(KEY_MODE == Mode)
    {
        if(DETERMIN == KEY_NUM)
        {
            OLED_Clear();
            OLED_ShowString(1,1,"KEY mode !");      
            while(1)
            {
                KEY_SCAN();
                ROCKER_Driction();
                Key_Send(KEY_NUM); 
                if(L_DIR == L_ON && R_DIR == R_ON)      //左右摇杆向上
                {
                    OLED_Clear();
                    break;
                }  
            }
        }
    }
    else if(AVOID_MODE == Mode)
    {
        if(DETERMIN == KEY_NUM)
        {
            OLED_Clear();
            OLED_ShowString(1,1,"AVOID mode !");   
            while(1)
            {
                NRF24L01_TX_Mode();
                Mode_TxBuf[0] = 'B';
                Mode_TxBuf[1] = 'Z';
                while(NRF24L01_TxPacket(Mode_TxBuf) == NRF24L01_TX_DS);
                ROCKER_Driction();
                if(L_DIR == L_ON && R_DIR == R_ON)      //左右摇杆向上
                {
                    OLED_Clear();
                    break;
                }  
            }       
        }
    }
    else if(WS2812_MODE == Mode)
    {
        if(DETERMIN == KEY_NUM)
        {
            OLED_Clear();
            OLED_ShowString(1,1,"WS2812 mode !");  
            while(1)
            {
                NRF24L01_TX_Mode();
                Mode_TxBuf[0] = 'W';
                Mode_TxBuf[1] = 'L';
                while(NRF24L01_TxPacket(Mode_TxBuf) == NRF24L01_TX_DS);
                ROCKER_Driction();
                if(L_DIR == L_ON && R_DIR == R_ON)      //左右摇杆向上
                {
                    OLED_Clear();
                    break;
                }  
            }        
        }
    }
}