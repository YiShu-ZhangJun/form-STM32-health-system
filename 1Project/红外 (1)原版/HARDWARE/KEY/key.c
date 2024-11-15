
#include "stm32f10x.h"                  // Device header
#include "Delay.h"
uint8_t number = 0;
uint8_t KeyNum1 = 0;
uint8_t KeyNum2 = 35;
uint8_t KeyNum3 = 37;
void Key_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

uint8_t Key_Mod(void)//按键1，模式选择
{
	
	if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == 0)
	{
		Delay_ms(20);
		if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == 0)
		{
			TIM_Cmd(TIM2,ENABLE);
			if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == 1)
			{
				TIM_Cmd(TIM2,DISABLE);
				if(number<80)
				{
					number=0 ;
					return 0 ; //模式0（按键时间小于100毫秒）
				}
				else
				{
					number=0;
					return 1; //模式1（大于100毫秒）
				}
			}
			
		}
	else
	{
		return 0;
	}
		
}
void Mod(void)


}
	

uint8_t Key_GetNum2(void)//温度范围警报，左数值，按2键加1，按4再按2键减1，初始为35
{
	
	if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_2) == 0)
	{
		Delay_ms(20);
		while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_2) == 0);
		Delay_ms(20);
		KeyNum2 = KeyNum2 + 1;
	}
	if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_2) == 0 && GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_4) == 0 )
	{
		Delay_ms(20);
		while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_2) == 0);
		Delay_ms(20);
		KeyNum2 = KeyNum2 - 1;	
	}
	
	return KeyNum2;
}
uint8_t Key_GetNum3(void)//温度范围报警，右数值，按3加1，按4同时按3减1，初始值为38
{
	
	if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_3) == 0)
	{
		Delay_ms(20);
		while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_3) == 0);
		Delay_ms(20);
		KeyNum3 = KeyNum3 + 1;
	}
	if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_3) == 0 && GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_4) == 0 )
	{
		Delay_ms(20);
		while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_2) == 0);
		Delay_ms(20);
		KeyNum3 = KeyNum3 - 1;	
	}	
	return KeyNum3;
}
uint8_t Key_GetNum4(void)//单独按四号键，显示温度
{
	if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_4) == 0)
	{
		uint8_t KeyNum4 = 0;
		Delay_ms(20);
		while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_4) == 0);
		Delay_ms(20);
		KeyNum4 = KeyNum4 - 1;
	}
	return KeyNum4;
}
