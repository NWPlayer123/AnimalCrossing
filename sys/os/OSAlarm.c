#include "OSAlarm.h"

uint32_t AlarmQueue[2];

void OSInitAlarm(void) {
	if ((uint32_t*)__OSGetExceptionHandler(8) != (uint32_t*)DecrementerExceptionHandler) {
		AlarmQueue[0] = 0;
		AlarmQueue[1] = 0;
		__OSSetExceptionHandler(8, (uint32_t*)DecrementerExceptionHandler);
	}
}

void DecrementerExceptionHandler(void) {
	
}