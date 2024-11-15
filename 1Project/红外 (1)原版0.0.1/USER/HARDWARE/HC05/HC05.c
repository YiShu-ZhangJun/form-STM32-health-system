//#include "stm32f10x.h"

// void My_USART1_Init(void)  
//{  
//    GPIO_InitTypeDef GPIO_InitStrue;  
//    USART_InitTypeDef USART_InitStrue;  
//    NVIC_InitTypeDef NVIC_InitStrue;  
//      
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//GPIO端口使能  
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);//串口端口使能  
//      
//    GPIO_InitStrue.GPIO_Mode=GPIO_Mode_AF_PP; //推挽复用输出（手册要求）
//    GPIO_InitStrue.GPIO_Pin=GPIO_Pin_9;  
//    GPIO_InitStrue.GPIO_Speed=GPIO_Speed_10MHz;  
//    GPIO_Init(GPIOA,&GPIO_InitStrue);  
//      
//    GPIO_InitStrue.GPIO_Mode=GPIO_Mode_IN_FLOATING;//浮空输入（手册要求）
//    GPIO_InitStrue.GPIO_Pin=GPIO_Pin_10;  
//    GPIO_InitStrue.GPIO_Speed=GPIO_Speed_10MHz;  
//    GPIO_Init(GPIOA,&GPIO_InitStrue);  
//      
//    USART_InitStrue.USART_BaudRate=115200;  //波特率                                                 /*要求另一台设备
//    USART_InitStrue.USART_HardwareFlowControl=USART_HardwareFlowControl_None; //不使用硬件控制          串口配置与这六
//    USART_InitStrue.USART_Mode=USART_Mode_Tx|USART_Mode_Rx;  //发送接收使能                            条一样
//    USART_InitStrue.USART_Parity=USART_Parity_No;  //不使用奇偶校验
//    USART_InitStrue.USART_StopBits=USART_StopBits_1;  //停止位为1
//    USART_InitStrue.USART_WordLength=USART_WordLength_8b; //字长8位                                           */
//      
//    USART_Init(USART1,&USART_InitStrue);
//      
//    USART_Cmd(USART1,ENABLE);//使能串口1  
//      
//    USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);//接收缓存器非空开启中断（及接收数据就触发中断）
//      
//    NVIC_InitStrue.NVIC_IRQChannel=USART1_IRQn;  
//    NVIC_InitStrue.NVIC_IRQChannelCmd=ENABLE;  //开启中断通道
//    NVIC_InitStrue.NVIC_IRQChannelPreemptionPriority=1;  //设置抢占优先级
//    NVIC_InitStrue.NVIC_IRQChannelSubPriority=1;  
//    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //中断优先级分组，两位抢占，两位相响应 
//    NVIC_Init(&NVIC_InitStrue);  
//      
//}  
//  
//void USART1_IRQHandler(void)  //串口1中断服务函数
//{  
//     char res;
//     if(USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET)  //判断中断标志位
// {  
//     res= USART_ReceiveData(USART1); 	 //读取串口一接受的数据
//     USART_SendData(USART1,res);         //向串口一发送数据
//  }  
//}  



#include "stm32f10x.h"
 
 void My_USART1_Init(void)  
{  
    GPIO_InitTypeDef GPIO_InitStrue;  
    USART_InitTypeDef USART_InitStrue;  
    NVIC_InitTypeDef NVIC_InitStrue;  
      
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//GPIO????  
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);//??????  
      
    GPIO_InitStrue.GPIO_Mode=GPIO_Mode_AF_PP;  
    GPIO_InitStrue.GPIO_Pin=GPIO_Pin_9;  
    GPIO_InitStrue.GPIO_Speed=GPIO_Speed_10MHz;  
    GPIO_Init(GPIOA,&GPIO_InitStrue);  
      
    GPIO_InitStrue.GPIO_Mode=GPIO_Mode_IN_FLOATING;  
    GPIO_InitStrue.GPIO_Pin=GPIO_Pin_10;  
    GPIO_InitStrue.GPIO_Speed=GPIO_Speed_10MHz;  
    GPIO_Init(GPIOA,&GPIO_InitStrue);  
      
    USART_InitStrue.USART_BaudRate=115200;  
    USART_InitStrue.USART_HardwareFlowControl=USART_HardwareFlowControl_None;  
    USART_InitStrue.USART_Mode=USART_Mode_Tx|USART_Mode_Rx;  
    USART_InitStrue.USART_Parity=USART_Parity_No;  
    USART_InitStrue.USART_StopBits=USART_StopBits_1;  
    USART_InitStrue.USART_WordLength=USART_WordLength_8b;  
      
    USART_Init(USART1,&USART_InitStrue);
      
    USART_Cmd(USART1,ENABLE); 
      
    USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
      
    NVIC_InitStrue.NVIC_IRQChannel=USART1_IRQn;  
    NVIC_InitStrue.NVIC_IRQChannelCmd=ENABLE;  
    NVIC_InitStrue.NVIC_IRQChannelPreemptionPriority=1;  
    NVIC_InitStrue.NVIC_IRQChannelSubPriority=1;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 
    NVIC_Init(&NVIC_InitStrue);  
      
}  
  
//void USART1_IRQHandler(void)  
//{  
//    u8 res;  
//     if(USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET)  
// {  
//     res= USART_ReceiveData(USART1); 	 
//     USART_SendData(USART1,res);     
//  }  
//}  
//   
 
   