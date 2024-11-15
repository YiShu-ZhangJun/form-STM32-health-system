#include "stm32f10x.h"                  // Device header
#include "delay.h"
#include "oled.h"
#include "Timer.h"

int number1 = 90;
int KeyNum1 =-1;
uint8_t KeyNum2 = 35;
uint8_t sign = 0;

void Key_Init(void)//按键初始化
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_15 | GPIO_Pin_14 | GPIO_Pin_13 | GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}
void Buzzer(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}



int Key_Num1(void)//模式一，按键2，3分模式加减
{
	if(sign==1)
	{
		return KeyNum1;
	}
	if(sign==0)
	{
		MoShiYi();
		if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14) == 0)
		{
			delay_ms(200);
				KeyNum1=KeyNum1+1;						
		}
		if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_13) == 0)
		{
			delay_ms(200);
				KeyNum1=KeyNum1-1;						
		}




		return KeyNum1;
	}
}
uint8_t Key_Num2(void)
{
	if(sign==0)
	{
		return KeyNum2;
	}
	if(sign==1)
	{
		MoShiEr();
		if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14) == 0)
		{
			delay_ms(200);
				KeyNum2++;				
		}
		if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_13) == 0)
		{
			delay_ms(200);
				KeyNum2--;
		}
		return KeyNum2;
	}
}



void EXTI15_10_IRQHandler(void)      //外部中断，用于改变模式
{
	delay_ms(200);
	if (EXTI_GetITStatus(EXTI_Line15) == SET)
	{
		if(sign==0)
		{
			sign=1;
		}
		else
		{
			sign=0;
		}
		
		EXTI_ClearITPendingBit(EXTI_Line15);//清除中断标志位
	}
}

