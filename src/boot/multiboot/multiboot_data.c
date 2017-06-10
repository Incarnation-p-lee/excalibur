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

    if (U32_BIT(multiboot_data.valid_mask, i) == BIT_SET) {
        return true;
    } else {
        return false;
    }
}

void
multiboot_data_header_initialize(s_multiboot_header_t *header)
{
    if (header) {
        kmemory_copy(&multiboot_data.header, header, sizeof(*header));
    }
}

void
multiboot_data_info_initialize(s_multiboot_info_t *info)
{
    if (info) {
        kmemory_copy(&multiboot_data.info, info, sizeof(*info));
    }
}

