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
    s_ordered_array_t ordered;
    bool              is_user;
    bool              is_writable;
    ptr_t             addr_start;
    ptr_t             addr_end;
    ptr_t             addr_max;
    ptr_t             last_hole_addr;
};

#define KHEAP_HOLE_COUNT        0x10000
#define KHEAP_BASE
#define KHEAP_INITIAL_SIZE      0x20000
#define KHEAP_MAGIC             0xA5A55A5A
#define KHEAP_MIN_SIZE          KHEAP_INITIAL_SIZE
#define KHEAP_HEADER_SIZE       sizeof(s_kernel_heap_header_t)
#define KHEAP_FOOTER_SIZE       sizeof(s_kernel_heap_footer_t)
#define KHEAP_INFO_SIZE         (KHEAP_HEADER_SIZE + KHEAP_FOOTER_SIZE)
#define KHEAP_HOLE_MIN_SIZE     (sizeof(ptr_t) + KHEAP_INFO_SIZE)

#define KHEAP_HOLE_SIZE(s)      ((s) + KHEAP_INFO_SIZE)
#define KHEAP_USER_TO_HEADER(u) (void *)((ptr_t)(u) - (ptr_t)KHEAP_HEADER_SIZE)

#endif

