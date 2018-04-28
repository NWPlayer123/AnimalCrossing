#pragma once

#include "dvdfs.h"
#include "dvdlow.h"
#include "dvdqueue.h"
#include "fstload.h"
#include "../sys.h"

void DVDInit(void);
void* DVDInquiryAsync(uint32_t *r3, uint32_t *r4, uint32_t *callback);