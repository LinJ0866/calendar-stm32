#ifndef __LIBRARY_H
#define __LIBRARY_H       

#include "stm32f10x.h"

#include "./lcd/bsp_ili9341_lcd.h"
#include "./font/fonts.h"	
#include "./usart/bsp_usart.h"
#include "./beep/bsp_beep.h"

#include "./rtc/bsp_rtc.h"
#include "./common/common.h"

#include "./ui/button.h"

#include "./layer/clock.h"
#include "./layer/temperature.h"


extern int system_back;
extern uint8_t first_display;
extern uint8_t page;
extern timeZone zone[26];
extern char *WEEK_STR[];


void Library_Button_Hover(uint16_t x,uint16_t y);
void Library_Button_Release(uint16_t x,uint16_t y);

void Create_Library_layer(void);
void Show_Library_layer(struct rtc_time *tm);


#endif /*end of __DISPLAY_H    */
