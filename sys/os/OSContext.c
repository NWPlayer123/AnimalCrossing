#include "OSContext.h"

/*
__OSLoadFPUContext
__OSSaveFPUContext
OSSetCurrentContext
OSGetCurrentContext
OSSaveContext
OSLoadContext*/

__asm__(
	".global OSGetStackPointer\n"
	"OSGetStackPointer:\n"
	"mr        3, 1\n"
	"blr\n"
);

/*
OSClearContext
OSInitContext*/
void OSDumpContext(uint32_t* context) {
	
}
/*OSSwitchFPUContext
__OSContextInit
OSFillFPUContext
*/