#include "exec/helper.h"
#include "cpu/reg.h"
#include "cpu/modrm.h"
make_helper(cli) {
	cpu.IF =  0;
	return 1;
}
