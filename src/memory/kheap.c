static inline void *
kmalloc_int(uint32 sz, bool align, ptr_t *phys)
{
    void *retval;

    if (align && (placement_ptr & 0xFFFFF000)) {
        placement_ptr &= 0xFFFFF000;
        placement_ptr += 0x1000;
    }

    if (placement_ptr + sz > MEMORY_LIMIT) {
        return NULL;
    } else if (phys) {
        *phys = placement_ptr;
    }

    retval = (void *)placement_ptr;
    placement_ptr += sz;

    return retval;
}

void *
kmalloc(uint32 sz)
{
    return kmalloc_int(sz, false, NULL);
}

void *
kmalloc_algn(uint32 sz)
{
    return kmalloc_int(sz, true, NULL);
}

void *
kmalloc_phys(uint32 sz, ptr_t *phys)
{
    return kmalloc_int(sz, false, phys);
}

void *
kmalloc_algn_with_phys(uint32 sz, ptr_t *phys)
{
    return kmalloc_int(sz, true, phys);
}

