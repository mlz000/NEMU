#include "exec/helper.h"

#define DATA_BYTE 1
#include "mul-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "mul-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "mul-template.h"
#undef DATA_BYTE


/* for instruction encoding overloading */

extern char suffix;
//mul
make_helper(mul_rm2a_v) {
	return (suffix == 'l' ? mul_rm2a_l(eip) : mul_rm2a_w(eip));
}
//imul
make_helper(imul_rm2a_v) {
	return (suffix == 'l' ? imul_rm2a_l(eip) : imul_rm2a_w(eip));
}
make_helper(imul_irm2r_v) {
	return (suffix == 'l' ? imul_irm2r_l(eip) : imul_irm2r_w(eip));
}
make_helper(imul_ibrm2r_v) {
	return (suffix == 'l' ? imul_ibrm2r_l(eip) : imul_ibrm2r_w(eip));
}
make_helper(imul_rm2r_v) {
	return (suffix == 'l' ? imul_rm2r_l(eip) : imul_rm2r_w(eip));
}
//div
make_helper(div_rm2a_v) {
	return (suffix == 'l' ? div_rm2a_l(eip) : div_rm2a_w(eip));
}
//idiv
make_helper(idiv_rm2a_v) {
	return (suffix == 'l' ? idiv_rm2a_l(eip) : idiv_rm2a_w(eip));
}
