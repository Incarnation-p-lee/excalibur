static inline s_page_directory_t *
page_directory_create(void)
{
    s_page_directory_t *page_dirt;

    page_dirt = memory_physical_aligned_allocate(sizeof(*page_dirt));
    kmemset(page_dirt, 0, sizeof(*page_dirt));

    return page_dirt;
}

static inline s_page_table_t *
page_table_create(void)
{
    s_page_table_t *page_table;

    page_table = memory_physical_aligned_allocate(sizeof(s_page_table_t));
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
page_directory_page_table_phys_set(s_page_directory_t *page_dirt, uint32 i,
    ptr_t page_table_phys)
{
    s_page_entry_t *entry;

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
    entry = (s_page_entry_t *)&page_table_phys;
    page_entry_attribute_present_set(entry, /* is_presented = */true);
    page_entry_attribute_us_set(entry, /* is_user = */false);
    page_entry_attribute_rw_set(entry, /* is_writable = */true);

    page_dirt->table_array_phys[i] = page_table_phys;
}

static inline void
page_directory_page_table_set(s_page_directory_t *page_dirt, uint32 i,
    s_page_table_t *page_table)
{
    kassert(page_dirt);
    kassert(i < ARRAY_CNT_OF(page_dirt->table_array));

    page_dirt->table_array[i] = page_table;

    page_directory_page_table_phys_set(page_dirt, i, (ptr_t)page_table);
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
page_entry_get(ptr_t addr)
{
    return page_directory_page_entry_get(kernel_page_dirt, addr);
}

static inline s_page_entry_t *
page_directory_page_entry_get(s_page_directory_t *page_dirt, ptr_t addr)
{
    ptr_t i; /* table index */
    ptr_t k; /* page index */
    ptr_t frame;
    s_page_table_t *page_table;

    kassert(page_dirt);

    frame = addr / PAGE_SIZE;
    i = frame / PAGE_ENTRY_COUNT;
    k = frame % PAGE_ENTRY_COUNT;

    page_table = page_directory_page_table(page_dirt, i);
    kassert(page_table);

    return page_table_page_entry(page_table, k);
}

static inline s_page_entry_t *
page_directory_page_obtain(s_page_directory_t *page_dirt, ptr_t addr)
{
    ptr_t i; /* table index */
    ptr_t k; /* page index */
    ptr_t frame;
    s_page_table_t *page_table;

    kassert(page_dirt);

    frame = addr / PAGE_SIZE;
    i = frame / PAGE_ENTRY_COUNT;
    k = frame % PAGE_ENTRY_COUNT;

    page_table = page_directory_page_table(page_dirt, i);

    if (page_table == NULL) {
        page_table = page_table_create();
        page_directory_page_table_set(page_dirt, i, page_table);
    }

    return page_table_page_entry(page_table, k);
}

static inline void
page_directory_switch(s_page_directory_t *page_dirt)
{
    kassert(page_dirt);

    current_page_dirt = page_dirt;

    asm volatile (
        "mov %0,          %%cr3\n\t"
        "mov %%cr0,       %%eax\n\t"
        "or  $0x80000000, %%eax\n\t"
        "mov %%eax,       %%cr0\n\t"
        :
        :"r"(&page_dirt->table_array_phys)
        :"eax");

    printf_vga_tk("Page initialized.\n");
    multiboot_env_cpu_detect();
}

static inline void
page_entry_initialize(s_page_entry_t *page_entry, ptr_t frame, bool is_user,
    bool is_writable)
{
    kassert(page_entry);

    page_entry_frame_set(page_entry, frame);

    page_entry_attribute_us_set(page_entry, is_user);
    page_entry_attribute_rw_set(page_entry, is_writable);
    page_entry_attribute_present_set(page_entry, /* is_presented = */true);
}

static inline s_page_entry_t *
page_allocate(ptr_t addr, bool is_user, bool is_writable)
{
    ptr_t frame;
    s_page_entry_t *page_entry;

    frame = frame_allocate();
    page_entry = page_directory_page_obtain(kernel_page_dirt, addr);

    page_entry_initialize(page_entry, frame, is_user, is_writable);

    return page_entry;
}

static inline void
page_free(ptr_t addr)
{
    ptr_t frame;
    ptr_t bit_idx;
    ptr_t mask_idx;
    s_page_entry_t *page_entry;

    page_entry = page_directory_page_entry_get(kernel_page_dirt, addr);
    frame = page_entry->frame;

    mask_idx = frame_bitmap_frame_mask_index(frame_bitmap, frame);
    bit_idx = frame_bitmap_frame_bit_index(frame_bitmap, frame);

    frame_bitmap_mask_clear(frame_bitmap, mask_idx, bit_idx);
}

static inline void
page_enabled_range_print(ptr_t addr_start, ptr_t addr_end)
{
    printf_vga_tk("Page enabled from %x -> %x.\n", addr_start, addr_end);
}

void
page_initialize(void)
{
    ptr_t addr;
    ptr_t memory_phys_limit;

    memory_phys_limit = multiboot_data_info_physical_memory_limit();
    frame_bitmap = frame_bitmap_create(memory_phys_limit);
    kernel_heap = memory_physical_allocate(sizeof(*kernel_heap));
    current_page_dirt = kernel_page_dirt = page_directory_create();
    /*
     * Allocate page entry without frame, leave the frame from 0x0 to
     * placement_phys maps to page 0x0 to placement_phys in virtual memory.
     * So we can access this transparently as if paging is not enabled
     */
    addr = KHEAP_START;
    while (addr < KHEAP_LIMIT) {
        page_directory_page_obtain(kernel_page_dirt, addr);

        addr += PAGE_SIZE;
    }

    addr = 0;
    page_enabled_range_print(addr, placement_phys + PAGE_SIZE);
    while (addr < placement_phys + PAGE_SIZE) {
        /* is_user = false, is_writable = true */
        page_allocate(addr, false, true);

        addr += PAGE_SIZE;
    }

    /* Now allocate frame for heap */
    addr = KHEAP_START;
    page_enabled_range_print(addr, KHEAP_START + KHEAP_INITIAL_SIZE);
    while (addr < KHEAP_START + KHEAP_INITIAL_SIZE) {
        /* is_user = false, is_writable = true */
        page_allocate(addr, false, true);

        addr += PAGE_SIZE;
    }

    /* Enable paging */
    page_directory_switch(kernel_page_dirt);
}

static inline void
page_align_i(ptr_t *addr)
{
    kassert(addr);

    if (PAGE_ALIGNED_P(*addr)) {
        return;
    } else {
        PAGE_ALIGN(*addr);
    }
}

void
page_align(ptr_t *addr)
{
    if (addr == NULL) {
        return;
    } else {
        page_align_i(addr);
    }
}


