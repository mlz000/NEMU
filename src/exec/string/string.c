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

make_helper(exec);
make_helper(stos_v) {
	return (suffix == 'l' ? stos_l(eip) : stos_w(eip));
}
//movs
make_helper(movs_v) {
		return (suffix == 'l' ? movs_l(eip) : movs_w(eip));
}
//rep
make_helper(rep) {
	while (reg_l(R_ECX) > 0) {
		exec(eip + 1);
		--reg_l(R_ECX);
	}
	char s[40];
	strcpy(s, assembly);
	print_asm("rep %s", s);
	return 2;
}
#include "exec/template-end.h"
