#ifndef __CLOCK_ALERT_H
#define __CLOCK_ALERT_H       

#include "stm32f10x.h"

#include "./lcd/bsp_ili9341_lcd.h"
#include "./font/fonts.h"	
#include "./usart/bsp_usart.h"

#include "./rtc/bsp_rtc.h"
#include "./common/common.h"

#include "./ui/button.h"

#include "./layer/clock.h"
#include "./layer/clock_stop.h"

extern int system_back;
extern uint8_t first_display;
extern uint8_t page;
extern timeZone zone[26];
extern char *WEEK_STR[];


typedef struct {
	char *time;
	uint8_t week[7];
	uint8_t status;
} alert_struct;

void Clock_Alert_Button_Hover(uint16_t x,uint16_t y);
void Clock_Alert_Button_Release(uint16_t x,uint16_t y);

void Create_Clock_Alert_layer(void);
void Show_Clock_Alert_layer(void);

void alert_Init(void);

#endif /*end of __DISPLAY_H    */
