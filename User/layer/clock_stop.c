#include "./layer/clock_stop.h"
#include "string.h"

/* ���жϱ�־���������ж�ʱ��1����ʱ�䱻ˢ��֮����0 */
__IO uint32_t time_stamp_ms;

#define BUTTON_NUM 8


/*��ť�ṹ������*/
static Touch_Button button[BUTTON_NUM];
static uint8_t max_dis_count = 2;
static uint8_t real_first_dis = 1;
static uint8_t bottom_refresh = 1;

static uint32_t rest_time = 0;
static uint32_t now_time = 0;
static uint32_t timer = 0;
static uint32_t time_stamp = 0;

static uint8_t str[200]; // �ַ����ݴ�

static void Time_Display(void);

static void button_switch_system_back(void *btn);
static void button_goto_clock_alert(void *btn);
static void button_goto_clock(void *btn);
static void button_goto_clock_stop(void *btn);

static void button_start(void *btn);
static void button_pause(void *btn);
static void button_clear(void *btn);


static void button_Init(void)
{
	button[0].status = 1;
	button[0].start_x = LINEY(1);
  button[0].start_y = LINE(1);
  button[0].end_x = LINEY(1)+LINEY(2);
  button[0].end_y = LINE(1)+LINE(1);
	button[0].shape = 2;
	button[0].text = "����";
	button[0].text_len = 2;
  button[0].dark_adapt = 1;
  button[0].touch_flag = 0;  
  button[0].draw_btn = Draw_Color_Button ;
  button[0].btn_command = button_goto_clock_alert;
	
	button[1].status = 1;
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
	
	
	button[2].status = 1;
	button[2].start_x = LINEY(7);
  button[2].start_y = LINE(1);
  button[2].end_x = LINEY(7)+LINEY(2);
  button[2].end_y = LINE(1)+LINE(1);
	button[2].fore_color = BLUE;
	button[2].shape = 2;
	button[2].text = "���";
	button[2].text_len = 2;
  button[2].touch_flag = 0;  
  button[2].draw_btn = Draw_Color_Button ;
  button[2].btn_command = button_goto_clock_stop;
	
	button[3].status = 1;
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
	
	button[4].status = 1;
	button[4].start_x = LINEY(7);
  button[4].start_y = LINE(15);
  button[4].end_x = button[4].start_x+LINE(2);
  button[4].end_y = button[4].start_y+LINE(2);
	button[4].shape = 1;
	button[4].text = ">";
	button[4].text_len = 0.5;
	button[4].fore_color = BLUE;
  button[4].back_color = GREY1;
  button[4].touch_flag = 0;  
  button[4].draw_btn = Draw_Color_Button ;
  button[4].btn_command = button_start;
	
	button[5].status = 0;
	button[5].start_x = LINEY(7);
  button[5].start_y = LINE(15);
  button[5].end_x = button[5].start_x+LINE(2);
  button[5].end_y = button[5].start_y+LINE(2);
	button[5].shape = 1;
	button[5].text = "||";
	button[5].text_len = 1;
	button[5].fore_color = BLUE;
  button[5].back_color = GREY1;
  button[5].touch_flag = 0;  
  button[5].draw_btn = Draw_Color_Button ;
  button[5].btn_command = button_pause;
	
	button[6].status = 0;
	button[6].start_x = LINEY(5);
  button[6].start_y = LINE(15);
  button[6].end_x = button[6].start_x+LINE(2);
  button[6].end_y = button[6].start_y+LINE(2);
	button[6].shape = 1;
	button[6].text = "o";
	button[6].text_len = 0.5;
	button[6].fore_color = BLUE;
  button[6].back_color = GREY1;
  button[6].touch_flag = 0;  
  button[6].draw_btn = Draw_Color_Button ;
  button[6].btn_command = button_clear;
		
	button[7].status = 0;
	button[7].start_x = LINEY(9);
  button[7].start_y = LINE(15);
  button[7].end_x = button[7].start_x+LINE(2);
  button[7].end_y = button[7].start_y+LINE(2);
	button[7].shape = 1;
	button[7].text = ">";
	button[7].text_len = 0.5;
	button[7].fore_color = BLUE;
  button[7].back_color = GREY1;
  button[7].touch_flag = 0;  
  button[7].draw_btn = Draw_Color_Button ;
  button[7].btn_command = button_start;
	
}


// ���������ٻ�
void Create_Clock_Stop_layer()
{
	real_first_dis = 1;
	first_display = 1;
	page = 3;
	bottom_refresh = 1;
}


