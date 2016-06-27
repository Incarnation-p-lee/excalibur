#ifndef HAVE_DEFINED_KHEAP_H
#define HAVE_DEFINED_KHEAP_H

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
typedef struct kheap_header s_kheap_header_t;

struct kheap_footer {
    uint32           magic;
    s_kheap_header_t *header;
};
typedef struct kheap_footer s_kheap_footer_t;

struct kheap {
    struct ordered_array ordered;
    bool                 supervisor;
    bool                 read_only;
    ptr_t                addr_start;
    ptr_t                addr_end;
    ptr_t                addr_max;
};
typedef struct kheap s_kheap_t;

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

