#include "stm32f10x.h"
#include <stdio.h>
#include "Delay.h"
#include "led.h"
#include "USART_Init_Config.h"
u8 r;




int main(void)
{
//	char Temp = 'a';
	

	USART_Init_Config();
    
	while(1)
	{		/*
		 
		 USART_ClearFlag (USART1, USART_FLAG_TC);
   USART_SendData (USART1,Temp ) ;
		Delay_s(1);
  USART_ClearFlag (USART1, USART_FLAG_RXNE);
		*/
		
	}
		 
}


void USART1_IRQHandler(void)                	//����1�жϷ������
{
	
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //�����ж�
	{
		r =USART_ReceiveData(USART1);//(USART1->DR);	//��ȡ���յ�������
		USART_SendData(USART1,r);
		while(USART_GetFlagStatus(USART1,USART_FLAG_TC) != SET);
	} 
	USART_ClearFlag(USART1,USART_FLAG_TC);
}


