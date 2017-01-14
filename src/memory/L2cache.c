#define BLOCK_WIDTH 6
#define SET_WIDTH 12
#define NR_SIZE 16

#include "nemu.h"
#include "lib/misc.h"
#include "stdlib.h"
#include "L2cache-template.h"
uint32_t dram_read(hwaddr_t addr, size_t len);
void dram_write(hwaddr_t addr, size_t len, uint32_t data);

