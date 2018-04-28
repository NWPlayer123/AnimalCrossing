#pragma once

#include <stdint.h>

#include "../sys.h"
#include "__ppc_eabi_init.h"
#include "__start.h"
#include "OSAlarm.h"
#include "OSArena.h"
#include "OSAudioSystem.h"
#include "OSCache.h"
#include "OSContext.h"
#include "OSError.h"
#include "OSInterrupt.h"
#include "OSReboot.h"
#include "OSReset.h"
#include "OSThread.h"
#include "OSTime.h"

void ClearArena(void);
void InquiryCallback(uint32_t r3, uint32_t r4);
void OSInit(void);
void __OSSetExceptionHandler(uint8_t number, uint32_t* handler);
uint32_t* __OSGetExceptionHandler(uint8_t number);
void __OSPSInit(void);