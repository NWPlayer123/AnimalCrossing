#pragma once

#include <stdint.h>
#include "OS.h"

void OSInitThreadQueue(uint32_t *queue);
uint32_t* OSGetCurrentThread(void);
uint32_t OSDisableScheduler(void);
