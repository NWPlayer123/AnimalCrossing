#include "db.h"

uint32_t __DBInterface = 0;
uint32_t DBVerbose = 0;

void DBInit(void) {
	__DBInterface = 0x80000040;
	*(uint32_t*)0x80000048 = (uint32_t)__DBExceptionDestination + 0x80000000;
	DBVerbose = 1; //                               physical addr ^^^^
}

void __DBExceptionDestinationAux(void) {
	OSReport("DBExceptionDestination\n");
	OSDumpContext((uint32_t*)0x800000C0);
	PPCHalt(); //we made an oopsie
}

__asm__(
	".global __DBExceptionDestination\n"
	"__DBExceptionDestination:\n"
	"mfmsr      3\n"
	"ori        3, 3, 0x30\n"
	"mtmsr      3\n"
	"b          __DBExceptionDestinationAux\n"
);


uint32_t __DBIsExceptionMarked(uint32_t r3) {
	return *(uint32_t*)(__DBInterface + 4) & (1 << (uint8_t)r3);
}

__asm__(
	".global DBPrintf\n"
	"DBPrintf:\n"
	"stwu       1, -0x70(1)\n"
	"bne        cr1, label1\n"
	"stfd       1, 0x28(1)\n"
	"stfd       2, 0x30(1)\n"
	"stfd       3, 0x38(1)\n"
	"stfd       4, 0x40(1)\n"
	"stfd       5, 0x48(1)\n"
	"stfd       6, 0x50(1)\n"
	"stfd       7, 0x58(1)\n"
	"stfd       8, 0x60(1)\n"
	"label1:\n"
	"stw        3, 8(1)\n"
	"stw        4, 0xC(1)\n"
	"stw        5, 0x10(1)\n"
	"stw        6, 0x14(1)\n"
	"stw        7, 0x18(1)\n"
	"stw        8, 0x1C(1)\n"
	"stw        9, 0x20(1)\n"
	"stw        10, 0x24(1)\n"
	"addi       1, 1, 0x70\n"
	"blr\n"
);