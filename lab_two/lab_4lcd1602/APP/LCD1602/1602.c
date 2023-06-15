#include "1602.h"
#include "system.h"
#include "systick.h"
/*******************LCD1602初始化************************/
void LCD1602_Init(void) 
{      
     GPIO_InitTypeDef  GPIO_InitStructure;
     RCC_APB2PeriphClockCmd(LCD_port_rcc, ENABLE);  //使能PA,PC端口时钟
	
	
     GPIO_InitStructure.GPIO_Pin = LCD_RS|LCD_RW|LCD_EN;     //LCD1602的三根控制线rs,rw,en
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //IO口速度为50MHz
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //推挽输出
     GPIO_Init(LCD_port, &GPIO_InitStructure);//根据设定参数初始化GPIOE      
   
     GPIO_InitStructure.GPIO_Pin = LCD_D0|LCD_D1|LCD_D2|LCD_D3|LCD_D4|LCD_D5|LCD_D6|LCD_D7;//LCD1602的8跟数据线        //[color=#0066cc]LED[/color]1-->PE.5 端口配置, 推挽输出
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//推挽输出
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//IO口速度为50MHz
     GPIO_Init(LCD_DO_port, &GPIO_InitStructure);//根据设定参数初始化GPIOE
					LcdInit()	;
}
 

void Lcd1602_Delay1ms(u16 c)   //延时函数，延时1ms
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

void LcdWriteCom(u8 com)	  //写入命令
{
	en = 0;	 //使能清零
	rs = 0;	 //选择写入命令
	rw = 0;	 //选择写入
GPIOB->ODR &=((com<< 8)|0x0000);
	//GPIO_Write(LCD_DO_port, com<<8|0x0000);	//由于4位的接线是接到P0口的高四位，所以传送高四位不用改
	Lcd1602_Delay1ms(5);

	en = 1;	 //写入时序
	Lcd1602_Delay1ms(30);
	en = 0;

}

void LcdWriteData(u8 dat)			//写入数据
{
	en = 0;	  //使能清零
	rs = 1;	  //选择写入数据
	rw = 0;	  //选择写入

	//GPIO_Write(LCD_DO_port, dat<<8|0x0000);	//由于4位的接线是接到P0口的高四位，所以传送高四位不用改
	Lcd1602_Delay1ms(5);

	en = 1;	  //写入时序
	Lcd1602_Delay1ms(30);
	en = 0;

}

void LcdInit(void)						  //LCD初始化子程序
{

	LcdWriteCom(0x0c);  //开显示不显示光标
	LcdWriteCom(0x38);  //两行显示
	LcdWriteCom(0x06);  //写一个指针加1
	LcdWriteCom(0x01);  //清屏
	LcdWriteCom(0x80);  //设置数据指针起点
	LcdClean();
}
		   
	   
void LcdWritestr(u8 *dat)			//向LCD写入多个字节的数据
{
	while(*dat != '\0')
	{
		LcdWriteData(*dat);
		dat++;	
	}
}

void LcdClean(void)// 清屏
{
	LcdWriteCom(0x01);
}
