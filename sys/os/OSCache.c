#include "OSCache.h"

__asm__(
	".global DCEnable\n"
	"DCEnable:\n"
	"sync\n"
	"mfspr     3, 0x3F0\n"
	"ori       3, 3, 0x4000\n"
	"mtspr     0x3F0, 3\n"
	"blr\n"
);

__asm__(
	".global DCInvalidateRange\n"
	"DCInvalidateRange:\n"
	"cmplwi    4, 0\n"
	"blelr\n"
	"clrlwi.   5, 3, 27\n"
	"beq       label1\n"
	"addi      4, 4, 0x20\n"
	"label1:\n"
	"addi      4, 4, 0x1F\n"
	"srwi      4, 4, 5\n"
	"mtctr     4\n"
	"label2:\n"
	"dcbi      0, 3\n"
	"addi      3, 3, 0x20\n"
	"bdnz      label2\n"
	"blr\n"
);

__asm__(
	".global DCFlushRange\n"
	"DCFlushRange:\n"
	"cmplwi    4, 0\n"
	"blelr\n"
	"clrlwi.   5, 3, 27\n"
	"beq       label3\n"
	"addi      4, 4, 0x20\n"
	"label3:\n"
	"addi      4, 4, 0x1F\n"
	"srwi      4, 4, 5\n"
	"mtctr     4\n"
	"label4:\n"
	"dcbf      0, 3\n"
	"addi      3, 3, 0x20\n"
	"bdnz      label4\n"
	"sc\n"
	"blr\n"
);

__asm__(
	".global DCStoreRange\n"
	"DCStoreRange:\n"
	"cmplwi    4, 0\n"
	"blelr\n"
	"clrlwi.   5, 3, 27\n"
	"beq       label5\n"
	"addi      4, 4, 0x20\n"
	"label5:\n"
	"addi      4, 4, 0x1F\n"
	"srwi      4, 4, 5\n"
	"mtctr     4\n"
	"label6:\n"
	"dcbst     0, 3\n"
	"addi      3, 3, 0x20\n"
	"bdnz      label6\n"
	"sc\n"
	"blr\n"
);

__asm__(
	".global DCFlushRangeNoSync\n"
	"DCFlushRangeNoSync:\n"
	"cmplwi    4, 0\n"
	"blelr\n"
	"clrlwi.   5, 3, 27\n"
	"beq       label7\n"
	"addi      4, 4, 0x20\n"
	"label7:\n"
	"addi      4, 4, 0x1F\n"
	"srwi      4, 4, 5\n"
	"mtctr     4\n"
	"label8:\n"
	"dcbf      0, 3\n"
	"addi      3, 3, 0x20\n"
	"bdnz      label8\n"
	"blr\n"
);

__asm__(
	".global DCStoreRangeNoSync\n"
	"DCStoreRangeNoSync:\n"
	"cmplwi    4, 0\n"
	"blelr\n"
	"clrlwi.   5, 3, 27\n"
	"beq       label9\n"
	"addi      4, 4, 0x20\n"
	"label9:\n"
	"addi      4, 4, 0x1F\n"
	"srwi      4, 4, 5\n"
	"mtctr     4\n"
	"label10:\n"
	"dcbst     0, 3\n"
	"addi      3, 3, 0x20\n"
	"bdnz      label10\n"
	"blr\n"
);

__asm__(
	".global DCZeroRange\n"
	"DCZeroRange:\n"
	"cmplwi    4, 0\n"
	"blelr\n"
	"clrlwi.   5, 3, 27\n"
	"beq       label11\n"
	"addi      4, 4, 0x20\n"
	"label11:\n"
	"addi      4, 4, 0x1F\n"
	"srwi      4, 4, 5\n"
	"mtctr     4\n"
	"label12:\n"
	"dcbz      0, 3\n"
	"addi      3, 3, 0x20\n"
	"bdnz      label12\n"
	"blr\n"
);

__asm__(
	".global DCTouchRange\n"
	"DCTouchRange:\n"
	"cmplwi    4, 0\n"
	"blelr\n"
	"clrlwi.   5, 3, 27\n"
	"beq       label13\n"
	"addi      4, 4, 0x20\n"
	"label13:\n"
	"addi      4, 4, 0x1F\n"
	"srwi      4, 4, 5\n"
	"mtctr     4\n"
	"label14:\n"
	"dcbt      0, 3\n"
	"addi      3, 3, 0x20\n"
	"bdnz      label14\n"
	"blr\n"
);

