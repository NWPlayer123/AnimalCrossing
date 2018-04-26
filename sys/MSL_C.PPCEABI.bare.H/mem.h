#pragma once

#include <stdint.h>
#include <stddef.h>
#include "../sys.h"
#define uchar_t unsigned char

int memcmp(const void *ptr1, const void *ptr2, size_t n);
void* memmove(void *dst, const void *src, size_t n);