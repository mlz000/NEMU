#include "exec/helper.h"

#define DATA_BYTE 1
#include "ret-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "ret-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "ret-template.h"
#undef DATA_BYTE


/* for instruction encoding overloading */

extern char suffix;

//ret
make_helper(ret_v) {
	return (suffix == 'l' ? ret_l(eip) : ret_w(eip));
}
make_helper(reti_v) {
	return (suffix == 'l' ? reti_l(eip) : reti_w(eip));
}
//call
make_helper(call_r_v) {
	return (suffix == 'l' ? call_r_l(eip) : call_r_w(eip));
}
make_helper(call_rm_v) {
	return (suffix == 'l' ? call_rm_l(eip) : call_rm_w(eip));
}
//movs
make_helper(movs_v) {
	return (suffix == 'l' ? movs_l(eip) : movs_w(eip));
}
//rep
make_helper(rep) {
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
	}
	return len + 1;
}
