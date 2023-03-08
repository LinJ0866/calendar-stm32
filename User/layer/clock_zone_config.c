#include "./layer/clock_zone_config.h"
#include "string.h"


#define BUTTON_NUM 3

/*��ť�ṹ������*/
static Touch_Button button[BUTTON_NUM];
static Touch_Button button1[4];
static uint8_t max_dis_count = 2;
static uint8_t has_choose = 2;
static uint8_t refresh_top = 1;
static uint8_t real_first_dis = 1;
static uint8_t local_page = 1;
static uint8_t str[200]; // �ַ����ݴ�  

static void zones_Display(uint16_t y, char *location, int rest, uint8_t id);
static void button_goto_clock(void *btn);
static void button_prev_page(void *btn);
static void button_next_page(void *btn);
static void button_switch_select(void *btn);

static void button_Init(void)
{
	button[0].start_x = LINEY(1);
  button[0].start_y = LINE(1)-10;
  button[0].end_x = LINEY(1)+LINE(2);
  button[0].end_y = LINE(1)-10+LINE(2);
	button[0].shape = 2;
	button[0].text = "��";
	button[0].text_len = 0.5;
	button[0].fore_color = BLUE;
  button[0].touch_flag = 0;  
  button[0].draw_btn = Draw_Color_Button ;
  button[0].btn_command = button_goto_clock;
	
	button[1].start_x = LINEY(3);
  button[1].start_y = LINE(17);
  button[1].end_x = LINEY(3)+LINE(4);
  button[1].end_y = LINE(17)+LINE(2);
	button[1].shape = 0;
	button[1].text = "��һҳ";
	button[1].text_len = 3;
	button[1].fore_color = GREY;
  button[1].back_color = GREY1;
  button[1].touch_flag = 0;  
  button[1].draw_btn = Draw_Color_Button ;
  button[1].btn_command = button_prev_page;
	
	button[2].start_x = LINEY(8);
  button[2].start_y = LINE(17);
  button[2].end_x = LINEY(8)+LINE(4);
  button[2].end_y = LINE(17)+LINE(2);
	button[2].shape = 0;
	button[2].text = "��һҳ";
	button[2].text_len = 3;
	button[2].fore_color = BLUE;
  button[2].back_color = GREY1;
  button[2].touch_flag = 0;  
  button[2].draw_btn = Draw_Color_Button ;
  button[2].btn_command = button_next_page;
	
	button1[0].start_x = LINEY(10);
  button1[0].start_y = LINE(3);
	button1[0].end_x = button1[0].start_x+LINE(4.6);
  button1[0].end_y = button1[0].start_y+LINE(2);
	button1[0].shape = 3;
  button1[0].touch_flag = 0;  
  button1[0].draw_btn = Draw_Color_Button ;
  button1[0].btn_command = button_switch_select;
	
	button1[1].start_x = LINEY(10);
  button1[1].start_y = LINE(6.5);
	button1[1].end_x = button1[1].start_x+LINE(4.6);
  button1[1].end_y = button1[1].start_y+LINE(2);
	button1[1].shape = 3;
  button1[1].touch_flag = 0;  
  button1[1].draw_btn = Draw_Color_Button ;
  button1[1].btn_command = button_switch_select;
	
	button1[2].start_x = LINEY(10);
  button1[2].start_y = LINE(10);
	button1[2].end_x = button1[2].start_x+LINE(4.6);
  button1[2].end_y = button1[2].start_y+LINE(2);
	button1[2].shape = 3;
  button1[2].touch_flag = 0;  
  button1[2].draw_btn = Draw_Color_Button ;
  button1[2].btn_command = button_switch_select;
	
	button1[3].start_x = LINEY(10);
  button1[3].start_y = LINE(13.5);
	button1[3].end_x = button1[3].start_x+LINE(4.6);
  button1[3].end_y = button1[3].start_y+LINE(2);
	button1[3].shape = 3;
  button1[3].touch_flag = 0;  
  button1[3].draw_btn = Draw_Color_Button ;
  button1[3].btn_command = button_switch_select;
}


// ���������ٻ�
void Create_Clock_Zone_Config_layer()
{
	real_first_dis = 1;
	refresh_top = 1;
	first_display = 1;
	page = 2;
	local_page = 1;
}


