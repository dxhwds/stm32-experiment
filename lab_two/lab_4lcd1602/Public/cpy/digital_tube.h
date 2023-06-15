#ifndef _DIGITAL_TUBE_H
#define _DIGITAL_TUBE_H

#include "stm32f10x.h"
#include "stdio.h"

void Digital_Tube_Pin_Init(void);
void Digital_Tube_Display(GPIO_TypeDef* GPIOx,u8 val); 

extern unsigned char code[];
extern unsigned char dynamic_code[];

#endif
