#include "boot.h"

uint32_t fakemain_check = 0;
uint64_t InitialStartTime = 0;
uint32_t osAppNMIBuffer[16];


/*  00000000 000f7c 800056c0  1 .text 	boot.o 
  00000000 000008 800056c0  4 soundArenaAlloc 	boot.o 
  00000008 0000c0 800056c8  4 search_partial_address 	boot.o 
  000000c8 000060 80005788  4 convert_partial_address 	boot.o 
  00000128 000088 800057e8  4 LoadStringTable 	boot.o 
  000001b0 000094 80005870  4 UnLink 	boot.o 
  00000244 0001a4 80005904  4 LoadLink 	boot.o 
  000003e8 000030 80005aa8  4 audioFatalCallback 	boot.o 
  00000418 00008c 80005ad8  4 sound_initial 	boot.o 
  000004a4 000048 80005b64  4 sound_initial2 	boot.o 
  000004ec 000050 80005bac  4 HotResetIplMenu 	boot.o 
  0000053c 000094 80005bfc  4 fault_callback_keyCheck 	boot.o 
  000005d0 000034 80005c90  4 fault_callback_OK 	boot.o 
  00000604 00002c 80005cc4  4 fault_callback_Setumei 	boot.o 
  00000630 0000d0 80005cf0  4 fault_callback_vimode 	boot.o 
  00000700 000244 80005dc0  4 fault_callback_scroll 	boot.o */
void adjustOSArena(void) {
	OSReport("ARENA %08x-%08x\x1B[m\n", OSGetArenaLo(), OSGetArenaHi());
}

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
	OSInitAlarm(); //TODO: struct threads            vvvv
	uint32_t var1 = OSGetStackPointer() - 0x100;
	uint32_t var2 = *(uint32_t*)(OSGetCurrentThread() + 0x304);
	uint32_t var3 = *(uint32_t*)(OSGetCurrentThread() + 0x308) + 4;
	if (var1 > var2) {
		if (var1 < var3) {
			memset((void*)var3, 0xFD, var1 - var3);
		}
	}
	bzero(osAppNMIBuffer, 0x40);
	if (OSGetResetCode() == 0) {
		OSReport("System Power On\n");
	} else if (OSGetResetCode() > 0x80000001) { //-0xFFFFFFFE, effort tho
		OSReport("Restart\n"); //Resetti's gonna be angery
		uint32_t start, end;
		OSGetSaveRegion(&start, &end);
		OSReport("OSGetSaveRegion %08x %08x\n", start, end);
		bcopy((const void*)0x811FFFC0, osAppNMIBuffer, 0x40); //bcopy 0x811FFFC0 to osAppNMIBuffer
	} else {
		OSReport("Hot Reset\n"); //not sure that's the right term but okie
		OSReport("OSGetResetCode=0x%08x\n", OSGetResetCode());
		OSReport("Ignore the reset code in release version\n"); //well you left this comment so ¯\_(ツ)_/¯
	}
}