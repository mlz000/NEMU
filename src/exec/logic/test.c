#include "exec/helper.h"

#define DATA_BYTE 1
#include "test-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "test-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "test-template.h"
#undef DATA_BYTE


/* for instruction encoding overloading */

extern char suffix;

make_helper(test_i2rm_v) {
	return (suffix == 'l' ? test_i2rm_l(eip) : test_i2rm_w(eip));
}
make_helper(test_i2a_v) {
	return (suffix == 'l' ? test_i2a_l(eip) : test_i2a_w(eip));
}
make_helper(test_r2rm_v) {
	return (suffix == 'l' ? test_r2rm_l(eip) : test_r2rm_w(eip));
}
make_helper(cld) {
	cpu.DF = 0;
	print_asm("cld");
	return 1;
}
make_helper(std) {
	cpu.DF = 1;
	print_asm("std");
	return 1;
}
