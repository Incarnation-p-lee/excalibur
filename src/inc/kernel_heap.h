#ifndef HAVE_DEFINED_KERNEL_HEAP_H
#define HAVE_DEFINED_KERNEL_HEAP_H

typedef struct kernel_heap_header s_kernel_heap_header_t;
typedef struct kernel_heap_footer s_kernel_heap_footer_t;
typedef struct kernel_heap        s_kernel_heap_t;

/*
 * Block/Hole memory structure layout
 * +---------------------+---------------+----------------+
 * |       header        |               |     footer     |
 * +-------+------+------| useable space |-------+--------+
 * | magic | hole | size |               | magic | header |
 * +-------+------+------+---------------+-------+--------+
 */
struct kernel_heap_header {
    uint32 magic;
    bool   is_hole;
    uint32 size;    /* sizeof the block, including the end footer */
};

struct kernel_heap_footer {
    uint32                 magic;
    s_kernel_heap_header_t *header;
};

struct kernel_heap {
    s_ordered_array_t *ordered;
    bool              supervisor;
    bool              read_only;
    ptr_t             addr_start;
    ptr_t             addr_end;
    ptr_t             addr_max;
};

#define KHEAP_BASE
#define KHEAP_HEADER_SIZE
#define KHEAP_INITIAL_SIZE   0x20000
#define KHEAP_IDX_SIZE       0x10000
#define KHEAP_MAGIC          0xA5A55A5A
#define KHEAP_MIN_SIZE       KHEAP_INITIAL_SIZE
#define KHEAP_INFO_SIZE      (sizeof(s_kheap_header_t) + sizeof(s_kheap_footer_t))
#define KHEAP_HOLE_MIN_SIZE  (sizeof(ptr_t) + KHEAP_INFO_SIZE)

#define PAGE_ALIGN_P(addr)   (0 == ((addr) & 0xfff) ? true : false)
#define PAGE_ALIGN_MASK      ((ptr_t)(-1) << 12)

#endif

