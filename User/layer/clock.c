#include "./layer/clock.h"
#include "string.h"


/* ���жϱ�־���������ж�ʱ��1����ʱ�䱻ˢ��֮����0 */
__IO uint32_t TimeDisplay = 0;

#define BUTTON_NUM 5

static uint8_t month[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

/*��ť�ṹ������*/
static Touch_Button button[BUTTON_NUM];
static uint8_t max_dis_count = 2;
static uint8_t real_first_dis = 1;

static void Time_Display(uint32_t TimeVar,struct rtc_time *tm);

static void button_switch_system_back(void *btn);
static void button_goto_zone(void *btn);
static void button_switch_system_back(void *btn);
static void button_goto_clock_alert(void *btn);
static void button_goto_clock(void *btn);
static void button_goto_clock_stop(void *btn);

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
	
	button[1].start_x = LINEY(7);
  button[1].start_y = LINE(17);
  button[1].end_x = LINEY(7)+LINE(2);
  button[1].end_y = LINE(17)+LINE(2);
	button[1].shape = 1;
	button[1].text = "+";
	button[1].text_len = 0.5;
	button[1].fore_color = BLUE;
  button[1].back_color = GREY1;
  button[1].touch_flag = 0;  
  button[1].draw_btn = Draw_Color_Button ;
  button[1].btn_command = button_goto_zone;
	
	button[2].start_x = LINEY(1);
  button[2].start_y = LINE(1);
  button[2].end_x = LINEY(1)+LINEY(2);
  button[2].end_y = LINE(1)+LINE(1);
	button[2].shape = 2;
	button[2].text = "����";
	button[2].text_len = 2;
  button[2].dark_adapt = 1;
  button[2].touch_flag = 0;  
  button[2].draw_btn = Draw_Color_Button ;
  button[2].btn_command = button_goto_clock_alert;
	
	button[3].start_x = LINEY(4);
  button[3].start_y = LINE(1);
  button[3].end_x = LINEY(4)+LINEY(2);
  button[3].end_y = LINE(1)+LINE(1);
	button[3].shape = 2;
	button[3].text = "ʱ��";
	button[3].text_len = 2;
  button[3].fore_color = BLUE;
  button[3].touch_flag = 0;  
  button[3].draw_btn = Draw_Color_Button ;
  button[3].btn_command = button_goto_clock;
	
	button[4].start_x = LINEY(7);
  button[4].start_y = LINE(1);
  button[4].end_x = LINEY(7)+LINEY(2);
  button[4].end_y = LINE(1)+LINE(1);
	button[4].shape = 2;
	button[4].text = "���";
	button[4].text_len = 2;
  button[4].dark_adapt = 1;
  button[4].touch_flag = 0;  
  button[4].draw_btn = Draw_Color_Button ;
  button[4].btn_command = button_goto_clock_stop;
}


// ���������ٻ�
void Create_Clock_layer()
{
	real_first_dis = 1;
	first_display = 1;
	page = 1;
	
}


/**
* @brief  ʱ��app�����ʼ��
* @param  ��
* @retval ��
*/
void Show_Clock_layer(struct rtc_time *tm)
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
		
		
		/* ��水ť */
		for(i=0;i<BUTTON_NUM;i++)
		{
			button[i].draw_btn(&button[i]);
		}
		first_display = 0;
		Time_Display( RTC_GetCounter(),tm);
	}

	/* ÿ��1s */
	if (TimeDisplay == 1)
	{
		/* Display current time */
     Time_Display( RTC_GetCounter(),tm); 		  
     TimeDisplay = 0;
  }
}


/**
* @brief  Touch_Button_Down ����������ʱ���õĺ������ɴ���������
* @param  x ����λ�õ�x����
* @param  y ����λ�õ�y����
* @retval ��
*/
void Clock_Button_Hover(uint16_t x,uint16_t y)
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
void Clock_Button_Release(uint16_t x,uint16_t y)
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

/*
��ť�¼�������
*/

static void button_switch_system_back(void *btn)
{
	if(system_back == BLACK) button[0].text = "��"; else button[0].text = "��";
  switch_system_back();
}

