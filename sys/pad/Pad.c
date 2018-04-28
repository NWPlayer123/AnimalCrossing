#include "Pad.h"

uint32_t __PADSpec = 0;
/*
.text
UpdateOrigin
PADOriginCallback
PADOriginUpdateCallback
PADProbeCallback
PADTypeAndStatusCallback
PADReceiveCheckCallback
PADReset
PADRecalibrate
PADInit
PADRead
PADControlAllMotors
PADControlMotor
PADSetSpec
SPEC0_MakeStatus
SPEC1_MakeStatus
SPEC2_MakeStatus
PADSetAnalogMode
OnReset
SamplingHandler
PADSetSamplingCallback
__PADDisableRecalibration
.data
ResetFunctionInfo
.bss
bss.0
Type
Origin
CmdProbeDevice
.sdata
ResettingChan
XPatchBits
AnalogMode
Spec
MakeStatus
CmdReadOrigin
CmdCalibrate
.sbss
Initialized
EnabledBits
ResettingBits
RecalibrateBits
WaitingBits
CheckingBits
PendingBits
SamplingCallback
recalibrated$396
__PADSpec
*/

uint32_t __PADDisableRecalibration(uint32_t r3) {
	uint32_t ret = OSDisableInterrupts();
	uint32_t r31 = *(uint8_t*)0x800030E3 & 0x40 ? 0 : 1;
	*(uint8_t*)0x800030E3 &= 0xBF;
	if (r3 != 0) {
		*(uint8_t*)0x800030E3 |= 0x40;
	}
	OSRestoreInterrupts(ret);
}