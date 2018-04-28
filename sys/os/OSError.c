#include "OSError.h"

uint32_t __OSErrorTable[20];

__asm__(
	".global OSSetErrorHandler\n"
	"OSSetErrorHandler:\n"
	"lis        5, __OSErrorTable@ha\n"
	"clrlslwi   3, 3, 16,2\n"
	"addi       0, 5, __OSErrorTable@l\n"
	"add        5, 0, 3\n"
	"lwz        3, 0(5)\n"
	"stw        4, 0(5)\n"
	"blr\n"
);
	
/*
.text
OSSetErrorHandler
__OSUnhandledException
.data
data.0
@10
@11
@12
@30
@31
@33
@34
@35
@36
@37
@38
@39
@40
@41
@42
@43
.bss
__OSErrorTable
.sdata
@32
*/