#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"
//je
make_helper(concat(je_r_, SUFFIX)) {
	if (cpu.ZF == 1) {
		DATA_TYPE t = instr_fetch(eip + 1, DATA_BYTE);
	    uint32_t x;
		if (DATA_BYTE == 1) {
			if (t >> 7 & 1)	x = t | 0xffffff00;
			else x = t & 0xff; 
		}
		else if (DATA_BYTE == 2) {
			if (t >> 15 & 1)	x = t | 0xffff0000;
			else x = t & 0xffff;
		}
		else x = t;
		cpu.eip += x;
		print_asm("je" str(SUFFIX) "    0x%x", cpu.eip);
	}
	return DATA_BYTE + 1;
}
//jmp
make_helper(concat(jmp_r_, SUFFIX)) {
	DATA_TYPE t = instr_fetch(eip + 1, DATA_BYTE);
	uint32_t x;
	if (DATA_BYTE == 1) {
		if (t >> 7 & 1)	x = t | 0xffffff00;
		else x = t & 0xff; 
	}
	else if (DATA_BYTE == 2) {
		if (t >> 15 & 1)	x = t | 0xffff0000;
		else x = t & 0xffff;
	}
	else x = t;
	cpu.eip += x;
	print_asm("jmp" str(SUFFIX) "   0x%x", cpu.eip);
	return DATA_BYTE + 1;
}
#include "exec/template-end.h"
