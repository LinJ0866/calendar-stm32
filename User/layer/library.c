#include "./layer/library.h"
#include "string.h"


#define BUTTON_NUM 4

/*��ť�ṹ������*/
static Touch_Button button[BUTTON_NUM];
static uint8_t real_first_dis = 1;
static uint8_t str[200]; // �ַ����ݴ�

static void button_switch_system_back(void *btn);
static void button_goto_clock(void *btn);
static void button_goto_temp(void *btn);
static void button_play(void *btn);

static void button_Init(void)
{
	button[0].start_x = LINEY(12);
  button[0].start_y = LINE(1)-10;
  button[0].end_x = LINEY(12)+LINE(2);
  button[0].end_y = LINE(1)-10+LINE(2);
	button[0].shape = 1;
	button[0].text = "��";
	button[0].text_len = 1;
	button[0].fore_color = BLUE;
  button[0].back_color = GREY1;
  button[0].touch_flag = 0;  
  button[0].draw_btn = Draw_Color_Button ;
  button[0].btn_command = button_switch_system_back;
	
	
	button[1].id = 1;
	button[1].start_x = LINEY(2);
  button[1].start_y = LINE(3.5);
	button[1].end_x = button[1].start_x+64;
  button[1].end_y = button[1].start_y+68+LINE(1);
	button[1].shape = 4;
	button[1].touch_flag = 0;  
  button[1].draw_btn = Draw_Color_Button ;
  button[1].btn_command = button_goto_clock;
	button[1].text = "ʱ��";
	button[1].text_len = 2;
	
	button[2].id = 2;
	button[2].start_x = LINEY(8.5);
  button[2].start_y = LINE(3.5);
	button[2].end_x = button[2].start_x+64;
  button[2].end_y = button[2].start_y+68+LINE(1);
	button[2].shape = 4;
	button[2].touch_flag = 0;  
  button[2].draw_btn = Draw_Color_Button ;
  button[2].btn_command = button_goto_temp;
	button[2].text = "�¶�";
	button[2].text_len = 2;
	
	button[3].id = 3;
	button[3].start_x = LINEY(2);
  button[3].start_y = LINE(10);
	button[3].end_x = button[3].start_x+64;
  button[3].end_y = button[3].start_y+68+LINE(1);
	button[3].shape = 4;
	button[3].touch_flag = 0;  
  button[3].draw_btn = Draw_Color_Button ;
  button[3].btn_command = button_play;
	button[3].text = "����";
	button[3].text_len = 2;
}



// ���������ٻ�
void Create_Library_layer()
{
	real_first_dis = 1;
	first_display = 1;
	page = 0;
}


/**
* @brief  ʱ��app�����ʼ��
* @param  ��
* @retval ��
*/
void Show_Library_layer(struct rtc_time *tm)
{
	uint8_t i;
	uint32_t BJ_TimeVar;
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
		for(i=0;i<BUTTON_NUM;i++)
		{
			button[i].draw_btn(&button[i]);
		}
		if(system_back == BLACK) LCD_SetColors(YELLOW, BLACK); else LCD_SetColors(BLUE1, WHITE);
		ILI9341_DrawBmp(LINEY(1),LINE(16),64,64, 0);
		if(system_back == BLACK) LCD_SetColors(WHITE, BLACK); else LCD_SetColors(BLACK, WHITE);
		ILI9341_DisplayStringEx(LINEY(1)+80, LINE(17),
														LINEY(1), LINE(1),
														"@LinJ0866", 0);
		LCD_SetColors(GREY, system_back);
		ILI9341_DisplayStringEx(LINEY(1)+80, LINE(18),
														LINEY(1), LINE(1),
														"ף���������~", 0);
		
		first_display = 0;
	}

	/*  �ѱ�׼ʱ��ת��Ϊ����ʱ��*/
	BJ_TimeVar =RTC_GetCounter() + TIME_ZOOM;
	to_tm(BJ_TimeVar, tm);/*�Ѷ�ʱ����ֵת��Ϊ����ʱ��*/	
	
	sprintf((char *)str,"%0.2d:%0.2d",
												tm->tm_hour, 									
												tm->tm_min);
	ILI9341_DisplayStringEx(LINEY(1), LINE(0.5),
														LINEY(1), LINE(1),
														str, 0);
}


/**
* @brief  Touch_Button_Down ����������ʱ���õĺ������ɴ���������
* @param  x ����λ�õ�x����
* @param  y ����λ�õ�y����
* @retval ��
*/
void Library_Button_Hover(uint16_t x,uint16_t y)
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
void Library_Button_Release(uint16_t x,uint16_t y)
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
	if(system_back == BLACK) button[0].text = "��"; else button[0].text = "��";
  switch_system_back();
}

static void button_goto_clock(void *btn)
{
	Create_Clock_layer();
}

static void button_goto_temp(void *btn)
{
	Create_Temperature_layer();
}

static void button_play(void *btn)
{
	play();
}
