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
  uint16_t start_x;   //������x��ʼ����  
  uint16_t start_y;   //������y��ʼ����
  uint16_t end_x;     //������x�������� 
  uint16_t end_y;     //������y��������
	uint8_t shape;  // ��ť��ʽ��3Ϊswitch, 2Ϊ������, 1ΪԲ�Σ�0Ϊ����
  uint32_t back_color;      //��ť������ɫ
	uint32_t fore_color;
	char  *text;      // ��ť����
	float text_len;
	uint8_t *is_checked;
  uint8_t touch_flag; //�������µı�־
  uint8_t dark_adapt;
  void (*draw_btn)(void * btn);     //������溯��
  void (*btn_command)(void * btn);  //��������ִ�к���
 
}Touch_Button;

void Draw_Color_Button(void *btn);

#endif
