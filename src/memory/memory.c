#include "common.h"
#include "nemu.h"
extern uint8_t current_sreg;
uint32_t dram_read(hwaddr_t addr, size_t len);
void dram_write(hwaddr_t addr, size_t len, uint32_t data);
lnaddr_t segment_translate(swaddr_t, uint8_t);
hwaddr_t page_translate(lnaddr_t);
/* Memory accessing interfaces */
uint32_t Icache_read(hwaddr_t addr, size_t len);
uint32_t Dcache_read(hwaddr_t addr, size_t len);
void Dcache_write(hwaddr_t addr, size_t len, uint32_t data);
uint32_t hwaddr_read(hwaddr_t addr, size_t len) {
	assert(len == 1 || len == 2 || len == 4);
	return Dcache_read(addr,len);
}

void hwaddr_write(hwaddr_t addr, size_t len, uint32_t data) {
	assert(len == 1 || len == 2 || len == 4);
	Dcache_write(addr, len, data);
}
uint32_t lnaddr_read(lnaddr_t addr, size_t len) {
	assert(len == 1 || len == 2 || len == 4);
	hwaddr_t hwaddr = page_translate(addr);
	return hwaddr_read(hwaddr, len);
}
void lnaddr_write(lnaddr_t addr, size_t len, uint32_t data) {
	assert(len == 1 || len == 2 || len == 4);
	hwaddr_t hwaddr = page_translate(addr);
	return hwaddr_write(hwaddr, len, data);
}
uint32_t swaddr_read(swaddr_t addr, size_t len) {
	assert(len == 1 || len == 2 || len == 4);
	lnaddr_t lnaddr = segment_translate(addr, current_sreg);	
	return lnaddr_read(lnaddr, len);
}

void swaddr_write(swaddr_t addr, size_t len, uint32_t data) {
	assert(len == 1 || len == 2 || len == 4);
	lnaddr_t lnaddr = segment_translate(addr, current_sreg);
	hwaddr_write(lnaddr, len, data);
}

static uint32_t hwaddr_read_instr(hwaddr_t addr, size_t len) {
	assert(len == 1 || len == 2 || len == 4);
	return Icache_read(addr, len);
}
uint32_t lnaddr_read_instr(lnaddr_t addr, size_t len) {
	assert(len == 1 || len == 2 || len == 4);
	hwaddr_t hwaddr = page_translate(addr);
	return hwaddr_read_instr(hwaddr, len);
}
uint32_t instr_fetch(swaddr_t addr, size_t len) {
	assert(len == 1 || len == 2 || len == 4);
	lnaddr_t lnaddr = segment_translate(addr, CS);
	return lnaddr_read_instr(lnaddr, len);
}

