#include "exec/helper.h"
#include "cpu/reg.h"

#define DATA_BYTE 1
#include "segment-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "segment-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "segment-template.h"
#undef DATA_BYTE

/* for instruction encoding overloading */

extern char suffix;
make_helper(lgdt_v){
	return (suffix == 'l' ? lgdt_l(eip) : lgdt_w(eip));
}


