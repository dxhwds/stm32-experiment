/*******************************************************************************
* ʵ������  	: DS18B20�¶ȴ�����ʵ��
* ʵ��˵��  : 
* ����˵��  : 1��DS18B20�¶ȴ�����ģ��-->��Ƭ�������ܽţ�STM32���İ壩
					J14-->P37��PA15��
* ʵ������	: �¶ȴ�������ú��ڴ��������ϻ���ʾ���ɹ�������ʾ�����¶�ֵ�����İ���
				D1ָʾ����˸
*******************************************************************************/
#include "system.h"
#include "SysTick.h"
#include "led.h"
#include "usart.h"
#include "ds18b20.h"
#include "1602.h"
u8 Disp[]=" Pechin Science ";




unsigned char fen=10,miao=50;//��ʼʱ��ֵ

void display_data(void)///��ʾ���ڡ�ʱ�䡢����
{
	LcdWriteCom(0x80); //��һ��
	LcdWritestr("Hello World!");	
	LcdWriteData(fen/10+0x30);
	LcdWriteData(fen%10+0x30);	
  
	LcdWriteCom(0xc0);	 //�ڶ���
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
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //�ж����ȼ����� ��2��
	LED_Init();
	USART1_Init(9600);
	
		
  LCD1602_Init();

	
	while(DS18B20_Init())
	{
		printf("DS18B20���ʧ�ܣ�����!\r\n");
		delay_ms(500);
	}
	printf("DS18B20���ɹ�!\r\n");
	
	


	
	
	
	while(1)
	{
		
	
	LcdWriteCom(0x80); //��һ��	
		
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
				printf("�����¶�Ϊ��-");
			}
			else
			{
				printf("�����¶�Ϊ�� ");
			}
			printf("%.2f��C\r\n",temper);
		
		}
		delay_ms(10);
	}
}
