#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"
void concat(setflag2_, SUFFIX) (DATA_TYPE x, DATA_TYPE y, int sub) {
	DATA_TYPE ty = y;
	if (sub)	y = ~y;
	DATA_TYPE z = x + y + (!!sub);
	if (sub)	cpu.CF = x < ty;
	else cpu.CF = z < x;
	cpu.SF = MSB(z);
	cpu.OF = (MSB(x) == MSB(y) && MSB(x) != MSB(z));
	cpu.ZF = (z == 0);
	int cnt = 0, i;
	for (i = 0; i < 8; ++i) {
		if (z & (1 << i))	++cnt;
	}
	cpu.PF = (~(cnt & 1));
}
//add
make_helper(concat(add_i2a_, SUFFIX)) {
	DATA_TYPE imm;
	imm = instr_fetch(eip + 1, DATA_BYTE);
	concat(setflag2_, SUFFIX) (imm, REG(R_EAX), 0);
	REG(R_EAX) += imm;
	print_asm("add" str(SUFFIX) "   0x%x, %%%s", imm, REG_NAME(R_EAX));
	return DATA_BYTE + 1;
}
make_helper(concat(add_i2rm_, SUFFIX)) {
	ModR_M m;
	DATA_TYPE imm;
	m.val = instr_fetch(eip + 1, 1);
	if(m.mod == 3) {
		imm = instr_fetch(eip + 1 + 1, DATA_BYTE);
		concat(setflag2_, SUFFIX) (imm, REG(m.R_M), 0);
		REG(m.R_M) += imm;
		print_asm("add" str(SUFFIX) "   $0x%x,%%%s", imm, REG_NAME(m.R_M));
		return 1 + DATA_BYTE + 1;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		imm = instr_fetch(eip + 1 + len, DATA_BYTE);
		concat(setflag2_, SUFFIX) (imm, MEM_R(addr), 0);
		MEM_W(addr, MEM_R(addr) + imm);
		print_asm("add" str(SUFFIX) "   $0x%x,%s", imm, ModR_M_asm);
		return len + DATA_BYTE + 1;
	}
}
make_helper(concat(add_ib2rm_, SUFFIX)) {
	ModR_M m;
	DATA_TYPE imm;
	m.val = instr_fetch(eip + 1, 1);
	if(m.mod == 3) {
		imm = instr_fetch(eip + 1 + 1, 1);
		if (imm & (1 << 7))	imm |= ((1ll << (DATA_BYTE * 8)) - 1) ^ ((1 << 8) - 1);//signal extend
		concat(setflag2_, SUFFIX) (imm, REG(m.R_M), 0);
		REG(m.R_M) += imm;
		print_asm("add" str(SUFFIX) "   $0x%x,%%%s", imm, REG_NAME(m.R_M));
		return 3;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		imm = instr_fetch(eip + 1 + len, 1);
		if (imm & (1 << 7))	imm |= ((1ll << (DATA_BYTE * 8)) - 1) ^ ((1 << 8) - 1);//signal extend
		concat(setflag2_, SUFFIX) (imm, MEM_R(addr), 0);
		printf("aaaaa %x\n", MEM_R(addr));
		MEM_W(addr, MEM_R(addr) + imm);
		printf("aaaaa %x\n", MEM_R(addr));
		print_asm("add" str(SUFFIX) "   $0x%x,%s", imm, ModR_M_asm);
		return len + 2;
	}
}
//MEM_R(addr)  swaddr_read(addr,DATA_BYTE)
//MEM_W(addr,value)   swaddr_write(addr,DATA_BYTE,value)
make_helper(concat(add_r2rm_, SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	if(m.mod == 3) {
		concat(setflag2_, SUFFIX) (REG(m.R_M), REG(m.reg), 0);
		REG(m.R_M) += REG(m.reg);
		print_asm("add" str(SUFFIX) "   %%%s,%%%s", REG_NAME(m.reg), REG_NAME(m.R_M));
		return 2;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		concat(setflag2_, SUFFIX) (MEM_R(addr), REG(m.reg), 0);
		MEM_W(addr, REG(m.reg) + MEM_R(addr));
		print_asm("add" str(SUFFIX) "   %%%s,%s", REG_NAME(m.reg), ModR_M_asm);
		return len + 1;
	}
}

make_helper(concat(add_rm2r_, SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	if(m.mod == 3) {
		concat(setflag2_, SUFFIX) (REG(m.reg), REG(m.R_M), 0);
		REG(m.reg) += REG(m.R_M);
		print_asm("add" str(SUFFIX) "   %%%s,%%%s", REG_NAME(m.R_M), REG_NAME(m.reg));
		return 2;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		concat(setflag2_, SUFFIX) (REG(m.reg), MEM_R(addr), 0);
		REG(m.reg) += MEM_R(addr);
		print_asm("add" str(SUFFIX) "   %s,%%%s", ModR_M_asm, REG_NAME(m.reg));
		return len + 1;
	}
}
//adc
make_helper(concat(adc_i2a_, SUFFIX)) {
	DATA_TYPE imm;
	imm = instr_fetch(eip + 1, DATA_BYTE);
	concat(setflag2_, SUFFIX) (imm, REG(R_EAX), 0);
	REG(R_EAX) += imm + cpu.CF;
	print_asm("adc" str(SUFFIX) "   0x%x, %%%s", imm, REG_NAME(R_EAX));
	return DATA_BYTE + 1;
}
make_helper(concat(adc_i2rm_, SUFFIX)) {
	ModR_M m;
	DATA_TYPE imm;
	m.val = instr_fetch(eip + 1, 1);
	if(m.mod == 3) {
		imm = instr_fetch(eip + 1 + 1, DATA_BYTE);
		concat(setflag2_, SUFFIX) (imm, REG(m.R_M), 0);
		REG(m.R_M) += imm + cpu.CF;
		print_asm("adc" str(SUFFIX) "   $0x%x,%%%s", imm, REG_NAME(m.R_M));
		return 1 + DATA_BYTE + 1;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		imm = instr_fetch(eip + 1 + len, DATA_BYTE);
		concat(setflag2_, SUFFIX) (imm, MEM_R(addr), 0);
		MEM_W(addr, MEM_R(addr) + imm + cpu.CF);
		print_asm("adc" str(SUFFIX) "   $0x%x,%s", imm, ModR_M_asm);
		return len + DATA_BYTE + 1;
	}
}
make_helper(concat(adc_ib2rm_, SUFFIX)) {
	ModR_M m;
	DATA_TYPE imm;
	m.val = instr_fetch(eip + 1, 1);
	if(m.mod == 3) {
		imm = instr_fetch(eip + 1 + 1, 1);
		if (imm & (1 << 7))	imm |= ((1ll << (DATA_BYTE * 8)) - 1) ^ ((1 << 8) - 1);//signal extend
		concat(setflag2_, SUFFIX) (imm, REG(m.R_M), 0);
		REG(m.R_M) += imm + cpu.CF;
		print_asm("adc" str(SUFFIX) "   $0x%x,%%%s", imm, REG_NAME(m.R_M));
		return 3;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		imm = instr_fetch(eip + 1 + len, 1);
		if (imm & (1 << 7))	imm |= ((1ll << (DATA_BYTE * 8)) - 1) ^ ((1 << 8) - 1);//signal extend
		concat(setflag2_, SUFFIX) (imm, MEM_R(addr), 0);
		MEM_W(addr, MEM_R(addr) + imm + cpu.CF);
		print_asm("adc" str(SUFFIX) "   $0x%x,%s", imm, ModR_M_asm);
		return len + 2;
	}
}
//MEM_R(addr)  swadcr_read(adcr,DATA_BYTE)
//MEM_W(addr,value)   swadcr_write(adcr,DATA_BYTE,value)
make_helper(concat(adc_r2rm_, SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	if(m.mod == 3) {
		concat(setflag2_, SUFFIX) (REG(m.R_M), REG(m.reg), 0);
		REG(m.R_M) += REG(m.reg) + cpu.CF;
		print_asm("adc" str(SUFFIX) "   %%%s,%%%s", REG_NAME(m.reg), REG_NAME(m.R_M));
		return 2;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		concat(setflag2_, SUFFIX) (MEM_R(addr), REG(m.reg), 0);
		MEM_W(addr, REG(m.reg) + MEM_R(addr) + cpu.CF);
		print_asm("adc" str(SUFFIX) "   %%%s,%s", REG_NAME(m.reg), ModR_M_asm);
		return len + 1;
	}
}

make_helper(concat(adc_rm2r_, SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	if(m.mod == 3) {
		concat(setflag2_, SUFFIX) (REG(m.reg), REG(m.R_M), 0);
		REG(m.reg) += REG(m.R_M) + cpu.CF;
		print_asm("adc" str(SUFFIX) "   %%%s,%%%s", REG_NAME(m.R_M), REG_NAME(m.reg));
		return 2;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		concat(setflag2_, SUFFIX) (REG(m.reg), MEM_R(addr), 0);
		REG(m.reg) += MEM_R(addr) + cpu.CF;
		print_asm("adc" str(SUFFIX) "   %s,%%%s", ModR_M_asm, REG_NAME(m.reg));
		return len + 1;
	}
}
//sbb
make_helper(concat(sbb_i2a_, SUFFIX)) {
	DATA_TYPE imm;
	imm = instr_fetch(eip + 1, DATA_BYTE);
	concat(setflag2_, SUFFIX) (REG(R_EAX), imm, 1);
	REG(R_EAX) -= imm + cpu.CF;
	print_asm("sbb" str(SUFFIX) "   0x%x, %%%s", imm, REG_NAME(R_EAX));
	return DATA_BYTE + 1;
}
make_helper(concat(sbb_i2rm_, SUFFIX)) {
	ModR_M m;
	DATA_TYPE imm;
	m.val = instr_fetch(eip + 1, 1);
	if(m.mod == 3) {
		imm = instr_fetch(eip + 1 + 1, DATA_BYTE);
		concat(setflag2_, SUFFIX) (REG(m.R_M),imm, 1);
		REG(m.R_M) -= imm + cpu.CF;
		print_asm("sbb" str(SUFFIX) "   $0x%x,%%%s", imm, REG_NAME(m.R_M));
		return 1 + DATA_BYTE + 1;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		imm = instr_fetch(eip + 1 + len, DATA_BYTE);
		concat(setflag2_, SUFFIX) (MEM_R(addr), imm, 1);
		MEM_W(addr, MEM_R(addr) - imm - cpu.CF);
		print_asm("sbb" str(SUFFIX) "   $0x%x,%s", imm, ModR_M_asm);
		return len + DATA_BYTE + 1;
	}
}
make_helper(concat(sbb_ib2rm_, SUFFIX)) {
	ModR_M m;
	DATA_TYPE imm;
	m.val = instr_fetch(eip + 1, 1);
	if(m.mod == 3) {
		imm = instr_fetch(eip + 1 + 1, 1);
		if (imm & (1 << 7))	imm |= ((1ll << (DATA_BYTE * 8)) - 1) ^ ((1 << 8) - 1);//signal extend
		concat(setflag2_, SUFFIX) (REG(m.R_M), imm, 1);
		REG(m.R_M) -= imm + cpu.CF;
		print_asm("sbb" str(SUFFIX) "   $0x%x,%%%s", imm, REG_NAME(m.R_M));
		return 3;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		imm = instr_fetch(eip + 1 + len, 1);
		if (imm & (1 << 7))	imm |= ((1ll << (DATA_BYTE * 8)) - 1) ^ ((1 << 8) - 1);//signal extend
		concat(setflag2_, SUFFIX) (MEM_R(addr), imm, 1);
		MEM_W(addr, MEM_R(addr) - imm - cpu.CF);
		print_asm("sbb" str(SUFFIX) "   $0x%x,%s", imm, ModR_M_asm);
		return len + 2;
	}
}
//MEM_R(addr)  swaddr_read(addr,DATA_BYTE)
//MEM_W(addr,value)   swaddr_write(addr,DATA_BYTE,value)
make_helper(concat(sbb_r2rm_, SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	if(m.mod == 3) {
		concat(setflag2_, SUFFIX) (REG(m.R_M), REG(m.reg), 1);
		REG(m.R_M) -= REG(m.reg) + cpu.CF;
		print_asm("sbb" str(SUFFIX) "   %%%s,%%%s", REG_NAME(m.reg), REG_NAME(m.R_M));
		return 2;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		concat(setflag2_, SUFFIX) (MEM_R(addr), REG(m.reg), 1);
		MEM_W(addr, REG(m.reg) - MEM_R(addr) - cpu.CF);
		print_asm("sbb" str(SUFFIX) "   %%%s,%s", REG_NAME(m.reg), ModR_M_asm);
		return len + 1;
	}
}

make_helper(concat(sbb_rm2r_, SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	if(m.mod == 3) {
		concat(setflag2_, SUFFIX) (REG(m.reg), REG(m.R_M), 1);
		REG(m.reg) -= REG(m.R_M) - cpu.CF;
		print_asm("sbb" str(SUFFIX) "   %%%s,%%%s", REG_NAME(m.R_M), REG_NAME(m.reg));
		return 2;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		concat(setflag2_, SUFFIX) (REG(m.reg), MEM_R(addr), 1);
		REG(m.reg) -= MEM_R(addr) + cpu.CF;
		print_asm("sbb" str(SUFFIX) "   %s,%%%s", ModR_M_asm, REG_NAME(m.reg));
		return len + 1;
	}
}
//sub
make_helper(concat(sub_i2a_, SUFFIX)) {
	DATA_TYPE imm;
	imm = instr_fetch(eip + 1, DATA_BYTE);
	concat(setflag2_, SUFFIX) (REG(R_EAX), imm, 1);
	REG(R_EAX) -= imm;
	print_asm("sub" str(SUFFIX) "   0x%x, %%%s", imm, REG_NAME(R_EAX));
	return DATA_BYTE + 1;
}
make_helper(concat(sub_i2rm_, SUFFIX)) {
	ModR_M m;
	DATA_TYPE imm;
	m.val = instr_fetch(eip + 1, 1);
	if(m.mod == 3) {
		imm = instr_fetch(eip + 1 + 1, DATA_BYTE);
		concat(setflag2_, SUFFIX) (REG(m.R_M),imm, 1);
		REG(m.R_M) -= imm;
		print_asm("sub" str(SUFFIX) "   $0x%x,%%%s", imm, REG_NAME(m.R_M));
		return 1 + DATA_BYTE + 1;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		imm = instr_fetch(eip + 1 + len, DATA_BYTE);
		concat(setflag2_, SUFFIX) (MEM_R(addr), imm, 1);
		MEM_W(addr, MEM_R(addr) - imm);
		print_asm("sub" str(SUFFIX) "   $0x%x,%s", imm, ModR_M_asm);
		return len + DATA_BYTE + 1;
	}
}
make_helper(concat(sub_ib2rm_, SUFFIX)) {
	ModR_M m;
	DATA_TYPE imm;
	m.val = instr_fetch(eip + 1, 1);
	if(m.mod == 3) {
		imm = instr_fetch(eip + 1 + 1, 1);
		if (imm & (1 << 7))	imm |= ((1ll << (DATA_BYTE * 8)) - 1) ^ ((1 << 8) - 1);//signal extend
		concat(setflag2_, SUFFIX) (REG(m.R_M), imm, 1);
		REG(m.R_M) -= imm;
		print_asm("sub" str(SUFFIX) "   $0x%x,%%%s", imm, REG_NAME(m.R_M));
		return 3;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		imm = instr_fetch(eip + 1 + len, 1);
		if (imm & (1 << 7))	imm |= ((1ll << (DATA_BYTE * 8)) - 1) ^ ((1 << 8) - 1);//signal extend
		concat(setflag2_, SUFFIX) (MEM_R(addr), imm, 1);
		MEM_W(addr, MEM_R(addr) - imm);
		print_asm("sub" str(SUFFIX) "   $0x%x,%s", imm, ModR_M_asm);
		return len + 2;
	}
}
//MEM_R(addr)  swaddr_read(addr,DATA_BYTE)
//MEM_W(addr,value)   swaddr_write(addr,DATA_BYTE,value)
make_helper(concat(sub_r2rm_, SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	if(m.mod == 3) {
		concat(setflag2_, SUFFIX) (REG(m.R_M), REG(m.reg), 1);
		REG(m.R_M) -= REG(m.reg);
		print_asm("sub" str(SUFFIX) "   %%%s,%%%s", REG_NAME(m.reg), REG_NAME(m.R_M));
		return 2;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		concat(setflag2_, SUFFIX) (MEM_R(addr), REG(m.reg), 1);
		MEM_W(addr, REG(m.reg) - MEM_R(addr));
		print_asm("sub" str(SUFFIX) "   %%%s,%s", REG_NAME(m.reg), ModR_M_asm);
		return len + 1;
	}
}

make_helper(concat(sub_rm2r_, SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	if(m.mod == 3) {
		concat(setflag2_, SUFFIX) (REG(m.reg), REG(m.R_M), 1);
		REG(m.reg) -= REG(m.R_M);
		print_asm("sub" str(SUFFIX) "   %%%s,%%%s", REG_NAME(m.R_M), REG_NAME(m.reg));
		return 2;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		concat(setflag2_, SUFFIX) (REG(m.reg), MEM_R(addr), 1);
		REG(m.reg) -= MEM_R(addr);
		print_asm("sub" str(SUFFIX) "   %s,%%%s", ModR_M_asm, REG_NAME(m.reg));
		return len + 1;
	}
}
//inc
make_helper(concat(inc_rm_, SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	if(m.mod == 3) {
		concat(setflag2_, SUFFIX) (REG(m.R_M),1, 0);
		++REG(m.R_M);
		print_asm("inc" str(SUFFIX) "   %%%s", REG_NAME(m.R_M));
		return 2;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		concat(setflag2_, SUFFIX) (MEM_R(addr), 1, 0);
		MEM_W(addr, MEM_R(addr) + 1);
		print_asm("inc" str(SUFFIX) "   %s", ModR_M_asm);
		return len + 1;
	}
}
make_helper(concat(inc_r_, SUFFIX)) {
	int reg_code = instr_fetch(eip, 1) & 0x7;
	concat(setflag2_, SUFFIX) (REG(reg_code), 1, 0);
	++REG(reg_code);
	print_asm("inc    %%%s", REG_NAME(reg_code));
	return 1;
}
//dec
make_helper(concat(dec_rm_, SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	if(m.mod == 3) {
		concat(setflag2_, SUFFIX) (REG(m.R_M),1, 1);
		--REG(m.R_M);
		print_asm("dec" str(SUFFIX) "   %%%s", REG_NAME(m.R_M));
		return 2;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		concat(setflag2_, SUFFIX) (MEM_R(addr), 1, 1);
		MEM_W(addr, MEM_R(addr) - 1);
		print_asm("dec" str(SUFFIX) "   %s", ModR_M_asm);
		return len + 1;
	}
}
make_helper(concat(dec_r_, SUFFIX)) {
	int reg_code = instr_fetch(eip, 1) & 0x7;
	concat(setflag2_, SUFFIX) (REG(reg_code), 1, 1);
	--REG(reg_code);
	print_asm("dec    %%%s", REG_NAME(reg_code));
	return 1;
}
//neg
make_helper(concat(neg_rm_, SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	if(m.mod == 3) {
		concat(setflag2_, SUFFIX)(0, REG(m.R_M), 1);
		if (!REG(m.R_M))	cpu.CF = 0;
		else cpu.CF = 1;
		REG(m.R_M) = -REG(m.R_M);
		print_asm("neg    %%%s", REG_NAME(m.R_M));
		return 2;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		concat(setflag2_, SUFFIX)(0, MEM_R(addr), 1);
		if (!MEM_R(addr))	cpu.CF = 0;
		else cpu.CF = 1;
		MEM_W(addr, -MEM_R(addr));
		print_asm("neg" str(SUFFIX)"   %s",ModR_M_asm);
		return len + 1;
	}
}
#include "exec/template-end.h"
