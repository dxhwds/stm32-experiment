#ifndef __LED_H
#define __LED_H

#include "stm32f10x.h"

void LED_Init(void);

#define LED2_REV GPIO_WriteBit(GPIOE, GPIO_Pin_5,(BitAction)(1-(GPIO_ReadOutputDataBit(GPIOE, GPIO_Pin_5))))
#endif


