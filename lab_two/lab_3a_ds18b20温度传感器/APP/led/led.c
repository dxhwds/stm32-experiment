#include "led.h"
#include "TIM3_PWM.h"
 u16 ccr=100;   //ֱ�����


void LED_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;//����ṹ�����
	
	RCC_APB2PeriphClockCmd(LED_PORT_RCC,ENABLE);
	
//	GPIO_InitStructure.GPIO_Pin=LED_PIN;  //ѡ����Ҫ���õ�IO��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7|GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;	 //�����������ģʽ
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	  //���ô�������
	GPIO_Init(LED_PORT,&GPIO_InitStructure); 	   /* ��ʼ��GPIO */
	
	
	GPIO_SetBits(GPIOA,GPIO_Pin_7);
		GPIO_ResetBits(GPIOA,GPIO_Pin_6);
//	GPIO_ResetBits(LED_PORT,GPIO_Pin_0); 
//	GPIO_SetBits(LED_PORT,GPIO_Pin_1);
}

void contr(float temp)
{
		if(temp>=29)
		{
			GPIO_SetBits(GPIOB,GPIO_Pin_7);
		//	ccr = (temp-29)*100;
	//	TIM_SetCompare2(TIM3,ccr);//����ccr�Ĵ�����ֵ
		
		}

		if(temp<=15)
		{
						GPIO_ResetBits(GPIOB,GPIO_Pin_7);
		//TIM_SetCompare2(TIM3,0);//����ccr�Ĵ�����ֵ
		
		}

}


