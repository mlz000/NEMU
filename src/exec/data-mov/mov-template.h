#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"
extern uint8_t current_sreg;
make_helper(concat(mov_i2r_, SUFFIX)) {
	int reg_code = instr_fetch(eip, 1) & 0x7;
	DATA_TYPE imm = instr_fetch(eip + 1, DATA_BYTE);
	REG(reg_code) = imm;

	print_asm("mov" str(SUFFIX) "   $0x%x,%%%s", imm, REG_NAME(reg_code));
	return DATA_BYTE + 1;
}

make_helper(concat(mov_i2rm_, SUFFIX)) {
	ModR_M m;
	DATA_TYPE imm;
	m.val = instr_fetch(eip + 1, 1);
	if(m.mod == 3) {
		imm = instr_fetch(eip + 1 + 1, DATA_BYTE);
		REG(m.R_M) = imm;
		print_asm("mov" str(SUFFIX) "   $0x%x,%%%s", imm, REG_NAME(m.R_M));
		return 1 + DATA_BYTE + 1;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		imm = instr_fetch(eip + 1 + len, DATA_BYTE);
		MEM_W(addr, imm);
		print_asm("mov" str(SUFFIX) "   $0x%x,%s", imm, ModR_M_asm);
		return len + DATA_BYTE + 1;
	}
}

