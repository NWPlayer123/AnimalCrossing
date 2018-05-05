#include "os.h"

void* __OSExceptionLocations[15] = {
	(void*)0x80000100,
	(void*)0x80000200,
	(void*)0x80000300,
	(void*)0x80000400,
	(void*)0x80000500,
	(void*)0x80000600,
	(void*)0x80000700,
	(void*)0x80000800,
	(void*)0x80000900,
	(void*)0x80000C00,
	(void*)0x80000F00,
	(void*)0x80001300,
	(void*)0x80001400,
	(void*)0x80001700};
uint32_t DriveInfo[2];
uint32_t DriveBlock[12];
uint32_t* BootInfo = 0;
uint32_t BI2DebugFlag = 0;
uint32_t BI2DebugFlagHolder = 0;
uint32_t __OSIsGcam = 0;
uint32_t AreWeInitialized = 0;
uint32_t* OSExceptionTable = 0;
uint32_t __OSSavedRegionEnd = 0;
uint32_t __OSSavedRegionStart = 0;
uint32_t __OSInIPL = 0;
uint64_t __OSStartTime = 0;

extern uint32_t __DVDLongFileNameFlag;
extern uint32_t __PADSpec;


//OSGetConsoleType

void ClearArena(void) {
	
}

void InquiryCallback(uint32_t r3, uint32_t r4) {
	
}

/*OSExceptionInit
__OSDBIntegrator
SDBINTSTART
__OSDBJump
SDBINTEND
SDBJUMPSTART
SDBJUMPEND
__OSSetExceptionHandler
__OSGetExceptionHandler
OSExceptionVector
SEVStart
BVECTOR
SEVSetNumber
SEVEnd
OSDefaultExceptionHandler
__OSPSInit
__OSGetDIConfig
.data
data.0
@84
@85
@86
@87
@88
@89
@90
@91
@92
@93
@94
@95
@96
__OSExceptionLocations
@130
@131
@132
@133
.bss
bss.0
DriveInfo
DriveBlock
.sbss
BootInfo
BI2DebugFlag
BI2DebugFlagHolder
__OSIsGcam
AreWeInitialized
OSExceptionTable
__OSSavedRegionEnd
__OSSavedRegionStart
__OSInIPL
__OSStartTime
*/

void OSInit(void) {
	if (AreWeInitialized)
		return;
	AreWeInitialized = 1; //don't initialize again
	//__OSStartTime = __OSGetSystemTime();
	OSDisableInterrupts();
	PPCDisableSpeculation();
	PPCSetFpNonIEEEMode();
	BI2DebugFlag = 0;
	BootInfo = 0;
	__DVDLongFileNameFlag = 0;
	uint32_t DVD_BI2 = *(uint32_t*)0x800000F4;
	if (DVD_BI2 != 0) {
		BI2DebugFlag = DVD_BI2 + 12;
		__PADSpec = *(uint32_t*)(DVD_BI2 + 0x24);
		*(uint8_t*)0x800030E8 = *(uint32_t*)DVD_BI2 & 0xFF;
	}
	
	//bunch of checks I'm not gonna bother with rn
	
	OSReport("Memory %d MB\n", *(uint32_t*)0x80000028 >> 20);
	OSReport("Arena : 0x%x - 0x%x\n", OSGetArenaLo(), OSGetArenaHi());
	if (BI2DebugFlag != 0)
		if (*(uint32_t*)BI2DebugFlag >= 2)
			EnableMetroTRKInterrupts();
	ClearArena();
	OSEnableInterrupts();
	if (__OSInIPL == 0) {
		DVDInit();
		if (__OSIsGcam != 0)
			*(uint16_t*)0x800030E6 = 0x9000;
		else {
			DCInvalidateRange(DriveInfo, 0x20);
			DVDInquiryAsync(DriveBlock, DriveInfo, (uint32_t*)InquiryCallback);
		}
	}
}

void OSExceptionInit(void) {
	int i = 0;
	if (*(uint32_t*)0x80000060 == 0) {
		DBPrintf("Installing OSDBIntegrator\n");
		memcpy((void*)0x80000060, (const void*)__OSDBIntegrator, __OSDBJump - __OSDBIntegrator);
		DCFlushRangeNoSync((void*)0x80000060, __OSDBJump - __OSDBIntegrator);
		asm("sync\n");
		ICInvalidateRange((void*)0x80000060, __OSDBJump - __OSDBIntegrator);
	}
	for (i = 0; i < 16; i++) {
		if (BI2DebugFlag && *(uint32_t*)BI2DebugFlag >= 2 && __DBIsExceptionMarked(i))
			DBPrintf(">>> OSINIT: exception %d commandeered by TRK\n", i);
		else {
			*(uint32_t*)(OSExceptionVector + 0x68) = 0x38600000 | i; //li r3, i
			if (__DBIsExceptionMarked(i)) {
				DBPrintf(">>> OSINIT: exception %d vectored to debugger\n", i);
				*(uint32_t*)(OSExceptionVector + 0x58) = 0x48000063; //bla 0x60, from __OSDBJump
			} else
				*(uint32_t*)__OSDBJump = 0x60000000; //nop
			memcpy(__OSExceptionLocations[i], OSExceptionVector, (uint32_t)OSDefaultExceptionHandler - (uint32_t)OSExceptionVector);
			DCFlushRangeNoSync(__OSExceptionLocations[i], (uint32_t)OSDefaultExceptionHandler - (uint32_t)OSExceptionVector);
			asm("sync\n");
			ICInvalidateRange(__OSExceptionLocations[i], (uint32_t)OSDefaultExceptionHandler - (uint32_t)OSExceptionVector);
		}
	}
	for (i = 0; i < 16; i++)
		__OSSetExceptionHandler(i, (void*)OSDefaultExceptionHandler);
	DBPrintf("Exceptions initialized...\n");
	*(uint32_t*)(OSExceptionVector + 0x68) = 0x38600000; //li r3, 0
}

