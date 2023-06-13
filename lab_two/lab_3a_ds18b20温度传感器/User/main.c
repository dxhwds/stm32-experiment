#include "system.h"
#include "SysTick.h"
#include "led.h"
#include "usart.h"
#include "ds18b20.h"

#include "TIM3_PWM.h"

#include "main.h"
#include "beep.h"
void bee()
{
	int ddd= 0;
	
	while(1)
			
		{
		
		ddd++;
	
			beep=!beep;
	
		
		delay_us(10);
		
		}
}




u8 DisplayData[8];
u8  smgduan[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
void datapros(float temp) 	 
{
	int aaa;
   	float tp;  
	if(temp< 0)				//���¶�ֵΪ����
  	{
		DisplayData[0] = 0x40; 	  //   -

		tp=temp;
		
		aaa=tp*100;	      
	
 
  	}
 	else
  	{			
		DisplayData[0] = 0x00;
		tp=temp;//��Ϊ���ݴ�����С�������Խ��¶ȸ���һ�������ͱ���
		
    aaa=tp*100;	
	
	}               
	DisplayData[1] = smgduan[aaa / 10000];
	DisplayData[2] = smgduan[aaa % 10000 / 1000];
	DisplayData[3] = smgduan[aaa % 1000 / 100] | 0x80;
	DisplayData[4] = smgduan[aaa % 100 / 10];
	DisplayData[5] = smgduan[aaa % 10];
	

}


int aaa;


int main()
{
	u8 i=0;
	u8 a =0;

	float temper;
//	int bbb;
	
	SysTick_Init(72);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //�ж����ȼ����� ��2��
	LED_Init();
	USART1_Init(9600);
	
	//����ܲ���
	Init_74HC138_Pin();
	Digital_Tube_Pin_Init();
	
	
	//ֱ���������
	//TIM3_PWM_Init(899,0);
	
		BEEP_Init();
	
	
	
	
	
	
	while(DS18B20_Init())
	{
		printf("DS18B20���ʧ�ܣ�����!\r\n");
		delay_ms(500);
	}
	printf("DS18B20���ɹ�!\r\n");
	
	
	while(1)
	{	
				datapros(DS18B20_GetTemperture());
			for (a = 0; a < 6;a++) {
				Control_Tube_Display(a);
				Digital_Tube_Display(GPIOB,DisplayData[a]);
				delay_ms(2);
			}
		
			
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
			

		aaa=temper*100;
		//ֱ�������ֵ����
//		contr(bbb);
		

		if(aaa>=3000)
		{
				GPIO_SetBits(GPIOA,GPIO_Pin_6);
		GPIO_ResetBits(GPIOA,GPIO_Pin_7);
		}

		if(aaa<=2900)
		{
			
					
		GPIO_ResetBits(GPIOA,GPIO_Pin_6);
			
			
			GPIO_SetBits(GPIOA,GPIO_Pin_7);
		
		}
		



	
		
			
			
	}
	
	
	
	
	
	
	
	

}
