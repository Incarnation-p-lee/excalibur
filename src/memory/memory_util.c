/*
 * for convention, a word idicate 16 bit
 */
static inline uint32
memory_set_fill_dword_element(uint8 v)
{
    uint32 element;
    uint8 *tmp;

    tmp = (uint8 *)&element;
    tmp[0] = v;
    tmp[1] = v;
    tmp[2] = v;
    tmp[3] = v;

    return element;
}

static inline void
memory_set_in_byte(void *base, uint8 v, uint32 len)
{
    assert_k(base);
    assert_k(len);

    while (len--) {
        *(uint8 *)base = v;
        base++;
    }
}

static inline void
memory_copy_in_byte(void *to, void *from, uint32 len)
{
    assert_k(to);
    assert_k(from);
    assert_k(len);

    while (len--) {
        *(uint8 *)to++ = *(uint8 *)from++;
    }
}

static inline void
memory_set_in_dword(uint32 *base, uint8 v, uint32 len)
{
    uint32 element;
    uint32 remainder;
    uint32 cnt;

    assert_k(base);
    assert_k(len);

    remainder = len % sizeof(element);

    if (len > remainder) {
        cnt = len / sizeof(element);
        element = memory_set_fill_dword_element(v);

        while (cnt--) {
            *base = element;
            base++;
        }
    }

    if (remainder) {
        memory_set_in_byte(base, v, remainder);
    }
}

static inline void
memory_copy_in_dword(uint32 *to, uint32 *from, uint32 len)
{
    uint32 remainder;
    uint32 cnt;

    assert_k(to);
    assert_k(from);
    assert_k(len);

    remainder = len % sizeof(remainder);
    if (len > remainder) {
        cnt = len / sizeof(remainder);

        while (cnt--) {
            *to++ = *from++;
        }
    }

    if (remainder) {
        memory_copy_in_byte(to, from, remainder);
    }
}

void
kmemset(void *base, uint8 v, uint32 len)
{
    if (base && len > 0) {
        memory_set_in_dword(base, v, len);
    }
}

void
memory_copy_k(void *to, void *from, uint32 len)
{
    if (to && from && len > 0) {
        if (from + len > to && from < to) {
            printf_vga("Need tmp memory for memory copy, not implemented.\n");
        } else {
            memory_copy_in_dword(to, from, len);
        }
    }
}

