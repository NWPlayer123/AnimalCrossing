#include "dvdfs.h"

uint32_t __DVDLongFileNameFlag = 0;
uint32_t __DVDThreadQueue[2];

void __DVDFSInit(void) {
	
}

/*DVDConvertPathToEntrynum
DVDFastOpen
DVDOpen
DVDClose
entryToPath
DVDGetCurrentDir
DVDReadAsyncPrio
cbForReadAsync
DVDReadPrio
cbForReadSync
DVDPrepareStreamAsync
cbForPrepareStreamAsync
.data
data.0
@117
@138
@237
@263
@269
@309
@340
@341
@342
@373
@374
@375
.sdata
@116
.sbss
BootInfo
FstStart
FstStringStart
MaxEntryNum
currentDirectory
__DVDLongFileNameFlag
__DVDThreadQueue
*/