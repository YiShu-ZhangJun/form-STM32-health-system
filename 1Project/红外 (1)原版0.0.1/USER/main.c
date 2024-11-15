//#include "stm32f10x.h"                  // Device header
#include "delay.h"
#include "key.h"
#include "sys.h"	 
#include "mlx90614.h" 
#include "oled.h"
//#include "HC05.h"
#include "CountSensor.h"
#include "string.h"

#include "stm32f10x.h"                // Device header
//#include "Delay.h"
//#include "OLED.h"
#include "usart.h"
#include "max30102.h"
#include "algorithm.h"
#include "xiic.h"
#include "blood.h"

int main(void)
{	
	int i=0;
	char A[]="Tem : ";
	uint8_t KeyNumber2,BaoJing;
    float KeyNumber1=0;
    float Temperature = 0;    //�¶����ݱ����������ͣ�
    char TempValue[80] = {0};
    char BuChang[80] = {0};	//����ֵ
	uart_init(115200);
	delay_init();	  //��ʱ������ʼ��
	Key_Init();//������ʼ��	
	OLED_Init()	;
	OLED_Clear() ;
	CountSensor_Init();
	SMBus_Init();
	display();
	Buzzer(); 

	IIC_GPIO_INIT();		
	MAX30102_GPIO();
	Max30102_reset();
  MAX30102_Config();
	for(i = 0;i < 128;i++) 
	{
		while(MAX30102_INTPin_Read()==0)
		{
			//读取FIFO
			max30102_read_fifo();
		}
	}
	printf("Neeko");
	OLED_ShowString(40,2,"----",16);//����4������ʾ�¶�
	//My_USART1_Init();
	while(1)
	{			
		printf("123");
		blood_Loop();				//获取血氧和心率
		if(
				1 //GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12) == 0
		)
		{
			delay_ms(200);
			Temperature = SMBus_ReadTemp()+KeyNumber1;
			sprintf(TempValue,"%.1f", Temperature); //������ת�����ַ���			
			OLED_ShowString(40,2,(uint8_t *)TempValue,16);//����OLED����ʾʵ�ʲ������¶�

			if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12) == 1)
			{
				for(char a=0;a<6;a++)
				{
					USART_SendData(USART1, A[a]);
					while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
				}
				int i = 0;
				for(;i < strlen(TempValue);++i){
					USART_SendData(USART1, *(uint8_t*)(TempValue+i));
				while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);				
				}
			}	
		
		}
//		KeyNumber1=Key_Num1()*0.1;
//		sprintf(BuChang,"%.1f", KeyNumber1);
//		OLED_ShowString(40,4,(uint8_t *)BuChang,16);
		
		KeyNumber2=Key_Num2();
		OLED_ShowNumber(40,6,KeyNumber2,2,16);
		
		if(Temperature>KeyNumber2)
		{
			GPIO_ResetBits(GPIOA,GPIO_Pin_5);
			Warning();			
		}
		else
		{
			GPIO_SetBits(GPIOA,GPIO_Pin_5);
			Safe();
		}		 
	}
			
	
}

