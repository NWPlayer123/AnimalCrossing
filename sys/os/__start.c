#include "__start.h"

void __check_pad3(void) {
	
}

void __start(void) {
	__init_registers();
	__init_hardware();
	__init_data();
	*(uint32_t*)0x80000044 = 0; //Debugger Exception mask
	uint32_t r7 = 0;
	
	
	/*if (*(uint32_t*)0x800000F4 == 0) {
		uint32_t r5 = *(uint32_t*)0x80000034;
		if (r5 != 0) {
			r7 = *(uint32_t*)0x800030E8; //yagcd is useless
		}
	} else {
		r7 = r7 = *(uint32_t*)0x80000100; //System Reset Interrupt
	}
	if (r7 == 2) {
		r5 = 0;
		asm( //don't trust it to optimize, I'll check later
			"lis       6, InitMetroTRK\n"
			"addi      6, 6, InitMetroTRK\n"
			"mtlr      6\n"
			"blrl\n"
		);
	} else if (r7 == 3) {
		r5 = 1;
		asm( //don't trust it to optimize, I'll check later
			"lis       6, InitMetroTRK\n"
			"addi      6, 6, InitMetroTRK\n"
			"mtlr      6\n"
			"blrl\n"
		);
	else
		r5 = 0;
	
	if (*(uint32_t*)0x800000F4 != 0) {
		r7 = *(uint32_t*)0x80000100; //System Reset Interrupt
		if (r7 == 2) {
			asm( //don't trust it to optimize, I'll check later
				"lis       6, InitMetroTRK\n"
				"addi      6, 6, InitMetroTRK\n"
				"mtlr      6\n"
				"blrl\n"
			);
		} else if (r7 == 3) {
			r5 = 1;
		} else {
	} else if (*(uint32_t*)0x80000034 != 0) {
		r7 = *(uint32_t*)0x800030E8; //yagcd is useless
	}
	if (*(uint32_t*)0x800000F4 == 0) {
		if (*(uint32_t*)0x80000034 != 0)
			r7 = *(uint32_t*)0x800030E8; //yagcd is useless
	} else
		r7 = *(uint32_t*)0x80000100; //System Reset Interrupt
	
	if (r7 == 2) {
		asm( //don't trust it to optimize, I'll check later
			"lis       6, InitMetroTRK\n"
			"addi      6, 6, InitMetroTRK\n"
			"mtlr      6\n"
			"blrl\n"
		);
	}*/
	DBInit();
	OSInit();
	if (*(uint16_t*)0x800030E6 & 0x8000 == 0 || *(uint16_t*)0x800030E6 & 0x7FFF == 1)
		__check_pad3();
	
	//__init_user();
	main1();
	//exit(); //should theoretically never get here
}

void __init_registers(void) {
	return; //TODO: implement the TOC and shit when you get farther
}

void __init_data(void) { //TODO: add linker shit to export all sections for it to init
	uint32_t* increment = (uint32_t*)0x8000556C;
	while (*(increment + 8) != 0) {
		if (*increment != *(increment + 4)) {
			//memcpy(*(increment + 4), *increment, *(increment + 8));
			__flush_cache(*(increment + 4), *(increment + 8));
		}
		increment += 12; //next 3 words
	}
	increment = (uint32_t*)0x800055F0;
	while (*(increment + 4) != 0) {
		memset((void*)*increment, 0, *(increment + 4));
		increment += 8;
	}
}