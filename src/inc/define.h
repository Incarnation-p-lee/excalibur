#ifndef HAVE_DEFINED_DEFINE_H
#define HAVE_DEFINED_DEFINE_H

#include "external.h"

#define true              1
#define false             0

#define ATTR_CLR          0
#define ATTR_SET          1

#define U32_BIT(x, idx)   ((uint32)(x) >> (idx) & 0x1)
#define U32_BITS(x, s, l) (((uint32)(x) >> (s)) & ((0x1 << (l)) - 1))

#define DPL_RING_0        0
#define DPL_RING_1        1
#define DPL_RING_2        2
#define DPL_RING_3        3

#define CODE_SEG_BASE     0x0
#define CODE_SEG_LMT      0xfffff

#define DATA_SEG_BASE     0x0
#define DATA_SEG_LMT      0xfffff

#define STACK_SEG_BASE    0x300000
#define STACK_SEG_LMT     0xfffff

#define USR_CODE_SEG_LMT  0xFFFFF
#define USR_CODE_SEG_BASE 0xFFFFF
#define USR_DATA_SEG_LMT  0xFFFFF

#define CHAR_NULL         0x0
#define CHAR_ZERO         0x30
#define CHAR_a            0x61

#define printf_vga_clear  screen_monitor_clear

#define ARRAY_CNT_OF(a)   (sizeof(a) / sizeof(a[0]))
#define assert_k(ex)      ((ex) || (assert_complain(#ex, \
    __FILE__, __FUNCTION__, __LINE__), false))

#endif

