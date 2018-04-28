#include "OSThread.h"

uint32_t Reschedule = 0;

/*
.text
__OSThreadInit*/

__asm__(
	".global OSInitThreadQueue\n"
	"OSInitThreadQueue:\n"
	"li         0, 0\n"
	"stw        0, 4(3)\n"
	"stw        0, 0(3)\n"
	"blr\n"
);

/*OSGetCurrentThread
OSIsThreadTerminated
OSDisableScheduler
OSEnableScheduler
UnsetRun
__OSGetEffectivePriority
SetEffectivePriority
__OSPromoteThread
SelectThread
__OSReschedule
OSYieldThread
OSCreateThread
OSExitThread
OSCancelThread
OSJoinThread
OSDetachThread
OSResumeThread
OSSuspendThread
OSSleepThread
OSWakeupThread
OSSetThreadPriority
OSGetThreadPriority
CheckThreadQueue
OSCheckActiveThreads
.data
data.0
.bss
bss.0
RunQueue
IdleThread
DefaultThread
IdleContext
.sdata
@796
.sbss
RunQueueBits
RunQueueHint
Reschedule
*/

uint32_t* OSGetCurrentThread(void) { 
	return *(uint32_t**)0x800000E4; //DefaultThread
}

uint32_t OSDisableScheduler(void) {
	uint32_t ret = OSDisableInterrupts();
	Reschedule += 1;
	OSRestoreInterrupts(ret);
	return Reschedule - 1; //too much to store, compiler can optimize
}