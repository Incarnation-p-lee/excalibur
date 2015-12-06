#ifndef HAVE_DEFINED_DEFINE_H
#define HAVE_DEFINED_DEFINE_H

#define ATTR_CLR          0
#define ATTR_SET          1

#define U32_BIT(x, idx)   ((uint32)(x) >> (idx) & 0x1)
#define U32_BITS(x, s, l) (((uint32)(x) >> (s)) & ((0x1 << (l)) - 1))

#endif

