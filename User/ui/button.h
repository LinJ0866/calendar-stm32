#ifndef __UI_BUTTON_H
#define __UI_BUTTON_H 

#include "./lcd/bsp_ili9341_lcd.h"
#include "./font/fonts.h"	
#include "./usart/bsp_usart.h"

#include <string.h>

extern int system_back;

typedef struct 
{
	uint8_t status;
	uint8_t id;
  uint16_t start_x;   //按键的x起始坐标  
  uint16_t start_y;   //按键的y起始坐标
  uint16_t end_x;     //按键的x结束坐标 
  uint16_t end_y;     //按键的y结束坐标
	uint8_t shape;  // 按钮样式，3为switch, 2为纯文字, 1为圆形，0为矩形
  uint32_t back_color;      //按钮背景颜色
	uint32_t fore_color;
	char  *text;      // 按钮内容
	float text_len;
	uint8_t *is_checked;
  uint8_t touch_flag; //按键按下的标志
  uint8_t dark_adapt;
  void (*draw_btn)(void * btn);     //按键描绘函数
  void (*btn_command)(void * btn);  //按键功能执行函数
 
}Touch_Button;

void Draw_Color_Button(void *btn);

#endif
