#include "OSThread.h"

uint32_t* OSGetCurrentThread(void) { 
	return *(uint32_t**)0x800000E4; //DefaultThread
}