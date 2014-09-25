#include "ui/breakpoint.h"

#include "nemu.h"

#define NR_BP 32

static BP bp_pool[NR_BP];
static BP *head, *free_;

void init_bp_pool() {
	int i;
	for(i = 0; i < NR_BP - 1; i ++) {
		bp_pool[i].NO = i;
		bp_pool[i].next = &bp_pool[i + 1];
	}
	bp_pool[i].next = NULL;

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
	if (head == NULL)	return ;
	BP *t = head;
	if (t == bp)	head = head -> next;
	else {
		int i;
		for (i = 0; i < NR_BP - 1 && t -> next != bp && t -> next != NULL; ++i) {
			t = t -> next;
		}
		t -> next = bp -> next;
	}
	bp -> next = free_;
	free_ = bp;
	return ;
}
void work() {
	BP *t = head;
	while(t != NULL) {
		swaddr_write(t -> addr, 1, 0xcc);
		t = t -> next;
	}
}
/* TODO: Implement the function of breakpoint */