make_helper(concat(mov_r2rm_, SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	if(m.mod == 3) {
		REG(m.R_M) = REG(m.reg);
		print_asm("mov" str(SUFFIX) "   %%%s,%%%s", REG_NAME(m.reg), REG_NAME(m.R_M));
		return 2;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		MEM_W(addr, REG(m.reg));

		print_asm("mov" str(SUFFIX) "   %%%s,%s", REG_NAME(m.reg), ModR_M_asm);
		return len + 1;
	}
}

make_helper(concat(mov_rm2r_, SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	if(m.mod == 3) {
		REG(m.reg) = REG(m.R_M);
		print_asm("mov" str(SUFFIX) "   %%%s,%%%s", REG_NAME(m.R_M), REG_NAME(m.reg));
		return 2;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		REG(m.reg) = MEM_R(addr);

		print_asm("mov" str(SUFFIX) "   %s,%%%s", ModR_M_asm, REG_NAME(m.reg));
		return len + 1;
	}
}

make_helper(concat(mov_a2moffs_, SUFFIX)) {
	swaddr_t addr = instr_fetch(eip + 1, 4);
	MEM_W(addr, REG(R_EAX));

	print_asm("mov" str(SUFFIX) "   %%%s,0x%x", REG_NAME(R_EAX), addr);
	return 5;
}

make_helper(concat(mov_moffs2a_, SUFFIX)) {
	swaddr_t addr = instr_fetch(eip + 1, 4);
	REG(R_EAX) = MEM_R(addr);

	print_asm("mov" str(SUFFIX) "   0x%x,%%%s", addr, REG_NAME(R_EAX));
	return 5;
}
make_helper(concat(movsx_rmb2r_, SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	if(m.mod == 3) {
		if (DATA_BYTE == 4) {
			reg_l(m.reg) = (int32_t)(int8_t)reg_b(m.R_M);
			print_asm("movsx" str(SUFFIX) " %%%s,%%%s", regsb[m.R_M], regsl[m.reg]);
		}
		else if(DATA_BYTE == 2) {
			reg_w(m.reg) = (int16_t)(int8_t)reg_b(m.R_M);
			print_asm("movsx" str(SUFFIX) " %%%s,%%%s", regsb[m.R_M], regsw[m.reg]);
		}
		return 2;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		if (DATA_BYTE == 4) {
			reg_l(m.reg) = (int32_t)(int8_t)swaddr_read(addr, 1);
			print_asm("movsx" str(SUFFIX) " %s,%%%s", ModR_M_asm, regsl[m.reg]);
		}
		else if (DATA_BYTE == 2) {
			reg_w(m.reg) = (int16_t)(int8_t)swaddr_read(addr, 1);
			print_asm("movsx" str(SUFFIX) " %s,%%%s", ModR_M_asm, regsw[m.reg]);
		}
		return len + 1;
	}
}
make_helper(concat(movsx_rmw2r_, SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	if(m.mod == 3) {
		reg_l(m.reg) = (int32_t)(int16_t)reg_w(m.R_M);
		print_asm("movsx" str(SUFFIX) " %%%s,%%%s", regsw[m.R_M], regsl[m.reg]);
		return 2;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		reg_l(m.reg) = (int32_t)(int16_t)swaddr_read(addr, 2);
		print_asm("movsx" str(SUFFIX) " %s,%%%s", ModR_M_asm, regsl[m.reg]);
		return len + 1;
	}
}
make_helper(concat(movzx_rmb2r_, SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	if(m.mod == 3) {
		if (DATA_BYTE == 4) {
			reg_l(m.reg) = (uint32_t)reg_b(m.R_M);
			print_asm("movzx" str(SUFFIX) " %%%s,%%%s", regsb[m.R_M], regsl[m.reg]);
		}
		else if (DATA_BYTE == 2) {
			reg_w(m.reg) = (uint16_t)reg_b(m.R_M);
			print_asm("movzx" str(SUFFIX) " %%%s,%%%s", regsb[m.R_M], regsw[m.reg]);
		}
		return 2;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		if (DATA_BYTE == 4) {
			reg_l(m.reg) = (uint32_t)swaddr_read(addr, 1);
			print_asm("movzx" str(SUFFIX) " %s,%%%s", ModR_M_asm, regsl[m.reg]);
		}
		else if (DATA_BYTE == 2) {
			reg_w(m.reg) = (uint16_t)swaddr_read(addr, 1);
			print_asm("movzx" str(SUFFIX) " %s,%%%s", ModR_M_asm, regsw[m.reg]);
		}
		return len + 1;
	}
}
make_helper(concat(movzx_rmw2r_, SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	if(m.mod == 3) {
		reg_l(m.reg) = (uint32_t)reg_w(m.R_M);
		print_asm("movzx" str(SUFFIX) " %%%s,%%%s", regsw[m.R_M], regsl[m.reg]);
		return 2;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		reg_l(m.reg) = (uint32_t)swaddr_read(addr, 2);
		print_asm("movzx" str(SUFFIX) " %s,%%%s", ModR_M_asm, regsl[m.reg]);
		return len + 1;
	}
}
make_helper(concat(push_r_, SUFFIX)) {
	int reg_code = instr_fetch(eip, 1) & 0x7;
	DATA_TYPE t = REG(reg_code);
	cpu.esp -= DATA_BYTE;
	MEM_W(cpu.esp, t);
	print_asm("push" str(SUFFIX) "  %%%s", REG_NAME(reg_code));
	return 1;
}
make_helper(concat(push_m_, SUFFIX)) {
	swaddr_t addr;
	int len = read_ModR_M(eip + 1, &addr);
	DATA_TYPE t = MEM_R(addr);
	cpu.esp -= DATA_BYTE;
	MEM_W(cpu.esp, t);
	print_asm("push" str(SUFFIX) "  %%%s", ModR_M_asm);
	return len + 1;
}
make_helper(concat(push_i_, SUFFIX)) {
	DATA_TYPE imm;
	imm = instr_fetch(eip + 1, DATA_BYTE);
	cpu.esp -= DATA_BYTE;
	MEM_W(cpu.esp, imm);
	print_asm("push" str(SUFFIX) "  $0x%x", imm);
	return DATA_BYTE + 1;
}
make_helper(concat(pop_r_, SUFFIX)) {
	int reg_code = instr_fetch(eip, 1) & 0x7;
	REG(reg_code) = MEM_R(cpu.esp);
	cpu.esp += DATA_BYTE;
	print_asm("pop" str(SUFFIX) "   %%%s", REG_NAME(reg_code));
	return 1;
}
make_helper(concat(pop_m_, SUFFIX)) {
	swaddr_t addr;
	int len = read_ModR_M(eip + 1, &addr);
	MEM_W(addr, MEM_R(cpu.esp));
	cpu.esp += DATA_BYTE;
	print_asm("pop" str(SUFFIX) "   %%%s", ModR_M_asm);
	return len + 1;
}
make_helper(concat(leave_, SUFFIX)) {
	REG(R_ESP) = REG(R_EBP);
	REG(R_EBP) = MEM_R(cpu.esp);
	cpu.esp += DATA_BYTE;
	print_asm("leave");
	return 1;
}
make_helper(concat(lea_, SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	swaddr_t addr;
	int len = read_ModR_M(eip + 1, &addr);
	REG(m.reg) = addr;
	print_asm("lea" str(SUFFIX) "    %s, %%%s", ModR_M_asm, REG_NAME(m.reg));
	return len + 1;
}
#include "exec/template-end.h"
