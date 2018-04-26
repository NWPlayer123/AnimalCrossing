#include "OSContext.h"

__asm__(
	".global OSGetStackPointer\n"
	"OSGetStackPointer:\n"
	"mr        3, 1\n"
	"blr\n"
);