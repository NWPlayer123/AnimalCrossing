#include "os.h"

void OSInit(void) {
	
}

void __OSSetExceptionHandler(uint8_t number, uint32_t* handler) {
	*(uint32_t**)(0x80003000 + (number << 2)) = handler;
}

uint32_t* __OSGetExceptionHandler(uint8_t number) {
	return *(uint32_t**)(0x80003000 + (number << 2)); //OSExceptionTable
}