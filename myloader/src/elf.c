#include <elf.h>
#include "trap.h"
#include "ui/breakpoint.h"
void loader() {
	/* The ELF file is located at memory address 0 */
	Elf32_Ehdr *elf = (void *)0;
	Elf32_Phdr *ph, *eph;
	uint32_t *a, j;
	ph = (void*)elf + elf -> e_phoff;
	eph = ph + elf -> e_phnum;
	for (; ph < eph; ++ph) {
		/* Scan the program header table, load each segment into memory */
		if(ph -> p_type == PT_LOAD) {
			uint32_t *addr = (void*)ph -> p_vaddr;
			if (ph -> p_filesz) {
				for (j = 0; j <= (ph -> p_filesz - 1) / 4; ++j) {
					addr[j] = ((uint32_t*)ph -> p_offset)[j];
				}
			}
			/* TODO: read the content of the segment from the ELF file 
			 * to the memory region [VirtAddr, VirtAddr + FileSiz)
			 */
			/* TODO: zero the memory region 
			 * [VirtAddr + FileSiz, VirtAddr + MemSiz)
			 */
			for (a = (void*)addr + ph -> p_filesz, j = 0; j < ph -> p_memsz-ph -> p_filesz; ++j)	a[j] = 0;
		}
	}

	/* Here we go! */
	((void(*)(void)) elf -> e_entry) ();

	/* When returning from the program, it is executed successfully */
	HIT_GOOD_TRAP;
}
