#ifndef __CLOCK_ZONE_CONFIG_H
#define __CLOCK_ZONE_CONFIG_H       

#include "stm32f10x.h"

#include "./lcd/bsp_ili9341_lcd.h"
#include "./font/fonts.h"	
#include "./usart/bsp_usart.h"

#include "./rtc/bsp_rtc.h"
#include "./common/common.h"

#include "./ui/button.h"

#include "./layer/clock.h"

extern int system_back;
extern uint8_t first_display;
extern uint8_t page;
extern timeZone zone[26];


void Clock_Zone_Config_Button_Hover(uint16_t x,uint16_t y);
void Clock_Zone_Config_Button_Release(uint16_t x,uint16_t y);

void Create_Clock_Zone_Config_layer(void);
void Show_Clock_Zone_Config_layer(void);

#endif /*end of __DISPLAY_H    */
