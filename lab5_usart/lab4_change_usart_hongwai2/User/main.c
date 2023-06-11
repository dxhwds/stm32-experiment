#include "TIM3_PWM.h"
#include "system.h"
#include "SysTick.h"
#include "led.h"
#include "usart.h"
#include "hwjs.h"
#include <ctype.h>
u8 smgduan[16]={0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07,
             0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};//0~F ����ܶ�ѡ����

						 
u32 r;					 
void DigDisplay(int aaa,int bbb,int ccc,int ddd,int eee,int fff,int ggg,int hhh)
{
	u8 i;
	for(i=0;i<8;i++)
	{
		switch(i)	 //λѡ��ѡ�����������ܣ�
		{
			case(0):
				//LSA=0;LSB=0;LSC=0; break;//��ʾ��0λ
			GPIO_WriteBit(GPIOA,GPIO_Pin_0,(BitAction)(0));GPIO_WriteBit(GPIOA,GPIO_Pin_1,(BitAction)(0));GPIO_WriteBit(GPIOA,GPIO_Pin_2,(BitAction)(0));
				GPIO_Write(GPIOB,(u16)(~smgduan[aaa])<<8);
			
			
			
			case(1):
				//LSA=1;LSB=0;LSC=0; break;//��ʾ��1λ
				GPIO_WriteBit(GPIOA,GPIO_Pin_0,(BitAction)(1));GPIO_WriteBit(GPIOA,GPIO_Pin_1,(BitAction)(0));GPIO_WriteBit(GPIOA,GPIO_Pin_2,(BitAction)(0));
			GPIO_Write(GPIOB,(u16)(~smgduan[bbb]));//���Ͷ���
			
			
			
			case(2):
				//LSA=0;LSB=1;LSC=0; break;//��ʾ��2λ
				GPIO_WriteBit(GPIOA,GPIO_Pin_0,(BitAction)(0));GPIO_WriteBit(GPIOA,GPIO_Pin_1,(BitAction)(1));GPIO_WriteBit(GPIOA,GPIO_Pin_2,(BitAction)(0));
				GPIO_Write(GPIOB,(u16)(~smgduan[ccc]<<8));//���Ͷ���
			
			
			
			case(3):
				//LSA=1;LSB=1;LSC=0; break;//��ʾ��3λ
			GPIO_WriteBit(GPIOA,GPIO_Pin_0,(BitAction)(1));GPIO_WriteBit(GPIOA,GPIO_Pin_1,(BitAction)(1));GPIO_WriteBit(GPIOA,GPIO_Pin_2,(BitAction)(0));			
				GPIO_Write(GPIOB,(u16)(~smgduan[ddd])<<8<<8);//���Ͷ���
			
			
			
			case(4):
				//LSA=0;LSB=0;LSC=1; break;//��ʾ��4λ
				GPIO_WriteBit(GPIOA,GPIO_Pin_0,(BitAction)(0));GPIO_WriteBit(GPIOA,GPIO_Pin_1,(BitAction)(0));GPIO_WriteBit(GPIOA,GPIO_Pin_2,(BitAction)(1));
				GPIO_Write(GPIOB,(u16)(~smgduan[eee])<<8);//���Ͷ���
			
			
			
			case(5):
				//LSA=1;LSB=0;LSC=1; break;//��ʾ��5λ
				GPIO_WriteBit(GPIOA,GPIO_Pin_0,(BitAction)(1));GPIO_WriteBit(GPIOA,GPIO_Pin_1,(BitAction)(0));GPIO_WriteBit(GPIOA,GPIO_Pin_2,(BitAction)(1));
				GPIO_Write(GPIOB,(u16)(~smgduan[fff])<<8);//���Ͷ���
			
			
			
			case(6):
				//LSA=0;LSB=1;LSC=1; break;//��ʾ��6λ
				GPIO_WriteBit(GPIOA,GPIO_Pin_0,(BitAction)(0));GPIO_WriteBit(GPIOA,GPIO_Pin_1,(BitAction)(1));GPIO_WriteBit(GPIOA,GPIO_Pin_2,(BitAction)(1));
				GPIO_Write(GPIOB,(u16)(~smgduan[ggg])<<8);//���Ͷ���
			
			
			
			case(7):
				//LSA=1;LSB=1;LSC=1; break;//��ʾ��7λ	
				GPIO_WriteBit(GPIOA,GPIO_Pin_0,(BitAction)(1));GPIO_WriteBit(GPIOA,GPIO_Pin_1,(BitAction)(1));GPIO_WriteBit(GPIOA,GPIO_Pin_2,(BitAction)(1));
			GPIO_Write(GPIOB,(u16)(~smgduan[hhh])<<8);//���Ͷ���
			
			
			
		}
		
			delay_ms(1000); //���һ��ʱ��ɨ��	
			//GPIO_Write(GPIOB,0X00<<8);
	}
}





 u16 ccr=100;
