#include "OSReboot.h"

uint32_t SaveStart = 0;
uint32_t SaveEnd = 0;

void OSGetSaveRegion(uint32_t* start, uint32_t* end) {
	*start = SaveStart;
	*end = SaveEnd;
}