#ifndef HAL_HWDEF_H
#define HAL_HWDEF_H

#if defined HAL_HW_F149
#include "f149/hal_hwdef_f149.h"
#elif defined HAL_HW_F5529
#include "f5529/hal_hwdef_f5529.h"
#endif

#endif