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
/* 0x28 */	sub_r2rm_b, sub_r2rm_v, sub_rm2r_b, sub_rm2r_v, 
/* 0x2c */	sub_i2a_b, sub_i2a_v, inv, inv, 
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
/* 0x68 */	push_i_v, imul_irm2r_v, push_i_b, imul_ibrm2r_v, 
/* 0x6c */	inv, inv, inv, inv, 
/* 0x70 */	jo_r_b, jno_r_b, jb_r_b, jae_r_b,
/* 0x74 */	je_r_b, jne_r_b, jbe_r_b, ja_r_b,
/* 0x78 */	js_r_b, jns_r_b, jp_r_b, jnp_r_b, 
/* 0x7c */	jl_r_b, jge_r_b, jle_r_b, jg_r_b, 
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
/* 0xc0 */	grp2ib, grp2ib, inv, ret_v,
/* 0xc4 */	inv, inv, mov_i2rm_b, mov_i2rm_v,
/* 0xc8 */	inv, leave_v, inv, inv,
/* 0xcc */	int3, inv, inv, inv,
/* 0xd0 */	grp2b, grp2v, grp2clb, grp2clv,
/* 0xd4 */	inv, inv, inv, inv,
/* 0xd8 */	inv, inv, inv, inv,
/* 0xdc */	inv, inv, inv, inv,
/* 0xe0 */	inv, inv, inv, jcxz_r_b,
/* 0xe4 */	inv, inv, inv, inv,
/* 0xe8 */	call_r_v, jmp_r_v, inv, jmp_r_b,
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
/* 0x80 */	jo_r_v, jno_r_v, jb_r_v, jae_r_v, 
/* 0x84 */	je_r_v, jne_r_v, jbe_r_v, ja_r_v, 
/* 0x88 */	js_r_v, jns_r_v, jp_r_v, jnp_r_v,
/* 0x8c */	jl_r_v, jge_r_v, jle_r_v, jg_r_v, 
/* 0x90 */	seto_rm_v, setno_rm_v, setb_rm_v, setae_rm_v,
/* 0x94 */	sete_rm_v, setne_rm_v, setbe_rm_v, seta_rm_v,
/* 0x98 */	sets_rm_v, setns_rm_v, setp_rm_v, setnp_rm_v, 
/* 0x9c */	setl_rm_v, setge_rm_v, setle_rm_v, setg_rm_v, 
/* 0xa0 */	mov_moffs2a_b, mov_moffs2a_v, mov_a2moffs_b, mov_a2moffs_v,
/* 0xa4 */	inv, inv, inv, inv,
/* 0xa8 */	test_i2a_b, test_i2a_v, inv, inv,
/* 0xac */	inv, inv, inv, imul_rm2r_v,
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
	//printf("t:%d\n", t >> 3 & 7);//debug
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
//C0
make_helper(grp2ib) {
	int t = instr_fetch(eip + 1, 1);
	switch((t >> 3) & 7) {
		case 4: return sal_rmi_b(eip);
		case 5: return shr_rmi_b(eip);
		case 7: return sar_rmi_b(eip);
	}
	return 1;
}
//C1
make_helper(grp2iv) {
	int t = instr_fetch(eip + 1, 1);
	switch((t >> 3) & 7) {
		case 4:	return sal_rmi_v(eip);
		case 5: return shr_rmi_v(eip);
		case 7: return sar_rmi_v(eip);
	}
	return 1;
}
//D0
make_helper(grp2b) {
	int t = instr_fetch(eip + 1, 1);
	switch((t >> 3) & 7) {
		case 4: return sal_rm_b(eip);
		case 5: return shr_rm_b(eip);
		case 7: return sar_rm_b(eip);
	}
	return 1;
}
//D1
make_helper(grp2v) {
	int t = instr_fetch(eip + 1, 1);
	switch((t >> 3) & 7) {
		case 4: return sal_rm_v(eip);
		case 5: return shr_rm_v(eip);
		case 7: return sar_rm_v(eip);
	}
	return 1;
}
//D2
make_helper(grp2clb) {
	int t = instr_fetch(eip + 1, 1);
	switch((t >> 3) & 7) {
		case 4: return sal_cl_b(eip);
		case 5: return shr_cl_b(eip);
		case 7:	return sar_cl_b(eip);
	}
	return 1;
}
//D3
make_helper(grp2clv) {
	int t = instr_fetch(eip + 1, 1);
	switch((t >> 3) & 7) {
		case 4: return sal_cl_v(eip);
		case 5: return shr_cl_v(eip);
		case 7: return sar_cl_v(eip);
	}
	return 1;
}
make_helper(grp3b) {
	int t = instr_fetch(eip + 1, 1);
	switch((t >> 3) & 7) {
		case 0:	return test_i2rm_b(eip);
		case 4: return mul_rm2a_b(eip);
		case 5: return imul_rm2a_b(eip);
		case 6: return div_rm2a_b(eip);
		case 7: return idiv_rm2a_b(eip);
	}
	return 1;
}
make_helper(grp3v) {
	int t = instr_fetch(eip + 1, 1);
	switch((t >> 3) & 7) {
		case 0: return test_i2rm_v(eip);
		case 4: return mul_rm2a_v(eip);
		case 5: return imul_rm2a_v(eip);
		case 6: return div_rm2a_v(eip);
		case 7: return idiv_rm2a_v(eip);
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
		case 2: return call_rm_v(eip);
		case 4: return jmp_rm_v(eip);
		case 6: return push_m_v(eip);
	
	}
	return 1;
}
