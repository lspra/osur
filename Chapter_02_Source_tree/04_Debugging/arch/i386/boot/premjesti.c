#include <types/basic.h>

void just_copy(char *from, char *to, size_t size)
{
	size_t i;
	for (i = 0; i < size; i++)
		to[i] = from[i];
}

void premjesti()
{
	extern char RAM_LOAD_ADDR, LOAD_ADDR_CODE, CODE_SIZE;
	extern char RODATA_ADDR_RAM, RODATA_ADDR, RODATA_SIZE;
	extern char DATA_ADDR_RAM, DATA_ADDR, DATA_SIZE;

	just_copy(&LOAD_ADDR_CODE, &RAM_LOAD_ADDR, (size_t) &CODE_SIZE);
	just_copy(&RODATA_ADDR, &RODATA_ADDR_RAM, (size_t) &RODATA_SIZE);
	just_copy(&DATA_ADDR, &DATA_ADDR_RAM, (size_t) &DATA_SIZE);
}