#ifndef HAVE_DEFINED_PAGING_H
#define HAVE_DEFINED_PAGING_H

#define PAGE_ENTRY_COUNT 1024
#define HEAP_SIZE        0x1000000  // 16 MB for heap
#define MEMORY_LIMIT     0x8000000  // 128 MB
#define PAGE_TABLE_COUNT (MEMORY_LIMIT / (PAGE_SIZE * PAGE_ENTRY_COUNT))

typedef struct page_table     s_page_table_t;
typedef struct page_entry     s_page_entry_t;
typedef struct page_directory s_page_directory_t;
typedef struct frame_bitmap   s_frame_bitmap_t;

struct page_entry {
    uint32 present:1;
    uint32 rw:1;
    uint32 user:1;
    uint32 reserved_1:2;
    uint32 accessed:1;  // The page been accessed since last refresh
    uint32 dirty:1;     // The page benn written since last refresh
    uint32 reserved_2:2;
    uint32 available:3; // unused and available for kernel
    uint32 frame:20;
};

struct page_table {
    s_page_entry_t entry_array[PAGE_ENTRY_COUNT];
};

struct page_directory {
    s_page_table_t *table_array[PAGE_TABLE_COUNT];
    /*
     * array of pointer to page table above, within physical address, the CR3
     * register will need this.
     */
    ptr_t          table_array_phys[PAGE_TABLE_COUNT];
    void           *phys_addr; /* physical address of above table_array_phys */
};

/*
 * page directory
 *     |- page table 0
 *            |- page entry 0
 *            |- page entry 1
 *            |- page entry 2
 *            ...
 *            |- page entry 1023
 *     |- page table 1
 *     |-
 *     |-
 *     ...
 *     |- page table 1023
 */

struct frame_bitmap {
    ptr_t  *bitmap;
    uint32 size;
    uint32 frame_limit;
};

static ptr_t placement_ptr = MEMORY_LIMIT - HEAP_SIZE;
// static ptr_t *frames_bitmap;
// static ptr_t frames_size;
static s_page_directory_t *kernel_page_dirt;
static s_page_directory_t *current_page_dirt;

#endif

