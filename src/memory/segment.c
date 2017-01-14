#include "nemu.h"

typedef struct {
	uint32_t lim0 : 16;
	uint32_t base0 : 16;
	uint32_t base1 : 8;
	uint32_t type : 4;
	uint32_t seg_type : 1;
	uint32_t DPL : 2;
	uint32_t P : 1;
	uint32_t limit2 : 4;
	uint32_t AVL : 1;
	uint32_t opsize : 1;
	uint32_t B : 1;
	uint32_t G : 1;
	uint32_t base2 : 8;
}SegDescriptor;
uint32_t hwaddr_read(lnaddr_t, size_t);
uint8_t current_sreg;

lnaddr_t segment_translate(swaddr_t addr, uint8_t code) {
	if (!cpu.CR0.PE)	return addr;
	static SegDescriptor* GDT = NULL;
	if (GDT == NULL)	GDT = (void *)malloc(cpu.gdt.lim + 1);
	int i;
	for (i = 0; i < cpu.gdt.lim; ++i)	*((uint8_t*)GDT + i) = hwaddr_read(cpu.gdt.base + i, 1);
	SegDescriptor t = GDT[reg_s(code).INDEX];
	uint32_t base = (t.base2 << 24) | (t.base1 << 16) | t.base0;
	return addr + base;
}