/**
* @brief  ʱ��app�����ʼ��
* @param  ��
* @retval ��
*/
void Show_Clock_Zone_Config_layer(void)
{
	/* ��ʼ����ť */
	if (real_first_dis) {
		button_Init();
		real_first_dis = 0;
	}
	
	if(refresh_top)
	{ 
		
		if(system_back == BLACK) LCD_SetColors(WHITE, BLACK); else LCD_SetColors(BLACK, WHITE);
		ILI9341_Clear(0,0,LCD_X_LENGTH,LINE(2.5));
	  sprintf((char *)str,"GMTѡ��(%d/%d)", has_choose, max_dis_count);
		ILI9341_DisplayStringEx(LINEY(5),LINE(1),LINEY(1),LINE(1), (char*)str, 0);
		button[0].draw_btn(&button[0]);
		refresh_top = 0;
	}
  
	if(first_display)
	{
		uint8_t i;
		if(system_back == BLACK) LCD_SetColors(WHITE, BLACK); else LCD_SetColors(BLACK, WHITE);
		ILI9341_Clear(0,LINE(3),LCD_X_LENGTH,LCD_Y_LENGTH);
		
		/* ��水ť */
		for(i=1;i<BUTTON_NUM;i++)
		{
			button[i].draw_btn(&button[i]);
		}
		
		for(i=4*(local_page-1); i<4*local_page && i<25; i++)
		{
			zones_Display(LINE(3+(i-4*(local_page-1))*3.5), zone[i].name, zone[i].zone, i);
			button1[i-4*(local_page-1)].id = i;
			button1[i-4*(local_page-1)].is_checked = &zone[i].is_select;
			button1[i-4*(local_page-1)].draw_btn(&button1[i-4*(local_page-1)]);
		}
		
		first_display = 0;
		// Time_Display( RTC_GetCounter(),tm);
	}

}


/**
* @brief  Touch_Button_Down ����������ʱ���õĺ������ɴ���������
* @param  x ����λ�õ�x����
* @param  y ����λ�õ�y����
* @retval ��
*/
void Clock_Zone_Config_Button_Hover(uint16_t x,uint16_t y)
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
	for(i=0;i<4;i++)
  {
    /* �������˰�ť */
    if(x<=button1[i].end_x && y<=button1[i].end_y && y>=button1[i].start_y && x>=button1[i].start_x )
    {
      if(button1[i].touch_flag == 0)     /*ԭ����״̬Ϊû�а��£������״̬*/
      {
      button1[i].touch_flag = 1;         /* ��¼���±�־ */
      
      button1[i].draw_btn(&button1[i]);  /*�ػ水ť*/
      }        
      
    }
    else if(button1[i].touch_flag == 1) /* �����Ƴ��˰����ķ�Χ��֮ǰ�а��°�ť */
    {
      button1[i].touch_flag = 0;         /* ������±�־���ж�Ϊ�����*/ 
      button1[i].draw_btn(&button1[i]);   /*�ػ水ť*/
    }
  }
}

/**
* @brief  Touch_Button_Up �������ͷ�ʱ���õĺ������ɴ���������
* @param  x ��������ͷ�ʱ��x����
* @param  y ��������ͷ�ʱ��y����
* @retval ��
*/
void Clock_Zone_Config_Button_Release(uint16_t x,uint16_t y)
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
		for(i=0;i<4;i++)
   {
      if((x<button1[i].end_x && x>button1[i].start_x && y<button1[i].end_y && y>button1[i].start_y))
      {        
        button1[i].touch_flag = 0;       /*�ͷŴ�����־*/
        
        button1[i].draw_btn(&button1[i]); /*�ػ水ť*/        
      
        button1[i].btn_command(&button1[i]);  /*ִ�а����Ĺ�������*/
        
        break;
      }
    }	 

}


static void button_goto_clock(void *btn)
{
	Create_Clock_layer();
}

static void button_prev_page(void *btn)
{
	if(local_page == 1) return;
	if(local_page == 7) button[2].fore_color = BLUE;
	local_page --;
	if(local_page == 1) button[1].fore_color = GREY;
	first_display = 1;	
}
static void button_next_page(void *btn)
{
	if(local_page == 7) return;
	if(local_page == 1) button[1].fore_color = BLUE;
	local_page ++;
	if(local_page == 7) button[2].fore_color = GREY;
	first_display = 1;
}

static void button_switch_select(void *btn)
{
	Touch_Button *ptr = (Touch_Button *)btn;
	
	if(*ptr->is_checked){
		*ptr->is_checked  = 0;
		has_choose -= 1;
	}else if(has_choose < max_dis_count){
		*ptr->is_checked = 1;
		has_choose += 1;
	} else {
		LCD_SetColors(RED, system_back);
	  sprintf((char *)str,"GMTѡ��(%d/%d)", has_choose, max_dis_count);
		ILI9341_DisplayStringEx(LINEY(5),LINE(1),LINEY(1),LINE(1), (char*)str, 0);
		return;
	}
	ptr->draw_btn(ptr);
	refresh_top = 1;
}

static void zones_Display(uint16_t y, char *location, int rest, uint8_t id)
{
		if(system_back == BLACK) LCD_SetColors(WHITE, BLACK); else LCD_SetColors(BLACK, WHITE);
	  sprintf((char *)str,"%s", location);
		ILI9341_DisplayStringEx(LINEY(1),y, LINEY(1.3), LINE(1.3), (char*)str, 0);
		sprintf((char *)str,"  GMT%+d", rest);
		LCD_SetTextColor(GREY);
		ILI9341_DispStringLine_EN_CH(y+LINE(1.5),(char*)str);
}

