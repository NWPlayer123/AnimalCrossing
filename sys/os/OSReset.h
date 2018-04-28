#pragma once

#include <stdint.h>
#include "OS.h"
#include "../sys.h"

void OSResetSystem(uint32_t r3, uint32_t r4, uint32_t r5);
int OSGetResetCode(void);