static inline void *
kmalloc_int(uint32 sz, bool align, ptr_t *phys)
{
    void *retval;

    if (align && 0 != (placement_ptr & 0xfff)) {
        placement_ptr &= ((ptr_t)-1 << 12);
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

sint32
kheap_compare(void *a, void *b)
{
    struct kheap_header *ka;
    struct kheap_header *kb;

    kassert(NULL != a);
    kassert(NULL != b);

    ka = a;
    kb = b;

    if (ka->size < kb->size) {
        return 1;
    } else if (ka->size > kb->size) {
        return -1;
    } else {
        return 0;
    }
}

struct kheap *
kheap_create(ptr_t addr_start, ptr_t addr_end, ptr_t addr_max,
    bool supervisor, bool read_only)
{
    struct kheap *heap;
    struct kheap_header *hole;

    if (addr_start > addr_end || 0 == addr_max) {
        return NULL;
    } else if (0 != (addr_start & 0xfff)) {
        return NULL;
    } else if (0 != (addr_end & 0xfff)) {
        return NULL;
    } else {
        heap = kmalloc(sizeof(*heap));
        heap->idx = ordered_array_place((void *)addr_start, KHEAP_IDX_SIZE, &kheap_compare);
        addr_start += sizeof(void *) * KHEAP_IDX_SIZE;

        if (0 != (addr_start & 0xfff)) {
            addr_start &= ((ptr_t)-1 << 12);
            addr_start += PAGE_SIZE;
        }

        heap->addr_start = addr_start;
        heap->addr_end = addr_end;
        heap->addr_max = addr_max;
        heap->supervisor = supervisor;
        heap->read_only = read_only;

        hole = (void *)addr_start;
        hole->magic = KHEAP_MAGIC;
        hole->is_hole = true;
        hole->size = addr_end - addr_start;
        ordered_array_insert(&heap->idx, (void *)hole);
        // Fix-Me, no footer here ?

        return heap;
    }
}

uint32
kheap_find_minimal_hole(uint32 size, bool page_align, struct kheap *heap)
{
    uint32 i;
    sint32 offset;
    ptr_t location;
    struct kheap_header *header;

    kassert(0 != size);
    kassert(NULL != heap);

    i = 0;
    while (i < heap->idx.size) {
        header = (void *)ordered_array_lookup(&heap->idx, i);
        if (page_align) {
            location = (ptr_t)header;
            offset = PAGE_SIZE - (location + sizeof(*header)) % PAGE_SIZE;

            if (header->size >= offset + size) {
                return i;
            }
        } else if (header->size >= size) {
            return i;
        }
        i++;
    }

    return IDX_INVALID;
}

void
kheap_resize(struct kheap *heap, uint32 new_size)
{
    ptr_t i;
    struct page_entry *pe;

    kassert(NULL != heap);

    if (0 != (new_size & 0xfff)) {
        new_size &= ((ptr_t)-1 << 12);
        new_size += PAGE_SIZE;
    }

    i = heap->addr_end - heap->addr_start;
    kassert(0 == (i & 0xfff));

    if (new_size + heap->addr_start <= heap->addr_end) {
        kassert(new_size >= KHEAP_MIN_SIZE);

        while (new_size < i) {
            i -= PAGE_SIZE;
            pe = paging_get(heap->addr_start + i, false, kernel_dirt);
            frame_free(pe);
        }
    } else {
        kassert(new_size + heap->addr_start <= heap->addr_max);

        while (i < new_size) {
            pe = paging_get(heap->addr_start + i, true, kernel_dirt);
            frame_allocate(pe, heap->supervisor, !heap->read_only);
            i += PAGE_SIZE;
        }
    }

    kassert(i == new_size);
    heap->addr_end = heap->addr_start + new_size;
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

