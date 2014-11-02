#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"
make_helper(concat(ret_, SUFFIX)) {
	REG(R_EBP) = MEM_R(cpu.esp);
	if (DATA_BYTE == 2)	REG(R_EBP) &= 0xffff;
	cpu.esp += DATA_BYTE;
	print_asm("ret");
	return 1;
}
#include "exec/template-end.h"
