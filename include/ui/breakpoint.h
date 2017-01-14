#ifndef __UI_BREAKPOINT_H__
#define __UI_BREAKPOINT_H__

#include "common.h"

#define INT3_CODE 0xcc

typedef struct breakpoint {
	int NO, kind;	//0:breakpoint 1:watchpoint
	char s[105];//expr
	struct breakpoint *next;
	uint32_t addr, inst, ago, now;
	/* TODO: Add more members if necessary */


} BP;

#endif
