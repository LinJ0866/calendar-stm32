/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   rtc ���ԣ���ʾʱ���ʽΪ: xx:xx:xx
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ�� F103-ָ���� STM32 ������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
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



// N = 2^32/365/24/60/60 = 136 ��

/*ʱ��ṹ�壬Ĭ��ʱ��2000-01-01 00:00:00*/
struct rtc_time systmtime=
{
0,0,0,1,1,2000,0
};

extern int system_back;
extern uint8_t first_display;
extern uint8_t page;
extern unsigned char const*Musics[];
extern uint8_t uc, ucDs18b20Id [ 8 ];


//��*��ע�����
//��bsp_rtc.h�ļ��У�

//1.�����ú�USE_LCD_DISPLAY�����Ƿ�ʹ��LCD��ʾ
//2.�����ú�RTC_CLOCK_SOURCE_LSI��RTC_CLOCK_SOURCE_LSE����ʹ��LSE������LSI����

//3.STM32��LSE����Ҫ��ǳ��ϸ�ͬ���ĵ�·������������Ʒʱ����Щ��������⡣
//  ��ʵ����Ĭ��ʹ��LSI����
//  
//4.��������ϣ��RTC������Դ�������Ȼ���У���Ҫ��������ĵ�ز۰�װť�۵�أ�
//  �������Ҹĳ�ʹ���ⲿ����ģʽRTC_CLOCK_SOURCE_LSE
//  ť�۵���ͺţ�CR1220
/**
  * @brief  ������
  * @param  ��  
  * @retval ��
  */
int main()
{		
		system_back = BLACK;
		first_display = 1;
	
//��ʹ�øú������Ƿ�ʹ��Һ����ʾ
	
		ILI9341_Init ();         //LCD ��ʼ��
		LCD_SetFont(&Font8x16);
		LCD_SetColors(GREY,BLACK);

		ILI9341_Clear(0,0,LCD_X_LENGTH,LCD_Y_LENGTH);	/* ��������ʾȫ�� */

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
		
		I2C_Configuration();//����CPU��Ӳ��I2C
		
		
		OLED_Init();    //��ʼ��OLED
		
		OLED_CLS();
		printf("asd");
		OLED_ShowStr(0,0,"50min DONE", 2);
		#endif
		
		BEEP_GPIO_Config();

		/* ����RTC���ж����ȼ� */
	  RTC_NVIC_Config();
	  RTC_CheckAndConfig(&systmtime);
		
		BASIC_TIM_Init();
		
		Temp_ADC1_Init();
		
		FAN_GPIO_Config();
		LCD_SetColors(RED, BLACK);
		DS18B20_Init();
		while( DS18B20_Init() )	
			ILI9341_DisplayStringEx(LINEY(1),LINE(3),LINE(1),LINE(1), "�Ҳ���Ds18b20...", 0);
		DS18B20_ReadId ( ucDs18b20Id  );           // ��ȡ DS18B20 �����к�
		
		while(1) {
			if (TPAD_Scan() == TPAD_ON && page != 0) Create_Library_layer();
			XPT2046_TouchEvenHandler();
			switch(page){
				case 0:
					Show_Library_layer(&systmtime);
					break;
				case 1: // ʱ��APP-ʱ��
					Show_Clock_layer(&systmtime);
					break;
				case 2: // ʱ��-ʱ��ѡ��
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

