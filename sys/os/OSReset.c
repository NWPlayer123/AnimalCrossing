#include "OSReset.h"

/*
.text
OSRegisterResetFunction
Reset
__OSDoHotReset
OSResetSystem
OSGetResetCode
.sbss
ResetFunctionQueue
*/

void OSResetSystem(uint32_t r3, uint32_t r4, uint32_t r5) {
	OSDisableScheduler();
	__OSStopAudioSystem();
	if (r3 == 2) {
		__PADDisableRecalibration(1);
	}
}

int OSGetResetCode(void) {
	if (*(uint8_t*)0x800030E2 != 0)
		return 0x80000000;
	else
		return (*(uint32_t*)0xCC003024 & 0x1FFFFFFF) >> 3;
}