/*******************************************************************************
* 实验名称  	: 按键控制实验
* 实验说明  : 
* 接线说明  : 1，独立按键模块-->单片机底座管脚（STM32核心板）
					K1-->P00（PB8）
					K2-->P01（PB9）
			  2，EEPROM模块-->单片机底座管脚（STM32核心板）
					SCL-->P02（PB10）
					SDA-->P03（PB11）	
* 实验现象	: 首先检测开发板上AT24C02是否正常，在串口助手上输出对应提示信息，然后按下K1键
				对EEPROM数据写入，每按一次数据加1写入，按下K2键进行读取。写入和读取的过程中
				在串口助手上均会显示对应的提示信息。核心板上D1指示灯闪烁
*******************************************************************************/

#include "system.h"
#include "SysTick.h"
#include "led.h"
#include "usart.h"
#include "key.h"
#include "24cxx.h"
#include "ds18b20.h"

u8 r[8];
char DisplayData[8];
u8 test[8] = "abcdef";
void datapros(float temp) 	 
{
	int aaa;
   	float tp; 
	tp=temp;
	aaa=tp*100;	 
/*	if(temp< 0)				//当温度值为负数
  	{
		DisplayData[0] = '-';//0x40; 	  //   -

		tp=temp;
		
		aaa=tp*100;	      
	
 
  	}
 	else
  	{			
		DisplayData[0] = ' ';//0x00;
		tp=temp;//因为数据处理有小数点所以将温度赋给一个浮点型变量
		
    aaa=tp*100;	
	
	}     */
	
	DisplayData[0] =(char) aaa / 10000;
	DisplayData[1] = (char)aaa % 10000 / 1000;
	DisplayData[2] = '.';
	DisplayData[3] = (char)aaa % 100 / 10;
	DisplayData[4] =(char) aaa % 10;
	

}

int main()
{
	u8 i=0;
	u8 key;
//	u8 k=0;   
//	u8 k_2= 0;
	
//	int aaa=0;
		float temper=0;
	
	SysTick_Init(72);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //中断优先级分组 分2组
	LED_Init();
	USART1_Init(9600);
	KEY_Init();
	
	AT24CXX_Init();

	
	while(AT24CXX_Check())  //检测AT24C02是否正常
	{
		printf("AT24C02检测不正常!\r\n");
		delay_ms(500);
	}
	printf("AT24C02检测正常!\r\n");
	
	
		while(DS18B20_Init())   //检测温度传感器是否正常
	{
		printf("DS18B20检测失败，请插好!\r\n");
		delay_ms(500);
	}
	printf("DS18B20检测成功!\r\n");
	
	
	
	while(1)
	{
	//	temper=DS18B20_GetTemperture();
		
		
		key=KEY_Scan(0);
		if(key==KEY1_VALUE)
		{
			
		
		temper=	DS18B20_GetTemperture();

			sprintf(DisplayData, "%.2f", temper);  // 将浮点数保留两位小数并转换为字符串

			for (i=0;i<6;i++)			
			{
				
					AT24CXX_WriteOneByte(i,DisplayData[i]); 

			}
		    
			printf("写入的温度是：%s\r\n",DisplayData);
			
	
		}

		
		
			if(key==KEY2_VALUE)
		{
	
		
			for (i=0;i<6;i++)			
			{
		
				r[i]=AT24CXX_ReadOneByte(i);
			}
		    printf("读取的温度是：%s\r\n",r);
			
			
		}
		
			
			
			i++;
		if(i%20==0)
		{
			led1=!led1;
		}
		
		delay_ms(10);
			
				
		}
		  
		
		
		
		
		}
		
		
		
		
	


