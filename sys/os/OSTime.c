#include "OSTime.h"

__asm__(
	".global OSGetTime\n"
	"OSGetTime:\n"
	"mftbu     3\n"
	"mftb      4\n"
	"mftbu     5\n"
	"cmpw      3, 5\n"
	"bne       OSGetTime\n"
	"blr\n"
);

__asm__(
	".global OSGetTick\n"
	"OSGetTick:\n"
	"mftb      3\n"
	"blr\n"
);