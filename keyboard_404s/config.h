#ifndef __CONFIG_H__
#define __CONFIG_H__

#include "intrins.h"
#include "stc15w404s.h"

typedef	bit BOOL ;	
typedef	unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned long DWORD;

#define OS_EVENT_WHILE_1					0x55
#define OS_EVENT_TIMER_10US 			0x50
#define OS_EVENT_TIMER_20US 			0x51
#define OS_EVENT_EXINT_SPEED_UP 	0x52
#define OS_EVENT_EXINT_SPEED_DOWN 0x53
#define OS_EVENT_EXINT_MESSAGE		0x54

#endif