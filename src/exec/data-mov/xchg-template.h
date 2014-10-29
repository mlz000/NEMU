#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"
make_helper(concat(xchg_r2a_, SUFFIX)) {
	int reg_code = instr_fetch(eip, 1) & 0x7;
	int t = REG(reg_code);
	REG(reg_code) = REG(R_EAX);
	REG(R_EAX) = t;
	print_asm("xchg" str(SUFFIX) " 0x%s,%%%s", REG_NAME(reg_code), REG_NAME(R_EAX));
	return 1;
}
make_helper(concat(xchg_r2rm_, SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	if(m.mod == 3) {
		int t = REG(m.R_M);
		REG(m.R_M) = REG(m.reg);
		REG(m.reg) = t;
		print_asm("xchg" str(SUFFIX) " %%%s,%%%s", REG_NAME(m.R_M), REG_NAME(m.reg));
		return 2;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		int t = REG(m.reg);
		REG(m.reg) = MEM_R(addr);
		MEM_W(addr, t);
		print_asm("xchg" str(SUFFIX) " %s,%%%s", ModR_M_asm, REG_NAME(m.reg));
		return len + 1;
	}
}
#include "exec/template-end.h"
