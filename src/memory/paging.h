#ifndef HAVE_DEFINED_PAGING_H
#define HAVE_DEFINED_PAGING_H

#define PAGE_TABLE_SIZE        1024
#define HEAP_SIZE              0x1000000
#define MEMORY_LIMIT           0x8000000  /* 128 MB */

struct page_entry {
    uint32 present:1;
    uint32 rw:1;
    uint32 user:1;
    uint32 reserved_1:2;
    uint32 accessed:1;  /* The page been accessed since last refresh */
    uint32 dirty:1;     /* The page benn written since last refresh */
    uint32 reserved_2:2;
    uint32 available:3; /* unused and available for kernel */
    uint32 frame:20;
};
typedef struct page_entry s_page_entry_t;

struct page_table {
    struct page_entry table[PAGE_TABLE_SIZE];
};
typedef struct page_table s_page_table_t;

struct page_directory {
    struct page_table *dirt[PAGE_TABLE_SIZE];
    // Pointers to pagetable above with physical address location, for loading
    // into CR3 register. For access your page tables.
    ptr_t dirt_phys[PAGE_TABLE_SIZE];
    // Only for when clone page directory, the new directory will have an address
    // in virtual memory that is not the same physical memory.
    void *phy_addr;
};
typedef struct page_directory s_page_directory_t;

static ptr_t placement_ptr = MEMORY_LIMIT - HEAP_SIZE;
static ptr_t *frames_bitmap;
static ptr_t frames_size;
static s_page_directory_t *kernel_dirt;
static s_page_directory_t *current_dirt;

#endif

