#ifndef _beep_H
#define _beep_H

#include "system.h"

/*  ������ʱ�Ӷ˿ڡ����Ŷ��� */
#define BEEP_PORT 			GPIOA   
#define BEEP_PIN 			GPIO_Pin_10
#define BEEP_PORT_RCC		RCC_APB2Periph_GPIOA

#define beep PAout(5)

void BEEP_Init(void);

#endif
