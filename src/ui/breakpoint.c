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
	BP *t = head;
	//printf("%u %u %s\n",t -> ago, t -> now,  head -> s);	//debug
	bool can = 0;
	for (; t != NULL; t = t -> next) {
		bool f = 1;
		if (t -> kind == 1) {
			uint32_t tmp = expr(t -> s, &f);
			//printf("%s %u\n", t -> s, t -> now);//debug
			if (t -> now != tmp) {
				can = 1;
				printf("Hardware watchpoint %d: %s\n", t -> NO, t -> s);
				printf("Old value = %u\n", t -> now);
				printf("New value = %u\n", tmp);
				t -> ago = t -> now;
				t -> now = tmp;
			}
		}
	}
	return can;
}
uint32_t find(uint32_t x) {
	if (head == NULL)	return -1;
	BP *t = head;
	int now = 31;
	while (now-- && t -> addr != x) {
		t = t -> next;
	}
	if (!now)	return -1;
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
	while(t != NULL) {	//restore breakpoint
		if (t -> kind == 0) {
			t -> inst = swaddr_read(t -> addr, 1);
			swaddr_write(t -> addr, 1, 0xcc);
			t = t -> next;
		}
		else {
			BP * q = t;
			t = t -> next;
			free_bp(q);
		}
	}
	return ;
}
void print_breakpoint() {
	BP *t = head;
	if (t == NULL)	return;
	printf ("Num\tPointNum\tType\tAddress or Expression\n");
	int cnt = 0;
	while(t != NULL) {
		if (t -> kind == 0) {
			printf("%d\t%d\tbreakpoint\t0x%x\n", ++cnt,t -> NO, t -> addr);
		}
		else {
			printf("%d\t%d\thw watchpoint\t%s\n", ++cnt, t -> NO, t -> s);
		}
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
