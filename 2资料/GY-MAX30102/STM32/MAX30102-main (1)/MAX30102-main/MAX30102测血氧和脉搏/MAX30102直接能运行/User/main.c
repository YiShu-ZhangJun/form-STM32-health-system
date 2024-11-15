#include "stm32f10x.h"                // Device header
#include "Delay.h"
#include "OLED.h"
//#include "usart.h"
#include "max30102.h"
#include "algorithm.h"
#include "xiic.h"
#include "blood.h"


int main(void)
{
	int i=0;
	Delay_init(72);			//�����ⲿ����͵�Ƭ��ʱ��Ƶ��Ϊ72m
	OLED_Init();				//OLED��ʼ��
	OLED_ShowString(1,1,"hello");
//	Usart1_Init(115200);		//���Դ��ڳ�ʼ��
//	Usart2_Init(115200);		//���ڳ�ʼ
//	
//	UsartPrintf(USART_DEBUG," ���\r\n");
	IIC_GPIO_INIT();		
	MAX30102_GPIO();
	Max30102_reset();
	MAX30102_Config();
	for(i = 0;i < 128;i++) 
	{
		while(MAX30102_INTPin_Read()==0)
		{
			//��ȡFIFO
			max30102_read_fifo();
		}
	}
	while (1)
	{
		blood_Loop();				//��ȡѪ��������
		
	}
}
