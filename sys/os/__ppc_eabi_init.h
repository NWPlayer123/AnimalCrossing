#pragma once

#include <stdint.h>

void __init_hardware(void) __attribute__ (( section(".init")));
void __flush_cache(uint32_t var1, uint32_t var2) __attribute__ (( section(".init")));

void __init_user(void) __attribute__ (( section(".text")));
void __init_cpp(void) __attribute__ (( section(".text")));