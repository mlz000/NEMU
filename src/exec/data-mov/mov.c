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
make_helper(push_r_v) {
	return (suffix == 'l' ? push_r_l(eip) : push_r_w(eip));
}
make_helper(push_m_v) {
	return (suffix == 'l' ? push_m_l(eip) : push_m_w(eip));
}
make_helper(push_i_v) {
	return (suffix == 'l' ? push_i_l(eip) : push_i_w(eip));
}
make_helper(pop_r_v) {
	return (suffix == 'l' ? pop_r_l(eip) : pop_r_w(eip));
}
make_helper(pop_m_v) {
	return (suffix == 'l' ? pop_m_l(eip) : pop_m_w(eip));
}
make_helper(leave_v) {
	return (suffix == 'l' ? leave_l(eip) : leave_w(eip));
}
//lea
make_helper(lea_v) {
	return (suffix == 'l' ? lea_l(eip) : lea_w(eip));
}
