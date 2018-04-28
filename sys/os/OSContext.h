#pragma once

#include <stdint.h>


uint32_t OSGetStackPointer(void);
void OSDumpContext(uint32_t* context);