/**
* @brief  ʱ��app�����ʼ��
* @param  ��
* @retval ��
*/
void Show_Clock_Stop_layer(void)
{
	/* ��ʼ����ť */
	if (real_first_dis) {
		button_Init();
		real_first_dis = 0;
	}
  
	if(first_display)
	{
		uint8_t i;

		if(system_back == BLACK) LCD_SetColors(WHITE, BLACK); else LCD_SetColors(BLACK, WHITE);
		ILI9341_Clear(0,0,LCD_X_LENGTH,LCD_Y_LENGTH);
		
		sprintf((char *)str,"%0.2d:%0.2d:%0.2d", rest_time/1000/60, (rest_time/1000)%60, (rest_time%1000)/10);
		ILI9341_DisplayStringEx(LINEY(1.5),LINE(5),3*LINEY(1),3*LINE(1), (char*)str, 0);
		
		
		
		/* ��水ť */
		for(i=0;i<4;i++)
		{
			button[i].draw_btn(&button[i]);
		}
		
		first_display = 0;
		
		// time_stamp = time_stamp_ms;
	}
	if(bottom_refresh)
	{
		if(system_back == BLACK) LCD_SetColors(WHITE, BLACK); else LCD_SetColors(BLACK, WHITE);
		ILI9341_Clear(0,LINE(13),LCD_X_LENGTH,LCD_Y_LENGTH-LINE(13));
		if(rest_time == 0 && time_stamp == 0)
		{
			button[4].status = 1;
			button[5].status = 0;
			button[6].status = 0;
			button[7].status = 0;
			button[4].draw_btn(&button[4]);
		} else if(time_stamp != 0) {
			button[4].status = 0;
			button[5].status = 1;
			button[6].status = 0;
			button[7].status = 0;
			button[5].draw_btn(&button[5]);
		} else {
			button[4].status = 0;
			button[5].status = 0;
			button[6].status = 1;
			button[7].status = 1;
			button[6].draw_btn(&button[6]);
			button[7].draw_btn(&button[7]);
		}
		bottom_refresh = 0;
	}
	Time_Display();
}


/**
* @brief  Touch_Button_Down ����������ʱ���õĺ������ɴ���������
* @param  x ����λ�õ�x����
* @param  y ����λ�õ�y����
* @retval ��
*/
void Clock_Stop_Button_Hover(uint16_t x,uint16_t y)
{
  uint8_t i;
  for(i=0;i<BUTTON_NUM;i++)
  {
    /* �������˰�ť */
    if(x<=button[i].end_x && y<=button[i].end_y && y>=button[i].start_y && x>=button[i].start_x && button[i].status )
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
void Clock_Stop_Button_Release(uint16_t x,uint16_t y)
{
   uint8_t i; 
   for(i=0;i<BUTTON_NUM;i++)
   {
     /* �����ڰ�ť�����ͷ� */
      if((x<button[i].end_x && x>button[i].start_x && y<button[i].end_y && y>button[i].start_y && button[i].status))
      {        
        button[i].touch_flag = 0;       /*�ͷŴ�����־*/
        
        button[i].draw_btn(&button[i]); /*�ػ水ť*/        
      
        button[i].btn_command(&button[i]);  /*ִ�а����Ĺ�������*/
        
        break;
      }
    }  

}

/*
��ť�¼�������
*/

static void button_switch_system_back(void *btn)
{
	if(system_back == BLACK) button[3].text = "��"; else button[3].text = "��";
	bottom_refresh = 1;
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

static void button_start(void *btn)
{
	printf("press start\n");
	time_stamp = time_stamp_ms;
	
	bottom_refresh = 1;
}

static void button_pause(void *btn)
{
	printf("press pause\n");
	rest_time += (time_stamp_ms-time_stamp);
	time_stamp = 0;
	bottom_refresh = 1;
}

static void button_clear(void *btn)
{
	rest_time = 0;
	time_stamp = 0;
	if(system_back == BLACK) LCD_SetColors(WHITE, BLACK); else LCD_SetColors(BLACK, WHITE);
	sprintf((char *)str,"%0.2d:%0.2d:%0.2d", 0, 0, 0);
	ILI9341_DisplayStringEx(LINEY(1.5),LINE(5),3*LINEY(1),3*LINE(1), (char*)str, 0);
	bottom_refresh = 1;
}



/*
 * ��������Time_Display
 * ����  ����ʾ��ǰʱ��ֵ
 * ����  ��-TimeVar RTC����ֵ����λΪ s
 * ���  ����
 * ����  ���ڲ�����
 */	
static void Time_Display()
{
	if (time_stamp == 0) return;
	now_time = time_stamp_ms;
	
	timer = rest_time + now_time - time_stamp;
	
	if(system_back == BLACK) LCD_SetColors(WHITE, BLACK); else LCD_SetColors(BLACK, WHITE);
	sprintf((char *)str,"%0.2d:%0.2d:%0.2d",
										 timer/1000/60, (timer/1000)%60, (timer%1000)/10);
	ILI9341_DisplayStringEx(LINEY(1.5),LINE(5),3*LINEY(1),3*LINE(1), (char*)str, 0);
}


