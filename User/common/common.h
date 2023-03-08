#ifndef __COMMON_H
#define __COMMON_H 

#include "stm32f10x.h"

typedef struct {
	int zone;
	char *name;
	uint8_t is_select;
} timeZone;

void timeZoneInit(void);

#endif
