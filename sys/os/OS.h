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
void __OSDBIntegrator(void);
void __OSDBJump(void); //idk
void __OSSetExceptionHandler(int type, void* handler);
uint32_t* __OSGetExceptionHandler(int type);
void OSExceptionVector(uint32_t something, uint32_t* sprg0, uint32_t something2);
void OSDefaultExceptionHandler(uint32_t unknown, uint32_t *context);
void __OSPSInit(void);
uint8_t __OSGetDIConfig(void);