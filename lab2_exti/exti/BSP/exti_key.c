#include "exti_key.h"
#include "misc.h"


void EXTI_Key_Init(void)
{
    
   
    GPIO_InitTypeDef GPIO_InitStructure;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO,ENABLE);//开启PA3和PA4的时钟，并开启复用时钟
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4;
	  
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOB,&GPIO_InitStructure);//GPIO初始化配置:PA3和PA4
	
	/*
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	  GPIO_Init(GPIOA,&GPIO_InitStructure);//GPIO初始化配置PA0
	*/
	
	  
    
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
   
    
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);//NVIC初始化配置
    
		
   
    NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure); //NVIC初始化配置
    
		
	
    EXTI_InitTypeDef EXTI_InitStructure;
	
 
    EXTI_ClearITPendingBit(EXTI_Line3&EXTI_Line4); //清楚中断线路3和44的挂起
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource3);//外部中断配置函数，，连接GPIO和中断
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource4);//外部中断配置函数，，连接GPIO和中断
     
		 
    EXTI_InitStructure.EXTI_Line = EXTI_Line3;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
		EXTI_InitStructure.EXTI_LineCmd = ENABLE ;
		
    EXTI_Init(&EXTI_InitStructure);//使能外部中断线路3
                
    EXTI_InitStructure.EXTI_Line = EXTI_Line4;//使能外部中断线路4
    EXTI_Init(&EXTI_InitStructure);

}
    


  
