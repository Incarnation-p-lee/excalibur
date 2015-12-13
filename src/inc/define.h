#ifndef HAVE_DEFINED_DEFINE_H
#define HAVE_DEFINED_DEFINE_H

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


#endif

