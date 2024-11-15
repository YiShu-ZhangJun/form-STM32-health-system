/*("/*********************************************/\n");
("//项 目 名:6500 MP3芯片参考代码\n");
("//功能要求:\n");
("//硬件配置:\n");
("//1) MCU型号: STM8S003F3P6\n");
("//2) 内部振荡频率为:16M\n");
("//软件版本:UART1: \n");
("//公 司 名: 深圳佳强电子有限公司\n");
("//作    者: \n");
("//		硬件：\n");
("//		软件：piao\n");
("//技术支持：E-mail:jianguo_luo@foxmail.com\n");
("//修改记录: 1）\n");
("//          2）\n");
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
	PC_DDR |= 0x08;	//PC3输出
    PC_CR1 |= 0x08;	//PC3推挽
	//IRQ
	PC_DDR &= 0xEF;	//PC4输入
    PC_CR1 &= 0xEF;	//PC4浮空
	//BUSY_CHECK
	PB_DDR &= 0xEF;	//PB4输入
    PB_CR1 &= 0xEF;	//PB4浮空

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
//函数名:SendUartString_U1()
//
//功能说明:发送232单字节数据,波特率为9600
//
//入口参数:dat为要发送的内容
//
//出口参数:无
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
//函数名:Next_Play()
//
//功能说明:设定音量
//
//入口参数:
//
//出口参数:NO
***********************************************************************************************/
void Next_Play()
{
	STM8_UART1_SendByte(0x7E); 
	STM8_UART1_SendByte(0x02);
	STM8_UART1_SendByte(0x01);
	STM8_UART1_SendByte(0xEF); 
}

/*********************************************************************************************
//函数名:Last_Play()
//
//功能说明:
//
//入口参数:
//
//出口参数:NO
***********************************************************************************************/
void Last_Play()
{
	STM8_UART1_SendByte(0x7E); 
	STM8_UART1_SendByte(0x02);
	STM8_UART1_SendByte(0x02);
	STM8_UART1_SendByte(0xEF); 
}
/*********************************************************************************************
//函数名:Specify_Musi_Play()
//
//功能说明:指定曲目播放
//
//入口参数:
//
//出口参数:NO
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
//函数名:Volume_add()
//
//功能说明:音量加
//
//入口参数:
//
//出口参数:NO
***********************************************************************************************/
void Volume_add()
{
	STM8_UART1_SendByte(0x7E); 
	STM8_UART1_SendByte(0x02);
	STM8_UART1_SendByte(0x04);
	STM8_UART1_SendByte(0xEF); 
}
/*********************************************************************************************
//函数名:Volume_nec()
//
//功能说明:音量减
//
//入口参数:
//
//出口参数:NO
***********************************************************************************************/
void Volume_nec()
{
	STM8_UART1_SendByte(0x7E); 
	STM8_UART1_SendByte(0x02);
	STM8_UART1_SendByte(0x05);
	STM8_UART1_SendByte(0xEF); 
}
/*********************************************************************************************
//函数名:Specify_Volume()
//
//功能说明:指定音量
//
//入口参数:
//
//出口参数:NO
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
//函数名:Music_play()
//
//功能说明:播放
//
//入口参数:
//
//出口参数:NO
***********************************************************************************************/
void Music_play()
{
	STM8_UART1_SendByte(0x7E); 
	STM8_UART1_SendByte(0x02);
	STM8_UART1_SendByte(0x0D);
	STM8_UART1_SendByte(0xEF); 
}
/*********************************************************************************************
//函数名:Music_pause()
//
//功能说明:暂停
//
//入口参数:
//
//出口参数:NO
***********************************************************************************************/
void Music_pause()
{
	STM8_UART1_SendByte(0x7E); 
	STM8_UART1_SendByte(0x02);
	STM8_UART1_SendByte(0x0E);
	STM8_UART1_SendByte(0xEF); 
}
/*********************************************************************************************
//函数名:Music_stop()
//
//功能说明:停止
//
//入口参数:
//
//出口参数:NO
***********************************************************************************************/
void Music_stop()
{
	STM8_UART1_SendByte(0x7E); 
	STM8_UART1_SendByte(0x02);
	STM8_UART1_SendByte(0x10);
	STM8_UART1_SendByte(0xEF); 
}
/*********************************************************************************************
//函数名:Switch_play_Device()
//
//功能说明:U/TF/AUX/SLEEP/FLASH(0/1/2/3/4)切换
//
//入口参数:
//
//出口参数:NO
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
//函数名:Cycle_play()
//
//功能说明:1:全部循环 0:单曲循环
//
//入口参数:
//
//出口参数:NO
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

	Switch_play_Device(1);//转到TF卡
	Delay_long(12);  
	Next_Play();
	Delay_long(12);
	Cycle_play(1);//全部循环
	while(1);
}


