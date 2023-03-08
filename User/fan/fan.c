#include "./fan/fan.h"   


void FAN_GPIO_Config(void)
{		
		/*定义一个GPIO_InitTypeDef类型的结构体*/
		GPIO_InitTypeDef GPIO_InitStructure;

		/*开启GPIO外设时钟*/
		RCC_APB2PeriphClockCmd( INA_GPIO_CLK | INB_GPIO_CLK, ENABLE);
		/*选择要控制的GPIO引脚*/
		GPIO_InitStructure.GPIO_Pin = INA_GPIO_PIN;	

		/*设置引脚模式为通用推挽输出*/
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

		/*设置引脚速率为50MHz */   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

		/*调用库函数，初始化GPIO*/
		GPIO_Init(INA_GPIO_PORT, &GPIO_InitStructure);	
		
		/*选择要控制的GPIO引脚*/
		GPIO_InitStructure.GPIO_Pin = INB_GPIO_PIN;

		/*调用库函数，初始化GPIO*/
		GPIO_Init(INB_GPIO_PORT, &GPIO_InitStructure);
		
		/* 关闭所有led灯	*/
		GPIO_SetBits(INA_GPIO_PORT, INA_GPIO_PIN);
		/* 关闭所有led灯	*/
		GPIO_SetBits(INB_GPIO_PORT, INB_GPIO_PIN);	 
}

/*********************************************END OF FILE**********************/
