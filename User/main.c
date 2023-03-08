/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   rtc 测试，显示时间格式为: xx:xx:xx
  ******************************************************************************
  * @attention
  *
  * 实验平台:野火 F103-指南者 STM32 开发板 
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */
	
#include "stm32f10x.h"
#include "./common/common.h"
#include "./usart/bsp_usart.h"
#include "./rtc/bsp_rtc.h"
#include "./lcd/bsp_ili9341_lcd.h"
#include "./lcd/bsp_xpt2046_lcd.h"
#include "./led/bsp_led.h"
#include "./key/bsp_key.h"
#include "./TimBase/bsp_TiMbase.h"
#include "./TPad/bsp_tpad.h"
#include "./temp/bsp_tempad.h"
#include "./temp/bsp_ds18b20.h"
#include "./beep/bsp_beep.h"
#include "./systick/bsp_SysTick.h"
#include "./fan/fan.h"

#include "./layer/library.h"
#include "./layer/clock.h"
#include "./layer/clock_Stop.h"
#include "./layer/clock_Alert.h"
#include "./layer/clock_zone_config.h"
#include "./layer/temperature.h"



// N = 2^32/365/24/60/60 = 136 年

/*时间结构体，默认时间2000-01-01 00:00:00*/
struct rtc_time systmtime=
{
0,0,0,1,1,2000,0
};

extern int system_back;
extern uint8_t first_display;
extern uint8_t page;
extern unsigned char const*Musics[];
extern uint8_t uc, ucDs18b20Id [ 8 ];


//【*】注意事项：
//在bsp_rtc.h文件中：

//1.可设置宏USE_LCD_DISPLAY控制是否使用LCD显示
//2.可设置宏RTC_CLOCK_SOURCE_LSI和RTC_CLOCK_SOURCE_LSE控制使用LSE晶振还是LSI晶振

//3.STM32的LSE晶振要求非常严格，同样的电路、板子批量产品时总有些会出现问题。
//  本实验中默认使用LSI晶振。
//  
//4.！！！若希望RTC在主电源掉电后仍然运行，需要给开发板的电池槽安装钮扣电池，
//  ！！！且改成使用外部晶振模式RTC_CLOCK_SOURCE_LSE
//  钮扣电池型号：CR1220
/**
  * @brief  主函数
  * @param  无  
  * @retval 无
  */
int main()
{		
		system_back = BLACK;
		first_display = 1;
	
//可使用该宏设置是否使用液晶显示
	
		ILI9341_Init ();         //LCD 初始化
		LCD_SetFont(&Font8x16);
		LCD_SetColors(GREY,BLACK);

		ILI9341_Clear(0,0,LCD_X_LENGTH,LCD_Y_LENGTH);	/* 清屏，显示全黑 */

		alert_Init();
		timeZoneInit();
	  USART_Config();		
		LED_GPIO_Config();
		Key_GPIO_Config();
		XPT2046_Init();
		// XPT2046_Touch_Calibrate(6);
	
		SysTick_Init();
		TPAD_Init();
		
		#if 0
		
		I2C_Configuration();//配置CPU的硬件I2C
		
		
		OLED_Init();    //初始化OLED
		
		OLED_CLS();
		printf("asd");
		OLED_ShowStr(0,0,"50min DONE", 2);
		#endif
		
		BEEP_GPIO_Config();

		/* 配置RTC秒中断优先级 */
	  RTC_NVIC_Config();
	  RTC_CheckAndConfig(&systmtime);
		
		BASIC_TIM_Init();
		
		Temp_ADC1_Init();
		
		FAN_GPIO_Config();
		LCD_SetColors(RED, BLACK);
		DS18B20_Init();
		while( DS18B20_Init() )	
			ILI9341_DisplayStringEx(LINEY(1),LINE(3),LINE(1),LINE(1), "找不到Ds18b20...", 0);
		DS18B20_ReadId ( ucDs18b20Id  );           // 读取 DS18B20 的序列号
		
		while(1) {
			if (TPAD_Scan() == TPAD_ON && page != 0) Create_Library_layer();
			XPT2046_TouchEvenHandler();
			switch(page){
				case 0:
					Show_Library_layer(&systmtime);
					break;
				case 1: // 时钟APP-时钟
					Show_Clock_layer(&systmtime);
					break;
				case 2: // 时钟-时区选择
					Show_Clock_Zone_Config_layer();
					break;
				case 3:
					Show_Clock_Stop_layer();
					break;
				case 4:
					Show_Clock_Alert_layer();
					break;
				case 5:
					Show_Temperature_layer();
					break;
			}
		}
}

/***********************************END OF FILE*********************************/

