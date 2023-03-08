#ifndef __FAN_H
#define	__FAN_H

#include "stm32f10x.h"

#define INA_GPIO_PORT    	GPIOA			              /* GPIO端口 */
#define INA_GPIO_CLK 	    RCC_APB2Periph_GPIOA		/* GPIO端口时钟 */
#define INA_GPIO_PIN		GPIO_Pin_4			        /* 连接到SCL时钟线的GPIO */

#define INB_GPIO_PORT    	GPIOA			              /* GPIO端口 */
#define INB_GPIO_CLK 	    RCC_APB2Periph_GPIOA		/* GPIO端口时钟 */
#define INB_GPIO_PIN		GPIO_Pin_5			        /* 连接到SCL时钟线的GPIO */

#define ON  0
#define OFF 1

/* 使用标准的固件库控制IO*/
#define FAN(a)	if (a)	\
					GPIO_SetBits(INA_GPIO_PORT,INA_GPIO_PIN);\
					else		\
					GPIO_ResetBits(INA_GPIO_PORT,INA_GPIO_PIN)

void FAN_GPIO_Config(void);

#endif