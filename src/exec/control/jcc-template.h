#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"
//jcxz
make_helper(concat(jcxz_r_, SUFFIX)) {
	DATA_TYPE t = instr_fetch(eip + 1, DATA_BYTE);
    int x = t;
	if (DATA_BYTE == 1) {
		if ((t >> 7) & 1)	x = t | 0xffffff00;
		//else x = t & 0xff; 
	}
	else if (DATA_BYTE == 2) {
		if ((t >> 15) & 1)	x = t | 0xffff0000;
		//else x = t & 0xffff;
	}
	else x = t;
	print_asm("jcxz   0x%x", eip + x + DATA_BYTE + 1);
	if (!reg_w(R_CX))	cpu.eip += x;
	return DATA_BYTE + 1;
}
//jo
make_helper(concat(jo_r_, SUFFIX)) {
	DATA_TYPE t = instr_fetch(eip + 1, DATA_BYTE);
    int x = t;
	if (DATA_BYTE == 1) {
		if ((t >> 7) & 1)	x = t | 0xffffff00;
	}
	else if (DATA_BYTE == 2) {
		if ((t >> 15) & 1)	x = t | 0xffff0000;
	}
	else x = t;
	print_asm("jo     0x%x", eip + x + DATA_BYTE + 1);
	if (cpu.OF == 1)	cpu.eip += x;
	return DATA_BYTE + 1;
}
//jno
make_helper(concat(jno_r_, SUFFIX)) {
	DATA_TYPE t = instr_fetch(eip + 1, DATA_BYTE);
    int x = t;
	if (DATA_BYTE == 1) {
		if ((t >> 7) & 1)	x = t | 0xffffff00;
	//	else x = t & 0xff; 
	}
	else if (DATA_BYTE == 2) {
		if ((t >> 15) & 1)	x = t | 0xffff0000;
	//	else x = t & 0xffff;
	}
	else x = t;
	print_asm("jno    0x%x", eip + x + DATA_BYTE + 1);
	if (cpu.OF == 0)	cpu.eip += x;
	return DATA_BYTE + 1;
}
//jb
make_helper(concat(jb_r_, SUFFIX)) {
	DATA_TYPE t = instr_fetch(eip + 1, DATA_BYTE);
    int x = t;
	if (DATA_BYTE == 1) {
		if ((t >> 7) & 1)	x = t | 0xffffff00;
		//else x = t & 0xff; 
	}
	else if (DATA_BYTE == 2) {
		if ((t >> 15) & 1)	x = t | 0xffff0000;
		//else x = t & 0xffff;
	}
	else x = t;
	print_asm("jb     0x%x", eip + x + DATA_BYTE + 1);
	if (cpu.CF == 1)	cpu.eip += x;
	return DATA_BYTE + 1;
}
//jae
make_helper(concat(jae_r_, SUFFIX)) {
	DATA_TYPE t = instr_fetch(eip + 1, DATA_BYTE);
    int x = t;
	if (DATA_BYTE == 1) {
		if ((t >> 7) & 1)	x = t | 0xffffff00;
		//else x = t & 0xff; 
	}
	else if (DATA_BYTE == 2) {
		if ((t >> 15) & 1)	x = t | 0xffff0000;
		//else x = t & 0xffff;
	}
	else x = t;
	print_asm("jae    0x%x", eip + x + DATA_BYTE + 1);
	if (cpu.CF == 0)	cpu.eip += x;
	return DATA_BYTE + 1;
}
//je
make_helper(concat(je_r_, SUFFIX)) {
	DATA_TYPE t = instr_fetch(eip + 1, DATA_BYTE);
    int x = t;
	if (DATA_BYTE == 1) {
		if ((t >> 7) & 1)	x = t | 0xffffff00;
		//else x = t & 0xff; 
	}
	else if (DATA_BYTE == 2) {
		if ((t >> 15) & 1)	x = t | 0xffff0000;
		//else x = t & 0xffff;
	}
	else x = t;
	print_asm("je     0x%x", eip + x + DATA_BYTE + 1);
	if (cpu.ZF == 1)	cpu.eip += x;
	return DATA_BYTE + 1;
}
//jne
make_helper(concat(jne_r_, SUFFIX)) {
	DATA_TYPE t = instr_fetch(eip + 1, DATA_BYTE);
    int x = t;
	if (DATA_BYTE == 1) {
		if ((t >> 7) & 1)	x = t | 0xffffff00;
		//else x = t & 0xff; 
	}
	else if (DATA_BYTE == 2) {
		if ((t >> 15) & 1)	x = t | 0xffff0000;
		//else x = t & 0xffff;
	}
	else x = t;
	print_asm("jne    0x%x", eip + x + DATA_BYTE + 1);
	if (cpu.ZF == 0)	cpu.eip += x;
	return DATA_BYTE + 1;
}
//jbe
make_helper(concat(jbe_r_, SUFFIX)) {
	DATA_TYPE t = instr_fetch(eip + 1, DATA_BYTE);
    int x = t;
	if (DATA_BYTE == 1) {
		if ((t >> 7) & 1)	x = t | 0xffffff00;
		//else x = t & 0xff; 
	}
	else if (DATA_BYTE == 2) {
		if ((t >> 15) & 1)	x = t | 0xffff0000;
		//else x = t & 0xffff;
	}
	else x = t;
	print_asm("jbe    0x%x", eip + x + DATA_BYTE + 1);
	if (cpu.CF || cpu.ZF)	cpu.eip += x;
	return DATA_BYTE + 1;
}
//ja
make_helper(concat(ja_r_, SUFFIX)) {
	DATA_TYPE t = instr_fetch(eip + 1, DATA_BYTE);
    int x = t;
	if (DATA_BYTE == 1) {
		if ((t >> 7) & 1)	x = t | 0xffffff00;
		//else x = t & 0xff; 
	}
	else if (DATA_BYTE == 2) {
		if ((t >> 15) & 1)	x = t | 0xffff0000;
		//else x = t & 0xffff;
	}
	else x = t;
	print_asm("ja     0x%x", eip + x + DATA_BYTE + 1);
	if ((!cpu.CF) && (!cpu.ZF))	cpu.eip += x;
	return DATA_BYTE + 1;
}
//js
make_helper(concat(js_r_, SUFFIX)) {
	DATA_TYPE t = instr_fetch(eip + 1, DATA_BYTE);
    int x = t;
	if (DATA_BYTE == 1) {
		if ((t >> 7) & 1)	x = t | 0xffffff00;
		//else x = t & 0xff; 
	}
	else if (DATA_BYTE == 2) {
		if ((t >> 15) & 1)	x = t | 0xffff0000;
		//else x = t & 0xffff;
	}
	else x = t;
	print_asm("js     0x%x", eip + x + DATA_BYTE + 1);
	if (cpu.SF == 1)	cpu.eip += x;
	return DATA_BYTE + 1;
}
//jns
make_helper(concat(jns_r_, SUFFIX)) {
	DATA_TYPE t = instr_fetch(eip + 1, DATA_BYTE);
    int x = t;
	if (DATA_BYTE == 1) {
		if ((t >> 7) & 1)	x = t | 0xffffff00;
		//else x = t & 0xff; 
	}
	else if (DATA_BYTE == 2) {
		if ((t >> 15) & 1)	x = t | 0xffff0000;
	//	else x = t & 0xffff;
	}
	else x = t;
	print_asm("jns    0x%x", eip + x + DATA_BYTE + 1);
	if (cpu.SF == 0)	cpu.eip += x;
	return DATA_BYTE + 1;
}
//jp
make_helper(concat(jp_r_, SUFFIX)) {
	DATA_TYPE t = instr_fetch(eip + 1, DATA_BYTE);
    int x = t;
	if (DATA_BYTE == 1) {
		if ((t >> 7) & 1)	x = t | 0xffffff00;
		//else x = t & 0xff; 
	}
	else if (DATA_BYTE == 2) {
		if ((t >> 15) & 1)	x = t | 0xffff0000;
		//else x = t & 0xffff;
	}
	else x = t;
	print_asm("jp     0x%x", eip + x + DATA_BYTE + 1);
	if (cpu.PF == 1)	cpu.eip += x;
	return DATA_BYTE + 1;
}
//jnp
make_helper(concat(jnp_r_, SUFFIX)) {
	DATA_TYPE t = instr_fetch(eip + 1, DATA_BYTE);
    int x = t;
	if (DATA_BYTE == 1) {
		if ((t >> 7) & 1)	x = t | 0xffffff00;
		//else x = t & 0xff; 
	}
	else if (DATA_BYTE == 2) {
		if ((t >> 15) & 1)	x = t | 0xffff0000;
		//else x = t & 0xffff;
	}
	else x = t;
	print_asm("jnp    0x%x", eip + x + DATA_BYTE + 1);
	if (cpu.PF == 0)	cpu.eip += x;
	return DATA_BYTE + 1;
}
//jl
make_helper(concat(jl_r_, SUFFIX)) {
	DATA_TYPE t = instr_fetch(eip + 1, DATA_BYTE);
    int x = t;
	if (DATA_BYTE == 1) {
		if ((t >> 7) & 1)	x = t | 0xffffff00;
		//else x = t & 0xff; 
	}
	else if (DATA_BYTE == 2) {
		if ((t >> 15) & 1)	x = t | 0xffff0000;
		//else x = t & 0xffff;
	}
	else x = t;
	print_asm("jl     0x%x", eip + x + DATA_BYTE + 1);
	if (cpu.SF != cpu.OF)	cpu.eip += x;
	return DATA_BYTE + 1;
}
//jge
make_helper(concat(jge_r_, SUFFIX)) {
	DATA_TYPE t = instr_fetch(eip + 1, DATA_BYTE);
    int x = t;
	if (DATA_BYTE == 1) {
		if ((t >> 7) & 1)	x = t | 0xffffff00;
		//else x = t & 0xff; 
	}
	else if (DATA_BYTE == 2) {
		if ((t >> 15) & 1)	x = t | 0xffff0000;
		//else x = t & 0xffff;
	}
	else x = t;
	print_asm("jge    0x%x", eip + x + DATA_BYTE + 1);
	if (cpu.SF == cpu.OF)	cpu.eip += x;
	return DATA_BYTE + 1;
}
//jle
make_helper(concat(jle_r_, SUFFIX)) {
	DATA_TYPE t = instr_fetch(eip + 1, DATA_BYTE);
    int x = t;
	if (DATA_BYTE == 1) {
		if ((t >> 7) & 1)	x = t | 0xffffff00;
		//else x = t & 0xff; 
	}
	else if (DATA_BYTE == 2) {
		if ((t >> 15) & 1)	x = t | 0xffff0000;
		//else x = t & 0xffff;
	}
	else x = t;
	print_asm("jle    0x%x", eip + x + DATA_BYTE + 1);
	if (cpu.ZF == 1 || (cpu.SF != cpu.OF))	cpu.eip += x;
	return DATA_BYTE + 1;
}
//jg
make_helper(concat(jg_r_, SUFFIX)) {
	DATA_TYPE t = instr_fetch(eip + 1, DATA_BYTE);
    int x = t;
	if (DATA_BYTE == 1) {
		if ((t >> 7) & 1)	x = t | 0xffffff00;
		//else x = t & 0xff; 
	}
	else if (DATA_BYTE == 2) {
		if ((t >> 15) & 1)	x = t | 0xffff0000;
		//else x = t & 0xffff;
	}
	else x = t;
	print_asm("jg     0x%x", eip + x + DATA_BYTE + 1);
	if ((!cpu.ZF) && (cpu.SF == cpu.OF))	cpu.eip += x;
	return DATA_BYTE + 1;
}
//jmp
make_helper(concat(jmp_r_, SUFFIX)) {
	DATA_TYPE t = instr_fetch(eip + 1, DATA_BYTE);
	int x = t;
	if (DATA_BYTE == 1) {
		if ((t >> 7) & 1)	x = t | 0xffffff00;
		//else x = t & 0xff; 
	}
	else if (DATA_BYTE == 2) {
		if ((t >> 15) & 1)	x = t | 0xffff0000;
		//else x = t & 0xffff;
	}
	else x = t;
	cpu.eip += x;
	if (DATA_BYTE == 2)	cpu.eip &= 0xffff;
	print_asm("jmp    0x%x", cpu.eip + DATA_BYTE + 1);
	return DATA_BYTE + 1;
}
make_helper(concat(jmp_rm_, SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	if (m.mod == 3) {
		cpu.eip = REG(m.R_M);
		print_asm("jmp    %%%s", REG_NAME(m.R_M));
		cpu.eip -= 2;
		return 2;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		cpu.eip = MEM_R(addr);
		print_asm("jmp    %s", ModR_M_asm);
		cpu.eip -= len + 1;
		return len + 1;
	}
}
make_helper(concat(ljmp_, SUFFIX)) {
	DATA_TYPE addr = instr_fetch(eip + 1, DATA_BYTE);
	uint16_t t = instr_fetch(eip + DATA_BYTE + 1, 2);
	if (!cpu.CR0.PE || (cpu.CR0.PE && cpu.VM)) {
		reg_s(CS).val = t;
		cpu.eip = addr;
		cpu.eip -= (DATA_BYTE + 3);
	}
	print_asm("ljmp $%#x, $%#x", t, addr);
	return DATA_BYTE + 3;
}
//setcc
make_helper(concat(seto_rm_, SUFFIX)){
	ModR_M m;
	uint8_t t = cpu.OF;
	m.val = instr_fetch(eip + 1, DATA_BYTE);
	if(m.mod == 3){
		REG(m.R_M) = t;
		print_asm("seto   %%%s", REG_NAME(m.R_M));
		return 2;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1,&addr);
		MEM_W(addr, t);
		print_asm("seto   %s", ModR_M_asm);
		return len + 1;
	}
}
make_helper(concat(setno_rm_, SUFFIX)){
	ModR_M m;
	uint8_t t = !cpu.OF;
	m.val = instr_fetch(eip + 1, DATA_BYTE);
	if(m.mod == 3){
		REG(m.R_M) = t;
		print_asm("setno  %%%s", REG_NAME(m.R_M));
		return 2;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1,&addr);
		MEM_W(addr, t);
		print_asm("setno  %s", ModR_M_asm);
		return len + 1;
	}
}
make_helper(concat(setb_rm_, SUFFIX)){
	ModR_M m;
	uint8_t t = cpu.CF;
	m.val = instr_fetch(eip + 1, DATA_BYTE);
	if(m.mod == 3){
		REG(m.R_M) = t;
		print_asm("setb   %%%s", REG_NAME(m.R_M));
		return 2;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1,&addr);
		MEM_W(addr, t);
		print_asm("setb   %s", ModR_M_asm);
		return len + 1;
	}
}
make_helper(concat(setae_rm_, SUFFIX)){
	ModR_M m;
	uint8_t t = !cpu.CF;
	m.val = instr_fetch(eip + 1, DATA_BYTE);
	if(m.mod == 3){
		REG(m.R_M) = t;
		print_asm("setae  %%%s", REG_NAME(m.R_M));
		return 2;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1,&addr);
		MEM_W(addr, t);
		print_asm("setae  %s", ModR_M_asm);
		return len + 1;
	}
}
make_helper(concat(sete_rm_, SUFFIX)){
	ModR_M m;
	uint8_t t = cpu.ZF;
	m.val = instr_fetch(eip + 1, DATA_BYTE);
	if(m.mod == 3){
		REG(m.R_M) = t;
		print_asm("sete   %%%s", REG_NAME(m.R_M));
		return 2;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1,&addr);
		MEM_W(addr, t);
		print_asm("sete   %s", ModR_M_asm);
		return len + 1;
	}
}
make_helper(concat(setne_rm_, SUFFIX)){
	ModR_M m;
	uint8_t t = (!cpu.ZF);
	m.val = instr_fetch(eip + 1, DATA_BYTE);
	if(m.mod == 3){
		REG(m.R_M) = t;
		print_asm("setne  %%%s", REG_NAME(m.R_M));
		return 2;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1,&addr);
		MEM_W(addr, t);
		print_asm("setne  %s", ModR_M_asm);
		return len + 1;
	}
}
make_helper(concat(setbe_rm_, SUFFIX)){
	ModR_M m;
	uint8_t t = (cpu.ZF && cpu.CF);
	m.val = instr_fetch(eip + 1, DATA_BYTE);
	if(m.mod == 3){
		REG(m.R_M) = t;
		print_asm("setbe  %%%s", REG_NAME(m.R_M));
		return 2;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1,&addr);
		MEM_W(addr, t);
		print_asm("setbe  %s", ModR_M_asm);
		return len + 1;
	}
}
make_helper(concat(seta_rm_, SUFFIX)){
	ModR_M m;
	uint8_t t = (!cpu.ZF && !cpu.CF);
	m.val = instr_fetch(eip + 1, DATA_BYTE);
	if(m.mod == 3){
		REG(m.R_M) = t;
		print_asm("seta   %%%s", REG_NAME(m.R_M));
		return 2;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1,&addr);
		MEM_W(addr, t);
		print_asm("seta   %s", ModR_M_asm);
		return len + 1;
	}
}
make_helper(concat(sets_rm_, SUFFIX)){
	ModR_M m;
	uint8_t t = cpu.SF;
	m.val = instr_fetch(eip + 1, DATA_BYTE);
	if(m.mod == 3){
		REG(m.R_M) = t;
		print_asm("sets   %%%s", REG_NAME(m.R_M));
		return 2;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1,&addr);
		MEM_W(addr, t);
		print_asm("sets   %s", ModR_M_asm);
		return len + 1;
	}
}
make_helper(concat(setns_rm_, SUFFIX)){
	ModR_M m;
	uint8_t t = !cpu.SF;
	m.val = instr_fetch(eip + 1, DATA_BYTE);
	if(m.mod == 3){
		REG(m.R_M) = t;
		print_asm("setns  %%%s", REG_NAME(m.R_M));
		return 2;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1,&addr);
		MEM_W(addr, t);
		print_asm("setns  %s", ModR_M_asm);
		return len + 1;
	}
}
make_helper(concat(setp_rm_, SUFFIX)){
	ModR_M m;
	uint8_t t = cpu.PF;
	m.val = instr_fetch(eip + 1, DATA_BYTE);
	if(m.mod == 3){
		REG(m.R_M) = t;
		print_asm("setp   %%%s", REG_NAME(m.R_M));
		return 2;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1,&addr);
		MEM_W(addr, t);
		print_asm("setp   %s", ModR_M_asm);
		return len + 1;
	}
}
make_helper(concat(setnp_rm_, SUFFIX)){
	ModR_M m;
	uint8_t t = !cpu.PF;
	m.val = instr_fetch(eip + 1, DATA_BYTE);
	if(m.mod == 3){
		REG(m.R_M) = t;
		print_asm("setnp  %%%s", REG_NAME(m.R_M));
		return 2;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1,&addr);
		MEM_W(addr, t);
		print_asm("setnp  %s", ModR_M_asm);
		return len + 1;
	}
}
make_helper(concat(setl_rm_, SUFFIX)){
	ModR_M m;
	uint8_t t = (cpu.SF != cpu.OF);
	m.val = instr_fetch(eip + 1, DATA_BYTE);
	if(m.mod == 3){
		REG(m.R_M) = t;
		print_asm("setl   %%%s", REG_NAME(m.R_M));
		return 2;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1,&addr);
		MEM_W(addr, t);
		print_asm("setl   %s", ModR_M_asm);
		return len + 1;
	}
}
make_helper(concat(setge_rm_, SUFFIX)){
	ModR_M m;
	uint8_t t = (cpu.SF == cpu.OF);
	m.val = instr_fetch(eip + 1, DATA_BYTE);
	if(m.mod == 3){
		REG(m.R_M) = t;
		print_asm("setge  %%%s", REG_NAME(m.R_M));
		return 2;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1,&addr);
		MEM_W(addr, t);
		print_asm("setge  %s", ModR_M_asm);
		return len + 1;
	}
}
make_helper(concat(setle_rm_, SUFFIX)){
	ModR_M m;
	uint8_t t = (cpu.ZF && cpu.SF != cpu.OF);
	m.val = instr_fetch(eip + 1, DATA_BYTE);
	if(m.mod == 3){
		REG(m.R_M) = t;
		print_asm("setle  %%%s", REG_NAME(m.R_M));
		return 2;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1,&addr);
		MEM_W(addr, t);
		print_asm("setle  %s", ModR_M_asm);
		return len + 1;
	}
}
make_helper(concat(setg_rm_, SUFFIX)){
	ModR_M m;
	uint8_t t = (!cpu.ZF && cpu.SF == cpu.OF);
	m.val = instr_fetch(eip + 1, DATA_BYTE);
	if(m.mod == 3){
		REG(m.R_M) = t;
		print_asm("setg   %%%s", REG_NAME(m.R_M));
		return 2;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1,&addr);
		MEM_W(addr, t);
		print_asm("setg   %s", ModR_M_asm);
		return len + 1;
	}
}
#include "exec/template-end.h"
