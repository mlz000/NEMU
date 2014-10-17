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

make_helper(jcc_i2r_v) {
	return (suffix == 'l' ? jcc_i2r_l(eip) : jcc_i2r_w(eip));
}

make_helper(jcc_i2rm_v) {
	return (suffix == 'l' ? jcc_i2rm_l(eip) : jcc_i2rm_w(eip));
}

make_helper(jcc_r2rm_v) {
	return (suffix == 'l' ? jcc_r2rm_l(eip) : jcc_r2rm_w(eip));
}

make_helper(jcc_rm2r_v) {
	return (suffix == 'l' ? jcc_rm2r_l(eip) : jcc_rm2r_w(eip));
}

make_helper(jcc_a2moffs_v) {
	return (suffix == 'l' ? jcc_a2moffs_l(eip) : jcc_a2moffs_w(eip));
}

make_helper(jcc_moffs2a_v) {
	return (suffix == 'l' ? jcc_moffs2a_l(eip) : jcc_moffs2a_w(eip));
}

