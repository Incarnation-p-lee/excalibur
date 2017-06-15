static inline void *
memory_physical_allocate_i(uint32 sz, bool is_page_aligned)
{
    ptr_t page_mask;
    void *memory_phys;
    ptr_t memory_phys_limit;

    page_mask = PAGE_SIZE - 1;
    memory_phys_limit = multiboot_data_info_physical_memory_limit();

    if (is_page_aligned && 0 != (placement_phys & page_mask)) {
        placement_phys &= ~page_mask;
        placement_phys += PAGE_SIZE;
    }

    if (placement_phys + sz > memory_phys_limit) {
        return NULL;
    }

    memory_phys = (void *)placement_phys;
    placement_phys += sz;

    return memory_phys;
}

static inline void *
memory_physical_aligned_allocate(uint32 sz)
{
    kassert(sz);

    return memory_physical_allocate_i(sz, /* is_page_aligned = */true);
}

static inline void *
memory_physical_allocate(uint32 sz)
{
    kassert(sz);

    return memory_physical_allocate_i(sz, /* is_page_aligned = */false);
}

