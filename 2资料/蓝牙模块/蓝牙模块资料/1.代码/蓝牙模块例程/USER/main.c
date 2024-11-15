/*
 * @Author: 译枢-章俊-zhangjun
 * @Date: 2024-10-02 22:38:05
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2024-11-05 17:02:14
 * @Description: 请填写简介
 */
#include "stm32f10x.h"
#include "led.h"
#include "usart.h"
#include "delay.h"
#include "oled.h"
#include "usart3.h"

/*****************辰哥单片机设计******************
											STM32
 * 项目			:	蓝牙模块通信实验                     
 * 版本			: V1.0
 * 日期			: 2024.10.2
 * MCU			:	STM32F103C8T6
 * 接口			:	参看usart3.h							
 * BILIBILI	:	辰哥单片机设计
 * CSDN			:	辰哥单片机设计
 * 作者			:	辰哥 

**********************BEGIN***********************/

u8 dakai;
u8 Flag_dakai;

int main(void)
{ 
	
  SystemInit();//配置系统时钟为72M	
	delay_init(72);
	LED_Init();
	LED_On();
	OLED_Init();
	OLED_Clear();
	USART1_Config();
	USART3_Config();
	printf("Start \n");
	OLED_Refresh();
	delay_ms(1000);

  while (1)
  {
	OLED_DisPlay_On();
	OLED_DrawCircle(30,30,10);
	OLED_Refresh();
	if(dakai==1&&Flag_dakai==0)
	{
			LED_On();
	Flag_dakai=1;
			printf("1 \n");
			OLED_ShowNum(80,50,1,1,24,1);
	}
	if(dakai==0&&Flag_dakai==1)
	{
			LED_Off();
	Flag_dakai=0;
			printf("0 \n");
			OLED_ShowNum(80,50,0,1,24,1);
	}
			
  }
}




