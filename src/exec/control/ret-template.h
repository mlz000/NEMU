#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"
//ret
extern uint8_t current_sreg;
make_helper(concat(ret_, SUFFIX)) {
	cpu.eip = MEM_R(REG(R_ESP));
	REG(R_ESP) += DATA_BYTE;
	if (DATA_BYTE == 2)	cpu.eip &= 0xffff;
	print_asm("ret");
	--cpu.eip;
	return 1;
}
make_helper(concat(reti_, SUFFIX)) {
	DATA_TYPE imm = instr_fetch(eip + 1, 2); 
	cpu.eip = MEM_R(REG(R_ESP));
	REG(R_ESP) += DATA_BYTE;
	if (DATA_BYTE == 2)	cpu.eip &= 0xffff;
	print_asm("reti");
	cpu.eip -= 3;
	REG(R_ESP) += imm;
	return 3;
}
//call
make_helper(concat(call_r_, SUFFIX)) {
	cpu.esp -= DATA_BYTE;
	MEM_W(cpu.esp, cpu.eip + 1 + DATA_BYTE);
	DATA_TYPE t = instr_fetch(eip + 1, DATA_BYTE);
	uint32_t x;
	if (DATA_BYTE == 1) {
		if ((t >> 7) & 1)	x = t | 0xffffff00;
		else x = t & 0xff; 
	}
	else if (DATA_BYTE == 2) {
		if ((t >> 15) & 1)	x = t | 0xffff0000;
		else x = t & 0xffff;
	}
	else x = t;
	if (DATA_BYTE == 2)	cpu.eip = (cpu.eip + x) & 0xffff;
	else cpu.eip += x;
	print_asm("call   0x%x", cpu.eip + DATA_BYTE + 1);
	return DATA_BYTE + 1;
}
make_helper(concat(call_rm_, SUFFIX)) {
	cpu.esp -= DATA_BYTE;
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	if (m.mod == 3) {
		MEM_W(cpu.esp, cpu.eip + 2);
		if (DATA_BYTE == 2)	cpu.eip = REG(m.R_M) & 0xffff;
		else cpu.eip = REG(m.R_M);
		print_asm("call   %%%s", REG_NAME(m.R_M));
		cpu.eip -= 2;
		return 2;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		MEM_W(cpu.esp, cpu.eip + len + 1);
		if (DATA_BYTE == 2)	cpu.eip = MEM_R(addr) & 0xffff;
		else cpu.eip = MEM_R(addr);
		print_asm("call    %s", ModR_M_asm);
		cpu.eip -= len + 1;
		return len + 1;
	}
}
#include "exec/template-end.h"
