#include "exec/helper.h"

#define DATA_BYTE 1
#include "xchg-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "xchg-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "xchg-template.h"
#undef DATA_BYTE


/* for instruction encoding overloading */

extern char suffix;
make_helper(xchg_r2rm_v) {
	return (suffix == 'l' ? xchg_r2rm_l(eip) : xchg_r2rm_w(eip));
}
make_helper(xchg_r2a_v) {
	return (suffix == 'l' ? xchg_r2a_l(eip) : xchg_r2a_w(eip));
}
