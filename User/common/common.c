#include "./common/common.h"

timeZone zone[25];

void timeZoneInit(void)
{
	zone[0].zone = 0;
	zone[0].name = "英国";
	zone[0].is_select = 1;
	zone[1].zone = 1;
	zone[1].name = "德国";
	zone[1].is_select = 0;
	zone[2].zone = 2;
	zone[2].name = "土耳其";
	zone[2].is_select = 0;
	zone[3].zone = 3;
	zone[3].name = "俄罗斯";
	zone[3].is_select = 0;
	zone[4].zone = 4;
	zone[4].name = "迪拜";
	zone[4].is_select = 0;
	zone[5].zone = 5;
	zone[5].name = "印度";
	zone[5].is_select = 0;
	zone[6].zone = 6;
	zone[6].name = "孟加拉国";
	zone[6].is_select = 0;
	zone[7].zone = 7;
	zone[7].name = "泰国";
	zone[7].is_select = 0;
	zone[8].zone = 8;
	zone[8].name = "中国";
	zone[8].is_select = 0;
	zone[9].zone = 9;
	zone[9].name = "日本";
	zone[9].is_select = 0;
	zone[10].zone = 10;
	zone[10].name = "悉尼";
	zone[10].is_select = 0;
	zone[11].zone = 11;
	zone[11].name = "所罗门群岛";
	zone[11].is_select = 0;
	zone[12].zone = 12;
	zone[12].name = "新西兰";
	zone[12].is_select = 0;
	zone[13].zone = -1;
	zone[13].name = "佛得角";
	zone[13].is_select = 0;
	zone[14].zone = -2;
	zone[14].name = "南乔治亚岛";
	zone[14].is_select = 0;
	zone[15].zone = -3;
	zone[15].name = "巴西";
	zone[15].is_select = 0;
	zone[16].zone = -4;
	zone[16].name = "智利";
	zone[16].is_select = 0;
	zone[17].zone = -5;
	zone[17].name = "哥伦比亚";
	zone[17].is_select = 0;
	zone[18].zone = -6;
	zone[18].name = "休斯顿";
	zone[18].is_select = 1;
	zone[19].zone = -7;
	zone[19].name = "亚利桑那";
	zone[19].is_select = 0;
	zone[20].zone = -8;
	zone[20].name = "洛杉矶";
	zone[20].is_select = 0;
	zone[21].zone = -9;
	zone[21].name = "阿拉斯加";
	zone[21].is_select = 0;
	zone[22].zone = -10;
	zone[22].name = "夏威夷";
	zone[22].is_select = 0;
	zone[23].zone = -11;
	zone[23].name = "萨摩亚";
	zone[23].is_select = 0;
	zone[24].zone = -12;
	zone[24].name = "西十二区";
	zone[24].is_select = 0;
}

/*星期，生肖用文字ASCII码*/
char const *WEEK_STR[] = {"日", "一", "二", "三", "四", "五", "六"};
char const *zodiac_sign[] = {"猪", "鼠", "牛", "虎", "兔", "龙", "蛇", "马", "羊", "猴", "鸡", "狗"};

/*英文，星期，生肖用文字ASCII码*/
char const *en_WEEK_STR[] = { "Sunday","Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
char const *en_zodiac_sign[] = {"Pig", "Rat", "Ox", "Tiger", "Rabbit", "Dragon", "Snake", "Horse", "Goat", "Monkey", "Rooster", "Dog"};