int main()
{

	int sum = 0;
 
//	u8 Date1=0;
//	int d =100;    //���ε���ת��
	TIM3_PWM_Init(899,0);
	SysTick_Init(72);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //�ж����ȼ����� ��2��
	SMG_Init();
	Hwjs_Init();
	LED_Init();
	USART1_Init(115200);
	
	while(1)
	{

				
		sum = ccr/100;
		GPIO_Write(SMG_PORT,(u16)(~smgduan[sum])<<8);
		//delay_ms(1000);
		
		if(hw_jsbz==1)	//���������յ�
		{
			
			hw_jsbz=0;	   //���ܱ�־����

    	
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
			


			hw_jsm=0;		//����������
		}
		

		
TIM_SetCompare2(TIM3,ccr);//����ccr�Ĵ�����ֵ

		
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



void USART1_IRQHandler(void)                	//����1�жϷ������
{
	
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //�����ж�
	{
		hw_jsm =USART_ReceiveData(USART1);//(USART1->DR);	//��ȡ���յ�������
		hw_jsbz=1;
		/*
		if(65<=hw_jsm&&hw_jsm<=90)
		{
		
		hw_jsm+=32;
		
		}
		
		if(97<=hw_jsm&&hw_jsm<=122)
		{
		
		hw_jsm-=32;
		
		}
		*/
		if(hw_jsm == '0')
			{
				ccr=0;
			}
			if(hw_jsm == '1')
			{
				ccr=100;
			}
			if(hw_jsm == '2')
			{
				ccr=200;
			}
			if(hw_jsm == '3')
			{
				ccr=300;
			}
			if(hw_jsm == '4')
			{
				ccr=400;
			}
			
			if(hw_jsm == '5')
			{
				ccr=500;
			}
			
				if(hw_jsm == '6')
			{
				ccr=600;
			}
			
				if(hw_jsm == '7')
			{
				ccr=700;
			}
			
				if(hw_jsm == '8')
			{
				ccr=800;
			}
			
				if(hw_jsm == '9')
			{
				ccr=900;
			}
			

          if(islower(hw_jsm))
					{
							GPIO_SetBits(GPIOA,GPIO_Pin_5);
                printf("Ϩ��LED��\n");
					}
                
          if(isupper(hw_jsm))
						
					{
					GPIO_ResetBits(GPIOA,GPIO_Pin_5);
                printf("����LED�� \n");
					}
                
         
          //    printf("��������ȷ��ָ�NϨ��ƣ�Y������!\n");
          
		
		
		
		
		USART_SendData(USART1,hw_jsm);
		
		 USART_SendData(USART1, islower(hw_jsm) ? toupper(hw_jsm) : tolower(hw_jsm));
		while(USART_GetFlagStatus(USART1,USART_FLAG_TC) != SET);
	} 
	USART_ClearFlag(USART1,USART_FLAG_TC);
} 	

 

