#include "./ui/button.h"


void Draw_Color_Button(void *btn)
{
  Touch_Button *ptr = (Touch_Button *)btn;
	if(ptr->shape == 3) { // switch
		if(ptr->touch_flag == 0)
		{
			if(*ptr->is_checked)
			{
				LCD_SetTextColor(BLUE);
				ILI9341_DrawCircle(ptr->start_x, ptr->start_y+LINE(1), LINE(1), 1);
				ILI9341_DrawRectangle(ptr->start_x, ptr->start_y, LINE(2.6), LINE(2), 1);
				ILI9341_DrawCircle(ptr->start_x+LINE(2.6), ptr->start_y+LINE(1), LINE(1), 1);
				LCD_SetTextColor(WHITE);
				ILI9341_DrawCircle(ptr->start_x+LINE(2.6), ptr->start_y+LINE(1), LINE(0.5), 1);
			} else {
				LCD_SetTextColor(GREY1);
				ILI9341_DrawCircle(ptr->start_x, ptr->start_y+LINE(1), LINE(1), 1);
				ILI9341_DrawRectangle(ptr->start_x, ptr->start_y, LINE(2.6), LINE(2), 1);
				ILI9341_DrawCircle(ptr->start_x+LINE(2.6), ptr->start_y+LINE(1), LINE(1), 1);
				LCD_SetTextColor(WHITE);
				ILI9341_DrawCircle(ptr->start_x, ptr->start_y+LINE(1), LINE(0.5), 1);
			}
		}
		return;
	}
	else if(ptr->shape == 1) // 圆形按钮
	{
		/*释放按键*/
		if(ptr->touch_flag == 0)
		{
			LCD_SetColors(ptr->back_color,ptr->back_color);
			ILI9341_DrawCircle(	ptr->start_x+(ptr->end_x - ptr->start_x)/2,
																ptr->start_y+(ptr->end_y - ptr->start_y)/2,
																(ptr->end_x - ptr->start_x)/2,1);
		}
		else  /*按键按下*/
		{
			if(system_back == BLACK) LCD_SetColors(BLACK, BLACK); else LCD_SetColors(WHITE, WHITE);
			ILI9341_DrawCircle(	ptr->start_x+(ptr->end_x - ptr->start_x)/2,
																ptr->start_y+(ptr->end_x - ptr->start_x)/2,
																(ptr->end_x - ptr->start_x)/2,1);
			
			/*白色背景*/
			if (ptr->back_color + 0x2084 < ptr->back_color)
			{
					LCD_SetColors(WHITE,WHITE);
			}
			else
			{
				LCD_SetColors(ptr->back_color + 0x2084,ptr->back_color + 0x2084);
			}
			
			ILI9341_DrawCircle(	ptr->start_x+(ptr->end_x - ptr->start_x)/2,
																ptr->start_y+(ptr->end_x - ptr->start_x)/2,
																(ptr->end_x - ptr->start_x)/2-2,1);
			#if 0
			/*按钮边框*/
			LCD_SetColors(GREEN,BLUE2);
			ILI9341_DrawCircle(	ptr->start_x+(ptr->end_x - ptr->start_x)/2,
																ptr->start_y+(ptr->end_x - ptr->start_x)/2,
																(ptr->end_x - ptr->start_x)/2-2,0);
			#endif
		}
	}
	else if (ptr->shape == 0) // 方形按钮
	{
		/*释放按键*/
		if(ptr->touch_flag == 0)
		{
			/*背景为功能键相应的颜色*/
			LCD_SetColors(ptr->back_color,ptr->back_color);
			ILI9341_DrawRectangle(	ptr->start_x,
																ptr->start_y,
																ptr->end_x - ptr->start_x,
																ptr->end_y - ptr->start_y,1);
		}
		else  /*按键按下*/
		{
			if(system_back == BLACK) LCD_SetColors(BLACK, BLACK); else LCD_SetColors(WHITE, WHITE);
			ILI9341_DrawRectangle(	ptr->start_x,
																ptr->start_y,
																ptr->end_x - ptr->start_x,
																ptr->end_y - ptr->start_y,1);
			
			if (ptr->back_color + 0x2084 < ptr->back_color)
			{
					LCD_SetColors(WHITE,WHITE);
			}
			else
			{
				LCD_SetColors(ptr->back_color + 0x2084,ptr->back_color + 0x2084);
			}
			
			ILI9341_DrawRectangle(	ptr->start_x+2,
															ptr->start_y+2,
															ptr->end_x - ptr->start_x-4,
															ptr->end_y - ptr->start_y-4,1);
			#if 0
			/*按钮边框*/
			LCD_SetColors(GREEN,BLUE2);
			ILI9341_DrawRectangle(	ptr->start_x+2,
																ptr->start_y+2,
																ptr->end_x - ptr->start_x-4,
																ptr->end_y - ptr->start_y-4,0);
			#endif
		} 
	}else if (ptr->shape == 4) {
		/*释放按键*/
		if(ptr->touch_flag == 0)
		{
			if(system_back == BLACK) LCD_SetColors(WHITE, BLACK); else LCD_SetColors(BLACK, WHITE);
			ILI9341_Clear( ptr->start_x-2,
										 ptr->start_y-2,
										 68,
										 74+LINE(1)
			);
		}
		else  /*按键按下*/
		{
			LCD_SetColors(BLUE, system_back);
			ILI9341_DrawRectangle(	ptr->start_x-2,
															ptr->start_y-2,
														  68, 74+LINE(1), 0);
		}
		LCD_SetColors(BLUE, system_back);
		ILI9341_DrawBmp(ptr->start_x, ptr->start_y,64,64, ptr->id);
		if(system_back == BLACK) LCD_SetColors(WHITE, BLACK); else LCD_SetColors(BLACK, WHITE);
		ILI9341_DisplayStringEx(ptr->start_x+32-LINEY(ptr->text_len)/2,
															ptr->start_y+70,
															LINEY(1), LINE(1),
															ptr->text, 0);
		return;
	}
	
	LCD_SetTextColor(ptr->fore_color);
	if(ptr->dark_adapt) {
		if(system_back == BLACK) LCD_SetColors(WHITE, BLACK); else LCD_SetColors(BLACK, WHITE);
	}
	if (strcmp(ptr->text, ""))
	{
		ILI9341_DisplayStringEx(ptr->start_x+(ptr->end_x - ptr->start_x)/2-ptr->text_len*LINEY(0.5),
														ptr->start_y+(ptr->end_y - ptr->start_y)/2-LINE(0.5),
														LINEY(1), LINE(1),
														ptr->text, 0);
	} 
}
