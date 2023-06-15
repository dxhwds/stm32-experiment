/*******************************************************************************
* 实验名称  	: DS18B20温度传感器实验
* 实验说明  : 
* 接线说明  : 1，DS18B20温度传感器模块-->单片机底座管脚（STM32核心板）
					J14-->P37（PA15）
* 实验现象	: 温度传感器插好后，在串口助手上会显示检测成功，并显示检测的温度值，核心板上
				D1指示灯闪烁
*******************************************************************************/
#include "system.h"
#include "SysTick.h"
#include "led.h"
#include "usart.h"
#include "ds18b20.h"
#include "1602.h"
u8 Disp[]=" Pechin Science ";




unsigned char fen=10,miao=50;//初始时间值

void display_data(void)///显示日期、时间、星期
{
	LcdWriteCom(0x80); //第一行
	LcdWritestr("Hello World!");	
	LcdWriteData(fen/10+0x30);
	LcdWriteData(fen%10+0x30);	
  
	LcdWriteCom(0xc0);	 //第二行
	LcdWritestr("2022-8-14");
	LcdWriteData(miao/10+0x30);	  
	LcdWriteData(miao%10+0x30);
}


int main()
{
	u8 i=0;
	u8 a=0;
	float temper;
	
	SysTick_Init(72);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //中断优先级分组 分2组
	LED_Init();
	USART1_Init(9600);
	
		
  LCD1602_Init();

	
	while(DS18B20_Init())
	{
		printf("DS18B20检测失败，请插好!\r\n");
		delay_ms(500);
	}
	printf("DS18B20检测成功!\r\n");
	
	


	
	
	
	while(1)
	{
		
	
	LcdWriteCom(0x80); //第一行	
		
	LcdInit();
	for(a=0;a<16;a++)
	{
		LcdWriteData(Disp[a]);	
	}	


	 

//	LcdInit();
//display_data();
		
		
	
	
		i++;
		if(i%20==0)
		{
			led1=!led1;
		}
		
		if(i%50==0)
		{
			temper=DS18B20_GetTemperture();
			if(temper<0)
			{
				printf("检测的温度为：-");
			}
			else
			{
				printf("检测的温度为： ");
			}
			printf("%.2f°C\r\n",temper);
		
		}
		delay_ms(10);
	}
}
