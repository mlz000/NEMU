#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"
void concat(setflagdiv_, SUFFIX) (DATA_TYPE x) {
	uint64_t t = (uint64_t)REG(R_EAX) | (((uint64_t)(REG(R_EDX)))<<(DATA_BYTE << 3));
	REG(R_EAX) = (DATA_TYPE)(t / x);
	if (DATA_BYTE == 1)	REG(R_AH) = (DATA_TYPE)(t % x);
	else REG(R_EDX) = (DATA_TYPE)(t % x);
}
void concat(setflagidiv_, SUFFIX) (DATA_TYPE_S x) {
	int64_t t = (int64_t)(REG(R_EAX)) | (((int64_t)(DATA_TYPE_S)(REG(R_EDX))) << (DATA_BYTE << 3));
	REG(R_EAX) = (DATA_TYPE_S)(t / x);
	if (DATA_BYTE == 1)	REG(R_AH) = (DATA_TYPE_S)(t % x);
	else REG(R_EDX) = (DATA_TYPE_S)(t % x);
}
void concat(setflagmul_, SUFFIX) (uint64_t x, uint64_t y, int c) {
	uint64_t t = x * y;
	DATA_TYPE ans = t;
	cpu.OF = cpu.CF = (ans != t);
	if (c) {
		if (DATA_BYTE != 1)	REG(R_EDX) = (DATA_TYPE)(t >> ((DATA_BYTE << 3) - 1));
		else REG(R_AH) = (DATA_TYPE)(t >> ((DATA_BYTE << 3) - 1));
	}
}
void concat(setflagimul_, SUFFIX) (int64_t x, int64_t y, int c) {
	int64_t t = x * y;
	DATA_TYPE_S ans = (DATA_TYPE_S)t;
	cpu.CF = cpu.OF = (ans != t);
	if (c) {
		if (DATA_BYTE != 1)	REG(R_EDX) = (DATA_TYPE)(t >> (DATA_BYTE << 3));
		else REG(R_AH) = (DATA_TYPE)(t >> (DATA_BYTE << 3));
	}
}
make_helper(concat(mul_rm2a_, SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	if (m.mod == 3) {
		concat(setflagmul_, SUFFIX) (REG(m.R_M), REG(R_EAX), 1);
		REG(R_EAX) = REG(m.R_M) * REG(R_EAX);
		print_asm("mul" str(SUFFIX) "   %%%s", REG_NAME(m.R_M));
		return 2;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		concat(setflagmul_, SUFFIX) ((MEM_R(addr)), REG(R_EAX), 1);
		REG(R_EAX) = MEM_R(addr) * REG(R_EAX);
		print_asm("mul" str(SUFFIX) "   %s", ModR_M_asm);
		return len + 1;
	}
}
//imul
make_helper(concat(imul_rm2a_, SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	if (m.mod == 3) {
		concat(setflagimul_, SUFFIX) (REG(m.R_M), REG(R_EAX), 1);
		REG(R_EAX) = (DATA_TYPE_S)REG(m.R_M) * (DATA_TYPE_S)REG(R_EAX);
		print_asm("imul   %%%s", REG_NAME(m.R_M));
		return 2;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		concat(setflagmul_, SUFFIX) (MEM_R(addr), REG(R_EAX), 1);
		REG(R_EAX) = (DATA_TYPE_S)MEM_R(addr) * (DATA_TYPE)REG(R_EAX);
		print_asm("imul"   str(SUFFIX) "  %s", ModR_M_asm);
		return len + 1;
	}
}
make_helper(concat(imul_rm2r_, SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	if (m.mod == 3) {
		concat(setflagimul_, SUFFIX)(REG(m.R_M), REG(m.reg), 0);
		REG(m.reg) = (DATA_TYPE_S)REG(m.R_M) * (DATA_TYPE_S)REG(m.reg);
		print_asm("imul   %%%s, %%%s", REG_NAME(m.R_M), REG_NAME(m.reg));
		return 2;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		concat(setflagimul_, SUFFIX)(MEM_R(addr), REG(m.reg), 0);
		REG(m.reg) = (DATA_TYPE_S)MEM_R(addr) * (DATA_TYPE_S)REG(m.reg);
		print_asm("imul   %s, %%%s", ModR_M_asm, REG_NAME(m.reg));
		return len + 1;
	}
}
//imm or r/rm
make_helper(concat(imul_irm2r_, SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	if (m.mod == 3) {
		DATA_TYPE imm = instr_fetch(eip + 2, DATA_BYTE);
		concat(setflagimul_, SUFFIX)(REG(m.R_M), imm, 0);
		REG(m.reg) = (DATA_TYPE_S)REG(m.R_M) * (DATA_TYPE_S)imm;
		if (m.reg == m.R_M)	print_asm("imul   $0x%x, %%%s", imm, REG_NAME(m.reg));
		else print_asm("imul   $0x%x, %%%s, %%%s", imm, REG_NAME(m.R_M), REG_NAME(m.reg));
		return DATA_BYTE + 2;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		DATA_TYPE imm = instr_fetch(eip + len + 1, DATA_BYTE);
		concat(setflagimul_, SUFFIX)(MEM_R(addr), imm, 0);
		REG(m.reg) = (DATA_TYPE_S)MEM_R(addr) * (DATA_TYPE_S)imm;
		print_asm("imul   $0x%x, %s, %%%s", imm, ModR_M_asm, REG_NAME(m.reg));
		return DATA_BYTE + len + 1;
	}
}
// 8 byte imm or r/rm
make_helper(concat(imul_ibrm2r_, SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	if(m.mod == 3){
		int8_t t = instr_fetch(eip + 2, 1);
		DATA_TYPE imm = (DATA_TYPE_S)t;
		concat(setflagimul_, SUFFIX)(REG(m.R_M), imm, 0);
		REG(m.reg) = (DATA_TYPE_S)REG(m.R_M) * (DATA_TYPE_S)imm;
		if(m.reg == m.R_M)	print_asm("imul   $0x%x,%%%s", t, REG_NAME(m.reg));
		else print_asm("imul   $0x%x,%%%s,%%%s", t, REG_NAME(m.R_M), REG_NAME(m.reg));
		return 3;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		int8_t t =instr_fetch(eip + len + 1, 1);
		DATA_TYPE imm = (DATA_TYPE_S)t;
		concat(setflagimul_, SUFFIX)(MEM_R(addr), imm, 0);
		REG(m.reg) = (DATA_TYPE_S)MEM_R(addr) * (DATA_TYPE_S)imm;
		print_asm("imul   $0x%x,%s,%%%s", t, ModR_M_asm, REG_NAME(m.reg));
		return len + 2;
	}
}
//div
make_helper(concat(div_rm2a_, SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	if(m.mod == 3){
		concat(setflagdiv_, SUFFIX)(REG(m.R_M));
		print_asm("div    %%%s",REG_NAME(m.R_M));
		return 2;
	}
	else  {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		concat(setflagdiv_, SUFFIX)(MEM_R(addr));
		print_asm("div" str(SUFFIX) "   %s",ModR_M_asm);
		return len + 1;
	}
}
//idiv
make_helper(concat(idiv_rm2a_, SUFFIX)){
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	if(m.mod == 3){
		concat(setflagidiv_, SUFFIX)(REG(m.R_M));
		print_asm("idiv   %%%s",REG_NAME(m.R_M));
		return 2;
	}
	else  {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		concat(setflagidiv_, SUFFIX)(MEM_R(addr));
		print_asm("idiv" str(SUFFIX) "  %s",ModR_M_asm);
		return len + 1;
	}
} 
#include "exec/template-end.h"
