#ifndef HAVE_DEFINED_DEFINE_H
#define HAVE_DEFINED_DEFINE_H

#include "external.h"

#define ATTR_CLR          0
#define ATTR_SET          1

#define U32_BIT(x, idx)   ((uint32)(x) >> (idx) & 0x1)
#define U32_BITS(x, s, l) (((uint32)(x) >> (s)) & ((0x1 << (l)) - 1))

#define DPL_RING_0        0
#define DPL_RING_1        1
#define DPL_RING_2        2
#define DPL_RING_3        3

#define CODE_SEG_LMT      0xFFFFF
#define DATA_SEG_LMT      0xFFFFF
#define USR_CODE_SEG_LMT  0xFFFFF
#define USR_DATA_SEG_LMT  0xFFFFF

#define ARRAY_CNT_OF(a)   (sizeof(a) / sizeof(a[0]))

#define print_clear       screen_monitor_clear
#define print_string(s)   screen_monitor_write_string(s)
#define print_uint32(u)   screen_monitor_write_uint32(u)

#define CHAR_NULL         0x0
#define CHAR_ZERO         0x30
#define CHAR_a            0x61

#endif

