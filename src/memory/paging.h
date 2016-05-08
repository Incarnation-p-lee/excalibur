#ifndef HAVE_DEFINED_PAGING_H
#define HAVE_DEFINED_PAGING_H

#define PAGE_TABLE_SIZE        1024

struct page_entry {
    uint32 present:1;
    uint32 rw:1;
    uint32 user:1;
    uint32 reserved:2;
    uint32 accessed:1;  // The page been accessed since last refresh
    uint32 dirty:1;     // The page benn written since last refresh
    uint32 reserved:2;
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
    void *dirt_phys[PAGE_TABLE_SIZE];
    // Only for when clone page directory, the new directory will have an address
    // in virtual memory that is not the same physical memory.
    void *phy_addr;
};

void paging_initilaize(void);
void paging_directory_switch(struct page_directory *new_dirt);
struct page_entry * paging_get(void *addr, uint32 make, struct page_directory *dir);
extern void paging_fault(struct pro_context *context);

#endif

