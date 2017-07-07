static inline void *
memory_physical_allocate_i(uint32 sz, bool is_page_aligned)
{
    void *memory_phys;
    ptr_t memory_phys_limit;

    memory_phys_limit = multiboot_data_info_physical_memory_limit();

    if (is_page_aligned && PAGE_UNALIGNED_P(placement_phys)) {
        PAGE_ALIGN(placement_phys);
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

void
memory_physical_placement_set(ptr_t addr_phys)
{
    if (placement_phys == 0) {
        placement_phys = addr_phys;
        printf_vga_tk("Set physical memory placement -> %x.\n", addr_phys);
    }
}

