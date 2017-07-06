static inline s_initrd_header_t *
fs_initrd_header(uint32 i)
{
    return &initrd_header_array[i];
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

