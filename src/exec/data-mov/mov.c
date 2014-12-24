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
make_helper(mov_cr2r) {
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	uint32_t t;
	if (!m.reg)	t = cpu.CR0.val;
	else if (m.reg == 3)	t = cpu.CR3.val;
	else t = 0;
	reg_l(m.R_M) = t;
	print_asm("mov    %%cr%d, %%%s", m.reg, regsl[m.R_M]);
	return 2;
}
make_helper(mov_r2cr) {
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	if (m.reg == 0)	cpu.CR0.val = reg_l(m.R_M);
	else if (m.reg == 3) {
		cpu.CR3.val = reg_l(m.R_M);
	}
	print_asm("mov    %%%s, %%cr%d", regsl[m.R_M], m.reg);
	return 2;
}

make_helper(mov_sr2rm) {
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	if (m.mod == 3) {
		reg_w(m.R_M) = reg_s(m.reg).val;
		print_asm("mov   %%%s, %%%s", regss[m.reg], regsw[m.R_M]);
		return 2;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		swaddr_write(addr, 2, reg_s(m.reg).val);
		print_asm("mov   %%%s, %s", regss[m.R_M], ModR_M_asm);
		return len + 1;
	}
}
make_helper(mov_rm2sr) {
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	if(m.mod == 3){
		reg_s(m.reg).val = reg_w(m.R_M);
		print_asm("mov    %%%s,%%%s", regsw[m.R_M], regss[m.reg]);
		return 2;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1,&addr);
		reg_s(m.reg).val= swaddr_read(addr,2);
		print_asm("mov    %s,%%%s",ModR_M_asm,regss[m.R_M]);
		return 1 + len;
	}
}
//movsx
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
