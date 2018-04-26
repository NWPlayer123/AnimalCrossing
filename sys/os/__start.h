#pragma once

#include <stdint.h>
#include <string.h>

#include "../sys.h"
#include "../../boot.h"

void __check_pad3(void);
void __start(void);
void __init_registers(void);
void __init_data(void);