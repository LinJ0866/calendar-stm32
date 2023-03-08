#include "./common/common.h"

timeZone zone[25];

void timeZoneInit(void)
{
	zone[0].zone = 0;
	zone[0].name = "Ӣ��";
	zone[0].is_select = 1;
	zone[1].zone = 1;
	zone[1].name = "�¹�";
	zone[1].is_select = 0;
	zone[2].zone = 2;
	zone[2].name = "������";
	zone[2].is_select = 0;
	zone[3].zone = 3;
	zone[3].name = "����˹";
	zone[3].is_select = 0;
	zone[4].zone = 4;
	zone[4].name = "�ϰ�";
	zone[4].is_select = 0;
	zone[5].zone = 5;
	zone[5].name = "ӡ��";
	zone[5].is_select = 0;
	zone[6].zone = 6;
	zone[6].name = "�ϼ�����";
	zone[6].is_select = 0;
	zone[7].zone = 7;
	zone[7].name = "̩��";
	zone[7].is_select = 0;
	zone[8].zone = 8;
	zone[8].name = "�й�";
	zone[8].is_select = 0;
	zone[9].zone = 9;
	zone[9].name = "�ձ�";
	zone[9].is_select = 0;
	zone[10].zone = 10;
	zone[10].name = "Ϥ��";
	zone[10].is_select = 0;
	zone[11].zone = 11;
	zone[11].name = "������Ⱥ��";
	zone[11].is_select = 0;
	zone[12].zone = 12;
	zone[12].name = "������";
	zone[12].is_select = 0;
	zone[13].zone = -1;
	zone[13].name = "��ý�";
	zone[13].is_select = 0;
	zone[14].zone = -2;
	zone[14].name = "�������ǵ�";
	zone[14].is_select = 0;
	zone[15].zone = -3;
	zone[15].name = "����";
	zone[15].is_select = 0;
	zone[16].zone = -4;
	zone[16].name = "����";
	zone[16].is_select = 0;
	zone[17].zone = -5;
	zone[17].name = "���ױ���";
	zone[17].is_select = 0;
	zone[18].zone = -6;
	zone[18].name = "��˹��";
	zone[18].is_select = 1;
	zone[19].zone = -7;
	zone[19].name = "����ɣ��";
	zone[19].is_select = 0;
	zone[20].zone = -8;
	zone[20].name = "��ɼ�";
	zone[20].is_select = 0;
	zone[21].zone = -9;
	zone[21].name = "����˹��";
	zone[21].is_select = 0;
	zone[22].zone = -10;
	zone[22].name = "������";
	zone[22].is_select = 0;
	zone[23].zone = -11;
	zone[23].name = "��Ħ��";
	zone[23].is_select = 0;
	zone[24].zone = -12;
	zone[24].name = "��ʮ����";
	zone[24].is_select = 0;
}

/*���ڣ���Ф������ASCII��*/
char const *WEEK_STR[] = {"��", "һ", "��", "��", "��", "��", "��"};
char const *zodiac_sign[] = {"��", "��", "ţ", "��", "��", "��", "��", "��", "��", "��", "��", "��"};

/*Ӣ�ģ����ڣ���Ф������ASCII��*/
char const *en_WEEK_STR[] = { "Sunday","Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
char const *en_zodiac_sign[] = {"Pig", "Rat", "Ox", "Tiger", "Rabbit", "Dragon", "Snake", "Horse", "Goat", "Monkey", "Rooster", "Dog"};

