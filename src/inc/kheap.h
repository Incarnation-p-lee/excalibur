#ifndef HAVE_DEFINED_KHEAP_H
#define HAVE_DEFINED_KHEAP_H

#define KHEAP_BASE
#define KHEAP_INITIAL_SIZE
#define KHEAP_IDX_SIZE     0x10000
#define KHEAP_MAGIC        0xA5A55A5A
#define KHEAP_MIN_SIZE     0xdead

/*
 * Block/Hole memory structure layout
 * +---------------------+---------------+----------------+
 * |       header        |               |     footer     |
 * +-------+------+------| useable space |-------+--------+
 * | magic | hole | size |               | magic | header |
 * +-------+------+------+---------------+-------+--------+
 */
struct kheap_header {
    uint32 magic;
    bool   is_hole;
    uint32 size;    // sizeof the block, including the end footer
};

struct kheap_footer {
    uint32              magic;
    struct kheap_header *header;
};

struct kheap {
    struct ordered_array idx;
    ptr_t                addr_start;
    ptr_t                addr_end;
    ptr_t                addr_max;
    bool                 supervisor;
    bool                 read_only;
};

#endif

