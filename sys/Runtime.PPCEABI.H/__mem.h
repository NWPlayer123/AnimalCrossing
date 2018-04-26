#pragma once

#include <stdint.h>
#include <stddef.h>
#define uchar_t unsigned char

void* memset(void *dst, int val, size_t n);
void __fill_mem(void *dst, int val, uint32_t n);
void* memcpy(void *dst, const void *src, size_t n);