#ifndef __CPU_REG_H__
#define __CPU_REG_H__

#include "common.h"

/* TODO: Re-organize the 'CPU_state' structure to match
 * the GPR encoding scheme in i386 instruction format.
 * For example, if we access reg_w(R_BX) we will get the 'bx' register;
 * if we access reg_b(R_CH), we will get the 'ch' register.
 * Hint: Use 'union'.
 * For more details about the GPR encoding scheme, see i386 manual.
 */

typedef struct{
	union {
		union{
			uint32_t _32;
			uint16_t _16;
			uint8_t _8[2];
		} gpr[8];

	/* Do NOT change the order of the GPRs' definitions. 
	 * They match the register encoding scheme used in i386 instruction format.
	 * See i386 manual for more details.
	 */
		struct{
			uint32_t eax, ecx, edx, ebx, esp, ebp, esi, edi;
		};
	};
	swaddr_t eip;
	struct {
		uint32_t CF : 1;
		uint32_t a : 1;
		uint32_t PF : 1;
		uint32_t b : 1;
		uint32_t AF : 1;
		uint32_t c : 1;
		uint32_t ZF : 1;
		uint32_t SF : 1;
		uint32_t TF : 1;
		uint32_t IF : 1;
		uint32_t DF : 1;
		uint32_t OF : 1;
	};
	struct {
		uint16_t lim;
		uint32_t base;
	}gdt;
	union {//copy from kerel
		struct {
			uint32_t PE : 1;
			uint32_t MC : 1;
			uint32_t EM : 1;
			uint32_t TS : 1;
			uint32_t ET : 1;
			uint32_t NE : 1;
			uint32_t pad0: 10;
			uint32_t WP : 1;
			uint32_t pad1: 1;
		    uint32_t AM : 1;
			uint32_t pad2: 10;
			uint32_t NW : 1;
			uint32_t CD : 1;
			uint32_t PG : 1;
		};
		uint32_t val;
	}CR0;
	union {
		struct {
			uint32_t pad0                : 3;
			uint32_t PWT  : 1;
			uint32_t PCW  : 1;
			uint32_t pad1                : 7;
			uint32_t PDB : 20;
		};
		uint32_t val;
	} CR3;
	union {
		struct {
			uint8_t RPL : 2;
			uint8_t TI : 1;
			uint16_t INDEX : 13;
		};
		uint16_t val;
	}Selector[6];
} CPU_state;

extern CPU_state cpu;

enum { R_EAX, R_ECX, R_EDX, R_EBX, R_ESP, R_EBP, R_ESI, R_EDI };
enum { R_AX, R_CX, R_DX, R_BX, R_SP, R_BP, R_SI, R_DI };
enum { R_AL, R_CL, R_DL, R_BL, R_AH, R_CH, R_DH, R_BH };
enum {ES, CS, SS, DS, FS, GS};
#define reg_s(index) (cpu.Selector[index])
#define reg_l(index) (cpu.gpr[index]._32)
#define reg_w(index) (cpu.gpr[index]._16)
#define reg_b(index) (cpu.gpr[index & 0x3]._8[index >> 2])

extern const char* regsl[];
extern const char* regsw[];
extern const char* regsb[];
extern const char* regss[];
#endif
