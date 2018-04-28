#include "dvd.h"

uint32_t currID = 0;
uint32_t bootInfo = 0;
uint32_t FirstTimeInBootrom = 0;
uint32_t DVDInitialized = 0;

extern uint32_t __DVDThreadQueue[2];

void DVDInit(void) {
	if (DVDInitialized)
		return;
	OSInitAlarm();
	DVDInitialized = 1;
	__DVDFSInit();
	__DVDClearWaitingQueue();
	__DVDInitWA();
	bootInfo = 0x80000000;
	currID = 0x80000000;
	__OSSetInterruptHandler(0x15, (uint32_t*)__DVDInterruptHandler);
	__OSUnmaskInterrupts(0x400);
	OSInitThreadQueue(__DVDThreadQueue);
	*(uint32_t*)0xCC006000 = 0x2A;
	*(uint32_t*)0xCC006004 = 0;
	if (((*(uint32_t*)(bootInfo + 0x20)) + 0x1AE00000) != 0x7C22) { //0xE5207C22
		OSReport("app booted via JTAG\n");
		OSReport("load fst\n");
		__fstLoad();
	} else if (((*(uint32_t*)(bootInfo + 0x20)) + 0xF2EB0000) != 0xEA5E) { //0xD15EA5E
		OSReport("app booted from bootrom\n");
	} else {
		FirstTimeInBootrom = 1; //BootROM being this bootstrap ??
		OSReport("bootrom\n");
	}
}

/*
stateReadingFST
cbForStateReadingFST
cbForStateError
stateTimeout
stateGettingError
CategorizeError
cbForStateGettingError
cbForUnrecoveredError
cbForUnrecoveredErrorRetry
stateGoToRetry
cbForStateGoToRetry
stateCheckID
stateCheckID3
stateCheckID2
cbForStateCheckID1
cbForStateCheckID2
cbForStateCheckID3
AlarmHandler
stateCoverClosed
stateCoverClosed_CMD
cbForStateCoverClosed
stateMotorStopped
cbForStateMotorStopped
stateReady
stateBusy
cbForStateBusy
issueCommand
DVDReadAbsAsyncPrio
DVDReadAbsAsyncForBS
DVDReadDiskID
DVDPrepareStreamAbsAsync
DVDCancelStream
cbForCancelStreamSync*/
void* DVDInquiryAsync(uint32_t *r3, uint32_t *r4, uint32_t *callback) {
	
}
/*DVDReset
DVDGetCommandBlockStatus
DVDGetDriveStatus
DVDSetAutoInvalidation
DVDCancelAsync
DVDCancel
cbForCancelSync
DVDGetCurrentDiskID
DVDCheckDisk
__DVDPrepareResetAsync
.data
data.0
@13
@14
@15
@16
@293
@331
@835
@936
.bss
bss.0
tmpBuffer
DummyCommandBlock
ResetAlarm
.sdata
autoInvalidation
.sbss
executing
currID
bootInfo
PauseFlag
PausingFlag
AutoFinishing
FatalErrorFlag
CurrCommand
Canceling
CancelCallback
ResumeFromHere
CancelLastError
LastError
NumInternalRetry
ResetRequired
FirstTimeInBootrom
DVDInitialized
LastState*/