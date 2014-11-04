#include "exec/helper.h"

#include "all-instr.h"

typedef int (*helper_fun)(swaddr_t);


/* TODO: Add more instructions!!! */

helper_fun opcode_table [256] = {
/* 0x00 */	add_r2rm_b, add_r2rm_v, add_rm2r_b, add_rm2r_v, 
/* 0x04 */	add_i2a_b, add_i2a_v, inv, inv, 
/* 0x08 */	inv, inv, inv, inv, 
/* 0x0c */	inv, inv, inv, jump, 
/* 0x10 */	inv, inv, inv, inv, 
/* 0x14 */	inv, inv, inv, inv, 
/* 0x18 */	inv, inv, inv, inv, 
/* 0x1c */	inv, inv, inv, inv, 
/* 0x20 */	inv, inv, inv, inv, 
/* 0x24 */	inv, inv, inv, inv,
/* 0x28 */	inv, inv, inv, inv, 
/* 0x2c */	inv, inv, inv, inv, 
/* 0x30 */	inv, inv, inv, inv, 
/* 0x34 */	inv, inv, inv, inv,
/* 0x38 */	cmp_r2rm_b, cmp_r2rm_v, cmp_rm2r_b, cmp_rm2r_v, 
/* 0x3c */	cmp_i2a_b, cmp_i2a_v, cmp_i2a_v, inv, 
/* 0x40 */	inc_r_v, inv, inv, inv, 
/* 0x44 */	inv, inv, inv, inv,
/* 0x48 */	dec_r_v, inv, inv, inv, 
/* 0x4c */	inv, inv, inv, inv, 
/* 0x50 */	push_r_v, push_r_v, push_r_v, push_r_v, 
/* 0x54 */	push_r_v, push_r_v, push_r_v, push_r_v,
/* 0x58 */	pop_r_v, inv, inv, inv, 
/* 0x5c */	inv, inv, inv, inv, 
/* 0x60 */	inv, inv, inv, inv,
/* 0x64 */	inv, inv, data_size, inv,
/* 0x68 */	push_i_v, inv, push_i_b, inv, 
/* 0x6c */	inv, inv, inv, inv, 
/* 0x70 */	inv, inv, inv, inv,
/* 0x74 */	je_r_b, inv, inv, inv,
/* 0x78 */	inv, inv, inv, inv, 
/* 0x7c */	inv, inv, jle_r_b, inv, 
/* 0x80 */	grp1ib, grp1iv, nemu_trap, grp1ibv, 
/* 0x84 */	test_r2rm_b, test_r2rm_v, xchg_r2rm_b, xchg_r2rm_v, 
/* 0x88 */	mov_r2rm_b, mov_r2rm_v, mov_rm2r_b, mov_rm2r_v,
/* 0x8c */	inv, inv, inv, pop_m_v, 
/* 0x90 */	xchg_r2a_v, xchg_r2a_v, xchg_r2a_v, xchg_r2a_v,
/* 0x94 */	xchg_r2a_v, xchg_r2a_v, xchg_r2a_v, xchg_r2a_v,
/* 0x98 */	inv, inv, inv, inv, 
/* 0x9c */	inv, inv, inv, inv, 
/* 0xa0 */	mov_moffs2a_b, mov_moffs2a_v, mov_a2moffs_b, mov_a2moffs_v,
/* 0xa4 */	inv, inv, inv, inv,
/* 0xa8 */	test_i2a_b, test_i2a_v, inv, inv,
/* 0xac */	inv, inv, inv, inv,
/* 0xb0 */	mov_i2r_b, mov_i2r_b, mov_i2r_b, mov_i2r_b,
/* 0xb4 */	mov_i2r_b, mov_i2r_b, mov_i2r_b, mov_i2r_b,
/* 0xb8 */	mov_i2r_v, mov_i2r_v, mov_i2r_v, mov_i2r_v, 
/* 0xbc */	mov_i2r_v, mov_i2r_v, mov_i2r_v, mov_i2r_v, 
/* 0xc0 */	inv, inv, inv, ret_v,
/* 0xc4 */	inv, inv, mov_i2rm_b, mov_i2rm_v,
/* 0xc8 */	inv, leave_v, inv, inv,
/* 0xcc */	int3, inv, inv, inv,
/* 0xd0 */	inv, inv, inv, inv,
/* 0xd4 */	inv, inv, inv, inv,
/* 0xd8 */	inv, inv, inv, inv,
/* 0xdc */	inv, inv, inv, inv,
/* 0xe0 */	inv, inv, inv, inv,
/* 0xe4 */	inv, inv, inv, inv,
/* 0xe8 */	inv, jmp_r_v, inv, jmp_r_b,
/* 0xec */	inv, inv, inv, inv,
/* 0xf0 */	inv, inv, inv, inv,
/* 0xf4 */	inv, inv, grp3b, grp3v,
/* 0xf8 */	inv, inv, inv, inv,
/* 0xfc */	inv, inv, grp4, grp5
};

