#include "./layer/clock_alert.h"
#include "string.h"


#define BUTTON_NUM 7

/*��ť�ṹ������*/
static Touch_Button button[BUTTON_NUM];
static uint8_t real_first_dis = 1;

static alert_struct alerts[3];

static void alert_item_Display(uint16_t y, char *location, uint8_t *week);
static void button_switch_system_back(void *btn);
static void button_goto_clock_alert(void *btn);
static void button_goto_clock(void *btn);
static void button_goto_clock_stop(void *btn);

static void button_switch_select(void *btn);

static void button_Init(void)
{
	button[0].start_x = LINEY(1);
  button[0].start_y = LINE(1);
  button[0].end_x = LINEY(1)+LINEY(2);
  button[0].end_y = LINE(1)+LINE(1);
	button[0].shape = 2;
	button[0].text = "����";
	button[0].text_len = 2;
	button[0].fore_color = BLUE;
  button[0].touch_flag = 0;  
  button[0].draw_btn = Draw_Color_Button ;
  button[0].btn_command = button_goto_clock_alert;
	
	button[1].start_x = LINEY(4);
  button[1].start_y = LINE(1);
  button[1].end_x = LINEY(4)+LINEY(2);
  button[1].end_y = LINE(1)+LINE(1);
	button[1].shape = 2;
	button[1].text = "ʱ��";
	button[1].text_len = 2;
	button[1].dark_adapt = 1;
  button[1].touch_flag = 0;  
  button[1].draw_btn = Draw_Color_Button ;
  button[1].btn_command = button_goto_clock;
	
	button[2].start_x = LINEY(7);
  button[2].start_y = LINE(1);
  button[2].end_x = LINEY(7)+LINEY(2);
  button[2].end_y = LINE(1)+LINE(1);
	button[2].fore_color = BLUE;
	button[2].shape = 2;
	button[2].dark_adapt = 1;
	button[2].text = "���";
	button[2].text_len = 2;
  button[2].touch_flag = 0;
  button[2].draw_btn = Draw_Color_Button ;
  button[2].btn_command = button_goto_clock_stop;
	
	button[3].start_x = LINEY(12);
  button[3].start_y = LINE(1)-10;
  button[3].end_x = LINEY(12)+LINE(2);
  button[3].end_y = LINE(1)-10+LINE(2);
	button[3].shape = 1;
	button[3].text = "��";
	button[3].text_len = 1;
	button[3].fore_color = BLUE;
  button[3].back_color = GREY1;
  button[3].touch_flag = 0;  
  button[3].draw_btn = Draw_Color_Button ;
  button[3].btn_command = button_switch_system_back;
	
	
	button[4].start_x = LINEY(10);
  button[4].start_y = LINE(3);
	button[4].end_x = button[4].start_x+LINE(4.6);
  button[4].end_y = button[4].start_y+LINE(2);
	button[4].shape = 3;
  button[4].touch_flag = 0;  
  button[4].draw_btn = Draw_Color_Button ;
  button[4].btn_command = button_switch_select;
	
	button[5].start_x = LINEY(10);
  button[5].start_y = LINE(8);
	button[5].end_x = button[5].start_x+LINE(4.6);
  button[5].end_y = button[5].start_y+LINE(2);
	button[5].shape = 3;
  button[5].touch_flag = 0;  
  button[5].draw_btn = Draw_Color_Button ;
  button[5].btn_command = button_switch_select;
	
	button[6].start_x = LINEY(10);
  button[6].start_y = LINE(13);
	button[6].end_x = button[6].start_x+LINE(4.6);
  button[6].end_y = button[6].start_y+LINE(2);
	button[6].shape = 3;
  button[6].touch_flag = 0;  
  button[6].draw_btn = Draw_Color_Button ;
  button[6].btn_command = button_switch_select;

}

void alert_Init(void) {
	alerts[0].time = "06:51";
	alerts[0].week[0] = 0;
	alerts[0].week[1] = 1;
	alerts[0].week[2] = 1;
	alerts[0].week[3] = 1;
	alerts[0].week[4] = 1;
	alerts[0].week[5] = 1;
	alerts[0].week[6] = 0;
	alerts[0].status = 0;
	
	alerts[1].time = "08:00";
	alerts[1].week[0] = 1;
	alerts[1].week[1] = 0;
	alerts[1].week[2] = 0;
	alerts[1].week[3] = 0;
	alerts[1].week[4] = 0;
	alerts[1].week[5] = 0;
	alerts[1].week[6] = 1;
	alerts[1].status = 0;
	
	alerts[2].time = "22:00";
	alerts[2].week[0] = 0;
	alerts[2].week[1] = 0;
	alerts[2].week[2] = 0;
	alerts[2].week[3] = 0;
	alerts[2].week[4] = 0;
	alerts[2].week[5] = 0;
	alerts[2].week[6] = 0;
	alerts[2].status = 1;
}


