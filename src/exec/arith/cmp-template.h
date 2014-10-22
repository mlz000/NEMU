#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"
void concat(setflag1_, SUFFIX) (DATA_TYPE t1,DATA_TYPE t2) {
	DATA_TYPE t = t1 - t2;
	if ((t1 >= 0 && t2 >= 0) || (t1 < 0 && t2 < 0))	cpu.OF = 0;
	if (t1 < t2)	cpu.CF = 1;
	else if (t1 > t2)	cpu.CF = 0;
	cpu.ZF = (t == 0);
	int cnt = 0, i;
	for (i = 0; i < 8; ++i) {
		if (t & (1 << i))	++cnt;
	}
	cpu.PF = (~(cnt & 1));
}
make_helper(concat(cmp_i2a_, SUFFIX)) {
	DATA_TYPE imm;
	imm = instr_fetch(eip + 1, DATA_BYTE);
	concat(setflag1_, SUFFIX) (imm, REG(R_EAX));
	print_asm("cmp" str(SUFFIX) " 0x%x, %%%s", imm, REG_NAME(R_EAX));
	return 2;
}
make_helper(concat(cmp_i2rm_, SUFFIX)) {
	ModR_M m;
	DATA_TYPE imm;
	m.val = instr_fetch(eip + 1, 1);
	if(m.mod == 3) {
		imm = instr_fetch(eip + 1 + 1, DATA_BYTE);
		concat(setflag1_, SUFFIX) (imm, REG(m.R_M));
		print_asm("cmp" str(SUFFIX) " $0x%x,%%%s", imm, REG_NAME(m.R_M));
		return 1 + DATA_BYTE + 1;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		imm = instr_fetch(eip + 1 + len, DATA_BYTE);
		concat(setflag1_, SUFFIX) (imm, addr);
		print_asm("cmp" str(SUFFIX) " $0x%x,%s", imm, ModR_M_asm);
		return len + DATA_BYTE + 1;
	}
}

make_helper(concat(cmp_r2rm_, SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	if(m.mod == 3) {
		REG(m.R_M) = REG(m.reg);
		print_asm("cmp" str(SUFFIX) " %%%s,%%%s", REG_NAME(m.reg), REG_NAME(m.R_M));
		return 2;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		MEM_W(addr, REG(m.reg));

		print_asm("cmp" str(SUFFIX) " %%%s,%s", REG_NAME(m.reg), ModR_M_asm);
		return len + 1;
	}
}

make_helper(concat(cmp_rm2r_, SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	if(m.mod == 3) {
		REG(m.reg) = REG(m.R_M);
		print_asm("cmp" str(SUFFIX) " %%%s,%%%s", REG_NAME(m.R_M), REG_NAME(m.reg));
		return 2;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		REG(m.reg) = MEM_R(addr);

		print_asm("cmp" str(SUFFIX) " %s,%%%s", ModR_M_asm, REG_NAME(m.reg));
		return len + 1;
	}
}

make_helper(concat(cmp_a2moffs_, SUFFIX)) {
	swaddr_t addr = instr_fetch(eip + 1, 4);
	MEM_W(addr, REG(R_EAX));

	print_asm("cmp" str(SUFFIX) " %%%s,0x%x", REG_NAME(R_EAX), addr);
	return 5;
}

make_helper(concat(cmp_moffs2a_, SUFFIX)) {
	swaddr_t addr = instr_fetch(eip + 1, 4);
	REG(R_EAX) = MEM_R(addr);

	print_asm("cmp" str(SUFFIX) " 0x%x,%%%s", addr, REG_NAME(R_EAX));
	return 5;
}

#include "exec/template-end.h"
