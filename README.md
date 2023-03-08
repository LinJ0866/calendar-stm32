# 嵌入式温湿度监测工作站

> HDU 自动化学院 嵌入式系统课程大作业，实际上应该叫万年历，为了简历改个名
>
> UPDATE_TIME: 2022-06-07

## 简介

一种基于STM32的智能万年历设计方案，本文案以STM32F103VET6作为主控核心，与LCD电阻显示屏、DS18B20温度传感器、OLED显示屏等模块组成硬件系统。其中以STM32内部的RTC（实时时钟）实现日历和时间的功能，通过修改计数器的值可以重新设置系统的当前时间和日期，LCD电阻屏实现用户交互，使用0.96寸OLED小屏提供专注信息传达的副屏`（但没实现）`。

![image-20230308110831992](http://picbed.rubbishman.xyz/202303081108162.png)

## 设计目标

通过STM32F103VET6实现万年历，要求实现如下：

（1） `基本任务`能够通过LCD提供实时时间显示；

（2） `基本任务`能够通过板载与外接ds18b20温度传感器提供CPU及室温的实时监控；

（6） `加分项`非常无聊的调整了UI，并适配了粗糙的深色模式；

（3） `加分项`提供全时区世界时间，并实现自动日期推算（加分项）；

（4） `加分项`创建可供不同应用切换的桌面与操作逻辑（加分项）；

（5） `加分项`控制直流电机驱动风扇，实现温度控制；

（6） `加分项`利用SysTick控制蜂鸣器频率，实现音乐播放。

## 硬件

- STM32F103VET6
- 触摸LCD
- DS18B20
- 直流电机

## 软件设计

![image-20230308111514389](http://picbed.rubbishman.xyz/202303081115532.png)