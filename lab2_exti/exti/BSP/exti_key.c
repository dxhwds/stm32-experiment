#include "exti_key.h"
#include "misc.h"


void EXTI_Key_Init(void)
{
    
   
    GPIO_InitTypeDef GPIO_InitStructure;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO,ENABLE);//����PA3��PA4��ʱ�ӣ�����������ʱ��
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4;
	  
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOB,&GPIO_InitStructure);//GPIO��ʼ������:PA3��PA4
	
	/*
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	  GPIO_Init(GPIOA,&GPIO_InitStructure);//GPIO��ʼ������PA0
	*/
	
	  
    
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
   
    
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);//NVIC��ʼ������
    
		
   
    NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure); //NVIC��ʼ������
    
		
	
    EXTI_InitTypeDef EXTI_InitStructure;
	
 
    EXTI_ClearITPendingBit(EXTI_Line3&EXTI_Line4); //����ж���·3��44�Ĺ���
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource3);//�ⲿ�ж����ú�����������GPIO���ж�
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource4);//�ⲿ�ж����ú�����������GPIO���ж�
     
		 
    EXTI_InitStructure.EXTI_Line = EXTI_Line3;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
		EXTI_InitStructure.EXTI_LineCmd = ENABLE ;
		
    EXTI_Init(&EXTI_InitStructure);//ʹ���ⲿ�ж���·3
                
    EXTI_InitStructure.EXTI_Line = EXTI_Line4;//ʹ���ⲿ�ж���·4
    EXTI_Init(&EXTI_InitStructure);

}
    


  
