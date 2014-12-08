#ifndef __FUNC_H__
#define __FUNC_H__
struct stack {
	swaddr_t rstack[1 << 23];
	int top;
};
extern struct stack func_stack;
swaddr_t now_func(swaddr_t);
char *func_name(swaddr_t);
#endif
