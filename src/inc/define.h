#ifndef HAVE_DEFINED_DEFINE_H
#define HAVE_DEFINED_DEFINE_H

#define true                      1
#define false                     0

#define ATTR_CLR                  0
#define ATTR_SET                  1

#define DPL_RING_0                0
#define DPL_RING_1                1
#define DPL_RING_2                2
#define DPL_RING_3                3

#define CODE_SEG_BASE             0x0
#define CODE_SEG_LMT              0xffffffff
#define DATA_SEG_BASE             0x0
#define DATA_SEG_LMT              0xffffffff
#define USR_CODE_SEG_BASE         0x0
#define USR_CODE_SEG_LMT          0xffffffff
#define USR_DATA_SEG_BASE         0x0
#define USR_DATA_SEG_LMT          0xffffffff

#define CHAR_NULL                 0x0
#define CHAR_ZERO                 0x30
#define CHAR_a                    0x61

#define printf_vga_clear          screen_monitor_clear

#define kassert(ex)               assert_complain(#ex, __FILE__, __FUNCTION__, __LINE__, (bool)(ex))
#define kassert_not_reached(msg)  assert_complain(msg, __FILE__, __FUNCTION__, __LINE__, false)
#define KERNEL_PANIC(msg)         kassert_not_reached(msg)

#define BM_INDEX(a)               ((a) / (sizeof(a) << 3))
#define BM_OFFSET(a)              ((a) % (sizeof(a) << 3))

#define BIT_SET                   1
#define BIT_CLEAR                 0
#define FRAME_BITMAP_SET          BIT_SET
#define FRAME_BITMAP_CLEAR        BIT_CLEAR
#define FRAME_NULL                0u
#define PAGE_SIZE                 0x1000

#define PTR_INVALID               (ptr_t)(-1)

#define ARRAY_CNT_OF(a)           (sizeof(a) / sizeof(a[0]))
#define BIT_WIDTH(t)              (sizeof(t) * 8)
#define U32_BIT_GET(x, idx)       ((uint32)(x) >> (idx) & 0x1)
#define U32_BITS_GET(x, s, l)     (((uint32)(x) >> (s)) & ((0x1 << (l)) - 1))

#endif

