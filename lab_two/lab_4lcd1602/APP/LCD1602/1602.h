#ifndef _1602_H
#define _1602_H

#include "system.h"



void LCD1602_Init(void);
void Lcd1602_Delay1ms(u16 c); 
//*LCD1602写入8位命令子函数
void LcdWriteCom(u8 com);
//*LCD1602写入8位数据子函数	
void LcdWriteData(u8 dat);
//*LCD1602初始化子程序		
void LcdInit(void);	
void LcdWritestr(u8 *dat);
void LcdClean(void);


//1602驱动端口
#define LCD_port_rcc   RCC_APB2Periph_GPIOB// 1602时钟初始化定义
#define LCD_port       GPIOB              // 1602 端口定义 
#define LCD_RS         GPIO_Pin_1        //1602 引脚定义
#define LCD_RW         GPIO_Pin_2         //1602 引脚定义
#define LCD_EN         GPIO_Pin_0         //1602 引脚定义


//1602位带定义
#define rs  PBout(1)//1602  GPIOB
#define rw  PBout(2)//1602
#define en  PBout(0)//1602


//1602
#define LCD_DO_port_rcc   RCC_APB2Periph_GPIOB// 1602 时钟初始化定义
#define LCD_DO_port       GPIOB              // 1602 端口定义 
#define LCD_D0         GPIO_Pin_8        //1602 引脚定义
#define LCD_D1         GPIO_Pin_9         //1602 引脚定义
#define LCD_D2         GPIO_Pin_10         //1602 引脚定义
#define LCD_D3         GPIO_Pin_11        //1602 引脚定义
#define LCD_D4         GPIO_Pin_12        //1602 引脚定义
#define LCD_D5         GPIO_Pin_13        //1602 引脚定义
#define LCD_D6         GPIO_Pin_14        //1602 引脚定义
#define LCD_D7         GPIO_Pin_15        //1602 引脚定义



	
#endif 
