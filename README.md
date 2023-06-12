# stm32实验

# 介绍

重庆邮电大学微控制器原理，实验课以及实践课源码



##  软件架构说明:



lab_one: 实验课源码

包含：led，外部中断，定时器，串口通信

lab_two:实践课源码

包含：直流电机，步进电机，温度传感器（ds18b20) ,Lcd1602液晶显示模块，i2C-EEPROM，红外遥控。

## 源码讲解

### lab_one

#### led实验

主要思路：STM32F10x 连接到一块 8 路 LED 的实现代码，其中使用了 GPIO_Write() 函数来确定所有 LED 的状态。将 `~0x0001`、`~0x0002`、`~0x0004`、`~0x0008`、`~0x0010`、`~0x0020`、`~0x0040` 和 `~0x0080` 作为参数，每次只让其中一个引脚为低电平，从而点亮对应的 LED，点亮时间为 `speed` 定义的时间间隔。如果需要实现 LED 的循环扫描显示，可以通过循环语句控制每个 LED 依次点亮的顺序即可。

步骤：

1.开启GPIO时钟，初始化GPIO

2.编写演示函数，用系统定时器，这部分可以直接拿过来用。

3.在循环中调用GPIO_Write（）函数，写入位操作，点亮第一个led灯。

4.没点亮一个led灯，延时100 ms，时间可以自己设定，定时越短跑马灯速度越快。

注意人眼识别极限，延时不要太低，频率太高人眼会识别不到。



实验现象：

<video src="E:\school\learnig_lab\lab\stm32-experiment\lab_one\lab1_led\IMG_2969.MP4"></video>



#### 外部中断实验

整体思路：

STM32F103控制8个LED灯以及通过外部中断按键实现不同灯光效果的控制。其中包含led.h、exti_key.h和Delay.h三个头文件，以及两个函数sb_1和sb_2，分别表示LED灯按照某种顺序亮起和熄灭的具体操作过程。在主函数中，通过调用LED_Init和EXTI_Key_Init函数初始化，然后在一个while(1)循环中等待外部中断触发。在中断函数EXTI1_IRQHandler和EXTI4_IRQHandler中，分别响应不同线路的中断，并调用sb_1和sb_2函数实现不同的LED灯光效果控制。需要注意的是，在中断函数中最后需要清除中断标志位。

步骤：

1.使能时钟，以及初始化GPIO

2.根据实际情况初始化外部中断，包括触发方式，线路

3.将流水灯代码封装成函数sb_1（）以及sb_2(),两个函数只是亮灯方向不同

4.编写外部中断函数，调用封装好的sb流水灯函数

注意清楚中断标志

实验现象：

<video src="E:\school\learnig_lab\lab\stm32-experiment\lab_one\lab2_exti\IMG_2970.MP4"></video>





#### 定时器实验

整体思路：

实现数字显示、红外遥控接收和PWM调速功能。其中，数字显示采用了数码管和循环扫描的方式实现多位数字的显示。红外遥控接收功能通过红外接收模块获取红外码，并根据接收到的码值进行相应的操作。PWM调速功能通过TIM3_PWM_Init函数初始化TIM3定时器，然后通过设置比较寄存器的值来实现PWM调速。整个代码中也用到了延时函数和串口通信等多种功能。



步骤：

1.使能时钟，以及初始化GPIO

2.初始化数码管段选数据，这一步对于数码管显示非常重要

2.初始化pwm，psc ccr 等寄存器的值，这里不需要用到定时器中断

3.编写红外解码函数，代码里面详细给出了

4.根据红外遥控器发送过来的电信号进行解码，并在swich语句里面进行操作



实验现象：

<video src="E:\school\learnig_lab\lab\stm32-experiment\lab_one\lab3_timer_hongwai2\IMG_2968.MP4"></video>



#### 串口通信实验

整体思路：

在上一个定时器红外遥控的基础上加入了串口控制。串口1接收中断服务程序。其中，当串口1收到数据时，会根据接收到的字符不同执行不同的操作。例如，如果接收到小写字母，则会熄灭连接在GPIOA的5号引脚的LED灯；如果接收到大写字母，则会点亮这个LED灯。此外，如果接收到数字0-9，则会通过PWM方式控制电机的转速，将当前的占空比存储在ccr变量中。最后，将接收到的数据通过USART1发送回去。

步骤：（在上一个代码的基础上）

1.初始化串口

2.编写串口中断函数，主要处理串口发送过来的数据，然后进行控制，（代码里面详细给出了具体逻辑）

实验现象：

<video src="E:\school\learnig_lab\lab\stm32-experiment\lab_one\lab4_usart_hongwai2\IMG_2973.MP4"></video>





















#### 参与贡献

1.  Fork 本仓库
2.  新建 Feat_xxx 分支
3.  提交代码
4.  新建 Pull Request


#### 特技

1.  使用 Readme\_XXX.md 来支持不同的语言，例如 Readme\_en.md, Readme\_zh.md
2.  Gitee 官方博客 [blog.gitee.com](https://blog.gitee.com)
3.  你可以 [https://gitee.com/explore](https://gitee.com/explore) 这个地址来了解 Gitee 上的优秀开源项目
4.  [GVP](https://gitee.com/gvp) 全称是 Gitee 最有价值开源项目，是综合评定出的优秀开源项目
5.  Gitee 官方提供的使用手册 [https://gitee.com/help](https://gitee.com/help)
6.  Gitee 封面人物是一档用来展示 Gitee 会员风采的栏目 [https://gitee.com/gitee-stars/](https://gitee.com/gitee-stars/)
