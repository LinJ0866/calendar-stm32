#include "./beep/bsp_beep.h"
#include "systick/bsp_SysTick.h"

int melody[] = {50, 50, 50, 50, 200, 200, 200, 400, 400, 500, 500, 500};

/**
  * @brief  初始化控制蜂鸣器的IO
  * @param  无
  * @retval 无
  */
void BEEP_GPIO_Config(void)
{
        /*定义一个GPIO_InitTypeDef类型的结构体*/
        GPIO_InitTypeDef GPIO_InitStructure;

        /*开启控制蜂鸣器的GPIO的端口时钟*/
        RCC_APB2PeriphClockCmd(BEEP_GPIO_CLK, ENABLE);

        /*选择要控制蜂鸣器的GPIO*/
        GPIO_InitStructure.GPIO_Pin = BEEP_GPIO_PIN;

        /*设置GPIO模式为通用推挽输出*/
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;

        /*设置GPIO速率为50MHz */
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

        /*调用库函数，初始化控制蜂鸣器的GPIO*/
        GPIO_Init(BEEP_GPIO_PORT, &GPIO_InitStructure);

        /* 关闭蜂鸣器*/
        GPIO_ResetBits(BEEP_GPIO_PORT, BEEP_GPIO_PIN);
}

void Sound(int16_t frq)

{
        int32_t n;

        if (frq != 1000) //如果频率不为1000则按频率输出，否则只延时

        {
                n = 500000 / ((int32_t)frq);

                BEEP(OFF);

                SysTick_Delay_Us(n);

                BEEP(ON);

                SysTick_Delay_Us(n);
        }
        else

                SysTick_Delay_Us(1000);
}

void play(void)

{
        //             低7  1   2   3   4   5   6   7  高1 高2 高3 高4 高5 不发音

        int16_t tone[] = {247, 262, 294, 330, 349, 392, 440, 494, 523, 587, 659, 698, 784, 1000}; //音频数据表
				int8_t music[] = {5,5,6,5,8,7,5,5,6,5,9,8};
				int8_t time[] = {3,3,5,5,5,5,3,3,5,5,5,5};
				
        int16_t i, e;

        for (i = 0; i < 12; i++)
        {
                for (e = 0; e < ((int16_t)time[i]) * tone[music[i]] / 10; e++)
                {
                        Sound((int32_t)tone[music[i]]);
                }
        }
				BEEP(OFF);
				
}
