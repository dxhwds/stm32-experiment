#include "1602.h"
#include "system.h"
#include "systick.h"
/*******************LCD1602��ʼ��************************/
void LCD1602_Init(void) 
{      
     GPIO_InitTypeDef  GPIO_InitStructure;
     RCC_APB2PeriphClockCmd(LCD_port_rcc, ENABLE);  //ʹ��PA,PC�˿�ʱ��
	
	
     GPIO_InitStructure.GPIO_Pin = LCD_RS|LCD_RW|LCD_EN;     //LCD1602������������rs,rw,en
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //IO���ٶ�Ϊ50MHz
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //�������
     GPIO_Init(LCD_port, &GPIO_InitStructure);//�����趨������ʼ��GPIOE      
   
     GPIO_InitStructure.GPIO_Pin = LCD_D0|LCD_D1|LCD_D2|LCD_D3|LCD_D4|LCD_D5|LCD_D6|LCD_D7;//LCD1602��8��������        //[color=#0066cc]LED[/color]1-->PE.5 �˿�����, �������
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//�������
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//IO���ٶ�Ϊ50MHz
     GPIO_Init(LCD_DO_port, &GPIO_InitStructure);//�����趨������ʼ��GPIOE
					LcdInit()	;
}
 

void Lcd1602_Delay1ms(u16 c)   //��ʱ��������ʱ1ms
{
    u8 a,b;
	for (; c>0; c--)
	{
		 for (b=199;b>0;b--)
		 {
		  	for(a=1;a>0;a--);
		 }      
	}
    	
}

void LcdWriteCom(u8 com)	  //д������
{
	en = 0;	 //ʹ������
	rs = 0;	 //ѡ��д������
	rw = 0;	 //ѡ��д��
GPIOB->ODR &=((com<< 8)|0x0000);
	//GPIO_Write(LCD_DO_port, com<<8|0x0000);	//����4λ�Ľ����ǽӵ�P0�ڵĸ���λ�����Դ��͸���λ���ø�
	Lcd1602_Delay1ms(5);

	en = 1;	 //д��ʱ��
	Lcd1602_Delay1ms(30);
	en = 0;

}

void LcdWriteData(u8 dat)			//д������
{
	en = 0;	  //ʹ������
	rs = 1;	  //ѡ��д������
	rw = 0;	  //ѡ��д��

	//GPIO_Write(LCD_DO_port, dat<<8|0x0000);	//����4λ�Ľ����ǽӵ�P0�ڵĸ���λ�����Դ��͸���λ���ø�
	Lcd1602_Delay1ms(5);

	en = 1;	  //д��ʱ��
	Lcd1602_Delay1ms(30);
	en = 0;

}

void LcdInit(void)						  //LCD��ʼ���ӳ���
{

	LcdWriteCom(0x0c);  //����ʾ����ʾ���
	LcdWriteCom(0x38);  //������ʾ
	LcdWriteCom(0x06);  //дһ��ָ���1
	LcdWriteCom(0x01);  //����
	LcdWriteCom(0x80);  //��������ָ�����
	LcdClean();
}
		   
	   
void LcdWritestr(u8 *dat)			//��LCDд�����ֽڵ�����
{
	while(*dat != '\0')
	{
		LcdWriteData(*dat);
		dat++;	
	}
}

void LcdClean(void)// ����
{
	LcdWriteCom(0x01);
}
