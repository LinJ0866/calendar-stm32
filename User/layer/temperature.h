#ifndef __CLOCK_TEMPE_H
#define __CLOCK_TEMPE_H       

#include "stm32f10x.h"

#include "./lcd/bsp_ili9341_lcd.h"
#include "./font/fonts.h"	
#include "./usart/bsp_usart.h"
#include "./temp/bsp_tempad.h"
#include "./temp/bsp_ds18b20.h"
#include "./fan/fan.h"

#include "./ui/button.h"

#include "./common/common.h"

extern int system_back;
extern uint8_t first_display;
extern uint8_t page;


void Temperature_Button_Hover(uint16_t x,uint16_t y);
void Temperature_Button_Release(uint16_t x,uint16_t y);

void Create_Temperature_layer(void);
void Show_Temperature_layer(void);

#endif /*end of __DISPLAY_H    */
