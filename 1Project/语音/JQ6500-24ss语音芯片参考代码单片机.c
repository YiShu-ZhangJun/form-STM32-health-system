#include <reg51.h>//ͷ�ļ�
/*
��ģ��ĵھŽ�Ҳ����RX�����ӵ���Ƭ����P3^1
        ��ʮ��Ҳ����TX�����ӵ���Ƭ����P3^0(����㲻����ģ�鷵�ص����ݿ��Բ�����)
				ͬʱ��ģ��͵�Ƭ����Ҫ���ؼ�GND����GND
				��ģ���������Ҳ����ֱ���ɵ�Ƭ���ϵĵ�Դ����
*/

typedef   unsigned char  uint8;
typedef   unsigned int   uint16;
sbit KEY1=P3^4;//��һ����
sbit KEY2=P3^5;//��һ����
sbit KEY3=P3^6;//����+��
sbit KEY4=P3^7;//��������


uint8 First[]={0x7E,0x04,0x03,0x00,0X01,0xEF};//��һ��ָ��
uint8 Next[]={0x7E,0x02,0x01,0xEF};    				//��һ��ָ��
uint8 Add[]={0x7E ,0x02, 0x04, 0xEF};					//����+ָ��	
uint8 Sub[]={0x7E ,0x02 ,0x05, 0xEF};         //������ָ��

/*
 * UART��ʼ��
 * �����ʣ�9600
*/
void UART_init(void)
{
    SCON = 0x50;        // 10λuart�������н���

    TMOD = 0x20;        // ��ʱ��1�����ڷ�ʽ2���Զ���װ��
    TH1 = 0xFD;
    TL1 = 0xFD;         //���ò�����Ϊ9600

    TR1 = 1;
}

/*
 * UART ����һ�ֽ�
 ��ڲ���uint8���������� ��Ҫ���͵�����
*/
void UART_send_byte(uint8 dat)
{
	SBUF = dat;
	while (TI == 0);
	TI = 0;
}

/*
 * UART �����ַ��� 
  ��һ������Ҫ�����ַ��������ݵ��׵�ַ
  �ڶ���������Ҫ���͵����ݻ��ַ����ĳ���
*/
void UART_send_string(uint8 *buf,uint8 len)
{  uint8 i;
	for(i=0;i<len;i++)
		UART_send_byte(*buf++);
}

main()
{
	UART_init();//���ڳ�ʼ��
	
	while (1)   //һ����ѭ��һֱ�ڼ�ⰴ���ͷ���ָ��
	{  if(KEY1==0)//�����һ���������²��ŵ�һ��

    {		while(!KEY1);//�ȴ������ɿ�
			 UART_send_string(First,6);
    }		
		else if(KEY2==0)//����ڶ����������²�����һ��

    {		while(!KEY2);//�ȴ������ɿ�
			 UART_send_string(Next,4);
    }		
		else if(KEY3==0)//�����������������������
			{		while(!KEY3);//�ȴ������ɿ�
			 UART_send_string(Add,4);
    }	
 else if(KEY4==0)//������ĸ���������������

    {		while(!KEY4);//�ȴ������ɿ�
			 UART_send_string(Sub,4);
    }			
	}

}