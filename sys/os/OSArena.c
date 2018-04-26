#include "OSArena.h"

uint32_t __OSArenaHi = 0;
uint32_t __OSArenaLo = 0;

uint32_t OSGetArenaHi(void) {
	return __OSArenaHi;
}

uint32_t OSGetArenaLo(void) {
	return __OSArenaLo;
}

void OSSetArenaHi(uint32_t addr) {
	__OSArenaHi = addr;
}

void OSSetArenaLo(uint32_t addr) {
	__OSArenaLo = addr;
}