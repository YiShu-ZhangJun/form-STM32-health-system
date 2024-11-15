#ifndef _MLX90614_H
#define _MLX90614_H
//#include "stm8s.h"
#include "sys.h"

#define ACK	 0
#define	NACK 1  //不应答或否定的应答
#define SA				0x00 //从机地址，单个MLX90614时地址为0x00,多个时地址默认为0x5a
#define RAM_ACCESS		0x00 //RAM access command
#define EEPROM_ACCESS	0x20 //EEPROM access command
#define RAM_TOBJ1		0x07 //To1 address in the eeprom


#define MLX_SCL_PINS P07
#define MLX_SDA_PINS P01
#define SMBUS_SDA_PIN  MLX_SDA_PINS
#define SMBUS_SDA_INPUT()  do{ P0OE  &= 0xfd; P0IE |= 0x02;   }while(0)
#define SMBUS_SDA_OUTPUT() do{ P0OE  |= 0x02; P0IE &= 0xfd;  }while(0)	
#define  SMBUS_SCK_H  MLX_SCL_PINS = 1
#define  SMBUS_SCK_L  MLX_SCL_PINS = 0
#define  SMBUS_SDA_H   MLX_SDA_PINS = 1
#define  SMBUS_SDA_L   MLX_SDA_PINS = 0
#define SMBUS_DELAY_1US do{_nop_();_nop_();_nop_();_nop_();\
                           _nop_();_nop_();_nop_();_nop_();\
                           _nop_();_nop_();_nop_();_nop_();\
                           _nop_();_nop_();_nop_();_nop_();\
                           _nop_();_nop_();_nop_();_nop_();\
                           _nop_();_nop_();_nop_();_nop_();\
}while(0)
#define SMBUS_DELAY_2US do{SMBUS_DELAY_1US;SMBUS_DELAY_1US; }while(0) 
#define SMBUS_DELAY_3US do{SMBUS_DELAY_1US;SMBUS_DELAY_1US;SMBUS_DELAY_1US;\
                             }while(0) 
#define SMBUS_DELAY_4US do{SMBUS_DELAY_1US;SMBUS_DELAY_1US;SMBUS_DELAY_1US;\
                            SMBUS_DELAY_1US;}while(0) 
#define SMBUS_DELAY_5US do{SMBUS_DELAY_1US;SMBUS_DELAY_1US;SMBUS_DELAY_1US;\
                            SMBUS_DELAY_1US;SMBUS_DELAY_1US; }while(0) 
#define SMBUS_DELAY_6US do{SMBUS_DELAY_1US;SMBUS_DELAY_1US;SMBUS_DELAY_1US;\
                            SMBUS_DELAY_1US;SMBUS_DELAY_1US; }while(0) 
void SMBus_StartBit(void);
void SMBus_StopBit(void);
void SMBus_SendBit(unsigned char);
unsigned char SMBus_SendByte(unsigned char);
unsigned char SMBus_ReceiveBit(void);
unsigned char SMBus_ReceiveByte(unsigned char);
void SMBus_Delay(unsigned int);
void MLX90614_SMBus_Init(void);
unsigned int SMBus_ReadMemory(unsigned char, unsigned char);
unsigned char PEC_Calculation(unsigned char*);
float SMBus_ReadTemp(void);    //获取温度值
#endif

