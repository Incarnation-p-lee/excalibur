#ifndef HAVE_DEFINED_KERNEL_HEAP_H
#define HAVE_DEFINED_KERNEL_HEAP_H

#define KHEAP_START             0xC0000000
#define KHEAP_LIMIT             0xC4000000 /* At most 64 MB for heap */

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
    ptr_t             addr_limit;
    ptr_t             last_hole_addr;
};

#endif

