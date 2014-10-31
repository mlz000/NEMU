#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"
void concat(setflag1_, SUFFIX) (DATA_TYPE x,DATA_TYPE y, int sub) {//t1 - t2
	DATA_TYPE ty = y;
	if (sub)	y = ~y;
	DATA_TYPE z = x + y + (!!sub);
	if (sub)	cpu.CF = x < ty;
	else cpu.CF = z < x; 
	cpu.OF = (MSB(x) == MSB(y) && MSB(x) != MSB(z));
	cpu.ZF = (z == 0);
	int cnt = 0, i;
	for (i = 0; i < 8; ++i) {
		if (z & (1 << i))	++cnt;
	}
	cpu.PF = (~(cnt & 1));
}
make_helper(concat(cmp_i2a_, SUFFIX)) {
	DATA_TYPE imm;
	imm = instr_fetch(eip + 1, DATA_BYTE);
	concat(setflag1_, SUFFIX) (imm, REG(R_EAX), 1);
	print_asm("cmp" str(SUFFIX) " 0x%x, %%%s", imm, REG_NAME(R_EAX));
	return 2;
}
make_helper(concat(cmp_i2rm_, SUFFIX)) {
	ModR_M m;
	DATA_TYPE imm;
	m.val = instr_fetch(eip + 1, 1);
	if(m.mod == 3) {
		imm = instr_fetch(eip + 1 + 1, DATA_BYTE);
		concat(setflag1_, SUFFIX) (imm, REG(m.R_M), 1);
		print_asm("cmp" str(SUFFIX) " $0x%x,%%%s", imm, REG_NAME(m.R_M));
		return 1 + DATA_BYTE + 1;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		imm = instr_fetch(eip + 1 + len, DATA_BYTE);
		concat(setflag1_, SUFFIX) (imm, addr, 1);
		print_asm("cmp" str(SUFFIX) " $0x%x,%s", imm, ModR_M_asm);
		return len + DATA_BYTE + 1;
	}
}
make_helper(concat(cmp_ib2rm_, SUFFIX)) {
	ModR_M m;
	DATA_TYPE imm;
	m.val = instr_fetch(eip + 1, 1);
	if(m.mod == 3) {
		imm = instr_fetch(eip + 1 + 1, 1);
		if (imm & (1 << 7)) { //signal extend
			if (DATA_BYTE == 2)	imm |= 0xff00;
			if (DATA_BYTE == 4)	imm |= 0xffff00;
		}
		concat(setflag1_, SUFFIX) (imm, REG(m.R_M), 1);
		print_asm("cmp" str(SUFFIX) " $0x%x,%%%s", imm, REG_NAME(m.R_M));
		return 3;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		imm = instr_fetch(eip + 1 + len, 1);
		if (imm & (1 << 7)) {
			if (DATA_BYTE == 2)	imm |= 0xff00;
			if (DATA_BYTE == 4)	imm |= 0xffff00;
		}
		concat(setflag1_, SUFFIX) (imm, addr, 1);
		print_asm("cmp" str(SUFFIX) " $0x%x,%s", imm, ModR_M_asm);
		return len + 2;
	}
}

make_helper(concat(cmp_r2rm_, SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	if(m.mod == 3) {
		concat(setflag1_, SUFFIX) (REG(m.R_M), REG(m.reg), 1);
		print_asm("cmp" str(SUFFIX) " %%%s,%%%s", REG_NAME(m.reg), REG_NAME(m.R_M));
		return 2;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		concat(setflag1_, SUFFIX) (addr, REG(m.reg), 1);
		print_asm("cmp" str(SUFFIX) " %%%s,%s", REG_NAME(m.reg), ModR_M_asm);
		return len + 1;
	}
}

make_helper(concat(cmp_rm2r_, SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	if(m.mod == 3) {
		concat(setflag1_, SUFFIX) (REG(m.reg), REG(m.R_M), 1);
		print_asm("cmp" str(SUFFIX) " %%%s,%%%s", REG_NAME(m.R_M), REG_NAME(m.reg));
		return 2;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		concat(setflag1_, SUFFIX) (REG(m.reg), MEM_R(addr), 1);

		print_asm("cmp" str(SUFFIX) " %s,%%%s", ModR_M_asm, REG_NAME(m.reg));
		return len + 1;
	}
}

#include "exec/template-end.h"
