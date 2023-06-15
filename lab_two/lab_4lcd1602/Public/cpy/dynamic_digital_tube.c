#include "dynamic_digital_tube.h"

/*******************************************************************************
*函数的原型：void Init_74HC138_Pin(void)
*函数的功能：74HC138编码器初始化
*函数的参数：None
*函数返回值：None
*函数的说明：
*函数编写者：庆
*函数编写日期：2022/3/5
*函数的版本号：V1.0
********************************************************************************/
void Init_74HC138_Pin(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	//打开时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

	//推挽输出
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_SetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2);	
}

/*******************************************************************************
*函数的原型：u8 Control_Tube_Display(u8 num)
*函数的功能：控制哪一个数码管显示
*函数的参数：
	@ u8 num：数码管序号 0-7
*函数返回值：
	0：成功 -1：失败
*函数的说明：
*函数编写者：庆
*函数编写日期：2022/3/5
*函数的版本号：V1.0
********************************************************************************/
int Control_Tube_Display(u8 num)
{
	u8 bit[5] = {0};
	u8 i = 0;
	
	if (num > 7)
			return -1;	
	
	while (num > 0) 
	{
		bit[i] = num % 2;
		i++;
		num  = num / 2;
	}
	
	GPIO_WriteBit(GPIOA,GPIO_Pin_0,(BitAction)bit[0]);
	GPIO_WriteBit(GPIOA,GPIO_Pin_1,(BitAction)bit[1]);
	GPIO_WriteBit(GPIOA,GPIO_Pin_2,(BitAction)bit[2]);
	
	/*switch (num) 
	{
		case 0:
			GPIO_WriteBit(GPIOA,GPIO_Pin_0,0);
			GPIO_WriteBit(GPIOA,GPIO_Pin_1,0);
			GPIO_WriteBit(GPIOA,GPIO_Pin_2,0);
		break;
		case 1:
			GPIO_WriteBit(GPIOA,GPIO_Pin_0,1);
			GPIO_WriteBit(GPIOA,GPIO_Pin_1,0);
			GPIO_WriteBit(GPIOA,GPIO_Pin_2,0);
		break;
		case 2:
			GPIO_WriteBit(GPIOA,GPIO_Pin_0,0);
			GPIO_WriteBit(GPIOA,GPIO_Pin_1,1);
			GPIO_WriteBit(GPIOA,GPIO_Pin_2,0);
		break;
		case 3:
			GPIO_WriteBit(GPIOA,GPIO_Pin_0,1);
			GPIO_WriteBit(GPIOA,GPIO_Pin_1,1);
			GPIO_WriteBit(GPIOA,GPIO_Pin_2,0);
		break;
		case 4:
			GPIO_WriteBit(GPIOA,GPIO_Pin_0,0);
			GPIO_WriteBit(GPIOA,GPIO_Pin_1,0);
			GPIO_WriteBit(GPIOA,GPIO_Pin_2,1);
		break;
		case 5:
			GPIO_WriteBit(GPIOA,GPIO_Pin_0,1);
			GPIO_WriteBit(GPIOA,GPIO_Pin_1,0);
			GPIO_WriteBit(GPIOA,GPIO_Pin_2,1);
		break;
		case 6:
			GPIO_WriteBit(GPIOA,GPIO_Pin_0,0);
			GPIO_WriteBit(GPIOA,GPIO_Pin_1,1);
			GPIO_WriteBit(GPIOA,GPIO_Pin_2,1);
		break;
		case 7:
			GPIO_WriteBit(GPIOA,GPIO_Pin_0,1);
			GPIO_WriteBit(GPIOA,GPIO_Pin_1,1);
			GPIO_WriteBit(GPIOA,GPIO_Pin_2,1);
		break;
							
	}*/
	
	
	return 0;
}
