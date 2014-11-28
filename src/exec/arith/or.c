#include "exec/helper.h"

#define DATA_BYTE 1
#include "or-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "or-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "or-template.h"
#undef DATA_BYTE


/* for instruction encoding overloading */

extern char suffix;
//or
make_helper(or_i2rm_v) {
	return (suffix == 'l' ? or_i2rm_l(eip) : or_i2rm_w(eip));
}
make_helper(or_r2rm_v) {
	return (suffix == 'l' ? or_r2rm_l(eip) : or_r2rm_w(eip));
}
make_helper(or_rm2r_v) {
	return (suffix == 'l' ? or_rm2r_l(eip) : or_rm2r_w(eip));
}
make_helper(or_i2a_v) {
	return (suffix == 'l' ? or_i2a_l(eip) : or_i2a_w(eip));
}
make_helper(or_ib2rm_v) {
	return (suffix == 'l' ? or_ib2rm_l(eip) : or_i2rm_w(eip));
}
//xor
make_helper(xor_i2rm_v) {
		return (suffix == 'l' ? xor_i2rm_l(eip) : xor_i2rm_w(eip));
}
make_helper(xor_r2rm_v) {
		return (suffix == 'l' ? xor_r2rm_l(eip) : xor_r2rm_w(eip));
}
make_helper(xor_rm2r_v) {
		return (suffix == 'l' ? xor_rm2r_l(eip) : xor_rm2r_w(eip));
}
make_helper(xor_i2a_v) {
		return (suffix == 'l' ? xor_i2a_l(eip) : xor_i2a_w(eip));
}
make_helper(xor_ib2rm_v) {
		return (suffix == 'l' ? xor_ib2rm_l(eip) : xor_i2rm_w(eip));
}
//and
make_helper(and_i2rm_v) {
		return (suffix == 'l' ? and_i2rm_l(eip) : and_i2rm_w(eip));
}
make_helper(and_r2rm_v) {
		return (suffix == 'l' ? and_r2rm_l(eip) : and_r2rm_w(eip));
}
make_helper(and_rm2r_v) {
		return (suffix == 'l' ? and_rm2r_l(eip) : and_rm2r_w(eip));
}
make_helper(and_i2a_v) {
		return (suffix == 'l' ? and_i2a_l(eip) : and_i2a_w(eip));
}
make_helper(and_ib2rm_v) {
		return (suffix == 'l' ? and_ib2rm_l(eip) : and_i2rm_w(eip));
}
//not
make_helper(not_rm_v) {
	return (suffix == 'l' ? not_rm_l(eip) : not_rm_w(eip));
}
//sal
make_helper(sal_rm_v) {
	return (suffix == 'l' ? sal_rm_l(eip) : sal_rm_w(eip));
}
make_helper(sal_rmi_v) {
	return (suffix == 'l' ? sal_rmi_l(eip) : sal_rmi_w(eip));
}
make_helper(sal_cl_v) {
	return (suffix == 'l' ? sal_cl_l(eip) : sal_cl_w(eip));
}
//sar
make_helper(sar_rm_v) {
	return (suffix == 'l' ? sar_rm_l(eip) : sar_rm_w(eip));
}
make_helper(sar_rmi_v) {
	return (suffix == 'l' ? sar_rmi_l(eip) : sar_rmi_w(eip));
}
make_helper(sar_cl_v) {
	return (suffix == 'l' ? sar_cl_l(eip) : sar_cl_w(eip));
}
//shr
make_helper(shr_rm_v) {
	return (suffix == 'l' ? shr_rm_l(eip) : shr_rm_w(eip));
}
make_helper(shr_rmi_v) {
	return (suffix == 'l' ? shr_rmi_l(eip) : shr_rmi_w(eip));
}
make_helper(shr_cl_v) {
	return (suffix == 'l' ? shr_cl_l(eip) : shr_cl_w(eip));
}
