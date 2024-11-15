/*
 * @Author: 译枢-章俊-zhangjun
 * @Date: 2024-11-06 16:01:32
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2024-11-07 11:20:37
 * @Description: 请填写简介
 */


#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"	 
#include "mlx90614.h" 
#include "oled.h"

#include "stm32f10x.h"                // Device header
#include "max30102.h"
#include "algorithm.h"
#include "xiic.h"
#include "blood.h"


//温度的单位 ℃
unsigned char TempCompany[][16]=
{
	0x06,0x09,0x09,0xE6,0xF8,0x0C,0x04,0x02,0x02,0x02,0x02,0x02,0x04,0x1E,0x00,0x00,
	0x00,0x00,0x00,0x07,0x1F,0x30,0x20,0x40,0x40,0x40,0x40,0x40,0x20,0x10,0x00,0x00,/*"℃",0*/	

};

static u8  fac_us=0;//us延时倍乘数
static u16 fac_ms=0;//ms延时倍乘数
void Delay_init(u8 SYSCLK)
{
//	SysTick->CTRL&=0xfffffffb;//bit2清空,选择外部时钟  HCLK/8
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);	//选择外部时钟  HCLK/8
	fac_us=SYSCLK/8;		    
	fac_ms=(u16)fac_us*1000;
}		

int main(void)
{	
	uint8_t i,j;	
	float Temperature = 0;    //温度数据变量（浮点型）
	char TempValue[80] = {0}; //温度值（字符串）
	delay_init();	  //延时函数初始化	  
	//Delay_init(72);
	uart_init(115200);//串口初始化为115200

	OLED_Init()	;
	OLED_Clear() ;
 	LED_Init();		//LED端口初始化
	SMBus_Init();
	//display();


	//IIC_GPIO_INIT();
	//MAX30102_GPIO();
	// Max30102_reset();
	// MAX30102_Config();
//	
//	for(i = 0;i < 128;i++) 
//	{
//		while(MAX30102_INTPin_Read()==0)
//		{
//			//读取FIFO
//			max30102_read_fifo();
//		}
//	}
	OLED_ShowString(1,0,"Hello Neeko",16);
	printf("Hello Neeko\r\n");	//在串口调试助手
	while(1)
	{		
		Temperature = SMBus_ReadTemp();
		printf("Temperature = %f\r\n",Temperature);	//在串口调试助手上打印结果
		delay_ms(300);//不加延时的话在电脑串口助手上看不到效果
		sprintf(TempValue,"%.1f", Temperature); //浮点型转换成字符串		
		//温度单位显示 （℃）
		for(i = 6;i < 7;i++)
		{
			j = i - 6;
			OLED_ShowCHinese16x16(i*16,2,j,TempCompany);			
		}
		OLED_ShowString(40,2,(uint8_t *)TempValue,16);//在在OLED上显示实际测量的温度

		// /************血氧部分**********/
		//blood_Loop();
	}
}


