#include "OSInterrupt.h"

uint32_t* InterruptHandlerTable = 0;

__asm__(
	".global OSDisableInterrupts\n"
	"OSDisableInterrupts:\n"
	"mfmsr     3\n"
	"rlwinm    4, 3, 0,17,15\n"
	"mtmsr     4\n"
	"extrwi    3, 3, 1,16\n"
	"blr\n"
);

__asm__(
	".global OSEnableInterrupts\n"
	"OSEnableInterrupts:\n"
	"mfmsr     3\n"
	"ori       4, 3, 0x8000\n"
	"mtmsr     4\n"
	"extrwi    3, 3, 1,16\n"
	"blr\n"
);


__asm__(
	".global OSRestoreInterrupts\n"
	"OSRestoreInterrupts:\n"
	"cmpwi     3, 0\n"
	"mfmsr     4\n"
	"beq       jump1\n"
	"ori       5, 4, 0x8000\n"
	"b         jump2\n"
	"jump1:\n"
	"rlwinm    5, 4, 0,17,15\n"
	"jump2:\n"
	"mtmsr     5\n"
	"extrwi    3, 4, 1,16\n"
	"blr\n"
);

void __OSSetInterruptHandler(uint32_t slot, uint32_t *handler) {
	*(uint32_t*)(*(uint32_t*)InterruptHandlerTable + (slot << 2)) = (uint32_t)handler;
}

void __OSUnmaskInterrupts(uint32_t mask) {
	uint32_t ret = OSDisableInterrupts();
	uint32_t var1 = (*(uint32_t*)0x800000C4 | *(uint32_t*)0x800000C8);
	uint32_t var2 = ((*(uint32_t*)0x800000C4 & ~mask) | *(uint32_t*)0x800000C8); //andc, or
	while (var1 != 0)
		var1 = SetInterruptMask(var1, var2);
	OSRestoreInterrupts(ret);
}

uint32_t SetInterruptMask(uint32_t var1, uint32_t var2) {
	
}