static inline void *
kmalloc_int(uint32 sz, uint32 align, uint32 *phys)
{
    uint32 retval;

    if (KM_ALIGNED == align && (placement_ptr & 0xFFFFF000)) {
        placement_ptr &= 0xFFFFF000;
        placement_ptr += 0x1000;
    }

    if (phys) {
        *phys = placement_ptr;
    }

    retval = placement_ptr;
    placement_ptr += sz;

    return retval;
}

void *
kmalloc(uint32 sz)
{
    return kmalloc_int(sz, KM_DEFAULT, NULL);
}

void *
kmalloc_algn(uint32 sz)
{
    return kmalloc_int(sz, KM_ALIGNED, NULL);
}

void *
kmalloc_phys(uint32 sz, uint32 *phys)
{
    return kmalloc_int(sz, KM_DEFAULT, phys);
}

void *
kmalloc_algn_with_phys(uint32 sz, uint32 *phys)
{
    return kmalloc_int(sz, KM_ALIGNED, phys);
}

