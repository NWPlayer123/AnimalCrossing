#include "mem.h"

int memcmp(const void *ptr1, const void *ptr2, size_t n) {
	uchar_t* p1 = (uchar_t*) ptr1;
	uchar_t* p2 = (uchar_t*) ptr2;
	while (--n != 0)
		if (*p1++ != *p2++)
			return (*--p1 - *--p2);
}

void* memmove(void *dst, const void *src, size_t n) {
	if (src == dst) {
		return dst;
	} else if (src > dst) {
		return memcpy(dst, src, n);
	} else {
		const char* a = (const char *) src + n;
		char* b = (char *) dst + n;
		int i = 0;
		if (n < 32) {
			for (i = 0; i < n; i++)
				*--b = *--a;
			return dst;
		} else { //32 or more, need to buffer
			uint32_t n2 = 0;
			while ((uint32_t)b & 7) { //align dst
				*--b = *--a;
				n--;
			}
			if ((uint32_t)a & 7 != 0) { //align src
				n2 = n / 4;
				for (i = 0; i < n2; i++) {
					a -= 4; b -= 4;
					*(uint32_t*) b = *(uint32_t*) a;
					n -= 4;
				}
			} else {
				n2 = n / 8;
				for (i = 0; i < n2; i++) {
					a -= 8; b -= 8;
					*(uint64_t*) b = *(uint64_t*) a;
					n -= 8;
				}
			}
			for (i = 0; i < n; i++) {
				*--b = *--a;
			}
		}
		return dst;
	}
}