helper_fun opcode_table2 [256] = {
/* 0x00 */	add_r2rm_b, add_r2rm_v, add_rm2r_b, add_rm2r_v, 
/* 0x04 */	add_i2a_b, add_i2a_v, inv, inv, 
/* 0x08 */	inv, inv, inv, inv, 
/* 0x0c */	inv, inv, inv, je_r_v, 
/* 0x10 */	inv, inv, inv, inv, 
/* 0x14 */	inv, inv, inv, inv, 
/* 0x18 */	inv, inv, inv, inv, 
/* 0x1c */	inv, inv, inv, inv, 
/* 0x20 */	inv, inv, inv, inv, 
/* 0x24 */	inv, inv, inv, inv,
/* 0x28 */	inv, inv, inv, inv, 
/* 0x2c */	inv, inv, inv, inv, 
/* 0x30 */	inv, inv, inv, inv, 
/* 0x34 */	inv, inv, inv, inv,
/* 0x38 */	cmp_r2rm_b, cmp_r2rm_v, cmp_rm2r_b, cmp_rm2r_v, 
/* 0x3c */	cmp_i2a_b, cmp_i2a_v, cmp_i2a_v, inv, 
/* 0x40 */	inv, inv, inv, inv, 
/* 0x44 */	inv, inv, inv, inv,
/* 0x48 */	inv, inv, inv, inv, 
/* 0x4c */	inv, inv, inv, inv, 
/* 0x50 */	push_r_v, push_r_v, push_r_v, push_r_v, 
/* 0x54 */	push_r_v, push_r_v, push_r_v, push_r_v,
/* 0x58 */	pop_r_v, inv, inv, inv, 
/* 0x5c */	inv, inv, inv, inv, 
/* 0x60 */	inv, inv, inv, inv,
/* 0x64 */	inv, inv, data_size, inv,
/* 0x68 */	push_i_v, inv, push_i_b, inv, 
/* 0x6c */	inv, inv, inv, inv, 
/* 0x70 */	inv, inv, inv, inv,
/* 0x74 */	je_r_b, inv, inv, inv,
/* 0x78 */	inv, inv, inv, inv, 
/* 0x7c */	inv, inv, inv, inv, 
/* 0x80 */	cmp_i2rm_b, cmp_i2rm_v, nemu_trap, cmp_ib2rm_v, 
/* 0x84 */	je_r_v, test_r2rm_v, xchg_r2rm_b, xchg_r2rm_v, 
/* 0x88 */	mov_r2rm_b, mov_r2rm_v, mov_rm2r_b, mov_rm2r_v,
/* 0x8c */	inv, inv, jle_r_v, pop_m_v, 
/* 0x90 */	xchg_r2a_v, xchg_r2a_v, xchg_r2a_v, xchg_r2a_v,
/* 0x94 */	xchg_r2a_v, xchg_r2a_v, xchg_r2a_v, xchg_r2a_v,
/* 0x98 */	inv, inv, inv, inv, 
/* 0x9c */	inv, inv, inv, inv, 
/* 0xa0 */	mov_moffs2a_b, mov_moffs2a_v, mov_a2moffs_b, mov_a2moffs_v,
/* 0xa4 */	inv, inv, inv, inv,
/* 0xa8 */	test_i2a_b, test_i2a_v, inv, inv,
/* 0xac */	inv, inv, inv, inv,
/* 0xb0 */	mov_i2r_b, mov_i2r_b, mov_i2r_b, mov_i2r_b,
/* 0xb4 */	mov_i2r_b, mov_i2r_b, movzx_rmb2r_v, movzx_rmw2r_v,
/* 0xb8 */	mov_i2r_v, mov_i2r_v, mov_i2r_v, mov_i2r_v, 
/* 0xbc */	mov_i2r_v, mov_i2r_v, movsx_rmb2r_v, movsx_rmw2r_v, 
/* 0xc0 */	inv, inv, inv, inv,
/* 0xc4 */	inv, inv, mov_i2rm_b, mov_i2rm_v,
/* 0xc8 */	inv, leave_v, inv, inv,
/* 0xcc */	int3, inv, inv, inv,
/* 0xd0 */	inv, inv, inv, inv,
/* 0xd4 */	inv, inv, inv, inv,
/* 0xd8 */	inv, inv, inv, inv,
/* 0xdc */	inv, inv, inv, inv,
/* 0xe0 */	inv, inv, inv, inv,
/* 0xe4 */	inv, inv, inv, inv,
/* 0xe8 */	inv, inv, inv, inv,
/* 0xec */	inv, inv, inv, inv,
/* 0xf0 */	inv, inv, inv, inv,
/* 0xf4 */	inv, inv, test_i2rm_b, test_i2rm_v,
/* 0xf8 */	inv, inv, inv, inv,
/* 0xfc */	inv, inv, inv, push_m_v
};


