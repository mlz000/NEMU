#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"
void concat(setflagor_, SUFFIX) (DATA_TYPE t1,DATA_TYPE t2) {//t1 - t2
	DATA_TYPE t = t1 | t2;
	cpu.CF = cpu.OF = 0;
	cpu.ZF = (t == 0);
	int cnt = 0, i;
	for (i = 0; i < 8; ++i) {
		if (t & (1 << i))	++cnt;
	}
	cpu.PF = (~(cnt & 1));
}
//or
make_helper(concat(or_i2a_, SUFFIX)) {
	DATA_TYPE imm;
	imm = instr_fetch(eip + 1, DATA_BYTE);
	concat(setflagor_, SUFFIX) (imm, REG(R_EAX));
	REG(R_EAX) |= imm;
	print_asm("or" str(SUFFIX) "    0x%x, %%%s", imm, REG_NAME(R_EAX));
	return DATA_BYTE + 1;
}
make_helper(concat(or_i2rm_, SUFFIX)) {
	ModR_M m;
	DATA_TYPE imm;
	m.val = instr_fetch(eip + 1, 1);
	if(m.mod == 3) {
		imm = instr_fetch(eip + 1 + 1, DATA_BYTE);
		concat(setflagor_, SUFFIX) (imm, REG(m.R_M));
		REG(m.R_M) |= imm;
		print_asm("or" str(SUFFIX) "    $0x%x,%%%s", imm, REG_NAME(m.R_M));
		return 1 + DATA_BYTE + 1;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		imm = instr_fetch(eip + 1 + len, DATA_BYTE);
		concat(setflagor_, SUFFIX) (imm, MEM_R(addr));
		MEM_W(addr, MEM_R(addr) | imm);
		print_asm("or" str(SUFFIX) "   $0x%x,%s", imm, ModR_M_asm);
		return len + DATA_BYTE + 1;
	}
}
make_helper(concat(or_ib2rm_, SUFFIX)) {
	ModR_M m;
	DATA_TYPE imm;
	m.val = instr_fetch(eip + 1, 1);
	if(m.mod == 3) {
		imm = instr_fetch(eip + 1 + 1, 1);
		if (imm & (1 << 7))	imm |= ((1ll << (DATA_BYTE * 8)) - 1) ^ ((1 << 8) - 1);//signal extend
		concat(setflagor_, SUFFIX) (imm, REG(m.R_M));
		REG(m.R_M) |= imm; 
		print_asm("or" str(SUFFIX) "    $0x%x,%%%s", imm, REG_NAME(m.R_M));
		return 3;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		imm = instr_fetch(eip + 1 + len, 1);
		if (imm & (1 << 7))	imm |= ((1ll << (DATA_BYTE * 8)) - 1) ^ ((1 << 8) - 1);//signal extend
		concat(setflagor_, SUFFIX) (imm, MEM_R(addr));
		MEM_W(addr, MEM_R(addr) | imm);
		print_asm("or" str(SUFFIX) "    $0x%x,%s", imm, ModR_M_asm);
		return len + 2;
	}
}

