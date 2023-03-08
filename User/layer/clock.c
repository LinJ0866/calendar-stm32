#include "./layer/clock.h"
#include "string.h"


/* 秒中断标志，进入秒中断时置1，当时间被刷新之后清0 */
__IO uint32_t TimeDisplay = 0;

#define BUTTON_NUM 5

static uint8_t month[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

/*按钮结构体数组*/
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
	button[0].text = "明";
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
	button[2].text = "闹钟";
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
	button[3].text = "时钟";
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
	button[4].text = "秒表";
	button[4].text_len = 2;
  button[4].dark_adapt = 1;
  button[4].touch_flag = 0;  
  button[4].draw_btn = Draw_Color_Button ;
  button[4].btn_command = button_goto_clock_stop;
}


// 窗体生命召唤
void Create_Clock_layer()
{
	real_first_dis = 1;
	first_display = 1;
	page = 1;
	
}


/**
* @brief  时间app界面初始化
* @param  无
* @retval 无
*/
void Show_Clock_layer(struct rtc_time *tm)
{
	/* 初始化按钮 */
	if (real_first_dis) {
		button_Init();
		real_first_dis = 0;
	}
  
	if(first_display)
	{
		uint8_t i;

		if(system_back == BLACK) LCD_SetColors(WHITE, BLACK); else LCD_SetColors(BLACK, WHITE);
		ILI9341_Clear(0,0,LCD_X_LENGTH,LCD_Y_LENGTH);
		
		
		/* 描绘按钮 */
		for(i=0;i<BUTTON_NUM;i++)
		{
			button[i].draw_btn(&button[i]);
		}
		first_display = 0;
		Time_Display( RTC_GetCounter(),tm);
	}

	/* 每过1s */
	if (TimeDisplay == 1)
	{
		/* Display current time */
     Time_Display( RTC_GetCounter(),tm); 		  
     TimeDisplay = 0;
  }
}


/**
* @brief  Touch_Button_Down 按键被按下时调用的函数，由触摸屏调用
* @param  x 触摸位置的x坐标
* @param  y 触摸位置的y坐标
* @retval 无
*/
void Clock_Button_Hover(uint16_t x,uint16_t y)
{
  uint8_t i;
  for(i=0;i<BUTTON_NUM;i++)
  {
    /* 触摸到了按钮 */
    if(x<=button[i].end_x && y<=button[i].end_y && y>=button[i].start_y && x>=button[i].start_x )
    {
      if(button[i].touch_flag == 0)     /*原本的状态为没有按下，则更新状态*/
      {
      button[i].touch_flag = 1;         /* 记录按下标志 */
      
      button[i].draw_btn(&button[i]);  /*重绘按钮*/
      }        
      
    }
    else if(button[i].touch_flag == 1) /* 触摸移出了按键的范围且之前有按下按钮 */
    {
      button[i].touch_flag = 0;         /* 清除按下标志，判断为误操作*/ 
      button[i].draw_btn(&button[i]);   /*重绘按钮*/
    }
  }
}

/**
* @brief  Touch_Button_Up 按键被释放时调用的函数，由触摸屏调用
* @param  x 触摸最后释放时的x坐标
* @param  y 触摸最后释放时的y坐标
* @retval 无
*/
void Clock_Button_Release(uint16_t x,uint16_t y)
{
   uint8_t i; 
   for(i=0;i<BUTTON_NUM;i++)
   {
     /* 触笔在按钮区域释放 */
      if((x<button[i].end_x && x>button[i].start_x && y<button[i].end_y && y>button[i].start_y))
      {        
        button[i].touch_flag = 0;       /*释放触摸标志*/
        
        button[i].draw_btn(&button[i]); /*重绘按钮*/        
      
        button[i].btn_command(&button[i]);  /*执行按键的功能命令*/
        
        break;
      }
    }  

}

/*
按钮事件定义区
*/

