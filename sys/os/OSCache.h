#pragma once

#include <stdint.h>
#include "OS.h"

void DCEnable(void);
void DCInvalidateRange(void* addr, uint32_t size);
void DCFlushRange(void* addr, uint32_t size);
void DCStoreRange(void* addr, uint32_t size);
void DCFlushRangeNoSync(void* addr, uint32_t size);
void DCStoreRangeNoSync(void* addr, uint32_t size);
void DCZeroRange(void* addr, uint32_t size);
void DCTouchRange(void* addr, uint32_t size);
void ICInvalidateRange(void* addr, uint32_t size);
void ICFlashInvalidate(void);
void ICEnable(void);
void LCDisable(void);
void L2GlobalInvalidate(void);
void DMAErrorHandler(const char *error, uint32_t *context);
void __OSCacheInit(void);