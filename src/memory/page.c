static inline s_page_directory_t *
page_directory_create(void)
{
    s_page_directory_t *page_dirt;

    page_dirt = kmalloc_algn(sizeof(*page_dirt));
    kmemset(page_dirt, 0, sizeof(*page_dirt));

    return page_dirt;
}

static inline s_page_table_t *
page_table_create(void)
{
    s_page_table_t *page_table;

    page_table = kmalloc_algn(sizeof(s_page_table_t));
    kmemset(page_table, 0, sizeof(s_page_table_t));

    return page_table;
}

static inline s_page_table_t *
page_directory_page_table(s_page_directory_t *page_dirt, uint32 i)
{
    kassert(page_dirt);
    kassert(i < ARRAY_CNT_OF(page_dirt->table_array));

    return page_dirt->table_array[i];
}

static inline void
page_directory_page_table_set(s_page_directory_t *page_dirt, uint32 i,
    s_page_table_t *page_table)
{
    kassert(page_dirt);
    kassert(i < ARRAY_CNT_OF(page_dirt->table_array));

    page_dirt->table_array[i] = page_table;
}

static inline void
page_directory_page_table_phys_set(s_page_directory_t *page_dirt, uint32 i,
    ptr_t page_table_phys)
{
    kassert(page_dirt);
    kassert(i < ARRAY_CNT_OF(page_dirt->table_array_phys));

    /*
     * The page_table pointed to an array of 1024 page entry.
     * Actually, page_table contains the pointer to that array, and at the same
     * time page_table is kind of page entry two(Page align).
     *
     * So the tail 12 bits of page table also controls the page entry array too.
     * A page is active if and only if their page table is active.
     *
     * This called 2-layers paging depends on CPU hardware implement, intel CPU
     * provide above page directory.
     */
    page_table_phys |= 0x7; /* us rw present */

    page_dirt->table_array_phys[i] = page_table_phys;
}

static inline s_page_entry_t *
page_table_page_entry(s_page_table_t *page_table, uint32 i)
{
    kassert(page_table);
    kassert(i < ARRAY_CNT_OF(page_table->entry_array));

    return &page_table->entry_array[i];
}

static inline void
page_entry_attribute_us_set(s_page_entry_t *page_entry, bool is_user)
{
    kassert(page_entry);

    if (is_user) {
        page_entry->user = BIT_SET;
    } else {
        page_entry->user = BIT_CLEAR;
    }
}

static inline void
page_entry_attribute_rw_set(s_page_entry_t *page_entry, bool is_writable)
{
    kassert(page_entry);

    if (is_writable) {
        page_entry->rw = BIT_SET;
    } else {
        page_entry->rw = BIT_CLEAR;
    }
}

static inline void
page_entry_attribute_present_set(s_page_entry_t *page_entry, bool is_presented)
{
    kassert(page_entry);

    if (is_presented) {
        page_entry->present = BIT_SET;
    } else {
        page_entry->present = BIT_CLEAR;
    }
}

static inline ptr_t
page_entry_frame(s_page_entry_t *page_entry)
{
    kassert(page_entry);

    return page_entry->frame;
}

static inline void
page_entry_frame_set(s_page_entry_t *page_entry, ptr_t frame)
{
    kassert(page_entry);

    page_entry->frame = frame;
}

static inline s_page_entry_t *
page_directory_page_obtain(s_page_directory_t *page_dirt, ptr_t addr)
{
    ptr_t i; /* table index */
    ptr_t k; /* page index */
    ptr_t frame;
    s_page_table_t *page_table;
    s_page_entry_t *page_entry;

    kassert(page_dirt);

    frame = addr / PAGE_SIZE;
    i = frame / PAGE_ENTRY_COUNT;
    k = frame % PAGE_ENTRY_COUNT;

    page_table = page_directory_page_table(page_dirt, i);

    if (page_table) {
        return page_table_page_entry(page_table, k);
    } else {
        page_table = page_table_create();
        page_directory_page_table_set(page_dirt, i, page_table);
        page_directory_page_table_phys_set(page_dirt, i, (ptr_t)page_table);

        page_entry = page_table_page_entry(page_table, k);
        page_entry_attribute_us_set(page_entry, /* is_user = */true);
        page_entry_attribute_rw_set(page_entry, /* is_writable = */true);
        page_entry_attribute_present_set(page_entry, /* is_presented = */true);

        return page_entry;
    }
}

static inline void
page_directory_switch(s_page_directory_t *page_dirt)
{
    uint32 cr0;

    kassert(page_dirt);

    asm volatile (
        "mov %1,    %%cr3\n\t"
        "mov %%cr0, %0\n\t"
        :"=r"(cr0)
        :"r"(&page_dirt->table_array_phys));

    cr0 |= 0x80000000u;

    asm volatile (
        "mov %0, %%cr0\n\t"
        :
        :"r"(cr0));


    current_page_dirt = page_dirt;
}

void
page_initialize(void)
{
    ptr_t addr;
    s_page_entry_t *page_entry;
    s_frame_bitmap_t *frame_bitmap;

    frame_bitmap = frame_bitmap_create(MEMORY_LIMIT);

    /* Init page directory */
    current_page_dirt = kernel_page_dirt = page_directory_create();

    printf_vga_tk("Page AAA\n");

    /*
     * Map phys addr to virt addr from 0x0 to placement_ptr address
     * so we can access this transparently as if paging is not enabled
     */
    addr = 0;
    while (addr < MEMORY_LIMIT) {
        page_entry = page_directory_page_obtain(kernel_page_dirt, addr);
        page_entry_frame_set(page_entry, frame_allocate(frame_bitmap));

        addr += PAGE_SIZE;
    }

    printf_vga_tk("Page BBB\n");

    /* Enable paging */
    page_directory_switch(kernel_page_dirt);
}

