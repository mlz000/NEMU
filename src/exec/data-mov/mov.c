#include "exec/helper.h"

#define DATA_BYTE 1
#include "mov-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "mov-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "mov-template.h"
#undef DATA_BYTE


/* for instruction encoding overloading */

extern char suffix;

make_helper(mov_i2r_v) {
	return (suffix == 'l' ? mov_i2r_l(eip) : mov_i2r_w(eip));
}

make_helper(mov_i2rm_v) {
	return (suffix == 'l' ? mov_i2rm_l(eip) : mov_i2rm_w(eip));
}

make_helper(mov_r2rm_v) {
	return (suffix == 'l' ? mov_r2rm_l(eip) : mov_r2rm_w(eip));
}

make_helper(mov_rm2r_v) {
	return (suffix == 'l' ? mov_rm2r_l(eip) : mov_rm2r_w(eip));
}

make_helper(mov_a2moffs_v) {
	return (suffix == 'l' ? mov_a2moffs_l(eip) : mov_a2moffs_w(eip));
}

make_helper(mov_moffs2a_v) {
	return (suffix == 'l' ? mov_moffs2a_l(eip) : mov_moffs2a_w(eip));
}
make_helper(movsx_rmb2r_v) {
	return (suffix == 'l' ? movsx_rmb2r_l(eip) : movsx_rmb2r_w(eip));
}
make_helper(movsx_rmw2r_v) {
	return (suffix == 'l' ? movsx_rmw2r_l(eip) : movsx_rmw2r_w(eip));
}
make_helper(movzx_rmb2r_v) {
	return (suffix == 'l' ? movzx_rmb2r_l(eip) : movzx_rmb2r_w(eip));
}
make_helper(movzx_rmw2r_v) {
	return (suffix == 'l' ? movzx_rmw2r_l(eip) : movzx_rmw2r_w(eip));
}
make_helper(pushr_v) {
	return (suffix == 'l' ? pushr_l(eip) : pushr_w(eip));
}
make_helper(pushm_v) {
	return (suffix == 'l' ? pushm_l(eip) : pushm_w(eip));
}
make_helper(pushi_v) {
	return (suffix == 'l' ? pushi_l(eip) : pushi_w(eip));
}
make_helper(popr_v) {
	return (suffix == 'l' ? popr_l(eip) : popr_w(eip));
}
make_helper(popm_v) {
	return (suffix == 'l' ? popm_l(eip) : popm_w(eip));
}
make_helper(leave_v) {
	return (suffix == 'l' ? leave_l(eip) : leave_w(eip));
}
