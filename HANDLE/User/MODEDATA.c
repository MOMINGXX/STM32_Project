#include "MODEDATA.h"
#include "bmp.h"

uint8_t Mode = 1;
uint8_t Mode_TxBuf[5] = " 0 ";  //Ä£Ê½Ñ¡Ïî»º´æ
uint8_t RGB_Mode = 1;

uint8_t KEY_NUM;

void OLED_Mode(Mode_Init Mode)
{
    switch(Mode)
    {
        case BLUETOOTH_MODE:
        OLED_ShowString(1,1," Bluetooth mode");  //À¶ÑÀ
        OLED_DrawBMP(40,2,88,8,BMP_LY);
        break;
        case ROCKER_MODE:
        OLED_ShowString(1,1,"  Rocker mode  ");  //Ò£¸Ð
        OLED_DrawBMP(40,2,88,8,BMP_YK);
        break;
        case PLAY_MODE:
        OLED_ShowString(1,1," MP3PLAY  mode ");  //²¥·Å
        OLED_DrawBMP(40,2,88,8,BMP_MP3);
        break;
        case GRAVITY_MODE:
        OLED_ShowString(1,1," Gravity  mode ");  //GRAVITY
        OLED_DrawBMP(40,2,88,8,BMP_ZL);
        break;
        case KEY_MODE:
        OLED_ShowString(1,1,"   KEY  mode   ");  //°´¼ü
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
            OLED_DrawBMP(40,2,88,8,BMP_LY);
            while(1)
            {
                NRF24L01_TX_Mode();
                Mode_TxBuf[0] = 'L';
                Mode_TxBuf[1] = 'Y';
                while(NRF24L01_TxPacket(Mode_TxBuf) == NRF24L01_TX_DS);
                ROCKER_Driction();
                if(L_DIR == L_ON && R_DIR == R_ON)      //×óÓÒÒ¡¸ËÏòÉÏ
                {
                    NRF24L01_TX_Mode();
                    Mode_TxBuf[0] = 'S';
                    Mode_TxBuf[1] = 'T';
                    Mode_TxBuf[2] = 'O';
                    Mode_TxBuf[3] = 'P';
                    while(NRF24L01_TxPacket(Mode_TxBuf) == NRF24L01_TX_DS);
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
            OLED_ShowString(1,1,"  Rocker mode !");
            while(1)
            {
                KEY_SCAN();
                ROCKERData_Send();
                OLED_Show_ROCKERValue();
                if(RETURN == KEY_NUM)
                {
                    NRF24L01_TX_Mode();
                    Mode_TxBuf[0] = 'S';
                    Mode_TxBuf[1] = 'T';
                    Mode_TxBuf[2] = 'O';
                    Mode_TxBuf[3] = 'P';
                    while(NRF24L01_TxPacket(Mode_TxBuf) == NRF24L01_TX_DS);
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
            OLED_DrawBMP(40,2,88,8,BMP_MP3);
            while(1)
            {
				ROCKER_Driction();
                KEY_SCAN();
                Key_Send(KEY_NUM); 
                if(L_DIR == L_ON && R_DIR == R_ON)      //×óÓÒÒ¡¸ËÏòÉÏ
                {
                    NRF24L01_TX_Mode();
                    Mode_TxBuf[0] = 'S';
                    Mode_TxBuf[1] = 'T';
                    Mode_TxBuf[2] = 'O';
                    Mode_TxBuf[3] = 'P';
                    while(NRF24L01_TxPacket(Mode_TxBuf) == NRF24L01_TX_DS);
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
            OLED_ShowString(1,1," GRAVITY mode !");     
            while(1)
            {
                ROCKER_Driction();
                ROCKERData_Send();
                MPU6050_SendData();
                OLED_Show_MPU6050Value();
                if(L_DIR == L_ON && R_DIR == R_ON)      //×óÓÒÒ¡¸ËÏòÉÏ
                {
                    NRF24L01_TX_Mode();
                    Mode_TxBuf[0] = 'S';
                    Mode_TxBuf[1] = 'T';
                    Mode_TxBuf[2] = 'O';
                    Mode_TxBuf[3] = 'P';
                    while(NRF24L01_TxPacket(Mode_TxBuf) == NRF24L01_TX_DS);
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
            OLED_ShowString(1,1,"   KEY mode !");
            OLED_DrawBMP(40,2,88,8,BMP_KY);      
            while(1)
            {
                KEY_SCAN();
                ROCKER_Driction();
                Key_Send(KEY_NUM); 
                if(L_DIR == L_ON && R_DIR == R_ON)      //×óÓÒÒ¡¸ËÏòÉÏ
                {
                    NRF24L01_TX_Mode();
                    Mode_TxBuf[0] = 'S';
                    Mode_TxBuf[1] = 'T';
                    Mode_TxBuf[2] = 'O';
                    Mode_TxBuf[3] = 'P';
                    while(NRF24L01_TxPacket(Mode_TxBuf) == NRF24L01_TX_DS);
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
            OLED_ShowString(1,1,"   AVOID mode !");  
            OLED_DrawBMP(40,2,88,8,BMP_BZ); 
            while(1)
            {
                NRF24L01_TX_Mode();
                Mode_TxBuf[0] = 'B';
                Mode_TxBuf[1] = 'Z';
                while(NRF24L01_TxPacket(Mode_TxBuf) == NRF24L01_TX_DS);
                ROCKER_Driction();
                if(L_DIR == L_ON && R_DIR == R_ON)      //×óÓÒÒ¡¸ËÏòÉÏ
                {
                    NRF24L01_TX_Mode();
                    Mode_TxBuf[0] = 'S';
                    Mode_TxBuf[1] = 'T';
                    Mode_TxBuf[2] = 'O';
                    Mode_TxBuf[3] = 'P';
                    while(NRF24L01_TxPacket(Mode_TxBuf) == NRF24L01_TX_DS);
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
            OLED_ShowString(1,1," WS2812 mode !"); 
            OLED_DrawBMP(40,2,88,8,BMP_CD); 
            while(1)
            {
                ROCKER_Driction();
                if(L_DIR == L_DOWN)       //s
                {
                    RGB_Mode++;
                    if(8 == RGB_Mode) RGB_Mode=0;
                    while(1)
                    {
                        ROCKER_Driction();
                        if(L_DIR == L_ON && R_DIR == R_ON)
                        {
                            break;
                        }
                    }
                }
                NRF24L01_TX_Mode();
                Mode_TxBuf[0] = 'W';
                Mode_TxBuf[1] = 'L';
                if(0 == RGB_Mode) Mode_TxBuf[2] = 'A'; 
                else if(1 == RGB_Mode) Mode_TxBuf[2] = 'E'; 
                else if(2 == RGB_Mode) Mode_TxBuf[2] = 'T'; 
                else if(3 == RGB_Mode) Mode_TxBuf[2] = 'W'; 
                else if(4 == RGB_Mode) Mode_TxBuf[2] = 'R'; 
                else if(5 == RGB_Mode) Mode_TxBuf[2] = 'G'; 
                else if(6 == RGB_Mode) Mode_TxBuf[2] = 'B'; 
                else if(7 == RGB_Mode) Mode_TxBuf[2] = 'C'; 
                while(NRF24L01_TxPacket(Mode_TxBuf) == NRF24L01_TX_DS);
                
                if(L_DIR == L_ON && R_DIR == R_ON)      //×óÓÒÒ¡¸ËÏòÉÏ
                {
                    NRF24L01_TX_Mode();
                    Mode_TxBuf[0] = 'S';
                    Mode_TxBuf[1] = 'T';
                    Mode_TxBuf[2] = 'O';
                    Mode_TxBuf[3] = 'P';
                    while(NRF24L01_TxPacket(Mode_TxBuf) == NRF24L01_TX_DS);
                    OLED_Clear();
                    break;
                }  
            }        
        }
    }
}