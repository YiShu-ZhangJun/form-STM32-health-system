/*("/*********************************************/\n");
("//�� Ŀ ��:6500 MP3оƬ�ο�����\n");
("//����Ҫ��:\n");
("//Ӳ������:\n");
("//1) MCU�ͺ�: STM8S003F3P6\n");
("//2) �ڲ���Ƶ��Ϊ:16M\n");
("//����汾:UART1: \n");
("//�� ˾ ��: ���ڼ�ǿ�������޹�˾\n");
("//��    ��: \n");
("//		Ӳ����\n");
("//		�����piao\n");
("//����֧�֣�E-mail:jianguo_luo@foxmail.com\n");
("//�޸ļ�¼: 1��\n");
("//          2��\n");
("/*********************************************/\n");*/


#define __MAIN_C__
#include "iostm8s103f2.h"


typedef unsigned long  u32;
typedef unsigned short u16;
typedef unsigned char  u8;
void Delay(u16 nCount);
void Delay_long(u16 nCount);

void Next_Play();
void Last_Play();
void Specify_Musi_Play(u8 num);
void Volume_add();
void Volume_nec();
void Music_play();
void Music_pause();
void Music_stop();
void Switch_play_Device(u8 num);
void Cycle_play(u8 num);
void Specify_Volume(u8 num);


/*===========================================================================*/


void STM8_CLK_Init(void)
{
    CLK_CKDIVR = 0x00;  /* 16MHz */
}

void STM8_GPIO_Init(void)
{
    //CS
	PC_DDR |= 0x08;	//PC3���
    PC_CR1 |= 0x08;	//PC3����
	//IRQ
	PC_DDR &= 0xEF;	//PC4����
    PC_CR1 &= 0xEF;	//PC4����
	//BUSY_CHECK
	PB_DDR &= 0xEF;	//PB4����
    PB_CR1 &= 0xEF;	//PB4����

}

void STM8_SPI_Init(void)
{
//    SPI_CR1   = 0x07;   /* 0B00000111 */
    SPI_CR1   = 0x3C;   /* 0B00111111 */
    SPI_CR2   = 0x03;   /* 0B00000011 */
    SPI_CRCPR = 0x07;

    /* Enable the SPI peripheral*/
    SPI_CR1 |= 0x40;
}

void STM8_UART1_Init(void)
{
    UART1_BRR2 = 0x02;  /* buadrate = 9600 */
    UART1_BRR1 = 0x68;
    UART1_CR2  = 0x2C;  /* enable send and receive */
}

void STM8_Init(void)
{
    asm("sim");

    STM8_CLK_Init();
    STM8_GPIO_Init();
    STM8_SPI_Init();
    STM8_UART1_Init();

    asm("rim");
}

/*===========================================================================*/


void STM8_UART1_SendByte(u8 dat)
{
    while(!UART1_SR_TXE);
    UART1_DR = dat;

    asm("nop");
}

/****************************************
//������:SendUartString_U1()
//
//����˵��:����232���ֽ�����,������Ϊ9600
//
//��ڲ���:datΪҪ���͵�����
//
//���ڲ���:��
*******************************************/
void SendUartString_U1(unsigned char *pData)
{
    while(*pData)
	{
	    STM8_UART1_SendByte(*pData);
		pData++;
	}
}




#pragma vector = UART1_R_RXNE_vector
__interrupt __root void UART1_Recv (void)
{
	u8 data;
	data=UART1_DR;
//	STM8_UART1_SendByte(data);
	return;
}
/*********************************************************************************************
//������:Next_Play()
//
//����˵��:�趨����
//
//��ڲ���:
//
//���ڲ���:NO
***********************************************************************************************/
void Next_Play()
{
	STM8_UART1_SendByte(0x7E); 
	STM8_UART1_SendByte(0x02);
	STM8_UART1_SendByte(0x01);
	STM8_UART1_SendByte(0xEF); 
}

/*********************************************************************************************
//������:Last_Play()
//
//����˵��:
//
//��ڲ���:
//
//���ڲ���:NO
***********************************************************************************************/
void Last_Play()
{
	STM8_UART1_SendByte(0x7E); 
	STM8_UART1_SendByte(0x02);
	STM8_UART1_SendByte(0x02);
	STM8_UART1_SendByte(0xEF); 
}
/*********************************************************************************************
//������:Specify_Musi_Play()
//
//����˵��:ָ����Ŀ����
//
//��ڲ���:
//
//���ڲ���:NO
***********************************************************************************************/
void Specify_Musi_Play(u8 num)
{
	STM8_UART1_SendByte(0x7E); 
	STM8_UART1_SendByte(0x04);
	STM8_UART1_SendByte(0x03);
	STM8_UART1_SendByte(0x00);
	STM8_UART1_SendByte(num);
	STM8_UART1_SendByte(0xEF); 
}

