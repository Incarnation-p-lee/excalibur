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
    // assert(NULL != base);

    while (len--) {
        *(uint8 *)base = v;
        base++;
    }
}

static inline void
memory_set_in_dword(uint32 *base, uint8 v, uint32 len)
{
    uint32 element;
    uint32 remainder;
    uint32 cnt;

    // assert(NULL != base);
    // assert(0 != len);

    remainder = len % sizeof(element);

    if (len > remainder) {
        cnt = len / sizeof(element);
        element = memory_set_fill_dword_element(v);

        while (cnt--) {
            *base = element;
            base++;
        }
    }

    memory_set_in_byte(base, v, remainder);
}

void
memory_set_k(void *base, uint8 v, uint32 len)
{
    if (base) {
        memory_set_in_dword(base, v, len);
    }
}