static void button_switch_system_back(void *btn)
{
	if(system_back == BLACK) button[0].text = "暗"; else button[0].text = "明";
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
 * 函数名：Time_Show
 * 描述  ：显示当前时间值
 * 输入  ：无
 * 输出  ：无
 * 调用  ：外部调用
 */ 
static void AdjoinTime_Display(uint16_t y, char *location, int rest,struct rtc_time tm)
{
		uint8_t str[200]; // 字符串暂存 
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
			sprintf((char *)str,"  %s%d小时%12d月%d日",
													"慢",
													8-rest,
													tm.tm_mon,
													tm.tm_mday);
		} else if(rest < 8) {
			sprintf((char *)str,"  %s%d小时%13d月%d日",
													"慢",
													8-rest,
													tm.tm_mon,
													tm.tm_mday);

		} else {
			sprintf((char *)str,"  %s%d小时%13d月%d日",
													"快",
													rest-8,
													tm.tm_mon,
													tm.tm_mday);

		}
		LCD_SetTextColor(GREY);
		ILI9341_DispStringLine_EN_CH(y+LINE(1.5),(char*)str);
}


/*
 * 函数名：Time_Display
 * 描述  ：显示当前时间值
 * 输入  ：-TimeVar RTC计数值，单位为 s
 * 输出  ：无
 * 调用  ：内部调用
 */	
static void Time_Display(uint32_t TimeVar,struct rtc_time *tm)
{
	   uint32_t BJ_TimeVar;
	   uint8_t str[200]; // 字符串暂存  
		 uint8_t dis_count = 0;
		 uint8_t i = 0;

	   /*  把标准时间转换为北京时间*/
	   BJ_TimeVar =TimeVar + TIME_ZOOM;

	   to_tm(BJ_TimeVar, tm);/*把定时器的值转换为北京时间*/	
	
		/*
		 if((!tm->tm_hour && !tm->tm_min && !tm->tm_sec)  || (FirstDisplay))
	   {
	      
	        GetChinaCalendar((u16)tm->tm_year, (u8)tm->tm_mon, (u8)tm->tm_mday, str);	
					printf("\r\n 今天新历：%0.2d%0.2d,%0.2d,%0.2d", str[0], str[1], str[2],  str[3]);
	
	        GetChinaCalendarStr((u16)tm->tm_year,(u8)tm->tm_mon,(u8)tm->tm_mday,str);
					printf("\r\n 今天农历：%s\r\n", str);
	
	        if(GetJieQiStr((u16)tm->tm_year, (u8)tm->tm_mon, (u8)tm->tm_mday, str))
					   printf("\r\n 今天农历：%s\r\n", str);
	
	        FirstDisplay = 0;
	  }	 	  	
		

	  // 输出时间戳，公历时间
	  printf(" UNIX时间戳 = %d 当前时间为: %d年(%s年) %d月 %d日 (星期%s)  %0.2d:%0.2d:%0.2d\r",TimeVar,
	                    tm->tm_year, zodiac_sign[(tm->tm_year-3)%12], tm->tm_mon, tm->tm_mday, 
	                    WEEK_STR[tm->tm_wday], tm->tm_hour, 
	                    tm->tm_min, tm->tm_sec);
		
		*/
		
		if(system_back == BLACK) LCD_SetColors(WHITE, BLACK); else LCD_SetColors(BLACK, WHITE);
		//时间
		sprintf((char *)str,"%0.2d:%0.2d:%0.2d",
																						tm->tm_hour, 									
																						tm->tm_min, 
																						tm->tm_sec);
		ILI9341_DisplayStringEx(LINEY(1),LINE(3),3*LINEY(1),3*LINE(1), (char*)str, 0);
		
		
		//日期
		sprintf((char *)str,"  %d年%d月%d日 周%s",
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
		
		// ILI9341_DisplayStringEx(LINEY(14),LINE(13),LINEY(1), LINE(1), "新", 0);
		
}


