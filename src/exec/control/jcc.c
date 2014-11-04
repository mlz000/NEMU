#include "exec/helper.h"

#define DATA_BYTE 1
#include "jcc-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "jcc-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "jcc-template.h"
#undef DATA_BYTE


/* for instruction encoding overloading */

extern char suffix;
//je
make_helper(je_r_v) {
	return (suffix == 'l' ? je_r_l(eip) : je_r_w(eip));
}
//jle
make_helper(jle_r_v) {
	return (suffix == 'l' ? jle_r_l(eip) : jle_r_w(eip));
}
//jmp
make_helper(jmp_r_v) {
	return (suffix == 'l' ? jmp_r_l(eip) : jmp_r_w(eip));
}