make_helper(exec) {
	return opcode_table[ instr_fetch(eip, 1) ](eip);
}
make_helper(jump) {
	return opcode_table2[ instr_fetch(eip + 1, 1) ] (eip + 1) + 1;
}
make_helper(grp1ib) {
	int t = instr_fetch(eip + 1, 1);
	switch((t >> 3) & 7) {
		case 0:	return add_i2rm_b(eip);
		case 1: return or_i2rm_b(eip);
	    case 2: return adc_i2rm_b(eip);
	    case 3: return sbb_i2rm_b(eip);
		case 4: return and_i2rm_b(eip);
		case 5: return sub_i2rm_b(eip);
		case 6: return xor_i2rm_b(eip);
		case 7: return cmp_i2rm_b(eip);
	}
	return 1;
}
make_helper(grp1iv) {
	int t = instr_fetch(eip + 1, 1);
	switch((t >> 3) & 7) {
		case 0:	return add_i2rm_v(eip);
		case 1: return or_i2rm_v(eip);
	    case 2: return adc_i2rm_v(eip);
	    case 3: return sbb_i2rm_v(eip);
		case 4: return and_i2rm_v(eip);
		case 5: return sub_i2rm_v(eip);
		case 6: return xor_i2rm_v(eip);
		case 7: return cmp_i2rm_v(eip);
	}
	printf("%d\n", t);//debug
	return 1;
}
make_helper(grp1ibv) {
	int t = instr_fetch(eip + 1, 1);
	switch((t >> 3) & 7) {
		case 0:	return add_ib2rm_v(eip);
		case 1: return or_ib2rm_v(eip);
	    case 2: return adc_ib2rm_v(eip);
	    case 3: return sbb_ib2rm_v(eip);
		case 4: return and_ib2rm_v(eip);
		case 5: return sub_ib2rm_v(eip);
		case 6: return xor_ib2rm_v(eip);
		case 7: return cmp_ib2rm_v(eip);
	}
	return 1;
}
make_helper(grp3b) {
	int t = instr_fetch(eip + 1, 1);
	switch((t >> 3) & 7) {
		case 0:	return test_i2rm_b(eip);
	}
	return 1;
}
make_helper(grp3v) {
	int t = instr_fetch(eip + 1, 1);
	switch((t >> 3) & 7) {
		case 0: return test_i2rm_v(eip);
	}
	return 1;
}
make_helper(grp4) {
	int t = instr_fetch(eip + 1, 1);
	switch((t >> 3) & 7) {
		case 0:	return inc_rm_b(eip);
		case 1: return dec_rm_b(eip);
	}
	return 1;
}
make_helper(grp5) {
	int t = instr_fetch(eip + 1, 1);
	switch((t >> 3) & 7) {
		case 0:	return inc_rm_v(eip);
		case 1: return dec_rm_v(eip);
		case 6: return push_m_v(eip);
	}
	return 1;
}
