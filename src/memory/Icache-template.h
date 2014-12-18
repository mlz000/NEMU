#define TAG_WIDTH (27-BLOCK_WIDTH-SET_WIDTH)
#define BLOCK_SIZE (1 << BLOCK_WIDTH)
#define SET_SIZE (1 << SET_WIDTH)
#define DATA_SIZE 4
#define DATA_MASK (DATA_SIZE - 1)
typedef union {
	struct {
		uint32_t offset : BLOCK_WIDTH;
		uint32_t set : SET_WIDTH;
		uint32_t tag : TAG_WIDTH;
	};
	uint32_t addr;
}Icache_addr;
uint32_t L2cache_read(hwaddr_t addr, size_t len);
typedef struct {
	uint8_t block[BLOCK_SIZE];
	int32_t tag;
	bool val;
}Cache[SET_SIZE][NR_SIZE];
Cache ca;
void init_Icache() {
	int i, j;
	for (i = 0; i < SET_SIZE; ++i)
		for (j = 0; j < NR_SIZE; ++j)
			ca[i][j].val = 0;
}

void Icache_replace(uint32_t i, int j, uint32_t tag) {
	int k;
	Icache_addr t;
	t.addr = 0;
	t.tag = tag;
	t.set = i;
	for (k = 0; k < BLOCK_SIZE; ++k)	ca[i][j].block[k] = L2cache_read(t.addr + k, 1);
	ca[i][j].tag = tag;
	ca[i][j].val = 1;
}
//like ddr3_read
void Icache_read2(hwaddr_t addr, void* data) {
	test(addr < HW_MEM_SIZE, "addr = %x\n", addr);
	Icache_addr t;
	t.addr = addr & ~ DATA_MASK;
	uint32_t offset = t.offset;
	uint32_t i = t.set;
	uint32_t tag = t.tag;
	int j;
	for (j = 0; j < NR_SIZE; ++j) {
		if ((!ca[i][j].val) || (ca[i][j].val && (ca[i][j].tag == tag)))	break;
	}
	if ((j == NR_SIZE) || (!ca[i][j].val)) {
		if (j == NR_SIZE)	j = rand() % NR_SIZE; //random replace
		Icache_replace(i, j, tag);
	}
	memcpy(data, ca[i][j].block + offset, DATA_SIZE);
}
//like ddr3_write
void Icache_write2(hwaddr_t addr, void* data, uint8_t* mask) {
	test(addr < HW_MEM_SIZE, "addr = %x\n", addr);
	Icache_addr t;
	t.addr = addr & ~DATA_MASK;
	uint32_t offset = t.offset;
	uint32_t i = t.set;
	uint32_t tag = t.tag;
	int j;
	for (j = 0; j < NR_SIZE; ++j) {
		if ((!ca[i][j].val) || (ca[i][j].val && (ca[i][j].tag == tag)))	break;
	}
	if ((j < NR_SIZE) && (ca[i][j].val))	memcpy_with_mask(ca[i][j].block + offset, data, DATA_SIZE, mask);
}
//like dram_read
uint32_t Icache_read(hwaddr_t addr, size_t len) {
	assert((len == 1) || (len == 2) || (len == 4));
	uint32_t offset = addr & DATA_MASK;
	uint8_t temp[2 * DATA_SIZE];
	Icache_read2(addr, temp);
	if ((addr ^ (addr + len - 1)) & (~DATA_MASK))	Icache_read2(addr + DATA_SIZE, temp + DATA_SIZE);
	return *(uint32_t*)(temp + offset) & (~0u >> ((4 - len) << 3));
}
/*
#undef TAG_WIDTH
#undef BLOCK_SIZE
#undef SET_SIZE 
#undef DATA_SIZE
#undef DATA_MASK 
 */

