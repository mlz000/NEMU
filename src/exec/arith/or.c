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