/*********************************************************************************************
//������:Volume_add()
//
//����˵��:������
//
//��ڲ���:
//
//���ڲ���:NO
***********************************************************************************************/
void Volume_add()
{
	STM8_UART1_SendByte(0x7E); 
	STM8_UART1_SendByte(0x02);
	STM8_UART1_SendByte(0x04);
	STM8_UART1_SendByte(0xEF); 
}
/*********************************************************************************************
//������:Volume_nec()
//
//����˵��:������
//
//��ڲ���:
//
//���ڲ���:NO
***********************************************************************************************/
void Volume_nec()
{
	STM8_UART1_SendByte(0x7E); 
	STM8_UART1_SendByte(0x02);
	STM8_UART1_SendByte(0x05);
	STM8_UART1_SendByte(0xEF); 
}
/*********************************************************************************************
//������:Specify_Volume()
//
//����˵��:ָ������
//
//��ڲ���:
//
//���ڲ���:NO
***********************************************************************************************/
void Specify_Volume(u8 num)
{
	STM8_UART1_SendByte(0x7E); 
	STM8_UART1_SendByte(0x03);
	STM8_UART1_SendByte(0x06);
	STM8_UART1_SendByte(num);
	STM8_UART1_SendByte(0xEF); 
}


/*********************************************************************************************
//������:Music_play()
//
//����˵��:����
//
//��ڲ���:
//
//���ڲ���:NO
***********************************************************************************************/
void Music_play()
{
	STM8_UART1_SendByte(0x7E); 
	STM8_UART1_SendByte(0x02);
	STM8_UART1_SendByte(0x0D);
	STM8_UART1_SendByte(0xEF); 
}
/*********************************************************************************************
//������:Music_pause()
//
//����˵��:��ͣ
//
//��ڲ���:
//
//���ڲ���:NO
***********************************************************************************************/
void Music_pause()
{
	STM8_UART1_SendByte(0x7E); 
	STM8_UART1_SendByte(0x02);
	STM8_UART1_SendByte(0x0E);
	STM8_UART1_SendByte(0xEF); 
}
/*********************************************************************************************
//������:Music_stop()
//
//����˵��:ֹͣ
//
//��ڲ���:
//
//���ڲ���:NO
***********************************************************************************************/
void Music_stop()
{
	STM8_UART1_SendByte(0x7E); 
	STM8_UART1_SendByte(0x02);
	STM8_UART1_SendByte(0x10);
	STM8_UART1_SendByte(0xEF); 
}
/*********************************************************************************************
//������:Switch_play_Device()
//
//����˵��:U/TF/AUX/SLEEP/FLASH(0/1/2/3/4)�л�
//
//��ڲ���:
//
//���ڲ���:NO
***********************************************************************************************/
void Switch_play_Device(u8 num)
{
	STM8_UART1_SendByte(0x7E); 
	STM8_UART1_SendByte(0x03);
	STM8_UART1_SendByte(0x09);
	STM8_UART1_SendByte(num);
	STM8_UART1_SendByte(0xEF); 
}
/*********************************************************************************************
//������:Cycle_play()
//
//����˵��:1:ȫ��ѭ�� 0:����ѭ��
//
//��ڲ���:
//
//���ڲ���:NO
***********************************************************************************************/
void Cycle_play(u8 num)
{
	STM8_UART1_SendByte(0x7E); 
	STM8_UART1_SendByte(0x03);
	STM8_UART1_SendByte(0x11);
	STM8_UART1_SendByte(num);
	STM8_UART1_SendByte(0xEF); 
}
 
/**
  * @brief Delay
  * @param nCount
  * @retval None
  */
void Delay(u16 nCount)
{
  /* Decrement nCount value */
  while (nCount != 0)
  {
    nCount--;
  }
}
void Delay_long(u16 nCount)
{
  /* Decrement nCount value */
  while (nCount != 0)
  {
    Delay(0xffff);
	nCount--;
  }
}

void main(void)
{
    u32 n = 4;
    STM8_Init();

	Switch_play_Device(1);//ת��TF��
	Delay_long(12);  
	Next_Play();
	Delay_long(12);
	Cycle_play(1);//ȫ��ѭ��
	while(1);
}


