#include "common.h"
#include "memory.h"
#include <string.h>

#include <elf.h>

#ifdef HAS_DEVICE
#define ELF_OFFSET_IN_DISK 0
#endif

#define STACK_SIZE (1 << 20)
uint32_t mm_malloc(uint32_t va, int len);
void ide_read(uint8_t *, uint32_t, uint32_t);
void create_video_mapping();
uint32_t get_ucr3();

uint32_t loader() {
		Elf32_Ehdr *elf;
			Elf32_Phdr *ph = NULL;
				Elf32_Phdr *eph;
					uint32_t *i;
						uint32_t j;

#ifdef HAS_DEVICE
							uint8_t buf[4096];
								ide_read(buf, ELF_OFFSET_IN_DISK, 4096);
									elf = (void*)buf;
#else
										/* The ELF file is located at memory address 0 */
										elf = (void *)0x0;
#endif

											/* Load each program segment */
											//nemu_assert(0);
											ph = (void*)elf + elf->e_phoff;
												eph = ph + elf->e_phnum;
													for(;ph<eph;ph++){
															//for(; true; ) {
																/* Scan the program header table, load each segment into memory */
																if(ph->p_type == PT_LOAD) {
																				//uint32_t *viraddr = (void*)ph->p_vaddr;
																				uint32_t *viraddr = (void*)mm_malloc(ph->p_vaddr,ph->p_memsz);
																							if(ph->p_filesz)
																												for(j=0;j<=(ph->p_filesz-1)/4;j++){
																																		viraddr[j] = ((uint32_t*)ph->p_offset)[j];
																																						}
																										/* TODO: read the content of the segment from the ELF file 
																										   			 * to the memory region [VirtAddr, VirtAddr + FileSiz)
																													 			 */
																										for(i=(void*)viraddr + ph->p_filesz,j=0;j<ph->p_memsz-ph->p_filesz;j++)i[j]=0; 

																													/* TODO: zero the memory region 
																													   			 * [VirtAddr + FileSiz, VirtAddr + MemSiz)
																																 			 */

																													/* Record the prgram break for future use. */
																													extern uint32_t brk;
																																uint32_t new_brk = ph->p_vaddr + ph->p_memsz - 1;
																																			if(brk < new_brk) { brk = new_brk; }
																																					}
																	}

														volatile uint32_t entry = elf->e_entry;

#ifdef IA32_PAGE
															mm_malloc(KOFFSET - STACK_SIZE, STACK_SIZE);

#ifdef HAS_DEVICE
																create_video_mapping();
#endif

																	write_cr3(get_ucr3());
#endif

																		return entry;
													}

