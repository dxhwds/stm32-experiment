#include "TIM3_PWM.h"
#include "system.h"
#include "SysTick.h"
#include "led.h"
#include "usart.h"
#include "hwjs.h"
#include <ctype.h>
u8 smgduan[16]={0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07,
             0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};//0~F 数码管段选数据


 u16 ccr=100;
int main()
{

	int sum = 0;
 
//	u8 Date1=0;
//	int d =100;    //单次调节转速
	TIM3_PWM_Init(899,0);
	SysTick_Init(72);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //中断优先级分组 分2组
	SMG_Init();
	Hwjs_Init();
	LED_Init();
	USART1_Init(9600);
	
	while(1)
	{

				
		sum = ccr/100;
		GPIO_Write(SMG_PORT,(u16)(~smgduan[sum])<<8);
		//delay_ms(1000);
		
		if(hw_jsbz==1)	//如果红外接收到
		{
			
			hw_jsbz=0;	   //接受标志清零

			switch(hw_jsm)
		{
			case 0x00:printf("POWER");printf("Key:%x, cnt:%d\n", hw_jsm, hw_jsbz);break;   
			case 0x80:printf("up");printf("Key:%x, cnt:%d\n", hw_jsm, hw_jsbz);break;	    
			case 0x40:printf("LED");printf("Key:%x, cnt:%d\n", hw_jsm, hw_jsbz);break;	    
			
			case 0x20:printf("left");printf("Key:%x, cnt:%d\n", hw_jsm, hw_jsbz);break;		 
			case 0xa0:printf("beep");printf("Key:%x, cnt:%d\n", hw_jsm, hw_jsbz);break;		  
			case 0x60:printf("right");printf("Key:%x, cnt:%d\n", hw_jsm, hw_jsbz);break;	   
			
			case 0x10:printf("TLEFT");printf("Key:%x, cnt:%d\n", hw_jsm, hw_jsbz);break;		  
			case 0x90:printf("down");printf("Key:%x, cnt:%d\n", hw_jsm, hw_jsbz);break;		  
			case 0x50:printf("TRIGHT");printf("Key:%x, cnt:%d\n", hw_jsm, hw_jsbz);break;		   
			
			case 0x30:printf("+");printf("Key:%x, cnt:%d\n", hw_jsm, hw_jsbz);break;		    
			case 0x00FF6897:printf("0");printf("Key:%x, cnt:%d\n", hw_jsm, hw_jsbz);ccr=0;      break;		  
			case 0x70:printf("-");printf("Key:%x, cnt:%d\n", hw_jsm, hw_jsbz);break;	   
			
			case 0x00FF30CF:printf("1");printf("Key:%x, cnt:%d\n", hw_jsm, hw_jsbz);ccr=100;						break;	    
			case 0x00FF18E7:printf("2");printf("Key:%x, cnt:%d\n", hw_jsm, hw_jsbz);ccr=200;						break;		    
			case 0x00FF7A85:printf("3");printf("Key:%x, cnt:%d\n", hw_jsm, hw_jsbz);ccr=300;						break;		    
			
			case 0x00FF10EF:printf("4");printf("Key:%x, cnt:%d\n", hw_jsm, hw_jsbz);ccr=400;						break;		  
			case 0x00FF38C7:printf("5");printf("Key:%x, cnt:%d\n", hw_jsm, hw_jsbz);ccr=500;						break;			   					
			case 0x00FF5AA5:printf("6");printf("Key:%x, cnt:%d\n", hw_jsm, hw_jsbz);			ccr=600;								break;	 
					
			case 0x00FF42BD:printf("7");printf("Key:%x, cnt:%d\n", hw_jsm, hw_jsbz);ccr=700;						break;
			case 0x00FF4AB5:printf("8");printf("Key:%x, cnt:%d\n", hw_jsm, hw_jsbz);ccr=800;						break;
			case 0x00FF52AD:printf("9");printf("Key:%x, cnt:%d\n", hw_jsm, hw_jsbz);ccr=900;					break;
			default: break;		 
		}
			hw_jsm=0;		//接收码清零
		}
		

		
TIM_SetCompare2(TIM3,ccr);//设置ccr寄存器的值

		
	}

	
}



void TIM3_IRQHandler(void)   
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) 
		{
		
        GPIO_WriteBit(GPIOB,GPIO_Pin_5,(BitAction)((1-GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5))));
            TIM_ClearITPendingBit(TIM3, TIM_IT_Update  ); 
		}
}



void USART1_IRQHandler(void)                	//串口1中断服务程序
{
	
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //接收中断
	{
		hw_jsm =USART_ReceiveData(USART1);//(USART1->DR);	//读取接收到的数据
		hw_jsbz=1;
		
          if(islower(hw_jsm))
					{
							GPIO_SetBits(GPIOA,GPIO_Pin_5);
                printf("熄灭LED灯\n");
					}
                
          if(isupper(hw_jsm))
						
					{
					GPIO_ResetBits(GPIOA,GPIO_Pin_5);
                printf("点亮LED灯 \n");
					}
			if(hw_jsm == '0')	ccr=0;
			if(hw_jsm == '1')ccr=100;
			if(hw_jsm == '2')ccr=200;
			if(hw_jsm == '3')ccr=300;
			if(hw_jsm == '4')ccr=400;
			if(hw_jsm == '6')ccr=600;
			if(hw_jsm == '7')ccr=700;
			if(hw_jsm == '8')ccr=800;
			if(hw_jsm == '9')ccr=900;

		
		 USART_SendData(USART1, islower(hw_jsm) ? toupper(hw_jsm) : tolower(hw_jsm));
				USART_SendData(USART1,hw_jsm);	
		while(USART_GetFlagStatus(USART1,USART_FLAG_TC) != SET);
	} 
	USART_ClearFlag(USART1,USART_FLAG_TC);
} 	

 

