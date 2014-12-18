#define TAG_WIDTH (27-BLOCK_WIDTH-SET_WIDTH)
#define BLOCK_SIZE (1 << BLOCK_WIDTH)
#define SET_SIZE (1 << SET_WIDTH)
#define DATA_SIZE 4
#define DATA_MASK (DATA_SIZE - 1)
uint32_t dram_read(hwaddr_t addr, size_t len);
void dram_write(hwaddr_t addr, size_t len, uint32_t data);
typedef union {
	struct {
		uint32_t offset : BLOCK_WIDTH;
		uint32_t set : SET_WIDTH;
		uint32_t tag : TAG_WIDTH;
	};
	uint32_t addr;
}L2cache_addr;

typedef struct {
	uint8_t block[BLOCK_SIZE];
	int32_t tag;
	bool val;
	bool dir;
}Cache[SET_SIZE][NR_SIZE];
Cache ca;
void init_L2cache() {
	int i, j;
	for (i = 0; i < SET_SIZE; ++i)
		for (j = 0; j < NR_SIZE; ++j)
			ca[i][j].val = 0;
}

void L2cache_replace(uint32_t i, int j, uint32_t tag) {
	int k;
	L2cache_addr t;
	if (ca[i][j].val && ca[i][j].dir) {
		t.addr = 0;
		t.tag = ca[i][j].tag;
		t.set = i;
	 	for (k = 0; k < BLOCK_SIZE; ++k) {
			dram_write(t.addr + k, 1, ca[i][j].block[k]);
		}
	}
	t.addr = 0;
	t.tag = tag;
	t.set = i;
	for (k = 0; k < BLOCK_SIZE; ++k)	ca[i][j].block[k] = dram_read(t.addr + k, 1);
	ca[i][j].tag = tag;
	ca[i][j].val = 1;
	ca[i][j].dir = 0;
}
//like ddr3_read
void L2cache_read2(hwaddr_t addr, void* data) {
	test(addr < HW_MEM_SIZE, "addr = %x\n", addr);
	L2cache_addr t;
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
		L2cache_replace(i, j, tag);
	}
	memcpy(data, ca[i][j].block + offset, DATA_SIZE);
}
//like ddr3_write
void L2cache_write2(hwaddr_t addr, void* data, uint8_t* mask) {
	test(addr < HW_MEM_SIZE, "addr = %x\n", addr);
	L2cache_addr t;
	t.addr = addr & ~DATA_MASK;
	uint32_t offset = t.offset;
	uint32_t i = t.set;
	uint32_t tag = t.tag;
	int j;
	for (j = 0; j < NR_SIZE; ++j) {
		if ((!ca[i][j].val) || (ca[i][j].val && (ca[i][j].tag == tag)))	break;
	}
	if ((j == NR_SIZE) || (!ca[i][j].val)) {
		if (j == NR_SIZE)	j = rand() % NR_SIZE;
		L2cache_replace(i, j, tag);
		memcpy_with_mask(ca[i][j].block + offset, data, DATA_SIZE, mask);
	}
	if ((j < NR_SIZE) && (ca[i][j].val))	memcpy_with_mask(ca[i][j].block + offset, data, DATA_SIZE, mask);
	ca[i][j].dir = 1;
}
//like dram_read
uint32_t L2cache_read(hwaddr_t addr, size_t len) {
	assert((len == 1) || (len == 2) || (len == 4));
	uint32_t offset = addr & DATA_MASK;
	uint8_t temp[2 * DATA_SIZE];
	L2cache_read2(addr, temp);
	if ((addr ^ (addr + len - 1)) & (~DATA_MASK))	L2cache_read2(addr + DATA_SIZE, temp + DATA_SIZE);
	return *(uint32_t*)(temp + offset) & (~0u >> ((4 - len) << 3));
}
//like dram_write
void L2cache_write(hwaddr_t addr, size_t len, uint32_t data) {
	assert((len == 1) || (len == 2) || (len == 4));
	uint32_t offset = addr & DATA_MASK;
	uint8_t temp[2 * DATA_SIZE];
	uint8_t mask[2 * DATA_SIZE];
	memset(mask, 0, 2 * DATA_SIZE);
	*(uint32_t*)(temp + offset) = data;
	memset(mask + offset, 1, len);
	L2cache_write2(addr, temp, mask);
	if ((addr ^ (addr + len - 1)) & (~DATA_MASK))	L2cache_write2(addr + DATA_SIZE, temp + DATA_SIZE, mask + DATA_SIZE);
	
}
/*
#undef TAG_WIDTH
#undef BLOCK_SIZE
#undef SET_SIZE 
#undef DATA_SIZE
#undef DATA_MASK 
*/
