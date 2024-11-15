 /**************************************************************************
* 文 件 名： main.c
* 使用芯片： STM32F103C8T6
* 硬件连接： 无
* 描述功能： 利用MLX90614显示温度
* 日    期： 2020/07/02
* 作    者： 刘尧
* 公 众 号： 果果小师弟
* 版    本： V1.0
* 修改记录： 无
**************************************************************************/

#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"	 
#include "mlx90614.h" 
#include "oled.h"


//温度的单位 ℃
unsigned char TempCompany[][16]=
{
	0x06,0x09,0x09,0xE6,0xF8,0x0C,0x04,0x02,0x02,0x02,0x02,0x02,0x04,0x1E,0x00,0x00,
	0x00,0x00,0x00,0x07,0x1F,0x30,0x20,0x40,0x40,0x40,0x40,0x40,0x20,0x10,0x00,0x00,/*"℃",0*/	

};

void main( void ) {
    float TEM_Value=0;
    GPIO_Config_Init();
    Usart0_Init();
    MLX90614_SMBus_Init();
    for( ;; ) {
    		TEM_Value = SMBus_ReadTemp();
		   Usart_Send_Number( TEM_Value*10,1 ); //串口发送温度显示
		   Usart1_Send_String( "\r\n" );
		   }
}