make_helper(concat(or_r2rm_, SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	if(m.mod == 3) {
		concat(setflagor_, SUFFIX) (REG(m.R_M), REG(m.reg));
		REG(m.R_M) |= REG(m.reg);
		print_asm("or" str(SUFFIX) "    %%%s,%%%s", REG_NAME(m.reg), REG_NAME(m.R_M));
		return 2;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		concat(setflagor_, SUFFIX) (MEM_R(addr), REG(m.reg));
		REG(m.reg) |= MEM_R(addr);
		print_asm("or" str(SUFFIX) "    %%%s,%s", REG_NAME(m.reg), ModR_M_asm);
		return len + 1;
	}
}

make_helper(concat(or_rm2r_, SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	if(m.mod == 3) {
		concat(setflagor_, SUFFIX) (REG(m.reg), REG(m.R_M));
		REG(m.reg) |= REG(m.R_M);
		print_asm("or" str(SUFFIX) "    %%%s,%%%s", REG_NAME(m.R_M), REG_NAME(m.reg));
		return 2;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		concat(setflagor_, SUFFIX) (REG(m.reg), MEM_R(addr));
		REG(m.reg) |= MEM_R(addr);
		print_asm("or" str(SUFFIX) "    %s,%%%s", ModR_M_asm, REG_NAME(m.reg));
		return len + 1;
	}
}
//xor
make_helper(concat(xor_i2a_, SUFFIX)) {
	DATA_TYPE imm;
	imm = instr_fetch(eip + 1, DATA_BYTE);
	concat(setflagor_, SUFFIX) (imm, REG(R_EAX));
	REG(R_EAX) ^= imm;
	print_asm("xor" str(SUFFIX) "    0x%x, %%%s", imm, REG_NAME(R_EAX));
	return DATA_BYTE + 1;
}
make_helper(concat(xor_i2rm_, SUFFIX)) {
	ModR_M m;
	DATA_TYPE imm;
	m.val = instr_fetch(eip + 1, 1);
	if(m.mod == 3) {
		imm = instr_fetch(eip + 1 + 1, DATA_BYTE);
		concat(setflagor_, SUFFIX) (imm, REG(m.R_M));
		REG(m.R_M) ^= imm;
		print_asm("xor" str(SUFFIX) "    $0x%x,%%%s", imm, REG_NAME(m.R_M));
		return 1 + DATA_BYTE + 1;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		imm = instr_fetch(eip + 1 + len, DATA_BYTE);
		concat(setflagor_, SUFFIX) (imm, MEM_R(addr));
		MEM_W(addr, MEM_R(addr) ^ imm);
		print_asm("xor" str(SUFFIX) "   $0x%x,%s", imm, ModR_M_asm);
		return len + DATA_BYTE + 1;
	}
}
make_helper(concat(xor_ib2rm_, SUFFIX)) {
	ModR_M m;
	DATA_TYPE imm;
	m.val = instr_fetch(eip + 1, 1);
	if(m.mod == 3) {
		imm = instr_fetch(eip + 1 + 1, 1);
		if (imm & (1 << 7))	imm ^= ((1ll << (DATA_BYTE * 8)) - 1) ^ ((1 << 8) - 1);//signal extend
		concat(setflagor_, SUFFIX) (imm, REG(m.R_M));
		REG(m.R_M) ^= imm; 
		print_asm("xor" str(SUFFIX) "    $0x%x,%%%s", imm, REG_NAME(m.R_M));
		return 3;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		imm = instr_fetch(eip + 1 + len, 1);
		if (imm & (1 << 7))	imm ^= ((1ll << (DATA_BYTE * 8)) - 1) ^ ((1 << 8) - 1);//signal extend
		concat(setflagor_, SUFFIX) (imm, MEM_R(addr));
		MEM_W(addr, MEM_R(addr) ^ imm);
		print_asm("xor" str(SUFFIX) "    $0x%x,%s", imm, ModR_M_asm);
		return len + 2;
	}
}

make_helper(concat(xor_r2rm_, SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	if(m.mod == 3) {
		concat(setflagor_, SUFFIX) (REG(m.R_M), REG(m.reg));
		REG(m.R_M) ^= REG(m.reg);
		print_asm("xor" str(SUFFIX) "    %%%s,%%%s", REG_NAME(m.reg), REG_NAME(m.R_M));
		return 2;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		concat(setflagor_, SUFFIX) (MEM_R(addr), REG(m.reg));
		REG(m.reg) ^= MEM_R(addr);
		print_asm("xor" str(SUFFIX) "    %%%s,%s", REG_NAME(m.reg), ModR_M_asm);
		return len + 1;
	}
}

make_helper(concat(xor_rm2r_, SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	if(m.mod == 3) {
		concat(setflagor_, SUFFIX) (REG(m.reg), REG(m.R_M));
		REG(m.reg) ^= REG(m.R_M);
		print_asm("xor" str(SUFFIX) "    %%%s,%%%s", REG_NAME(m.R_M), REG_NAME(m.reg));
		return 2;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		concat(setflagor_, SUFFIX) (REG(m.reg), MEM_R(addr));
		REG(m.reg) ^= MEM_R(addr);
		print_asm("xor" str(SUFFIX) "    %s,%%%s", ModR_M_asm, REG_NAME(m.reg));
		return len + 1;
	}
}
//and
make_helper(concat(and_i2a_, SUFFIX)) {
	DATA_TYPE imm;
	imm = instr_fetch(eip + 1, DATA_BYTE);
	concat(setflagor_, SUFFIX) (imm, REG(R_EAX));
	REG(R_EAX) &= imm;
	print_asm("and" str(SUFFIX) "    0x%x, %%%s", imm, REG_NAME(R_EAX));
	return DATA_BYTE + 1;
}
make_helper(concat(and_i2rm_, SUFFIX)) {
	ModR_M m;
	DATA_TYPE imm;
	m.val = instr_fetch(eip + 1, 1);
	if(m.mod == 3) {
		imm = instr_fetch(eip + 1 + 1, DATA_BYTE);
		concat(setflagor_, SUFFIX) (imm, REG(m.R_M));
		REG(m.R_M) &= imm;
		print_asm("and" str(SUFFIX) "    $0x%x,%%%s", imm, REG_NAME(m.R_M));
		return 1 + DATA_BYTE + 1;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		imm = instr_fetch(eip + 1 + len, DATA_BYTE);
		concat(setflagor_, SUFFIX) (imm, MEM_R(addr));
		MEM_W(addr, MEM_R(addr) & imm);
		print_asm("and" str(SUFFIX) "   $0x%x,%s", imm, ModR_M_asm);
		return len + DATA_BYTE + 1;
	}
}
make_helper(concat(and_ib2rm_, SUFFIX)) {
	ModR_M m;
	DATA_TYPE imm;
	m.val = instr_fetch(eip + 1, 1);
	if(m.mod == 3) {
		imm = instr_fetch(eip + 1 + 1, 1);
		if (imm & (1 << 7))	imm |= ((1ll << (DATA_BYTE * 8)) - 1) ^ ((1 << 8) - 1);//signal extend
		concat(setflagor_, SUFFIX) (imm, REG(m.R_M));
		REG(m.R_M) &= imm; 
		print_asm("and" str(SUFFIX) "    $0x%x,%%%s", imm, REG_NAME(m.R_M));
		return 3;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		imm = instr_fetch(eip + 1 + len, 1);
		if (imm & (1 << 7))	imm |= ((1ll << (DATA_BYTE * 8)) - 1) ^ ((1 << 8) - 1);//signal extend
		concat(setflagor_, SUFFIX) (imm, MEM_R(addr));
		MEM_W(addr, MEM_R(addr) & imm);
		print_asm("and" str(SUFFIX) "    $0x%x,%s", imm, ModR_M_asm);
		return len + 2;
	}
}

make_helper(concat(and_r2rm_, SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	if(m.mod == 3) {
		concat(setflagor_, SUFFIX) (REG(m.R_M), REG(m.reg));
		REG(m.R_M) &= REG(m.reg);
		print_asm("and" str(SUFFIX) "    %%%s,%%%s", REG_NAME(m.reg), REG_NAME(m.R_M));
		return 2;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		concat(setflagor_, SUFFIX) (MEM_R(addr), REG(m.reg));
		REG(m.reg) &= MEM_R(addr);
		print_asm("and" str(SUFFIX) "    %%%s,%s", REG_NAME(m.reg), ModR_M_asm);
		return len + 1;
	}
}

make_helper(concat(and_rm2r_, SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	if(m.mod == 3) {
		concat(setflagor_, SUFFIX) (REG(m.reg), REG(m.R_M));
		REG(m.reg) &= REG(m.R_M);
		print_asm("and" str(SUFFIX) "    %%%s,%%%s", REG_NAME(m.R_M), REG_NAME(m.reg));
		return 2;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		concat(setflagor_, SUFFIX) (REG(m.reg), MEM_R(addr));
		REG(m.reg) &= MEM_R(addr);
		print_asm("and" str(SUFFIX) "    %s,%%%s", ModR_M_asm, REG_NAME(m.reg));
		return len + 1;
	}
}
//not
make_helper(concat(not_rm_, SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	if (m.mod == 3) {
		REG(m.R_M) = !REG(m.R_M);
		print_asm("not    %%%s", REG_NAME(m.R_M));
		return 2;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		MEM_W(addr, !MEM_R(addr));
		print_asm("not" str(SUFFIX)"   %s", ModR_M_asm);
		return len + 1;
	}
}
#include "exec/template-end.h"
