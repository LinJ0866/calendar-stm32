#include "./layer/temperature.h"


#define BUTTON_NUM 2

extern __IO u16 ADC_ConvertedValue;
extern __IO uint32_t TimeDisplay;
extern uint8_t uc, ucDs18b20Id [ 8 ];

static uint8_t str[200]; // �ַ����ݴ�
static uint8_t fan_status;

/*��ť�ṹ������*/
static u16 Current_Temp;	
static Touch_Button button[BUTTON_NUM];

static void button_switch_system_back(void *btn);
static void button_switch_fan(void *btn);

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
	
	button[1].start_x = LINEY(6);
  button[1].start_y = LINE(17);
  button[1].end_x = LINEY(6)+LINE(4);
  button[1].end_y = LINE(17)+LINE(2);
	button[1].shape = 0;
	button[1].text = "��";
	button[1].text_len = 1;
	button[1].fore_color = BLUE;
  button[1].back_color = GREY1;
  button[1].touch_flag = 0;  
  button[1].draw_btn = Draw_Color_Button ;
  button[1].btn_command = button_switch_fan;
}

// ���������ٻ�
void Create_Temperature_layer()
{
	first_display = 1;
	page = 5;
	fan_status = 0;
}


/**
* @brief  app�����ʼ��
* @param  ��
* @retval ��
*/
void Show_Temperature_layer(void)
{
	uint8_t i;

	if(first_display)
	{
		button_Init();
		if(system_back == BLACK) LCD_SetColors(WHITE, BLACK); else LCD_SetColors(BLACK, WHITE);
		ILI9341_Clear(0,0,LCD_X_LENGTH,LCD_Y_LENGTH);
		
		/* ��水ť */
		for(i=0;i<BUTTON_NUM;i++)
		{
			button[i].draw_btn(&button[i]);
		}
		
		first_display = 0;
		if(system_back == BLACK) LCD_SetColors(WHITE, BLACK); else LCD_SetColors(BLACK, WHITE);
		ILI9341_DisplayStringEx(LINEY(1),LINE(3),LINE(1),LINE(1), "The IC current temperature", 0);
		ILI9341_DisplayStringEx(LINEY(1),LINE(5),LINE(3),LINE(3), "--��", 0);
		
		ILI9341_DisplayStringEx(LINEY(1),LINE(10),LINE(1),LINE(1), "The actual temperature", 0);
		ILI9341_DisplayStringEx(LINEY(1),LINE(12),LINE(3),LINE(3), "--��", 0);
	}
	if (TimeDisplay == 1) {
		if(system_back == BLACK) LCD_SetColors(WHITE, BLACK); else LCD_SetColors(BLACK, WHITE);
		ILI9341_Clear(0,LINE(5), LCD_X_LENGTH,LINE(3));
		ILI9341_Clear(0,LINE(12), LCD_X_LENGTH,LINE(3));
		Current_Temp=(V25-ADC_ConvertedValue)/AVG_SLOPE+25;
		sprintf((char *)str,"%02d��", Current_Temp);
		ILI9341_DisplayStringEx(LINEY(1),LINE(5),LINE(3),LINE(3), (char*)str, 0);
		sprintf((char *)str,"%02.1lf��", DS18B20_GetTemp_MatchRom ( ucDs18b20Id ));
		ILI9341_DisplayStringEx(LINEY(1),LINE(12),LINE(3),LINE(3), (char*)str, 0);
		TimeDisplay = 0;
	}
}


/**
* @brief  Touch_Button_Down ����������ʱ���õĺ������ɴ���������
* @param  x ����λ�õ�x����
* @param  y ����λ�õ�y����
* @retval ��
*/
void Temperature_Button_Hover(uint16_t x,uint16_t y)
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
void Temperature_Button_Release(uint16_t x,uint16_t y)
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
	first_display = 1;
  switch_system_back();
}

static void button_switch_fan(void *btn)
{
	if(fan_status) {
		FAN(OFF);
		button[1].text = "��";
		fan_status = 0;
	} else {
		FAN(ON);
		button[1].text = "��";
		fan_status = 1;
	}
	button[1].draw_btn(&button[1]);
}

