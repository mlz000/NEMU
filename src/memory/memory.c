#include "common.h"
#include "nemu.h"
uint32_t dram_read(hwaddr_t addr, size_t len);
void dram_write(hwaddr_t addr, size_t len, uint32_t data);

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

uint32_t swaddr_read(swaddr_t addr, size_t len) {
	assert(len == 1 || len == 2 || len == 4);
	return hwaddr_read(addr, len);
}

void swaddr_write(swaddr_t addr, size_t len, uint32_t data) {
	assert(len == 1 || len == 2 || len == 4);
	hwaddr_write(addr, len, data);
}

static uint32_t hwaddr_read_instr(hwaddr_t addr, size_t len) {
	assert(len == 1 || len == 2 || len == 4);
	return Icache_read(addr, len);
}

uint32_t instr_fetch(swaddr_t addr, size_t len) {
	assert(len == 1 || len == 2 || len == 4);
	return hwaddr_read_instr(addr, len);
}
