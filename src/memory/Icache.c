#define BLOCK_WIDTH 6
#define SET_WIDTH 7
#define NR_SIZE 8

#include "nemu.h"
#include "lib/misc.h"
#include "stdlib.h"
#include "Icache-template.h"
uint32_t dram_read(hwaddr_t addr, size_t len);
void dram_write(hwaddr_t addr, size_t len, uint32_t data);
void init_L2cache();
void init_Icache();
void init_Dcache();
void init_cache() {
	puts("AAA");	//debug
	init_L2cache();
	init_Icache();
	init_Dcache();
}
