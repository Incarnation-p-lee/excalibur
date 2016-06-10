#ifndef HAVE_DEFINED_PAGING_H
#define HAVE_DEFINED_PAGING_H

#define PAGE_TABLE_SIZE        1024
#define HEAP_SIZE              0x1000000  // 16 MB for heap
#define MEMORY_LIMIT           0x4000000  // 64 MB

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
    struct page_entry table[PAGE_TABLE_SIZE];
};

struct page_directory {
    struct page_table *dirt[PAGE_TABLE_SIZE];
    // Pointers to pagetable above with physical address location, for loading
    // into CR3 register. For access your page tables.
    ptr_t dirt_phys[PAGE_TABLE_SIZE];
    // Only for when clone page directory, the new directory will have an address
    // in virtual memory that is not the same physical memory.
    void *phy_addr;
};

static ptr_t placement_ptr = MEMORY_LIMIT - HEAP_SIZE;
static ptr_t *frames_bitmap;
static ptr_t frames_size;
static struct page_directory *kernel_dirt;
static struct page_directory *current_dirt;

#endif