// ���������ٻ�
void Create_Clock_Alert_layer()
{
	real_first_dis = 1;
	first_display = 1;
	page = 4;
}


/**
* @brief  ʱ��app�����ʼ��
* @param  ��
* @retval ��
*/
void Show_Clock_Alert_layer(void)
{
	uint8_t i;
	/* ��ʼ����ť */
	if (real_first_dis) {
		button_Init();
		real_first_dis = 0;
	}
	
	if(first_display)
	{
		if(system_back == BLACK) LCD_SetColors(WHITE, BLACK); else LCD_SetColors(BLACK, WHITE);
		ILI9341_Clear(0,0,LCD_X_LENGTH,LCD_Y_LENGTH);
		
		/* ��水ť */
		for(i=0;i<4;i++)
		{
			button[i].draw_btn(&button[i]);
		}
		
		for(i=0; i<3; i++)
		{
			alert_item_Display(LINE(3+i*5), alerts[i].time, alerts[i].week);
			button[i+4].is_checked = &alerts[i].status;
			button[i+4].draw_btn(&button[i+4]);
		}
		
		
		first_display = 0;
	}

}


/**
* @brief  Touch_Button_Down ����������ʱ���õĺ������ɴ���������
* @param  x ����λ�õ�x����
* @param  y ����λ�õ�y����
* @retval ��
*/
void Clock_Alert_Button_Hover(uint16_t x,uint16_t y)
{
  uint8_t i;
  for(i=0;i<BUTTON_NUM;i++)
  {
    /* �������˰�ť */
    if(x<=button[i].end_x && y<=button[i].end_y && y>=button[i].start_y && x>=button[i].start_x )
    {
      if(button[i].touch_flag == 0)     /*ԭ����״̬Ϊû�а��£������״̬*/
      {
      button[i].touch_flag = 1;         /* ��¼���±�־ */
      
      button[i].draw_btn(&button[i]);  /*�ػ水ť*/
      }        
      
    }
    else if(button[i].touch_flag == 1) /* �����Ƴ��˰����ķ�Χ��֮ǰ�а��°�ť */
    {
      button[i].touch_flag = 0;         /* ������±�־���ж�Ϊ�����*/ 
      button[i].draw_btn(&button[i]);   /*�ػ水ť*/
    }
  }
}

/**
* @brief  Touch_Button_Up �������ͷ�ʱ���õĺ������ɴ���������
* @param  x ��������ͷ�ʱ��x����
* @param  y ��������ͷ�ʱ��y����
* @retval ��
*/
void Clock_Alert_Button_Release(uint16_t x,uint16_t y)
{
   uint8_t i; 
   for(i=0;i<BUTTON_NUM;i++)
   {
     /* �����ڰ�ť�����ͷ� */
      if((x<button[i].end_x && x>button[i].start_x && y<button[i].end_y && y>button[i].start_y))
      {        
        button[i].touch_flag = 0;       /*�ͷŴ�����־*/
        
        button[i].draw_btn(&button[i]); /*�ػ水ť*/        
      
        button[i].btn_command(&button[i]);  /*ִ�а����Ĺ�������*/
        
        break;
      }
    }	 

}


static void button_switch_system_back(void *btn)
{
	if(system_back == BLACK) button[3].text = "��"; else button[3].text = "��";
  switch_system_back();
}

static void button_goto_clock_alert(void *btn)
{
	Create_Clock_Alert_layer();
}

static void button_goto_clock(void *btn)
{
	Create_Clock_layer();
}

static void button_goto_clock_stop(void *btn)
{
	Create_Clock_Stop_layer();
}


static void button_switch_select(void *btn)
{
	Touch_Button *ptr = (Touch_Button *)btn;
	
	if(*ptr->is_checked){
		*ptr->is_checked  = 0;
	} else {
		*ptr->is_checked = 1;
	}
	ptr->draw_btn(ptr);
	// first_display = 1;
}

static void alert_item_Display(uint16_t y, char *location, uint8_t *week)
{
		uint8_t i;
		uint8_t str[200]; // �ַ����ݴ�  
		if(system_back == BLACK) LCD_SetColors(WHITE, BLACK); else LCD_SetColors(BLACK, WHITE);
	  sprintf((char *)str,"%s", location);
		ILI9341_DisplayStringEx(LINEY(1),y, LINEY(2), LINE(2), (char*)str, 0);
		LCD_SetTextColor(GREY);
		ILI9341_DispStringLine_EN_CH(y+LINE(2.5), "  �� һ �� �� �� �� ��");
		LCD_SetTextColor(BLUE);
		for(i = 0; i<7; i++)
		{
			if(week[i]) ILI9341_DisplayStringEx(LINEY(1+i*1.5),y+LINE(2.5), LINEY(1), LINE(1), WEEK_STR[i], 0);
		}
		
}

