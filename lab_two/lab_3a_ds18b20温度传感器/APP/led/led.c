#include "led.h"
#include "TIM3_PWM.h"
 u16 ccr=100;   //直流电机


void LED_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;//定义结构体变量
	
	RCC_APB2PeriphClockCmd(LED_PORT_RCC,ENABLE);
	
//	GPIO_InitStructure.GPIO_Pin=LED_PIN;  //选择你要设置的IO口
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7|GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;	 //设置推挽输出模式
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	  //设置传输速率
	GPIO_Init(LED_PORT,&GPIO_InitStructure); 	   /* 初始化GPIO */
	
	
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
	//	TIM_SetCompare2(TIM3,ccr);//设置ccr寄存器的值
		
		}

		if(temp<=15)
		{
						GPIO_ResetBits(GPIOB,GPIO_Pin_7);
		//TIM_SetCompare2(TIM3,0);//设置ccr寄存器的值
		
		}

}


