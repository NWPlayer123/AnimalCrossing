#include "__mem.h"

void* memset(void *dst, int val, size_t n) {
	__fill_mem(dst, val, n);
}

void __fill_mem(void *dst, int val, uint32_t n) {
	uint32_t v = (uint32_t)val & 0xFF;
	uchar_t* ptr1 = (uchar_t*)dst - 1;
	if (n >= 32) {
		uint32_t i = ~(uint32_t)ptr1 & 3;
		if (i != 0) { //align to 4
			n -= i;
			do {
				*ptr1++ = v;
			} while (--i);
		}
		
		if (v != 0) { //now we can use 32-bit operations
			v |= v << 24 | v << 16 | v << 8;
		}
		uint32_t* ptr2 = (uint32_t*)ptr1 - 3; //??? compiler optimized
		i = n >> 5;
		if (i != 0) {
			do {
				*ptr2++ = v;
				*ptr2++ = v;
				*ptr2++ = v;
				*ptr2++ = v;
				*ptr2++ = v;
				*ptr2++ = v;
				*ptr2++ = v;
				*ptr2++ = v;
			} while (--i);
		}

		i = (n << 30) & 7;
		if (i != 0) {
			do {
				*ptr2++ = v;
			} while (--i);
		}

		n &= 3;
		ptr1 = (uchar_t*)ptr2 + 3; //idk
	}

	if (n != 0) {
		do {
			*ptr1++ = v;
		} while (--n);
	}
}

void* memcpy(void *dst, const void *src, size_t n) {
	const char *s = src;
	char *d = dst;
	while (n--) {
		*d++ = *s++;
	}
	return dst;
}