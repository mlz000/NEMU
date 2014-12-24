#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"
make_helper(concat(lgdt_, SUFFIX)) {
	swaddr_t addr;
	int len = read_ModR_M(eip + 1, &addr);
	uint16_t lim = instr_fetch(addr, 2);
	uint32_t base = instr_fetch(addr + 2, 4);
	if (DATA_BYTE == 2)	base &= 0xffffff;
	cpu.gdt.lim = lim;
	cpu.gdt.base = base;
	print_asm("lgdt" str(SUFFIX) "  %s", ModR_M_asm);
	return len + 1;
}
#include "exec/template-end.h"
