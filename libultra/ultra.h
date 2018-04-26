#pragma once

#include <stdint.h>
#include <stddef.h>
#include "../sys/sys.h"

void bcopy(const void *dst, void *src, size_t n);
void bzero(void *ptr, size_t size);