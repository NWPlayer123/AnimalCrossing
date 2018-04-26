#include "__ppc_eabi_init.h"

__asm__(
	".global __init_hardware\n"
	"__init_hardware:\n"
	"mfmsr     0\n"
	"ori       0, 0, 0x2000\n"
	"mtmsr     0\n"
	"mflr      31\n"
	/*"bl        __OSPSInit\n"
	"bl        __OSCacheInit\n"*/
	"mtlr      31\n"
	"blr\n"
);
__asm__(
	".global __flush_cache\n"
	"__flush_cache:\n"
	"lis       5, 0xFFFF\n"
	"ori       5, 5,0xFFF1\n"
	"and       5, 5, 3\n"
	"subf      3, 5, 3\n"
	"add       4, 4, 3\n"
	"loop:\n"
	"dcbst     0, 5\n"
	"sync\n"
	"icbi      0, 5\n"
	"addic     5, 5, 8\n"
	"addic.    4, 4, -8\n"
	"bge       loop\n"
	"isync\n"
	"blr\n"
);
/*__init_user
__init_cpp
_ExitProcess*/