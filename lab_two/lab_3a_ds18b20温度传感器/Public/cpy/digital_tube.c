#include "digital_tube.h"

//unsigned char smgduan[] ={0xc0, 0xf9,0xa4, 0xb0, 0x99, 0x92, 0x82, 
//									0xf8,0x80, 0x90, 0x88, 0x83, 0xc6,0xa1, 0x86, 0x8e};//���������  

unsigned char code[] ={0x40, 0x79,0x24, 0x30, 0x19, 0x12, 0x02, 
									0x78,0x00, 0x10, 0x08, 0x03, 0x46,0x21, 0x06, 0x0e};//��������� ��ʾ�� 									
									
unsigned char dynamic_code[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71}; //���������  ��Ҫ��ʾ��ģ������λ��һ����
									
/*******************************************************************************
*������ԭ�ͣ�void Digital_Tube_Pin_Init(void)
*�����Ĺ��ܣ���������ų�ʼ��
*�����Ĳ�����None
*��������ֵ��None
*������˵����
*������д�ߣ���
*������д���ڣ�2022/2/25
*�����İ汾�ţ�V1.0
********************************************************************************/
void Digital_Tube_Pin_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	//��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);

	//�������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | 
																GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	GPIO_SetBits(GPIOB, GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | 
											GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
}	

/*******************************************************************************
*������ԭ�ͣ�void Digital_Tube_Display(GPIO_TypeDef* GPIOx,u8 val)
	@ u8 val����ʾ��ֵ
*��������ֵ��None
*������˵����
*������д�ߣ���
*������д���ڣ�2022/2/26
*�����İ汾�ţ�V1.0
********************************************************************************/
void Digital_Tube_Display(GPIO_TypeDef* GPIOx,u8 val)
{
	uint16_t display_val = val << 8;
	
	GPIO_Write(GPIOx,display_val);
}
	

