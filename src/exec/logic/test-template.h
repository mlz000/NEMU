#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"
#include "cpu/reg.h"
void concat(setflag_, SUFFIX)(DATA_TYPE t){
	cpu.OF = cpu.CF = 0;
	cpu.SF = MSB(t);
	cpu.ZF = (t == 0);
	int cnt = 0, i;
	for (i = 0; i < 8; ++i) {
		if (t & (1 << i))	++cnt;
	}
	cpu.PF = (~(cnt & 1));
}
make_helper(concat(test_i2a_, SUFFIX)) {
	DATA_TYPE imm;
	imm = instr_fetch(eip + 1, DATA_BYTE);
	DATA_TYPE t;
	t = imm & REG(R_EAX);
	concat(setflag_, SUFFIX) (t);
	print_asm("test" str(SUFFIX) " 0x%x,%%%s", imm, REG_NAME(R_EAX));
	return 2;
}
make_helper(concat(test_i2rm_, SUFFIX)) {
	ModR_M m;
	DATA_TYPE imm;
	m.val = instr_fetch(eip + 1, 1);
	DATA_TYPE t;
	if(m.mod == 3) {
		imm = instr_fetch(eip + 1 + 1, DATA_BYTE);
		t = (imm & REG(m.R_M));
		concat(setflag_, SUFFIX)(t);
		print_asm("test" str(SUFFIX) " $0x%x,%%%s", imm, REG_NAME(m.R_M));
		return 1 + DATA_BYTE + 1;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		imm = instr_fetch(eip + 1 + len, DATA_BYTE);
		t = (imm & MEM_R(addr));
		concat(setflag_, SUFFIX)(t);
		print_asm("test" str(SUFFIX) " $0x%x,%s", imm, ModR_M_asm);
		return len + DATA_BYTE + 1;
	}
}
make_helper(concat(test_r2rm_, SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	DATA_TYPE t;
	if(m.mod == 3) {
		t = REG(m.reg) & REG(m.R_M);
		concat(setflag_, SUFFIX)(t);
		print_asm("test" str(SUFFIX) " %%%s,%%%s", REG_NAME(m.reg), REG_NAME(m.R_M));
		return 2;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		t = REG(m.reg) & MEM_R(addr);
		concat(setflag_, SUFFIX)(t);
		print_asm("test" str(SUFFIX) " %%%s,%s", REG_NAME(m.reg), ModR_M_asm);
		return len + 1;
	}
}
#include "exec/template-end.h"