static void button_goto_zone(void *btn)
{
	Create_Clock_Zone_Config_layer();
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



/*
 * ��������Time_Show
 * ����  ����ʾ��ǰʱ��ֵ
 * ����  ����
 * ���  ����
 * ����  ���ⲿ����
 */ 
static void AdjoinTime_Display(uint16_t y, char *location, int rest,struct rtc_time tm)
{
		uint8_t str[200]; // �ַ����ݴ� 
		if(system_back == BLACK) LCD_SetColors(WHITE, BLACK); else LCD_SetColors(BLACK, WHITE);
		tm.tm_hour = tm.tm_hour-8+rest;
		if(tm.tm_hour < 0) {
			tm.tm_hour += 24;
			tm.tm_mday -= 1;
			if(tm.tm_mday < 1) {
				if(tm.tm_mon == 1) tm.tm_mon = 13;
				tm.tm_mon -= 1;
				tm.tm_mday += month[tm.tm_mon-1];
				if((tm.tm_year % 4 == 0 && tm.tm_year % 100) || tm.tm_year % 400 == 0) tm.tm_mday += 1;
			}
		}
	  sprintf((char *)str,"%-15s%0.2d:%0.2d",
												location,
												tm.tm_hour, 									
												tm.tm_min);
		ILI9341_DisplayStringEx(LINEY(1),y, LINEY(1.3), LINE(1.3), (char*)str, 0);
		if(rest < -2)
		{
			sprintf((char *)str,"  %s%dСʱ%12d��%d��",
													"��",
													8-rest,
													tm.tm_mon,
													tm.tm_mday);
		} else if(rest < 8) {
			sprintf((char *)str,"  %s%dСʱ%13d��%d��",
													"��",
													8-rest,
													tm.tm_mon,
													tm.tm_mday);

		} else {
			sprintf((char *)str,"  %s%dСʱ%13d��%d��",
													"��",
													rest-8,
													tm.tm_mon,
													tm.tm_mday);

		}
		LCD_SetTextColor(GREY);
		ILI9341_DispStringLine_EN_CH(y+LINE(1.5),(char*)str);
}


/*
 * ��������Time_Display
 * ����  ����ʾ��ǰʱ��ֵ
 * ����  ��-TimeVar RTC����ֵ����λΪ s
 * ���  ����
 * ����  ���ڲ�����
 */	
static void Time_Display(uint32_t TimeVar,struct rtc_time *tm)
{
	   uint32_t BJ_TimeVar;
	   uint8_t str[200]; // �ַ����ݴ�  
		 uint8_t dis_count = 0;
		 uint8_t i = 0;

	   /*  �ѱ�׼ʱ��ת��Ϊ����ʱ��*/
	   BJ_TimeVar =TimeVar + TIME_ZOOM;

	   to_tm(BJ_TimeVar, tm);/*�Ѷ�ʱ����ֵת��Ϊ����ʱ��*/	
	
		/*
		 if((!tm->tm_hour && !tm->tm_min && !tm->tm_sec)  || (FirstDisplay))
	   {
	      
	        GetChinaCalendar((u16)tm->tm_year, (u8)tm->tm_mon, (u8)tm->tm_mday, str);	
					printf("\r\n ����������%0.2d%0.2d,%0.2d,%0.2d", str[0], str[1], str[2],  str[3]);
	
	        GetChinaCalendarStr((u16)tm->tm_year,(u8)tm->tm_mon,(u8)tm->tm_mday,str);
					printf("\r\n ����ũ����%s\r\n", str);
	
	        if(GetJieQiStr((u16)tm->tm_year, (u8)tm->tm_mon, (u8)tm->tm_mday, str))
					   printf("\r\n ����ũ����%s\r\n", str);
	
	        FirstDisplay = 0;
	  }	 	  	
		

	  // ���ʱ���������ʱ��
	  printf(" UNIXʱ��� = %d ��ǰʱ��Ϊ: %d��(%s��) %d�� %d�� (����%s)  %0.2d:%0.2d:%0.2d\r",TimeVar,
	                    tm->tm_year, zodiac_sign[(tm->tm_year-3)%12], tm->tm_mon, tm->tm_mday, 
	                    WEEK_STR[tm->tm_wday], tm->tm_hour, 
	                    tm->tm_min, tm->tm_sec);
		
		*/
		
		if(system_back == BLACK) LCD_SetColors(WHITE, BLACK); else LCD_SetColors(BLACK, WHITE);
		//ʱ��
		sprintf((char *)str,"%0.2d:%0.2d:%0.2d",
																						tm->tm_hour, 									
																						tm->tm_min, 
																						tm->tm_sec);
		ILI9341_DisplayStringEx(LINEY(1),LINE(3),3*LINEY(1),3*LINE(1), (char*)str, 0);
		
		
		//����
		sprintf((char *)str,"  %d��%d��%d�� ��%s",
																						tm->tm_year, 
																						tm->tm_mon,
																						tm->tm_mday,
																						WEEK_STR[tm->tm_wday]);
		LCD_SetTextColor(GREY);
		ILI9341_DispStringLine_EN_CH(LINE(6),(char*)str);

		for(i=0; i<26; i++)
		{
			if(zone[i].is_select == 1 && dis_count < max_dis_count) {
				AdjoinTime_Display(LINE(9)+dis_count*LINE(4), zone[i].name, zone[i].zone, *tm);
				dis_count ++;
			}
		}
		
		// ILI9341_DisplayStringEx(LINEY(14),LINE(13),LINEY(1), LINE(1), "��", 0);
		
}


