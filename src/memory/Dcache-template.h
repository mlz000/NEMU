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
}Dcache_addr;
void Icache_write2(hwaddr_t addr, void* data, uint8_t* mask);
void L2cache_write(hwaddr_t addr, size_t len, uint32_t data);
void L2cache_write2(hwaddr_t addr, void* data, uint8_t* mask);
uint32_t L2cache_read(hwaddr_t addr, size_t len);
typedef struct {
	uint8_t block[BLOCK_SIZE];
	int32_t tag;
	bool val;
}Cache[SET_SIZE][NR_SIZE];
Cache ca;
void init_Dcache() {
	int i, j;
	for (i = 0; i < SET_SIZE; ++i)
		for (j = 0; j < NR_SIZE; ++j)
			ca[i][j].val = 0;
}

void Dcache_replace(uint32_t i, int j, uint32_t tag) {
	int k;
	Dcache_addr t;
	t.addr = 0;
	t.tag = tag;
	t.set = i;
	for (k = 0; k < BLOCK_SIZE; ++k)	ca[i][j].block[k] = L2cache_read(t.addr + k, 1);
	ca[i][j].tag = tag;
	ca[i][j].val = 1;
}
//like ddr3_read
void Dcache_read2(hwaddr_t addr, void* data) {
	test(addr < HW_MEM_SIZE, "addr = %x\n", addr);
	Dcache_addr t;
	t.addr = addr & ~ DATA_MASK;
	uint32_t i = t.set;
	uint32_t offset = t.offset;
	uint32_t tag = t.tag;
	int j;
	for (j = 0; j < NR_SIZE; ++j) {
		if ((!ca[i][j].val) || (ca[i][j].val && (ca[i][j].tag == tag)))	break;
	}
	if ((j == NR_SIZE) || (!ca[i][j].val)) {
		if (j == NR_SIZE)	j = rand() % NR_SIZE; //random replace
		Dcache_replace(i, j, tag);
	}
	memcpy(data, ca[i][j].block + offset, DATA_SIZE);
}
//like ddr3_write
void Dcache_write2(hwaddr_t addr, void* data, uint8_t* mask) {
	test(addr < HW_MEM_SIZE, "addr = %x\n", addr);
	Dcache_addr t;
	t.addr = addr & ~DATA_MASK;
	uint32_t i = t.set;
	uint32_t offset = t.offset;
	uint32_t tag = t.tag;
	int j;
	for (j = 0; j < NR_SIZE; ++j) {
		if ((!ca[i][j].val) || (ca[i][j].val && (ca[i][j].tag == tag)))	break;
	}
	if ((j < NR_SIZE) && (ca[i][j].val))	memcpy_with_mask(ca[i][j].block + offset, data, DATA_SIZE, mask);
}
//like dram_read
uint32_t Dcache_read(hwaddr_t addr, size_t len) {
	assert((len == 1) || (len == 2) || (len == 4));
	uint32_t offset = addr & DATA_MASK;
	uint8_t temp[2 * DATA_SIZE];
	Dcache_read2(addr, temp);
	if ((addr ^ (addr + len - 1)) & (~DATA_MASK))	Dcache_read2(addr + DATA_SIZE, temp + DATA_SIZE);
	return *(uint32_t*)(temp + offset) & (~0u >> ((4 - len) << 3));
}
//like dram_write
void Dcache_write(hwaddr_t addr, size_t len, uint32_t data) {
	assert((len == 1) || (len == 2) || (len == 4));
	uint32_t offset = addr & DATA_MASK;
	uint8_t temp[2 * DATA_SIZE];
	uint8_t mask[2 * DATA_SIZE];
	memset(mask, 0, 2 * DATA_SIZE);
	*(uint32_t*)(temp + offset) = data;
	memset(mask + offset, 1, len);
	Dcache_write2(addr, temp, mask);
	if ((addr ^ (addr + len - 1)) & (~DATA_MASK))	Dcache_write2(addr + DATA_SIZE, temp + DATA_SIZE, mask + DATA_SIZE);
	Icache_write2(addr, temp, mask);
	if ((addr ^ (addr + len - 1)) & (~DATA_MASK))	Icache_write2(addr + DATA_SIZE, temp + DATA_SIZE, mask + DATA_SIZE);
	L2cache_write(addr, len, data);
}
/*
#undef TAG_WIDTH
#undef BLOCK_SIZE
#undef SET_SIZE 
#undef DATA_SIZE
#undef DATA_MASK 
 */

