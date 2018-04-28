#pragma once

#include <stdint.h>

uint32_t PPCMfmsr(void);
void PPCMtmsr(uint32_t value);
uint32_t PPCMfhid0(void);
void PPCMthid0(uint32_t value);
uint32_t PPCMfl2cr(void);
void PPCMtl2cr(uint32_t value);
void PPCMtdec(uint32_t value);
void PPCSync(void);
void PPCHalt(void);
uint32_t PPCMfhid2(void);
void PPCMthid2(uint32_t value);
void PPCMtwpar(uint32_t value);
void PPCDisableSpeculation(void);
void PPCSetFpNonIEEEMode(void);