__asm__(
	".global ICInvalidateRange\n"
	"ICInvalidateRange:\n"
	"cmplwi    4, 0\n"
	"blelr\n"
	"clrlwi.   5, 3, 27\n"
	"beq       label15\n"
	"addi      4, 4, 0x20\n"
	"label15:\n"
	"addi      4, 4, 0x1F\n"
	"srwi      4, 4, 5\n"
	"mtctr     4\n"
	"label16:\n"
	"icbi      0, 3\n"
	"addi      3, 3, 0x20\n"
	"bdnz      label16\n"
	"sync\n"
	"isync\n"
	"blr\n"
);

__asm__(
	".global ICFlashInvalidate\n"
	"ICFlashInvalidate:\n"
	"mfspr     3, 0x3F0\n"
	"ori       3, 3, 0x800\n"
	"mtspr     0x3F0, 3\n"
	"blr\n"
);

__asm__(
	".global ICEnable\n"
	"ICEnable:\n"
	"isync\n"
	"mfspr     3, 0x3F0\n"
	"ori       3, 3, 0x8000\n"
	"mtspr     0x3F0, 3\n"
	"blr\n"
);

__asm__(
	".global LCDisable\n"
	"LCDisable:\n"
	"lis       3, 0xE000\n"
	"li        4, 0x200\n"
	"mtctr     4\n"
	"label17:\n"
	"dcbi      0, 3\n"
	"addi      3, 3, 0x20\n"
	"bdnz      label17\n"
	"mfspr     4, 0x398\n"
	"rlwinm    4, 4, 0,4,2\n"
	"mtspr     0x398, 4\n"
	"blr\n"
);

void L2GlobalInvalidate(void) {
	asm("sync\n");
	PPCMtl2cr(PPCMfl2cr() & 0x7FFFFFFF);
	asm("sync\n");
	PPCMtl2cr(PPCMfl2cr() | 0x200000);
	while (PPCMfl2cr() & 1) {;}
	PPCMtl2cr(PPCMfl2cr() & 0x700000);
	while (PPCMfl2cr() & 1)
		DBPrintf(">>> L2 INVALIDATE : SHOULD NEVER HAPPEN\n");
}

void DMAErrorHandler(const char *error, uint32_t *context) {
	DBPrintf(error); //inlined for some reason
	OSReport("Machine check received\n");
	OSReport("HID2 = 0x%x   SRR1 = 0x%x\n", PPCMfhid2(), *(uint32_t*)(context + 0x19C));
	if (PPCMfhid2() & 0xF00000 == 0 || *(uint32_t*)(context + 0x19C) & 0x200000 == 0) {
		OSReport("Machine check was not DMA/locked cache related\n");
		OSDumpContext(context);
		PPCHalt();
	}
	OSReport("DMAErrorHandler(): An error occurred while processing DMA.\n");
	OSReport("The following errors have been detected and cleared :\n");
	if (PPCMfhid2() & 0x800000)
		OSReport("\t- Requested a locked cache tag that was already in the cache\n");
	if (PPCMfhid2() & 0x400000)
		OSReport("\t- DMA attempted to access normal cache\n");
	if (PPCMfhid2() & 0x200000)
		OSReport("\t- DMA missed in data cache\n");
	if (PPCMfhid2() & 0x100000)
		OSReport("\t- DMA queue overflowed\n");
	//has a PPCMthid2 but unnecessary
}

void __OSCacheInit(void) {
	if (PPCMfhid0() & 0x8000 == 0) {
		ICEnable();
		DBPrintf("L1 i-caches initialized\n");
	}
	if (PPCMfhid0() & 0x4000 == 0) {
		DCEnable();
		DBPrintf("L1 d-caches initialized\n");
	}
	if (PPCMfl2cr() & 0x80000000 == 0) {
		uint32_t msr = PPCMfmsr(); //save it
		asm("sync\n");
		PPCMtmsr(0x30);
		asm("sync\n");
		PPCMtl2cr(PPCMfl2cr() & 0x7FFFFFFF);
		asm("sync\n");
		L2GlobalInvalidate();
		PPCMtmsr(msr);
		PPCMtl2cr((PPCMfl2cr() | 0x80000000) & 0x700000);
		DBPrintf("L2 cache initialized\n");
	}
	OSSetErrorHandler(1, (void*)DMAErrorHandler);
	DBPrintf("Locked cache machine check handler installed\n");
}