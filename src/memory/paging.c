void
paging_initialize(void)
{
    ptr_t i;
    uint32 bytes;
    struct page_entry *pe;

    // Init frames_size and frames_bitmap
    frames_size = MEMORY_LIMIT / PAGE_SIZE;
    bytes = frames_size / 8;
    bytes += (bytes % sizeof(ptr_t)) ? sizeof(ptr_t) : 0;

    frames_bitmap = kmalloc(bytes);
    kmemset(frames_bitmap, 0, bytes);

    // Init page directory
    kernel_dirt = kmalloc_algn(sizeof(*kernel_dirt));
    kmemset(kernel_dirt, 0, sizeof(*kernel_dirt));
    current_dirt = kernel_dirt;

    // Map phys addr to virt addr from 0x0 to placement ptr address
    // so we can access this transparently as if paging is not enabled
    i = 0;
    while (i < MEMORY_LIMIT) {
        pe = paging_get(i, true, kernel_dirt);
        frame_allocate(pe, false, false);
        i += PAGE_SIZE;
    }

    // register page fault handler and Enable paging
    isr_handler_register(PAGE_FAL, &isr_handler_14_paging_fault);
    paging_directory_switch(kernel_dirt);

    printf_vga_ts("Paging initialized.\n");
}

static inline void
paging_directory_switch(struct page_directory *dirt)
{
    uint32 cr0;

    kassert(NULL != dirt);

    current_dirt = dirt;

    asm volatile (
        "mov %1,    %%cr3\n\t"
        "mov %%cr0, %0\n\t"
        :"=r"(cr0)
        :"r"(&dirt->dirt_phys));

    cr0 |= 0x80000000u;

    asm volatile (
        "mov %0, %%cr0\n\t"
        :
        :"r"(cr0));
}

static inline struct page_entry *
paging_get(ptr_t addr, bool make, struct page_directory *dirt)
{
    ptr_t index;
    ptr_t frame;
    ptr_t phys;

    kassert(NULL != dirt);

    frame = addr / PAGE_SIZE;
    index = frame / PAGE_TABLE_SIZE;

    if (dirt->dirt[index]) {
        return &dirt->dirt[index]->table[frame % PAGE_TABLE_SIZE];
    } else if (make) {
        dirt->dirt[index] = kmalloc_algn_with_phys(sizeof(struct page_table), &phys);
        kmemset(dirt->dirt[index], 0, sizeof(struct page_table));
        // Set present, R/W and U/S
        dirt->dirt_phys[index] = phys | 0x7;
        return &dirt->dirt[index]->table[frame % PAGE_TABLE_SIZE];
    } else {
        return NULL;
    }
}

