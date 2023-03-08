#ifndef __CLOCK_H
#define __CLOCK_H       

#include "stm32f10x.h"

#include "./lcd/bsp_ili9341_lcd.h"
#include "./font/fonts.h"	
#include "./usart/bsp_usart.h"

#include "./rtc/bsp_rtc.h"
#include "./common/common.h"

#include "./ui/button.h"

#include "./layer/clock_zone_config.h"
#include "./layer/clock_alert.h"
#include "./layer/clock_stop.h"

extern int system_back;
extern uint8_t first_display;
extern uint8_t page;
extern timeZone zone[26];
extern char *WEEK_STR[];

// ´¥ÃþÊÂ¼þ
void Clock_Button_Hover(uint16_t x,uint16_t y);
void Clock_Button_Release(uint16_t x,uint16_t y);

// ´°Ìå
void Create_Clock_layer(void);
void Show_Clock_layer(struct rtc_time *tm);

#endif /*end of __DISPLAY_H    */
