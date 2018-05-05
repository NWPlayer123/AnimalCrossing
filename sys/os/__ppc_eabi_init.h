#pragma once

#include <stdint.h>

void __init_hardware(void);
void __flush_cache(uint32_t var1, uint32_t var2);
void __init_user(void);
void __init_cpp(void);