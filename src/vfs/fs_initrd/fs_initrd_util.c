static inline s_initrd_header_t *
fs_initrd_header(uint32 i)
{
    return &initrd_header_array[i];
}

static inline char *
fs_initrd_header_name(s_initrd_header_t *header)
{
    kassert(fs_initrd_header_legal_p(header));

    return header->name;
}

static inline bool
fs_initrd_header_legal_p(s_initrd_header_t *header)
{
    if (header == NULL) {
        return false;
    } else if (header->magic != INITRD_MAGIC) {
        return false;
    } else {
        return true;
    }
}

static inline uint32
fs_initrd_header_length(s_initrd_header_t *header)
{
    kassert(fs_initrd_header_legal_p(header));

    return header->length;
}

static inline uint32
fs_initrd_header_count(ptr_t location)
{
    kassert(location);

    return *(uint32 *)location;
}

static inline void
fs_initrd_header_set(ptr_t location)
{
    kassert(location);

    initrd_header_array = (void *)location;
}

static inline ptr_t
fs_initrd_addr_start(void)
{
    kassert(initrd_addr_start);

    return initrd_addr_start;
}

static inline void
fs_initrd_addr_start_set(ptr_t addr)
{
    kassert(addr);

    initrd_addr_start = addr;
}

