#include "gettime.h"

uint64_t __osTimeOffset = 0;

uint64_t osGetTime(void) {
	return OSGetTime() + __osTimeOffset;
}