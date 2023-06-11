#include "led.h"
#include "stm32f10x.h"


void LED_Init(void)
{

	 
	 GPIO_InitTypeDef GPIO_InitStructure; //结构体命名
	 
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE); //是使能rcc外设时钟
	 
	 GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;//GPIO参数配置
	 GPIO_InitStructure.GPIO_Pin=GPIO_Pin_All;
	 GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	 
	 GPIO_Init(GPIOA,&GPIO_InitStructure );//GPIO初始化
	 
	
}
