__asm__(
	".global __OSDBIntegrator\n"
	"__OSDBIntegrator:\n"
	"li        5, 0x40\n"
	"mflr      3\n"
	"stw       3, 0xC(5)\n"
	"lwz       3, 8(5)\n"
	"oris      3, 3, 0x8000\n"
	"mtlr      3\n"
	"li        3, 0x30\n"
	"mtmsr     3\n"
	"blr\n"
);

__asm__(
	".global __OSDBJump\n"
	"__OSDBJump:\n"
	"bla       0x60\n"
);
	

__asm__(
	".global __OSSetExceptionHandler\n"
	"__OSSetExceptionHandler:\n"
	"lis       4, 0x8000\n"
	"addi      4, 4, 0x3000\n"
	"rlwinm    3, 3, 2,26,29\n" //slot << 2 (align to word), & 0x3C (16 handles)
	"stwx      3, 3, 4\n"
	"blr\n"
);

__asm__(
	".global __OSGetExceptionHandler\n"
	"__OSGetExceptionHandler:\n"
	"lis       4, 0x8000\n"
	"addi      4, 4, 0x3000\n"
	"rlwinm    3, 3, 2,26,29\n"
	"lwzx      3, 3, 4\n"
	"blr\n"
);

__asm__(
	".global OSExceptionVector\n"
	"OSExceptionVector:\n"
	"mtsprg0   4\n"
	"lwz       4, 0xC0(0)\n"
	"stw       3, 0xC(4)\n"
	"mfsprg0   3\n"
	"stw       3, 0x10(4)\n"
	"stw       5, 0x14(4)\n"
	"lhz       3, 0x1A2(4)\n"
	"ori       3, 3, 2\n"
	"sth       3, 0x1A2(4)\n"
	"mfcr      3\n"
	"stw       3, 0x80(4)\n"
	"mflr      3\n"
	"stw       3, 0x84(4)\n"
	"mfctr     3\n"
	"stw       3, 0x88(4)\n"
	"mfxer     3\n"
	"stw       3, 0x8C(4)\n"
	"mfsrr0    3\n"
	"stw       3, 0x198(4)\n"
	"mfsrr1    3\n"
	"stw       3, 0x19C(4)\n"
	"mr        5, 3\n"
	"nop\n"
	"mfmsr     3\n"
	"ori       3, 3, 0x30\n"
	"mtsrr1    3\n"
	"li        3, 0\n"
	"lwz       4, 0xD4(0)\n"
	"rlwinm.   5, 5, 0,30,30\n"
	"bne       loc_80078FBC\n"
	"lis       5, OSDefaultExceptionHandler@ha\n"
	"addi      5, 5, OSDefaultExceptionHandler@l\n"
	"mtsrr0    5\n"
	"rfi\n"
	"loc_80078FBC:\n"
	"clrlslwi  5, 3, 24,2\n"
	"lwz       5, 0x3000(5)\n"
	"mtsrr0    5\n"
	"rfi\n"
	"nop\n"
);


__asm__(
	".global OSDefaultExceptionHandler\n"
	"OSDefaultExceptionHandler:\n"
	"stw       0, 0(4)\n"
	"stw       1, 4(4)\n"
	"stw       2, 8(4)\n"
	"stmw      6, 0x18(4)\n"
	"mfspr     0, 0x391\n"
	"stw       0, 0x1A8(4)\n"
	"mfspr     0, 0x392\n"
	"stw       0, 0x1AC(4)\n"
	"mfspr     0, 0x393\n"
	"stw       0, 0x1B0(4)\n"
	"mfspr     0, 0x394\n"
	"stw       0, 0x1B4(4)\n"
	"mfspr     0, 0x395\n"
	"stw       0, 0x1B8(4)\n"
	"mfspr     0, 0x396\n"
	"stw       0, 0x1BC(4)\n"
	"mfspr     0, 0x397\n"
	"stw       0, 0x1C0(4)\n"
	"mfdsisr   5\n"
	"mfdar     6\n"
	"stwu      1, -8(1)\n"
	//"b         __OSUnhandledException\n"
);


__asm__( //no need for stack frame
	".global __OSPSInit\n"
	"__OSPSInit:\n"
	"bl        PPCMfhid2\n"
	"oris      3, 3, 0xA000\n"
	"bl        PPCMthid2\n"
	"bl        ICFlashInvalidate\n"
	"sync\n"
	"li        3, 0\n"
	"mtspr     0x390, 3\n"
	"blr\n"
);

__asm__( //they convert to uint8_t anyways
	".global __OSGetDIConfig\n"
	"__OSGetDIConfig:\n"
	"lis       3, 0xCC00\n"
	"lbz       3, 0x6027(3)\n"
	"blr\n"
);