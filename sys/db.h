#pragma once

#include <stdint.h>
#include "sys.h"

void DBInit(void);
void __DBExceptionDestinationAux(void);
void __DBExceptionDestination(void);
uint32_t __DBIsExceptionMarked(uint32_t r3);
void DBPrintf(const char *format, ...);