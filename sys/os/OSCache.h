#pragma once

#include "OS.h"

void DCEnable(void);
void DCInvalidateRange(uint32_t* addr, uint32_t size);
void ICFlashInvalidate(void);
void ICEnable(void);
void L2GlobalInvalidate(void);
void DMAErrorHandler(const char* error, uint32_t *context);
void __OSCacheInit(void);