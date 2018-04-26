/* https://stackoverflow.com/questions/38120764/specifying-section-name-for-code-in-gcc */

ENTRY(__start)
SECTIONS
{
	. = 0x80003100;
	.init : ALIGN(4) {
		./build/sys/os/__start.o
		./build/sys/os/__ppc_eabi_init.o
		./build/sys/Runtime.PPCEABI.H/__mem.o
		/*mem_TRK.o
		__exception.o
		dolphin_trk.o*/
	}
	. = 0x800056C0;
    .rodata     : ALIGN(4) { *(.rodata*); . = ALIGN(4); }
    .data       : ALIGN(4) { *(.data*); . = ALIGN(4); }
    .bss        : ALIGN(8) { __bss_start = .; *(.bss* COMMON); . = ALIGN(8); __bss_end = .; }

    . = ALIGN(4);
}