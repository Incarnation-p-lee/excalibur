static inline void
multiboot_data_valid_set(uint32 i)
{
    kassert(i < MULTIBOOT_DATA_TYPE_LIMIT);

    multiboot_data.valid_mask |= 1u << i;
}

static inline bool
multiboot_data_valid_p(uint32 i)
{
    kassert(i < MULTIBOOT_DATA_TYPE_LIMIT);

    if (U32_BIT_GET(multiboot_data.valid_mask, i) == BIT_SET) {
        return true;
    } else {
        return false;
    }
}

static inline bool
multiboot_data_invalid_p(uint32 i)
{
    return !multiboot_data_valid_p(i);
}

static inline void
multiboot_data_header_initialize(s_multiboot_header_t *header)
{
    kassert(header);

    multiboot_data_valid_set(MULTIBOOT_HEADER);
    kmemory_copy(&multiboot_data.header, header, sizeof(*header));
}

static inline void
multiboot_data_info_initialize(s_multiboot_info_t *info)
{
    kassert(info);

    multiboot_data_valid_set(MULTIBOOT_INFO);
    kmemory_copy(&multiboot_data.info, info, sizeof(*info));
}

static inline uint32
multiboot_data_info_physical_memory_lower_i(void)
{
    kassert(multiboot_data_valid_p(MULTIBOOT_INFO));

    return multiboot_data.info.memory_lower; /* count in KB */
}

static inline uint32
multiboot_data_info_physical_memory_upper_i(void)
{
    kassert(multiboot_data_valid_p(MULTIBOOT_INFO));

    return multiboot_data.info.memory_upper; /* count in KB */
}

ptr_t
multiboot_data_info_physical_memory_lower(void)
{
    if (multiboot_data_invalid_p(MULTIBOOT_INFO)) {
        KERNEL_PANIC("Invalid data of multiboot info.\n");
        return MEMORY_INVALID;
    } else {
        return multiboot_data_info_physical_memory_lower_i();
    }
}

ptr_t
multiboot_data_info_physical_memory_upper(void)
{
    if (multiboot_data_invalid_p(MULTIBOOT_INFO)) {
        KERNEL_PANIC("Invalid data of multiboot info.\n");
        return MEMORY_INVALID;
    } else {
        return multiboot_data_info_physical_memory_upper_i();
    }
}

ptr_t
multiboot_data_info_physical_memory_limit(void)
{
    ptr_t page_mask;
    ptr_t memory_kb_limit;
    ptr_t memory_bytes_limit;

    if (multiboot_data_invalid_p(MULTIBOOT_INFO)) {
        KERNEL_PANIC("Invalid data of multiboot info.\n");
        return MEMORY_INVALID;
    } else {
        page_mask = PAGE_SIZE - 1;
        memory_kb_limit = multiboot_data_info_physical_memory_upper_i();
        memory_bytes_limit = memory_kb_limit * 1024;

        if ((memory_bytes_limit & page_mask) != 0) {
            memory_bytes_limit &= ~page_mask;
        }

        return memory_bytes_limit;
    }
}

