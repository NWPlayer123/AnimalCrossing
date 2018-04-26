#include "OSReset.h"

int OSGetResetCode(void) {
	if (*(uint8_t*)0x800030E2 != 0)
		return 0x80000000;
	else
		return (*(uint32_t*)0xCC003024 & 0x1FFFFFFF) >> 3;
}