#pragma once

#include <stdint.h>


uint32_t OSGetArenaHi(void);
uint32_t OSGetArenaLo(void);
void OSSetArenaHi(uint32_t addr);
void OSSetArenaLo(uint32_t addr);