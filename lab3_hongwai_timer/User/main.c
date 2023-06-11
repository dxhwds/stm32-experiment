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
			//printf("红外接收码 %0.8X\r\n",hw_jsm);	//打印调试
		/*	
			if(Date1==hw_jsm)//ccr寄存器的值变大，灯变强,相同变强
			{
				ccr+=d;
			}

			if(Date1!=hw_jsm)//ccr寄存器的值变大，灯变弱
			{
				ccr-=d;
			}
			
			if(ccr==1000)//亮度达到最大，反转
			{
				d= -d;
				//ccr=0;
			
			}
			
			if(ccr==0)//亮度最低，反转
			{
				d=-d;
				//ccr = 1000;
			
			}
			*/
    	
			if(hw_jsm == 0x00FF6897)
			{
				ccr=0;
			}
			if(hw_jsm == 0x00FF30CF)
			{
				ccr=100;
			}
			if(hw_jsm == 0x00FF18E7)
			{
				ccr=200;
			}
			if(hw_jsm == 0x00FF7A85)
			{
				ccr=300;
			}
			if(hw_jsm == 0x00FF10EF)
			{
				ccr=400;
			}
			
			if(hw_jsm == 0x00FF38C7)
			{
				ccr=500;
			}
			
				if(hw_jsm == 0x00FF5AA5)
			{
				ccr=600;
			}
			
				if(hw_jsm == 0x00FF42BD)
			{
				ccr=700;
			}
			
				if(hw_jsm == 0x00FF4AB5)
			{
				ccr=800;
			}
			
				if(hw_jsm == 0x00FF52AD)
			{
				ccr=900;
			}
			

	//	Date1=hw_jsm;
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


