#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"
make_helper(concat(je_r_, SUFFIX)) {
	if (cpu.ZF == 1) {
		DATA_TYPE t = instr_fetch(eip + 1, DATA_BYTE);
		cpu.eip += t;
	}
	return 2;
}
#include "exec/template-end.h"
