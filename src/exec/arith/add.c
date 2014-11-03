#include "exec/helper.h"

#define DATA_BYTE 1
#include "add-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "add-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "add-template.h"
#undef DATA_BYTE


/* for instruction encoding overloading */

extern char suffix;
//add
make_helper(add_i2rm_v) {
	return (suffix == 'l' ? add_i2rm_l(eip) : add_i2rm_w(eip));
}
make_helper(add_r2rm_v) {
	return (suffix == 'l' ? add_r2rm_l(eip) : add_r2rm_w(eip));
}
make_helper(add_rm2r_v) {
	return (suffix == 'l' ? add_rm2r_l(eip) : add_rm2r_w(eip));
}
make_helper(add_i2a_v) {
	return (suffix == 'l' ? add_i2a_l(eip) : add_i2a_w(eip));
}
make_helper(add_ib2rm_v) {
	return (suffix == 'l' ? add_ib2rm_l(eip) : add_ib2rm_w(eip));
}
//adc
make_helper(adc_i2rm_v) {
		return (suffix == 'l' ? adc_i2rm_l(eip) : adc_i2rm_w(eip));
}
make_helper(adc_r2rm_v) {
		return (suffix == 'l' ? adc_r2rm_l(eip) : adc_r2rm_w(eip));
}
make_helper(adc_rm2r_v) {
		return (suffix == 'l' ? adc_rm2r_l(eip) : adc_rm2r_w(eip));
}
make_helper(adc_i2a_v) {
		return (suffix == 'l' ? adc_i2a_l(eip) : adc_i2a_w(eip));
}
make_helper(adc_ib2rm_v) {
	return (suffix == 'l' ? adc_ib2rm_l(eip) : adc_ib2rm_w(eip));
}
//sbb
make_helper(sbb_i2rm_v) {
	return (suffix == 'l' ? sbb_i2rm_l(eip) : sbb_i2rm_w(eip));
}
make_helper(sbb_r2rm_v) {
	return (suffix == 'l' ? sbb_r2rm_l(eip) : sbb_r2rm_w(eip));
}
make_helper(sbb_rm2r_v) {
	return (suffix == 'l' ? sbb_rm2r_l(eip) : sbb_rm2r_w(eip));
}
make_helper(sbb_i2a_v) {
	return (suffix == 'l' ? sbb_i2a_l(eip) : sbb_i2a_w(eip));
}
make_helper(sbb_ib2rm_v) {
	return (suffix == 'l' ? sbb_ib2rm_l(eip) : sbb_ib2rm_w(eip));
}
//sub
make_helper(sub_i2rm_v) {
	return (suffix == 'l' ? sub_i2rm_l(eip) : sub_i2rm_w(eip));
}
make_helper(sub_r2rm_v) {
	return (suffix == 'l' ? sub_r2rm_l(eip) : sub_r2rm_w(eip));
}
make_helper(sub_rm2r_v) {
	return (suffix == 'l' ? sub_rm2r_l(eip) : sub_rm2r_w(eip));
}
make_helper(sub_i2a_v) {
	return (suffix == 'l' ? sub_i2a_l(eip) : sub_i2a_w(eip));
}
make_helper(sub_ib2rm_v) {
	return (suffix == 'l' ? sub_ib2rm_l(eip) : sub_ib2rm_w(eip));
}
//inc
make_helper(inc_rm_v) {
	return (suffix == 'l' ? inc_rm_l(eip) : inc_rm_w(eip));
}
make_helper(inc_r_v) {
	return (suffix == 'l' ? inc_r_l(eip) : inc_r_w(eip));
}
//dec
make_helper(dec_rm_v) {
	return (suffix == 'l' ? dec_rm_l(eip) : dec_rm_w(eip));
}
make_helper(dec_r_v) {
	return (suffix == 'l' ? dec_r_l(eip) : dec_r_w(eip));
}
//neg
make_helper(neg_rm_v) {
	return (suffix == 'l' ? neg_rm_l(eip) : neg_rm_w(eip));
}
