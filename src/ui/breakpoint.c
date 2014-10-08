#include "ui/breakpoint.h"

#include "nemu.h"

#define NR_BP 32

static BP bp_pool[NR_BP];
static BP *head, *free_;
uint32_t expr(char *e, bool *f);
void init_bp_pool() {
	int i;
	for(i = 0; i < NR_BP - 1; i ++) {
		bp_pool[i].NO = i;
		bp_pool[i].next = &bp_pool[i + 1];
	}
	bp_pool[i].next = NULL;
	bp_pool[31].NO = 31;
	head = NULL;
	free_ = bp_pool;
}
BP* new_bp() {
	if (free_ == NULL)	assert(0);
	BP *t = free_;
	free_ = free_ -> next;
	t -> next = head;
	head = t;
	return head;
}
bool change() {
	if (head == NULL)	return 0;
	BP *t;
	bool can = 0;
	for (t = head; t != NULL; t = t -> next) {
		bool f = 1;
		if (t -> kind == 1) {
			t -> now = expr(t -> s, &f);
			if (t -> ago != t -> now) {
				printf("Hardware watchpoint %d: %s", t -> NO, t -> s);
				printf("Old value = %u\n", t -> ago);
				printf("New value = %u\n", t -> now);
				can = 1;
				t -> ago = t -> now;
			}
		}
	}
	return can;
}
uint32_t find(uint32_t x) {
	if (head == NULL)	assert(0);
	BP *t = head;
	int now = 31;
	while (now-- && t -> addr != x) {
		t = t -> next;
	}
	return t -> inst;
}
void free_bp(BP *bp) {
	if (head == NULL || bp == NULL)	return ;
	BP *t = head;
	swaddr_write(bp -> addr, 1, bp -> inst);
	if (t == bp)	head = head -> next;
	else {
		int n = 32;
		while (n-- && t -> next != NULL) {
			if (t -> next == bp) {
				t -> next = bp -> next;
				break;
			}
			else t = t -> next;
		}
	}
	bp -> next = free_;
	free_ = bp;
	return ;
}
void work() {
	BP *t = head;
	while(t != NULL) {
		t -> inst = swaddr_read(t -> addr, 1);
		swaddr_write(t -> addr, 1, 0xcc);
		t = t -> next;
	}
	return ;
}
void print_breakpoint() {
	BP *t = head;
	if (t == NULL)	return;
	printf ("Num\tBreakpointNum\tType\tAddress\n");
	int cnt = 0;
	while(t != NULL) {
		printf("%d\t%d\tbreakpoint\t0x%x\n", ++cnt,t -> NO, t -> addr);
		t = t -> next;
	}
	return ;
}
void del_breakpoint(int n) {
	BP *t = head;
	int i;
	if (n == 100) {
		for (i = 1; i <= n; ++i){
			if (t == NULL)	break;
			else {
				BP *tmp = t -> next;
				free_bp(t);
				t = tmp;
			}
		}
	}
	else {
		while(t != NULL) {
			if (t -> NO == n) {
				free_bp(t);
				break;
			}
			t = t -> next;
		}
	}
	return ;
}
/* TODO: Implement the function of breakpoint */
