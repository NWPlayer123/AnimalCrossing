#include "os.h"

uint32_t __OSExceptionLocations[15] =
	{0x100, 0x200, 0x300, 0x400,  0x500,  0x600,  0x700,
	 0x800, 0x900, 0xC00, 0xF00, 0x1300, 0x1400, 0x1700};
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

void __OSSetExceptionHandler(uint8_t number, uint32_t* handler) {
	*(uint32_t**)(0x80003000 + (number << 2)) = handler;
}

uint32_t* __OSGetExceptionHandler(uint8_t number) {
	return *(uint32_t**)(0x80003000 + (number << 2)); //OSExceptionTable
}

void __OSPSInit(void) {
	PPCMthid2(PPCMfhid2() & 0xA0000000);
	ICFlashInvalidate();
	asm(
		"sync\n"
		"li         3, 0\n"
		"mtspr      0x390, 3\n" //General Quantization Register 0
	);
}