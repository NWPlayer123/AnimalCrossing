#include "PPCArch.h"


__asm__(
	".global PPCMfmsr\n"
	"PPCMfmsr:\n"
	"mfmsr      3\n"
	"blr\n"
);

__asm__(
	".global PPCMtmsr\n"
	"PPCMtmsr:\n"
	"mtmsr      3\n"
	"blr\n"
);

__asm__(
	".global PPCMfhid0\n"
	"PPCMfhid0:\n"
	"mfspr      3, 0x3F0\n"
	"blr\n"
);

__asm__(
	".global PPCMthid0\n"
	"PPCMthid0:\n"
	"mtspr      0x3F0, 3\n"
	"blr\n"
);

__asm__(
	".global PPCMfl2cr\n"
	"PPCMfl2cr:\n"
	"mfspr      3, 0x3F9\n"
	"blr\n"
);

__asm__(
	".global PPCMtl2cr\n"
	"PPCMtl2cr:\n"
	"mtspr      0x3F9, 3\n"
	"blr\n"
);

__asm__(
	".global PPCMtdec\n"
	"PPCMtdec:\n"
	"mtdec      3\n"
	"blr\n"
);

__asm__(
	".global PPCSync\n"
	"PPCSync:\n"
	"sc\n"
	"blr\n"
);

__asm__(
	".global PPCHalt\n"
	"PPCHalt:\n"
	"sync\n"
	"label1:\n"
	"nop\n"
	"li         3, 0\n"
	"nop\n"
	"b          label1\n"
);
	

__asm__(
	".global PPCMfhid2\n"
	"PPCMfhid2:\n"
	"mfspr      3, 0x398\n"
	"blr\n"
);

__asm__(
	".global PPCMthid2\n"
	"PPCMthid2:\n"
	"mtspr      0x398, 3\n"
	"blr\n"
);

__asm__(
	".global PPCMtwpar\n"
	"PPCMtwpar:\n"
	"mtspr      0x399, 3\n"
	"blr\n"
);

__asm__(
	".global PPCDisableSpeculation\n"
	"PPCDisableSpeculation:\n"
	"bl         PPCMfhid0\n"
	"ori        3, 3, 0x200\n"
	"bl         PPCMthid0\n"
	"blr\n"
);

__asm__(
	".global PPCSetFpNonIEEEMode\n"
	"PPCSetFpNonIEEEMode:\n"
	"mtfsb1     4*cr7+gt\n"
	"blr\n"
);