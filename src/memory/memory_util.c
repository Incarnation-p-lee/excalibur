/*
 * for convention, a word idicate 16 bit
 */
static inline uint32
memory_byte_to_dword_fill(uint8 val)
{
    uint32 element;
    uint8 *tmp;

    tmp = (uint8 *)&element;
    tmp[0] = val;
    tmp[1] = val;
    tmp[2] = val;
    tmp[3] = val;

    return element;
}

static inline uint32
memory_word_to_dword_fill(uint16 val)
{
    uint16 *tmp;
    uint32 element;

    tmp = (void *)&element;

    tmp[0] = val;
    tmp[1] = val;

    return element;
}

static inline void
memory_byte_copy(uint8 *to, uint8 *from, uint32 len)
{
    uint32 i;

    kassert(to);
    kassert(from);
    kassert(len);

    i = 0;

    while (i < len) {
        *to++ = *from++;
        i++;
    }
}

static inline void *
memory_dword_set(uint32 *base, uint32 val, uint32 len)
{
    uint32 i;

    kassert(base);
    kassert(len);

    i = 0;

    while (i < len) {
        *base++ = val;
        i++;
    }

    return base;
}

static inline void *
memory_word_set(uint16 *base, uint16 val, uint32 len)
{
    uint32 i;

    kassert(base);
    kassert(len);

    i = 0;

    while (i < len) {
        *base++ = val;
        i++;
    }

    return base;
}

static inline void
memory_byte_set(uint8 *base, uint8 val, uint32 len)
{
    uint32 i;

    kassert(base);
    kassert(len);

    i = 0;

    while (i < len) {
        *base++ = val;
        i++;
    }
}

static inline void
kmemset_i(void *base, uint8 val, uint32 len)
{
    uint32 count;
    uint32 element;
    uint32 reminder;

    kassert(base);
    kassert(len);

    count = len / sizeof(uint32);
    reminder = len % sizeof(uint32);
    element = memory_byte_to_dword_fill(val);

    if (count) {
        base = memory_dword_set(base, element, count);
    }

    if (reminder) {
        memory_byte_set(base, val, reminder);
    }
}

void
kmemset(void *base, uint8 v, uint32 len)
{
    if (base == NULL) {
        return;
    } else if (len == 0) {
        return;
    } else {
        kmemset_i(base, v, len);
    }
}

static inline void
kmemset_u16_i(void *base, uint16 val, uint32 len)
{
    uint32 count;
    uint32 element;
    uint32 reminder;

    kassert(base);
    kassert(len);

    count = len / sizeof(val);
    reminder = len % sizeof(val);
    element = memory_word_to_dword_fill(val);

    if (count) {
        base = memory_dword_set(base, element, count);
    }

    if (reminder) {
        memory_word_set(base, val, reminder);
    }
}

static inline uint32
memory_dword_copy(uint32 *to, uint32 *from, uint32 len)
{
    uint32 i;
    uint32 bytes_count;

    kassert(to);
    kassert(from);

    i = 0;

    while (i < len) {
        *to++ = *from++;
        i++;
    }

    bytes_count = len * sizeof(uint32);

    return bytes_count;
}

static inline void
kmemory_copy_i(void *to, void *from, uint32 len)
{
    uint32 count;
    uint32 offset;
    uint32 reminder;

    kassert(to);
    kassert(from);
    kassert(len);

    count = len / sizeof(uint32);
    reminder = len % sizeof(uint32);

    if (count) {
        offset = memory_dword_copy(to, from, count);
        to = (void *)((ptr_t)to + (ptr_t)offset);
        from = (void *)((ptr_t)from + (ptr_t)offset);
    }

    if (reminder) {
        memory_byte_copy(to, from, reminder);
    }
}

void
kmemset_u16(void *base, uint16 val, uint32 len)
{
    if (base == NULL) {
        return;
    } else if (len == 0) {
        return;
    } else {
        kmemset_u16_i(base, val, len);
    }
}

void
kmemory_copy(void *to, void *from, uint32 len)
{
    if (to == NULL) {
        return;
    } else if (from == NULL) {
        return;
    } else if (len == 0) {
        return;
    } else if (from + len > to && from < to) {
        printf_vga("Need tmp memory for memory copy, not implemented.\n");
    } else {
        kmemory_copy_i(to, from, len);
    }
}

