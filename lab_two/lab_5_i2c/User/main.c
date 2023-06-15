/*******************************************************************************
* ʵ������  	: ��������ʵ��
* ʵ��˵��  : 
* ����˵��  : 1����������ģ��-->��Ƭ�������ܽţ�STM32���İ壩
					K1-->P00��PB8��
					K2-->P01��PB9��
			  2��EEPROMģ��-->��Ƭ�������ܽţ�STM32���İ壩
					SCL-->P02��PB10��
					SDA-->P03��PB11��	
* ʵ������	: ���ȼ�⿪������AT24C02�Ƿ��������ڴ��������������Ӧ��ʾ��Ϣ��Ȼ����K1��
				��EEPROM����д�룬ÿ��һ�����ݼ�1д�룬����K2�����ж�ȡ��д��Ͷ�ȡ�Ĺ�����
				�ڴ��������Ͼ�����ʾ��Ӧ����ʾ��Ϣ�����İ���D1ָʾ����˸
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
/*	if(temp< 0)				//���¶�ֵΪ����
  	{
		DisplayData[0] = '-';//0x40; 	  //   -

		tp=temp;
		
		aaa=tp*100;	      
	
 
  	}
 	else
  	{			
		DisplayData[0] = ' ';//0x00;
		tp=temp;//��Ϊ���ݴ�����С�������Խ��¶ȸ���һ�������ͱ���
		
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
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //�ж����ȼ����� ��2��
	LED_Init();
	USART1_Init(9600);
	KEY_Init();
	
	AT24CXX_Init();

	
	while(AT24CXX_Check())  //���AT24C02�Ƿ�����
	{
		printf("AT24C02��ⲻ����!\r\n");
		delay_ms(500);
	}
	printf("AT24C02�������!\r\n");
	
	
		while(DS18B20_Init())   //����¶ȴ������Ƿ�����
	{
		printf("DS18B20���ʧ�ܣ�����!\r\n");
		delay_ms(500);
	}
	printf("DS18B20���ɹ�!\r\n");
	
	
	
	while(1)
	{
	//	temper=DS18B20_GetTemperture();
		
		
		key=KEY_Scan(0);
		if(key==KEY1_VALUE)
		{
			
		
		temper=	DS18B20_GetTemperture();

			sprintf(DisplayData, "%.2f", temper);  // ��������������λС����ת��Ϊ�ַ���

			for (i=0;i<6;i++)			
			{
				
					AT24CXX_WriteOneByte(i,DisplayData[i]); 

			}
		    
			printf("д����¶��ǣ�%s\r\n",DisplayData);
			
	
		}

		
		
			if(key==KEY2_VALUE)
		{
	
		
			for (i=0;i<6;i++)			
			{
		
				r[i]=AT24CXX_ReadOneByte(i);
			}
		    printf("��ȡ���¶��ǣ�%s\r\n",r);
			
			
		}
		
			
			
			i++;
		if(i%20==0)
		{
			led1=!led1;
		}
		
		delay_ms(10);
			
				
		}
		  
		
		
		
		
		}
		
		
		
		
	


