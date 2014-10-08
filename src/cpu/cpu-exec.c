#include "ui/ui.h"
#include "nemu.h"

#include <setjmp.h>

#define LOADER_START 0x100000

int exec(swaddr_t);
void load_prog();
void init_dram();
void work();
char assembly[40];
jmp_buf jbuf;	/* Make it easy to perform exception handling */
uint32_t find(uint32_t x);
bool change();
extern uint8_t loader [];
extern uint32_t loader_len;

extern int quiet;

void restart() {
	/* Perform some initialization to restart a program */
	load_prog();
	memcpy(hwa_to_va(LOADER_START), loader, loader_len);

	cpu.eip = LOADER_START;

	init_dram();
	work();
}

static void print_bin_instr(swaddr_t eip, int len) {
	int i;
	printf("%8x:   ", eip);
	for(i = 0; i < len; i ++) {
		printf("%02x ", swaddr_read(eip + i, 1));
	}
	printf("%*.s", 50 - (12 + 3 * len), "");
}

void cpu_exec(volatile uint32_t n) {
	volatile uint32_t n_temp = n;

	setjmp(jbuf);
	for(; n > 0; n --) {
		swaddr_t eip_temp = cpu.eip;
		int instr_len = exec(cpu.eip);
		cpu.eip += instr_len;
		if (nemu_state == BREAK_0) {
			cpu.eip -= instr_len;
			uint32_t tmp = find(cpu.eip);
			swaddr_write(cpu.eip, 1, tmp);
			nemu_state = BREAK_1;
			break;
		}
		else if (nemu_state == BREAK_1) {
			swaddr_write(cpu.eip - instr_len, 1, 0xcc);
			nemu_state = RUNNING;
		}
		if (change()) {
			break;
		}
		if(n_temp != -1 || (enable_debug && !quiet)) {
			print_bin_instr(eip_temp, instr_len);
			puts(assembly);
		}
		if(nemu_state == INT) {
			printf("\n\nUser interrupt\n");
			return;
		} 
		else if(nemu_state == END) { return; }
	}
}
