#include "TIM3_PWM.h"
#include "system.h"
#include "SysTick.h"
#include "led.h"
#include "usart.h"
#include "hwjs.h"

u8 smgduan[16]={0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07,
             0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};//0~F 数码管段选数据

						 
						 
void DigDisplay(int aaa,int bbb,int ccc,int ddd,int eee,int fff,int ggg,int hhh)
{
	u8 i;
	for(i=0;i<8;i++)
	{
		switch(i)	 //位选，选择点亮的数码管，
		{
			case(0):
				//LSA=0;LSB=0;LSC=0; break;//显示第0位
			GPIO_WriteBit(GPIOA,GPIO_Pin_0,(BitAction)(0));GPIO_WriteBit(GPIOA,GPIO_Pin_1,(BitAction)(0));GPIO_WriteBit(GPIOA,GPIO_Pin_2,(BitAction)(0));
				GPIO_Write(GPIOB,(u16)(~smgduan[aaa])<<8);
			
			
			
			case(1):
				//LSA=1;LSB=0;LSC=0; break;//显示第1位
				GPIO_WriteBit(GPIOA,GPIO_Pin_0,(BitAction)(1));GPIO_WriteBit(GPIOA,GPIO_Pin_1,(BitAction)(0));GPIO_WriteBit(GPIOA,GPIO_Pin_2,(BitAction)(0));
			GPIO_Write(GPIOB,(u16)(~smgduan[bbb]));//发送段码
			
			
			
			case(2):
				//LSA=0;LSB=1;LSC=0; break;//显示第2位
				GPIO_WriteBit(GPIOA,GPIO_Pin_0,(BitAction)(0));GPIO_WriteBit(GPIOA,GPIO_Pin_1,(BitAction)(1));GPIO_WriteBit(GPIOA,GPIO_Pin_2,(BitAction)(0));
				GPIO_Write(GPIOB,(u16)(~smgduan[ccc]<<8));//发送段码
			
			
			
			case(3):
				//LSA=1;LSB=1;LSC=0; break;//显示第3位
			GPIO_WriteBit(GPIOA,GPIO_Pin_0,(BitAction)(1));GPIO_WriteBit(GPIOA,GPIO_Pin_1,(BitAction)(1));GPIO_WriteBit(GPIOA,GPIO_Pin_2,(BitAction)(0));			
				GPIO_Write(GPIOB,(u16)(~smgduan[ddd])<<8<<8);//发送段码
			
			
			
			case(4):
				//LSA=0;LSB=0;LSC=1; break;//显示第4位
				GPIO_WriteBit(GPIOA,GPIO_Pin_0,(BitAction)(0));GPIO_WriteBit(GPIOA,GPIO_Pin_1,(BitAction)(0));GPIO_WriteBit(GPIOA,GPIO_Pin_2,(BitAction)(1));
				GPIO_Write(GPIOB,(u16)(~smgduan[eee])<<8);//发送段码
			
			
			
			case(5):
				//LSA=1;LSB=0;LSC=1; break;//显示第5位
				GPIO_WriteBit(GPIOA,GPIO_Pin_0,(BitAction)(1));GPIO_WriteBit(GPIOA,GPIO_Pin_1,(BitAction)(0));GPIO_WriteBit(GPIOA,GPIO_Pin_2,(BitAction)(1));
				GPIO_Write(GPIOB,(u16)(~smgduan[fff])<<8);//发送段码
			
			
			
			case(6):
				//LSA=0;LSB=1;LSC=1; break;//显示第6位
				GPIO_WriteBit(GPIOA,GPIO_Pin_0,(BitAction)(0));GPIO_WriteBit(GPIOA,GPIO_Pin_1,(BitAction)(1));GPIO_WriteBit(GPIOA,GPIO_Pin_2,(BitAction)(1));
				GPIO_Write(GPIOB,(u16)(~smgduan[ggg])<<8);//发送段码
			
			
			
			case(7):
				//LSA=1;LSB=1;LSC=1; break;//显示第7位	
				GPIO_WriteBit(GPIOA,GPIO_Pin_0,(BitAction)(1));GPIO_WriteBit(GPIOA,GPIO_Pin_1,(BitAction)(1));GPIO_WriteBit(GPIOA,GPIO_Pin_2,(BitAction)(1));
			GPIO_Write(GPIOB,(u16)(~smgduan[hhh])<<8);//发送段码
			
			
			
		}
		
			delay_ms(1000); //间隔一段时间扫描	
			//GPIO_Write(GPIOB,0X00<<8);
	}
}




int main()
{
	int sum = 0;
  u16 ccr=100;
//	u8 Date1=0;
//	int d =100;    //单次调节转速
	TIM3_PWM_Init(899,0);
	SysTick_Init(72);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //中断优先级分组 分2组
	SMG_Init();
	Hwjs_Init();
	LED_Init();
	
	
	while(1)
	{
		//DigDisplay(0,0,0,0,0, ccr/100,0,0);
		
//		GPIO_WriteBit(GPIOA,GPIO_Pin_0,(BitAction)(0));GPIO_WriteBit(GPIOA,GPIO_Pin_1,(BitAction)(0));GPIO_WriteBit(GPIOA,GPIO_Pin_2,(BitAction)(0));	
		
		
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
			case 0x68:printf("6");printf("Key:%x, cnt:%d\n", hw_jsm, hw_jsbz);			ccr=600;								break;	 
				
			case 0x00FF5AA5:printf("7");printf("Key:%x, cnt:%d\n", hw_jsm, hw_jsbz);ccr=700;						break;
			case 0x00FF42BD:printf("8");printf("Key:%x, cnt:%d\n", hw_jsm, hw_jsbz);ccr=800;						break;
			case 0x00FF4AB5:printf("9");printf("Key:%x, cnt:%d\n", hw_jsm, hw_jsbz);ccr=900;						break;
			default: break;		 
		}
			
	//	Date1=hw_jsm;
			hw_jsm=0;		//接收码清零
		}
	
TIM_SetCompare2(TIM3,ccr);//设置ccr寄存器的值

		
	}

	
}


/*
void TIM3_IRQHandler(void)   
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) 
		{
		
        GPIO_WriteBit(GPIOB,GPIO_Pin_5,(BitAction)((1-GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5))));
            TIM_ClearITPendingBit(TIM3, TIM_IT_Update  ); 
		}
}

*/
