/*! linker script for memory layout */

/* Its parsed as C before used in linking! */

ENTRY(arch_startup)

RAM_LOAD_ADDR = 0x200000;

SECTIONS {
	/DISCARD/ : {
		*(.eh_frame)
		*(.note.gnu.property)
	}
	.boot_code LOAD_ADDR : AT (LOAD_ADDR) {
		*?/boot/startup.asm.o (.text*)
		*?/boot/premjesti.o (.text*)
	}
	BOOT_DATA = LOAD_ADDR + SIZEOF(.boot_code);
	.boot_data BOOT_DATA : {
		*?/boot/startup.asm.o (.rodata* .data* .bss*)
		*?/boot/premjesti.o (.rodata* .data* .bss*)
	}
	LOAD_ADDR_CODE = BOOT_DATA + SIZEOF(.boot_data);
	.code RAM_LOAD_ADDR : AT (LOAD_ADDR_CODE)
	{
		/* instructions */
		kernel_code_addr = .;
		*( .text* )
	}
	CODE_SIZE = SIZEOF(.code);
	RODATA_ADDR = LOAD_ADDR_CODE + CODE_SIZE;
	RODATA_ADDR_RAM = RAM_LOAD_ADDR + CODE_SIZE;
	.data RODATA_ADDR_RAM : AT(RODATA_ADDR)
	{

		/* read only data (constants), initialized global variables */
		* ( .rodata*)
		* ( .data*)
	}
	RODATA_SIZE = SIZEOF(.data);
	DATA_ADDR = RODATA_ADDR + RODATA_SIZE;
	DATA_ADDR_RAM = RODATA_ADDR_RAM + RODATA_SIZE;
	.bss DATA_ADDR_RAM : AT(DATA_ADDR)
	{
		*(.bss* COMMON* )
	}
	DATA_SIZE = SIZEOF(.bss);
	SIZE_STACK = STACK_SIZE;
	STACK_ADDR_RAM = 0x800000 - STACK_SIZE;
	STACK_ADDR = DATA_ADDR + DATA_SIZE;
/*	.stack_segment STACK_ADDR_RAM : AT (STACK_ADDR_RAM)
	{
		* ( .stack_section* )
	} */
	system_stack = STACK_ADDR_RAM;

	/*
	 * what with other sections generated with gcc (various versions)?
	 * if optimizing for size discard them with: /DISCARD/ : { *(*) }
	 * if debugging with qemu/gdb they must be included
	 * - they can be included implicitly, without declaring them here
	 * - but they will be put behind "kernel_end_addr" so its best to use
	 *   multiboot loader (QEMU is that)
	 */

#ifndef DEBUG
	/DISCARD/ : { *(*) }
#endif
}
