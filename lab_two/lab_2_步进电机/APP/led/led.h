#ifndef _led_H
#define _led_H

#include "stm32f10x.h"



/*  �����ʱ�Ӷ˿ڡ����Ŷ��� */
#define SMG_PORT 			GPIOB   
#define SMG_PIN 			(GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15)
#define SMG_PORT_RCC		RCC_APB2Periph_GPIOB


void SMG_Init(void);//����ܳ�ʼ��
void LED_Init(void);

#define LED_PORT 			GPIOA   
#define LED_PIN 			GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4
#define LED_PORT_RCC		RCC_APB2Periph_GPIOA

#define led1 PAout(0)  	//D1ָʾ�����ӵ���PA0�ܽ�


#endif
