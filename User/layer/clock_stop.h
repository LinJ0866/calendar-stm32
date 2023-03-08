#ifndef __CLOCK_STOP_H
#define __CLOCK_STOP_H       

#include "stm32f10x.h"

#include "./lcd/bsp_ili9341_lcd.h"
#include "./font/fonts.h"	
#include "./usart/bsp_usart.h"

#include "./rtc/bsp_rtc.h"
#include "./TimBase/bsp_TiMbase.h"
#include "./common/common.h"

#include "./ui/button.h"

#include "./layer/clock.h"
#include "./layer/clock_alert.h"

extern int system_back;
extern uint8_t first_display;
extern uint8_t page;

// ´¥ÃþÊÂ¼þ
void Clock_Stop_Button_Hover(uint16_t x,uint16_t y);
void Clock_Stop_Button_Release(uint16_t x,uint16_t y);

// ´°Ìå
void Create_Clock_Stop_layer(void);
void Show_Clock_Stop_layer(void);

#endif /*end of __DISPLAY_H    */
