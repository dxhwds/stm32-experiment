#include "stm32f10x.h"
#include "led.h"
#include "exti_key.h"
#include "Delay.h"
#define speed 100
void sb_1()
{
		GPIO_Write(GPIOA, ~0x0000);
		GPIO_Write(GPIOA, ~0x0001);	//GPIOA的端口状态，下同：0000 0000 0000 0001
		Delay_ms(speed);
		
		GPIO_Write(GPIOA, ~0x0002);	//0000 0000 0000 0010
		Delay_ms(speed);
		
		GPIO_Write(GPIOA, ~0x0004);	//0000 0000 0000 0100
		Delay_ms(speed);
		
		GPIO_Write(GPIOA, ~0x0008);	//0000 0000 0000 1000
		Delay_ms(speed);
		
		GPIO_Write(GPIOA, ~0x0010);	//0000 0000 0001 0000
		Delay_ms(speed);
		
		GPIO_Write(GPIOA, ~0x0020);	//0000 0000 0010 0000
		Delay_ms(speed);
		
		GPIO_Write(GPIOA, ~0x0040);	//0000 0000 0100 0000
		Delay_ms(speed);
		
		GPIO_Write(GPIOA, ~0x0080);	//0000 0000 1000 0000
		Delay_ms(speed);




}
void sb_2()
{
	
		GPIO_Write(GPIOA, ~0x0000);
	
		GPIO_Write(GPIOA, ~0x0080);	//0000 0000 1000 0000
		Delay_ms(speed);
		GPIO_Write(GPIOA, ~0x0040);	//0000 0000 0100 0000
		Delay_ms(speed);
	
		GPIO_Write(GPIOA, ~0x0020);	//0000 0000 0010 0000
		Delay_ms(speed);
		GPIO_Write(GPIOA, ~0x0010);	//0000 0000 0001 0000
		Delay_ms(speed);
	
		GPIO_Write(GPIOA, ~0x0008);	//0000 0000 0000 1000
		Delay_ms(speed);
	
	
		GPIO_Write(GPIOA, ~0x0004);	//0000 0000 0000 0100
		Delay_ms(speed);
	
	
		GPIO_Write(GPIOA, ~0x0002);	//0000 0000 0000 0010
		Delay_ms(speed);
	
	
		GPIO_Write(GPIOA, ~0x0001);	//GPIOA的端口状态，下同：0000 0000 0000 0001
		Delay_ms(speed);
		
	


}



int main(void)
{
    LED_Init();
    
    
    EXTI_Key_Init();
	
     GPIO_Write(GPIOA, ~0x0000);
    while(1)
    {
			/*
	if(a==1)
	{
		sb_1();
	
	}
	if(a==0)
	{
	sb_2();
	}
	*/
			
    }
    
}

//中断函数配置

void EXTI3_IRQHandler(void)
{
    if(EXTI_GetITStatus(EXTI_Line3) != RESET)
    {
			
			//	GPIO_WriteBit(GPIOB,GPIO_Pin_5,(BitAction)((1-GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_5))));
			Delay_ms(300);
		sb_1();
			GPIO_Write(GPIOA, ~0x0000);
        
        EXTI_ClearITPendingBit(EXTI_Line3);
    }

}

void EXTI4_IRQHandler(void)
{
    if(EXTI_GetITStatus(EXTI_Line4) != RESET)
    {
		//	 GPIO_WriteBit(GPIOB,GPIO_Pin_6,(BitAction)((1-GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_6))));
			
			
			
			
			Delay_ms(300);
			sb_1();
      sb_2();
			GPIO_Write(GPIOA, ~0x0000);
        EXTI_ClearITPendingBit(EXTI_Line4);
    }

}


