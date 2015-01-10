#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"
#include "memory.h"
extern uint8_t current_sreg;
//movs
make_helper(concat(movs_, SUFFIX)) {
	if (DATA_BYTE == 1) {
		current_sreg = ES;
		uint8_t t = swaddr_read(reg_l(R_ESI), 1);
		current_sreg = DS;
		swaddr_write(reg_l(R_EDI), 1, t);
	}
	else {
		current_sreg = ES;
		DATA_TYPE t = MEM_R(reg_l(R_ESI));
		current_sreg = DS;
		MEM_W(reg_l(R_EDI), t);
	}
	if (cpu.DF) cpu.esi -= DATA_BYTE, cpu.edi -= DATA_BYTE;
	else cpu.esi += DATA_BYTE, cpu.edi += DATA_BYTE;
	print_asm("movs" str(SUFFIX)"  %%ds:(%%esi),%%es:(%%edi)");
	return 1;
}
//stos
make_helper(concat(stos_, SUFFIX)) {
	current_sreg = ES;
	MEM_W(reg_l(R_EDI), REG(R_EAX));
	if (cpu.DF)	cpu.edi -= DATA_BYTE;
	else cpu.edi += DATA_BYTE;
	print_asm("stos"str(SUFFIX)"  %s,%%es:(%%edi)", REG_NAME(R_EAX));
	return 1;
}
#include "exec/template-end.h"
