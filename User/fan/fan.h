#ifndef __FAN_H
#define	__FAN_H

#include "stm32f10x.h"

#define INA_GPIO_PORT    	GPIOA			              /* GPIO�˿� */
#define INA_GPIO_CLK 	    RCC_APB2Periph_GPIOA		/* GPIO�˿�ʱ�� */
#define INA_GPIO_PIN		GPIO_Pin_4			        /* ���ӵ�SCLʱ���ߵ�GPIO */

#define INB_GPIO_PORT    	GPIOA			              /* GPIO�˿� */
#define INB_GPIO_CLK 	    RCC_APB2Periph_GPIOA		/* GPIO�˿�ʱ�� */
#define INB_GPIO_PIN		GPIO_Pin_5			        /* ���ӵ�SCLʱ���ߵ�GPIO */

#define ON  0
#define OFF 1

/* ʹ�ñ�׼�Ĺ̼������IO*/
#define FAN(a)	if (a)	\
					GPIO_SetBits(INA_GPIO_PORT,INA_GPIO_PIN);\
					else		\
					GPIO_ResetBits(INA_GPIO_PORT,INA_GPIO_PIN)

void FAN_GPIO_Config(void);

#endif