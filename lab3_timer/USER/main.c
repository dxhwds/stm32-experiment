#include "Timer.h"
#include "TIM3_PWM.h"
#include "led.h"
#include "stm32f10x.h"

sbit LSA PAout(2)  	//D1ָʾ�����ӵ���PA0�ܽ�
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
					0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};//��ʾ0~F��ֵ
void DigDisplay(int aaa,int bbb,int ccc,int ddd,int eee,int fff,int ggg,int hhh)
{
	u8 i;
	for(i=0;i<8;i++)
	{
		switch(i)	 //λѡ��ѡ�����������ܣ�
		{
			case(0):
				LSA=0;LSB=0;LSC=0; break;//��ʾ��0λ
			//P0=smgduan[i];//���Ͷ���
			case(1):
				LSA=1;LSB=0;LSC=0; break;//��ʾ��1λ
			//P0=smgduan[i];//���Ͷ���
			case(2):
				LSA=0;LSB=1;LSC=0; break;//��ʾ��2λ
			/P0=smgduan[i];//���Ͷ���
			case(3):
				LSA=1;LSB=1;LSC=0; break;//��ʾ��3λ
			//P0=smgduan[i];//���Ͷ���
			case(4):
				LSA=0;LSB=0;LSC=1; break;//��ʾ��4λ
			//P0=smgduan[i];//���Ͷ���
			case(5):
				LSA=1;LSB=0;LSC=1; break;//��ʾ��5λ
			//P0=smgduan[i];//���Ͷ���
			case(6):
				LSA=0;LSB=1;LSC=1; break;//��ʾ��6λ
			//P0=smgduan[i];//���Ͷ���
			case(7):
				LSA=1;LSB=1;LSC=1; break;//��ʾ��7λ	
			//P0=smgduan[i];//���Ͷ���
		}
		
		delay(100); //���һ��ʱ��ɨ��	
	//	P0=0x00;//����
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






					


