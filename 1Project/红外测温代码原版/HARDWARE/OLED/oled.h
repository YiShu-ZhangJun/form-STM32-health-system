/*
 * @Author: 译枢-章俊-zhangjun
 * @Date: 2024-11-07 11:23:30
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2024-11-07 11:46:11
 * @Description: 请填写简介
 */
#ifndef __OLED_H
#define __OLED_H	

#include "stdlib.h"
#include "sys.h"
#define OLED_MODE 1
#define SIZE 8
#define XLevelL		0x00
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF 
#define X_WIDTH 	128
#define Y_WIDTH 	64	    						  
//-----------------OLED IIC�˿ڶ���----------------  		

#define OLED_SCL_GPIO GPIO_Pin_4
#define OLED_SDA_GPIO GPIO_Pin_5


#define OLED_SCLK_Clr() GPIO_ResetBits(GPIOB,OLED_SCL_GPIO)//SCL
#define OLED_SCLK_Set() GPIO_SetBits(GPIOB,OLED_SCL_GPIO)

#define OLED_SDIN_Clr() GPIO_ResetBits(GPIOB,OLED_SDA_GPIO)//SDA
#define OLED_SDIN_Set() GPIO_SetBits(GPIOB,OLED_SDA_GPIO)

 		     
#define OLED_CMD  0	//д����
#define OLED_DATA 1	//д����
void OLED_ShowChinese(u8 x,u8 y,u8 num,u8 size1);

//OLED�����ú���
void OLED_WR_Byte(unsigned dat,unsigned cmd);  
void OLED_Display_On(void);
void OLED_Display_Off(void);	   							   		    
void OLED_Init(void);
void OLED_Clear(void);
void OLED_DrawPoint(unsigned  char x,unsigned  char y,unsigned  char t);
void OLED_Fill(unsigned  char x1,unsigned  char y1,unsigned  char x2,unsigned  char y2,unsigned  char dot);
void OLED_ShowChar(unsigned  char x,unsigned  char y,unsigned  char chr,unsigned  char Char_Size);
void OLED_ShowNumber(unsigned  char x,unsigned  char y,unsigned  int num,unsigned  char len,unsigned  char size);
void OLED_ShowString(unsigned    char x,unsigned  char y, unsigned  char *p,unsigned  char Char_Size);	 
void OLED_Set_Pos(unsigned char x, unsigned char y);
void OLED_ShowCHinese(unsigned  char x,unsigned  char y,unsigned  char no);
void OLED_ShowCHinese16x16(unsigned  char x,unsigned  char y,unsigned  char num,unsigned  char (*buf)[16]);
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[]);
void fill_picture(unsigned char fill_Data);
void Picture(void);
void OLED_IIC_Start(void);
void OLED_IIC_Stop(void);
void OLED_Write_IIC_Command(unsigned char IIC_Command);
void OLED_Write_IIC_Data(unsigned char IIC_Data);
void OLED_Write_IIC_Byte(unsigned char IIC_Byte);
void OLED_IIC_Wait_Ack(void);

void OLED_fuhao_write(unsigned char x,unsigned char y,unsigned char asc);
void OLED_Num_write(unsigned char x,unsigned char y,unsigned char asc) ;
void OLED_Float(unsigned char Y,unsigned char X,double real,unsigned char N);
void OLED_Float2(unsigned char Y,unsigned char X,double real,unsigned char N1,unsigned char N2);
void OLED_Num2(unsigned char x,unsigned char y, int number);
void OLED_Num3(unsigned char x,unsigned char y,int number); 
void OLED_Num4(unsigned char x,unsigned char y, int number);
void OLED_Num5(unsigned char x,unsigned char y,unsigned int number);
void oled_show(void);
void oled_first_show(void);	


void Delay(unsigned  int count);
void display(void);   //��ʾ������Сʦ�� �¶� ���롱

#endif  
