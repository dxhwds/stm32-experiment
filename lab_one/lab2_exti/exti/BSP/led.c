#include "led.h"
#include "stm32f10x.h"


void LED_Init(void)
{

	 
	 GPIO_InitTypeDef GPIO_InitStructure; //�ṹ������
	 
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE); //��ʹ��rcc����ʱ��
	 
	 GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;//GPIO��������
	 GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	 GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	 
	 GPIO_Init(GPIOA,&GPIO_InitStructure );//GPIO��ʼ��
	 
	
}
















