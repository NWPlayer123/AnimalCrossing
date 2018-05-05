#include "OSAudioSystem.h"

uint32_t DSPInitCode[32] = {
	0x029F0010, 0x029F0033, 0x029F0034, 0x029F0035,
	0x029F0036, 0x029F0037, 0x029F0038, 0x029F0039,
	0x12061203, 0x12041205, 0x00808000, 0x0088FFFF,
	0x00841000, 0x0064001D, 0x02180000, 0x81001C1E,
	0x00441B1E, 0x00840800, 0x00640027, 0x191E0000,
	0x00DEFFFC, 0x02A08000, 0x029C0028, 0x16FC0054,
	0x16FD4348, 0x002102FF, 0x02FF02FF, 0x02FF02FF,
	0x02FF02FF, 0x00000000, 0x00000000, 0x00000000};

void __OSInitAudioSystem(void) {
	memcpy((void*)(OSGetArenaHi() - 0x80), (void*)0x81000000, 0x80); //backup v
	memcpy((void*)0x81000000, (void*)DSPInitCode, 0x80); //copy new stuff
	DCFlushRange((void*)0x81000000, 0x80);
	AR_INFO = 0x43;
	DSP_CONTROL = 0x8AC;
	DSP_CONTROL |= 1; //???
	while (DSP_CONTROL & 1) {;}
	DSP_MAIL_TO_DSP_HI = 0;
	while (((DSP_MAIL_FROM_DSP_HI << 16) | DSP_MAIL_FROM_DSP_LO) & 0x80000000) {;} //idk why two 16s
	AR_DMA_MMADDR = 0x100;
	AR_DMA_ARADDR = 0;
	AR_DMA_CNT = 0x20;
	while (DSP_CONTROL & 32 == 0) {;}
	//unnecessary sth back
	uint32_t temp = OSGetTick();
	while (OSGetTick() - temp < 0x892) {;}
	AR_DMA_MMADDR = 0x100;
	AR_DMA_ARADDR = 0;
	AR_DMA_CNT = 0x20;
	while (DSP_CONTROL & 32 == 0) {;}
	DSP_CONTROL &= 0x1C00;
	while (DSP_CONTROL & 0x400) {;}
	DSP_CONTROL &= 14;
	while (DSP_CONTROL & 0x8000 == 0) {;}
	DSP_CONTROL |= 4; //halt DSP
	DSP_CONTROL = 0x8AC;
	DSP_CONTROL |= 1; //reset DSP
	while (DSP_CONTROL & 1) {;}
	memcpy((void*)0x81000000, (void*)(OSGetArenaHi() - 0x80), 0x80); //restore ^
}

void __OSStopAudioSystem(void) {
	DSP_CONTROL = 0x804;
	AUDIO_DMA_CONTROL_LEN &= 0xC000; //0x1C000 but impossible cuz lhz
	while (DSP_CONTROL & 0x400) {;}
	while (DSP_CONTROL & 0x200) {;}
	DSP_CONTROL = 0x8AC;
	DSP_MAIL_TO_DSP_HI = 0;
	while (((DSP_MAIL_FROM_DSP_HI << 16) | DSP_MAIL_FROM_DSP_LO) & 0x80000000) {;} //idk why two 16s
	uint32_t temp = OSGetTick();
	while (OSGetTick() - temp < 0x2C) {;}
	DSP_CONTROL |= 1;
	while (DSP_CONTROL & 1) {;}
	
}