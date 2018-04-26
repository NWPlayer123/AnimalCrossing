#include "boot.h"

uint32_t fakemain_check = 0;
uint64_t InitialStartTime = 0;

int main1(void) { //TODO: r3 r4 this
	ReconfigBATs();
	if (fakemain_check != 0)
		return -1;
	fakemain_check = 1;
	OSReport("NDEBUG defined.\x1B[m\n");
	OSReport("_DEBUG not defined.\x1B[m\n");
	OSReport("DEBUG=%d\x1B[m\n", 0);
	InitialStartTime = osGetTime();
	OSInit();
	OSInitAlarm();
	OSGetCurrentThread();
}