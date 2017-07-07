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

static inline uint32
multiboot_data_info_flag(void)
{
    kassert(multiboot_data_valid_p(MULTIBOOT_INFO));

    return multiboot_data.info.flags;
}

static inline bool
multiboot_data_info_flag_enabled_p(uint32 flag)
{
    uint32 flags;

    kassert(multiboot_data_valid_p(MULTIBOOT_INFO));

    flags = multiboot_data_info_flag();

    if ((flags & flag) == flag) {
        return true;
    } else {
        return false;
    }
}

static inline bool
multiboot_data_info_flag_disabled_p(uint32 flag)
{
    return !multiboot_data_info_flag_enabled_p(flag);
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

static inline ptr_t
multiboot_data_info_modules_addr_i(void)
{
    kassert(multiboot_data_valid_p(MULTIBOOT_INFO));

    return multiboot_data.info.mods_addr;
}

ptr_t
multiboot_data_info_modules_addr(void)
{
    if (multiboot_data_invalid_p(MULTIBOOT_INFO)) {
        KERNEL_PANIC("Invalid data of multiboot info.\n");
        return MEMORY_INVALID;
    } else {
        return multiboot_data_info_modules_addr_i();
    }
}

static inline uint32
multiboot_data_info_boot_modules_count_i(void)
{
    kassert(multiboot_data_valid_p(MULTIBOOT_INFO));

    return multiboot_data.info.mods_count;
}

static inline s_boot_module_t *
multiboot_data_info_boot_module(uint32 i)
{
    s_boot_module_t *module;

    kassert(i < multiboot_data_info_boot_modules_count_i());
    kassert(multiboot_data_info_flag_enabled_p(MULTIBOOT_FLAG_MODS));

    module = (void *)multiboot_data_info_modules_addr_i();

    return &module[i];
}

ptr_t
multiboot_data_info_boot_module_start(uint32 i)
{
    s_boot_module_t *module;

    kassert(i < multiboot_data_info_boot_modules_count_i());
    kassert(multiboot_data_info_flag_enabled_p(MULTIBOOT_FLAG_MODS));

    module = multiboot_data_info_boot_module(i);

    return module->module_start;
}

static inline ptr_t
multiboot_data_info_end_address(void)
{
    uint32 mods_count;
    s_boot_module_t *module;

    kassert(multiboot_data_valid_p(MULTIBOOT_INFO));

    mods_count = multiboot_data_info_boot_modules_count_i();

    if (mods_count == 0) {
        return (ptr_t)&end;
    } else if (multiboot_data_info_flag_disabled_p(MULTIBOOT_FLAG_MODS)) {
        return (ptr_t)&end;
    } else {
        module = multiboot_data_info_boot_module(mods_count - 1);

        return (ptr_t)module->module_end;
    }
}

uint32
multiboot_data_info_boot_modules_count(void)
{
    if (multiboot_data_invalid_p(MULTIBOOT_INFO)) {
        KERNEL_PANIC("Invalid data of multiboot info.\n");
        return COUNT_INVALID;
    } else {
        return multiboot_data_info_boot_modules_count_i();
    }
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

