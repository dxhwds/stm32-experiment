#include "dynamic_digital_tube.h"

/*******************************************************************************
*������ԭ�ͣ�void Init_74HC138_Pin(void)
*�����Ĺ��ܣ�74HC138��������ʼ��
*�����Ĳ�����None
*��������ֵ��None
*������˵����
*������д�ߣ���
*������д���ڣ�2022/3/5
*�����İ汾�ţ�V1.0
********************************************************************************/
void Init_74HC138_Pin(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	//��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

	//�������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_SetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2);	
}

/*******************************************************************************
*������ԭ�ͣ�u8 Control_Tube_Display(u8 num)
*�����Ĺ��ܣ�������һ���������ʾ
*�����Ĳ�����
	@ u8 num���������� 0-7
*��������ֵ��
	0���ɹ� -1��ʧ��
*������˵����
*������д�ߣ���
*������д���ڣ�2022/3/5
*�����İ汾�ţ�V1.0
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
