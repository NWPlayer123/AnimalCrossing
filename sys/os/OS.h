#pragma once

#include <stdint.h>

#include "__ppc_eabi_init.h"
#include "__start.h"
#include "OSAlarm.h"
#include "OSThread.h"
#include "OSTime.h"

void OSInit(void);
void __OSSetExceptionHandler(uint8_t number, uint32_t* handler);
uint32_t* __OSGetExceptionHandler(uint8_t number);