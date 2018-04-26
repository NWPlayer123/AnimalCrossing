#include "ultra.h"

void bcopy(const void *src, void *dst, size_t n) {
	memmove(dst, src, n);
}

//bcmp
void bzero(void *ptr, size_t size) {
	memset(ptr, 0, size);
}