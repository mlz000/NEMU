#include "nemu.h"
#include "stdlib.h"
#define SIZE 64
typedef union {
	struct {
		uint32_t present : 1;
		uint32_t read_write : 1;
		uint32_t user_supervisor : 1;
		uint32_t PWT : 1;//page_write_through
		uint32_t PCD : 1;//page_cache_disable 
		uint32_t accessed : 1;
		uint32_t pad0 : 6;
		uint32_t page_frame : 20;
	};
	uint32_t val;
}PDE;
typedef union {
	struct {
		uint32_t present : 1;
		uint32_t read_write : 1;
		uint32_t user_supervisor : 1;
		uint32_t PWT : 1;//page_write_through
		uint32_t PCD : 1;//page_cache_disable 
		uint32_t accessed : 1;
		uint32_t dirty : 1;
		uint32_t pad0 : 1;
		uint32_t global : 1;
		uint32_t pad1 : 3;
		uint32_t page_frame : 20;
	};
	uint32_t val;
}PTE;
typedef union {
	struct {
		uint32_t offset : 12;
		uint32_t page : 10;
		uint32_t dir : 10;
	};
	struct {
		uint32_t : 12;
		uint32_t tag : 20;
	};
	uint32_t val;
}ln_addr;
typedef struct {
	PTE pte;
	uint32_t tag;
	bool val;
}TLB[SIZE];
TLB tlb;

void init_tlb() {
	int i;
	for (i = 0; i < SIZE; ++i)	tlb[i].val = 0; 
}
uint32_t hwaddr_read(hwaddr_t, size_t);
hwaddr_t page_translate(lnaddr_t addr) {
	if ((!cpu.CR0.PE) || (!cpu.CR0.PG))	return addr;
	ln_addr laddr;
	laddr.val = addr;
	int i;
	for (i = 0; i < SIZE; ++i)	{
		if ((!tlb[i].val) || (tlb[i].val && (tlb[i].tag == laddr.tag)))	break;
	}
	if (i == SIZE || (!tlb[i].val)) {
		//if (i == SIZE)	i = rand() % SIZE;
		hwaddr_t pdeaddr, pteaddr;
		PDE pde;
		PTE pte;
		if (i == SIZE)	i = rand() % SIZE;
		pdeaddr = (cpu.CR3.PDB << 12) + laddr.dir * sizeof(PDE);
		pde.val = hwaddr_read(pdeaddr, 4);
		pteaddr = (pde.page_frame << 12) + laddr.page * sizeof(PTE);
		pte.val = hwaddr_read(pteaddr, 4);
		tlb[i].tag = laddr.tag;
		tlb[i].val = 1;
		tlb[i].pte = pte;
	}
	PTE pte = tlb[i].pte;
	return (pte.page_frame << 12) + laddr.offset;
}
