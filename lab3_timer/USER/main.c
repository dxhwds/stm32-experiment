#include "Timer.h"
#include "TIM3_PWM.h"
#include "led.h"
#include "stm32f10x.h"

sbit LSA PAout(2)  	//D1指示灯连接的是PA0管脚
sbit LSB PAout(3) 
sbit LSC PAout(4) 

/*
sbit LSA=PA^2;
sbit LSB=PA^3;
sbit LSC=PA^4;
*/
void delay(u32 nCount)
{
    for(;nCount !=0;nCount --);
}


u8 smgduan[17]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
					0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};//显示0~F的值
void DigDisplay(int aaa,int bbb,int ccc,int ddd,int eee,int fff,int ggg,int hhh)
{
	u8 i;
	for(i=0;i<8;i++)
	{
		switch(i)	 //位选，选择点亮的数码管，
		{
			case(0):
				LSA=0;LSB=0;LSC=0; break;//显示第0位
			//P0=smgduan[i];//发送段码
			case(1):
				LSA=1;LSB=0;LSC=0; break;//显示第1位
			//P0=smgduan[i];//发送段码
			case(2):
				LSA=0;LSB=1;LSC=0; break;//显示第2位
			/P0=smgduan[i];//发送段码
			case(3):
				LSA=1;LSB=1;LSC=0; break;//显示第3位
			//P0=smgduan[i];//发送段码
			case(4):
				LSA=0;LSB=0;LSC=1; break;//显示第4位
			//P0=smgduan[i];//发送段码
			case(5):
				LSA=1;LSB=0;LSC=1; break;//显示第5位
			//P0=smgduan[i];//发送段码
			case(6):
				LSA=0;LSB=1;LSC=1; break;//显示第6位
			//P0=smgduan[i];//发送段码
			case(7):
				LSA=1;LSB=1;LSC=1; break;//显示第7位	
			//P0=smgduan[i];//发送段码
		}
		
		delay(100); //间隔一段时间扫描	
	//	P0=0x00;//消隐
	}
}

int main(void)
{   
	
	   LED_Init();
     Timer_Init();
     TIM2_NVIC_Configuration();
     TIM3_PWM_Init(29999,36000);  
    	
	

}   

void TIM2_IRQHandler(void)
{
    if(TIM_GetITStatus(TIM2,TIM_IT_Update) != RESET)
    {
        GPIO_WriteBit(GPIOA,GPIO_Pin_0,(BitAction)((1-GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_0))));
        TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
    }
}






					


