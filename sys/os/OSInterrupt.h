#pragma once

#include <stdint.h>

uint32_t OSDisableInterrupts(void);
void OSEnableInterrupts(void);
void OSRestoreInterrupts(uint32_t r3);
void __OSSetInterruptHandler(uint32_t slot, uint32_t *handler);
void __OSUnmaskInterrupts(uint32_t mask);
uint32_t SetInterruptMask(uint32_t var1, uint32_t var2);