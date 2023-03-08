#include "./fan/fan.h"   


void FAN_GPIO_Config(void)
{		
		/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
		GPIO_InitTypeDef GPIO_InitStructure;

		/*����GPIO����ʱ��*/
		RCC_APB2PeriphClockCmd( INA_GPIO_CLK | INB_GPIO_CLK, ENABLE);
		/*ѡ��Ҫ���Ƶ�GPIO����*/
		GPIO_InitStructure.GPIO_Pin = INA_GPIO_PIN;	

		/*��������ģʽΪͨ���������*/
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

		/*������������Ϊ50MHz */   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

		/*���ÿ⺯������ʼ��GPIO*/
		GPIO_Init(INA_GPIO_PORT, &GPIO_InitStructure);	
		
		/*ѡ��Ҫ���Ƶ�GPIO����*/
		GPIO_InitStructure.GPIO_Pin = INB_GPIO_PIN;

		/*���ÿ⺯������ʼ��GPIO*/
		GPIO_Init(INB_GPIO_PORT, &GPIO_InitStructure);
		
		/* �ر�����led��	*/
		GPIO_SetBits(INA_GPIO_PORT, INA_GPIO_PIN);
		/* �ر�����led��	*/
		GPIO_SetBits(INB_GPIO_PORT, INB_GPIO_PIN);	 
}

/*********************************************END OF FILE**********************/
