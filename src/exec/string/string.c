#include "exec/helper.h"
#include "cpu/reg.h"

#define DATA_BYTE 1
#include "string-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "string-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "string-template.h"
#undef DATA_BYTE
extern char suffix;
//stos
make_helper(stos_v) {
	return (suffix == 'l' ? stos_l(eip) : stos_w(eip));
}
//movs
make_helper(movs_v) {
		return (suffix == 'l' ? movs_l(eip) : movs_w(eip));
}
//rep
make_helper(rep) {
	puts("wtf!!!");
	int op = instr_fetch(eip + 1, 1);
	int flag = instr_fetch(eip - 1, 1);
	uint32_t len = 1, t = 4;
	if (flag == 0x66)	t = 2;
	switch(op) {
		case 0xa4: while (reg_b(R_ECX)--)	len = movs_b(eip + 1);
					   ++reg_b(R_ECX);
		case 0xa5: if (t == 2) {
					   while (reg_w(R_ECX)--)	len = movs_v(eip + 1);
					   ++reg_w(R_ECX);
				   }
				   else {
					   while (reg_l(R_ECX)--)	len = movs_v(eip + 1);
					   ++reg_l(R_ECX);
				   }
		case 0xaa: while(reg_b(R_ECX)--)	len = stos_b(eip + 1);
					   ++reg_b(R_ECX);
		case 0xab: if (t == 2) {
					   while (reg_w(R_ECX)--)	len = stos_b(eip + 1);
					   ++reg_w(R_ECX);
				   }
	}
	char s[40];
	strcpy(s, assembly);
	print_asm("rep %s", s);
	return len + 1;
}
#include "exec/template-end.h"
