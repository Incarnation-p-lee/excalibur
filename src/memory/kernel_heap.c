static inline bool
kernel_heap_legal_p(s_kernel_heap_t *heap)
{
    if (heap == NULL) {
        return false;
    } else if (ordered_array_illegal_p(&heap->ordered)) {
        return false;
    } else if (heap->addr_start > heap->addr_end) {
        return false;
    } else if (heap->addr_end > heap->addr_limit) {
        return false;
    } else {
        return true;
    }
}

static inline ptr_t
kernel_heap_addr_start(s_kernel_heap_t *heap)
{
    kassert(kernel_heap_legal_p(heap));

    return heap->addr_start;
}

static inline ptr_t
kernel_heap_addr_end(s_kernel_heap_t *heap)
{
    kassert(kernel_heap_legal_p(heap));

    return heap->addr_end;
}

static inline void
kernel_heap_addr_end_set(s_kernel_heap_t *heap, ptr_t addr_end)
{
    kassert(kernel_heap_legal_p(heap));

    heap->addr_end = addr_end;
}

static inline ptr_t
kernel_heap_last_hole_addr(s_kernel_heap_t *heap)
{
    kassert(kernel_heap_legal_p(heap));

    return heap->last_hole_addr;
}

static inline bool
kernel_heap_illegal_p(s_kernel_heap_t *heap)
{
    return !kernel_heap_legal_p(heap);
}

static inline s_ordered_array_t *
kernel_heap_ordered_array(s_kernel_heap_t *heap)
{
    kassert(kernel_heap_legal_p(heap));

    return &heap->ordered;
}

static inline bool
kernel_heap_header_legal_p(s_kernel_heap_header_t *header)
{
    if (header == NULL) {
        return false;
    } else if (header->size == 0) {
        return false;
    } else if (header->magic != KHEAP_MAGIC) {
        return false;
    } else {
        return true;
    }
}

static inline bool
kernel_heap_header_illegal_p(s_kernel_heap_header_t *header)
{
    return !kernel_heap_header_legal_p(header);
}

static inline bool
kernel_heap_footer_legal_p(s_kernel_heap_footer_t *footer)
{
    if (footer == NULL) {
        return false;
    } else if (footer->header == NULL) {
        return false;
    } else if (footer->magic != KHEAP_MAGIC) {
        return false;
    } else {
        return true;
    }
}

static inline bool
kernel_heap_footer_illegal_p(s_kernel_heap_footer_t *footer)
{
    return !kernel_heap_footer_legal_p(footer);
}

static inline ptr_t
kernel_heap_hole_usable_limit(s_kernel_heap_header_t *header)
{
    ptr_t limit;
    ptr_t hole_size;

    kassert(kernel_heap_header_legal_p(header));

    hole_size = (ptr_t)kernel_heap_hole_size(header);
    limit = hole_size + (ptr_t)header - (ptr_t)KHEAP_FOOTER_SIZE;

    return limit;
}

static inline bool
kernel_heap_is_user_p(s_kernel_heap_t *heap)
{
    kassert(kernel_heap_legal_p(heap));

    return heap->is_user;
}

static inline bool
kernel_heap_is_writable_p(s_kernel_heap_t *heap)
{
    kassert(kernel_heap_legal_p(heap));

    return heap->is_writable;
}

static inline bool
kernel_heap_header_is_hole_p(s_kernel_heap_header_t *header)
{
    kassert(kernel_heap_header_legal_p(header));

    return header->is_hole;
}

static inline bool
kernel_heap_header_is_not_hole_p(s_kernel_heap_header_t *header)
{
    return !kernel_heap_header_is_hole_p(header);
}

static inline void
kernel_heap_header_is_hole_set(s_kernel_heap_header_t *header, bool is_hole)
{
    kassert(kernel_heap_header_legal_p(header));

    header->is_hole = is_hole;
}

static inline s_kernel_heap_footer_t *
kernel_heap_header_to_left_footer(s_kernel_heap_header_t *header)
{
    s_kernel_heap_footer_t *last_footer;

    kassert(kernel_heap_header_legal_p(header));

    last_footer = (void *)((ptr_t)header - (ptr_t)KHEAP_FOOTER_SIZE);

    return last_footer;
}

static inline s_kernel_heap_header_t *
kernel_heap_footer_to_right_header(s_kernel_heap_footer_t *footer)
{
    s_kernel_heap_header_t *right_header;

    kassert(kernel_heap_footer_legal_p(footer));

    right_header = (void *)((ptr_t)footer + (ptr_t)KHEAP_FOOTER_SIZE);

    return right_header;
}

static inline bool
kernel_heap_header_magic_valid_p(s_kernel_heap_header_t *header)
{
    kassert(kernel_heap_header_legal_p(header));

    if (header->magic == KHEAP_MAGIC) {
        return true;
    } else {
        return false;
    }
}

static inline bool
kernel_heap_header_magic_invalid_p(s_kernel_heap_header_t *header)
{
    return !kernel_heap_header_magic_valid_p(header);
}

static inline ptr_t
kernel_heap_size(s_kernel_heap_t *heap)
{
    kassert(kernel_heap_legal_p(heap));

    return heap->addr_end - heap->addr_start;
}

static inline sint32
kernel_heap_compare(void *a, void *b)
{
    uint32 size_a;
    uint32 size_b;

    kassert(a);
    kassert(b);

    size_a = kernel_heap_hole_size(a);
    size_b = kernel_heap_hole_size(b);

    if (size_a < size_b) {
        return 1;
    } else if (size_a > size_b) {
        return -1;
    } else {
        return 0;
    }
}

static inline void
kernel_heap_initialize_i(s_kernel_heap_t *heap, ptr_t addr_start,
    ptr_t addr_end, ptr_t addr_limit)
{
    uint32 bytes_count;
    s_ordered_array_t *ordered;
    s_kernel_heap_header_t *header;

    kassert(heap);
    kassert(addr_start < addr_end);
    kassert(addr_limit > 0 && addr_limit > addr_end);
    kassert(PAGE_ALIGNED_P(addr_start));
    kassert(PAGE_ALIGNED_P(addr_end));
    kassert(PAGE_ALIGNED_P(addr_limit));

    ordered = &heap->ordered; /* heap is not initialized here */
    addr_start = (ptr_t)ordered_array_place(ordered, (void *)addr_start,
        KHEAP_HOLE_COUNT, &kernel_heap_compare);

    page_align_i(&addr_start);

    heap->addr_start = addr_start;
    heap->addr_end = addr_end;
    heap->addr_limit = addr_limit;
    heap->is_user = false;
    heap->is_writable = true;

    bytes_count = (uint32)(addr_end - addr_start);
    header = kernel_heap_hole_make((void *)addr_start, bytes_count);
    ordered_array_insert(ordered, header);
}

static inline ptr_t
kernel_heap_hole_size(s_kernel_heap_header_t *header)
{
    kassert(kernel_heap_header_legal_p(header));

    return header->size;
}

static inline ptr_t
kernel_heap_hole_usable_size(s_kernel_heap_header_t *header)
{
    kassert(kernel_heap_header_legal_p(header));

    return kernel_heap_hole_size(header) - KHEAP_INFO_SIZE;
}

static inline s_kernel_heap_header_t *
kernel_heap_minimal_hole_obtain(s_kernel_heap_t *heap, uint32 request_size,
    ptr_t *usable_addr)
{
    uint32 i, limit;
    ptr_t hole_addr;
    uint32 hole_size;
    s_ordered_array_t *ordered;
    s_kernel_heap_header_t *header;

    kassert(kernel_heap_legal_p(heap));
    kassert(request_size);
    kassert(usable_addr);

    i = 0;
    ordered = kernel_heap_ordered_array(heap);
    limit = ordered_array_limit(ordered);

    while (i < limit) {
        header = ordered_array_value(ordered, i);
        hole_addr = (ptr_t)header;
        hole_size = KHEAP_INFO_SIZE + request_size;

        if (hole_size <= kernel_heap_hole_size(header)) {
            *usable_addr = hole_addr + (ptr_t)KHEAP_HEADER_SIZE;
            ordered_array_remove(ordered, i);

            return header;
        }

        i++;
    }

    *usable_addr = ADDR_INVALID;
    return PTR_INVALID;
}

static inline bool
kernel_heap_hole_legal_p(void *hole_addr)
{
    s_kernel_heap_header_t *header;
    s_kernel_heap_footer_t *footer;

    kassert(hole_addr);

    header = hole_addr;
    footer = kernel_heap_header_to_footer(header);

    if (footer->magic != KHEAP_MAGIC) {
        return false;
    } else if (header->magic != KHEAP_MAGIC) {
        return false;
    } else if (footer->header != header) {
        return false;
    } else {
        return true;
    }
}

static inline s_kernel_heap_header_t *
kernel_heap_hole_make(void *hole_addr, uint32 size)
{
    uint32 bytes_count;
    s_kernel_heap_header_t *header;
    s_kernel_heap_footer_t *footer;

    kassert(hole_addr);
    kassert(size >= KHEAP_HOLE_MIN_SIZE);

    header = hole_addr;
    bytes_count = size - KHEAP_FOOTER_SIZE;
    footer = (void *)((ptr_t)hole_addr + bytes_count);

    header->magic = KHEAP_MAGIC;
    header->is_hole = true;
    header->size = size;

    footer->magic = KHEAP_MAGIC;
    footer->header = header;

    return header;
}

static inline void
kernel_heap_block_make(void *hole_addr, uint32 size)
{
    s_kernel_heap_header_t *hole_header;

    kassert(hole_addr);
    kassert(size >= KHEAP_HOLE_MIN_SIZE);

    hole_header = kernel_heap_hole_make(hole_addr, size);
    kernel_heap_header_is_hole_set(hole_header, /* is_hole = */false);
}

static inline uint32
kernel_heap_hole_rear_size(s_kernel_heap_header_t *header, uint32 req_size)
{
    ptr_t usable_addr;
    ptr_t usable_limit;

    kassert(kernel_heap_header_legal_p(header));

    usable_addr = (ptr_t)header + KHEAP_HEADER_SIZE;
    usable_limit = (ptr_t)kernel_heap_hole_usable_limit(header);

    return (uint32)(usable_limit - usable_addr - (ptr_t)req_size);
}

/*
 *       usable_addr
 *          |
 * |        |                       | <-   rear size   -> |
 * +--------+----------+------------+------------+--------+
 * | header | req_size | new footer | free space | footer |
 * +--------+----------+------------+------------+--------+
 *                                               |
 *                                           usable_limit
 *
 * WE decide to make allocate simple and do not handle alignment here. So the
 * usable_addr should be located after header immediately.
 */
static inline void
kernel_heap_hole_split(s_kernel_heap_header_t *header, uint32 req_size,
    s_ordered_array_t *ordered)
{
    ptr_t hole_addr, addr_start;
    uint32 hole_size, rear_size;

    kassert(req_size);
    kassert(ordered_array_legal_p(ordered));
    kassert(kernel_heap_header_legal_p(header));

    hole_size = kernel_heap_hole_size(header);
    hole_addr = (ptr_t)header;
    rear_size = kernel_heap_hole_rear_size(header, req_size);

    if (rear_size >= KHEAP_HOLE_MIN_SIZE) {
        addr_start = hole_addr + (ptr_t)(hole_size - rear_size);

        kernel_heap_hole_make((void *)addr_start, rear_size);
        ordered_array_insert(ordered, (void *)addr_start);

        hole_size -= rear_size;
    }

    kernel_heap_block_make((void *)hole_addr, hole_size);
}

static inline void
kernel_heap_expand(s_kernel_heap_t *heap, uint32 expand_size)
{
    uint32 hole_size;
    bool is_user, is_writable;
    s_page_entry_t *page_entry;
    ptr_t addr, frame, addr_limit;
    s_kernel_heap_header_t *header, *left_header;

    kassert(expand_size);
    kassert(kernel_heap_legal_p(heap));

    page_align_i(&expand_size);

    header = (void *)(addr = kernel_heap_addr_end(heap));
    addr_limit = addr + expand_size;

    is_user = kernel_heap_is_user_p(heap);
    is_writable = kernel_heap_is_writable_p(heap);

    while (addr < addr_limit) {
        frame = frame_allocate();
        page_entry = page_entry_get(addr);
        page_entry_initialize(page_entry, frame, is_user, is_writable);

        addr += PAGE_SIZE;
    }

    kernel_heap_addr_end_set(heap, kernel_heap_addr_start(heap) + expand_size);

    kernel_heap_hole_make(header, expand_size);
    left_header = kernel_heap_header_left_unify(header);

    if (left_header) {
        header = left_header;
        hole_size = kernel_heap_hole_size(left_header) + expand_size;
        kernel_heap_hole_make(header, hole_size);
    }

    ordered_array_insert(kernel_heap_ordered_array(heap), header);
}

static inline void
kernel_heap_contract(s_kernel_heap_t *heap, uint32 new_size)
{
    ptr_t addr;
    uint32 heap_size;

    kassert(kernel_heap_legal_p(heap));
    kassert(new_size < kernel_heap_size(heap));

    page_align_i(&new_size);

    heap_size = kernel_heap_size(heap);
    addr = kernel_heap_addr_end(heap);

    while (new_size < heap_size) {
        addr -= PAGE_SIZE;
        page_free(addr);

        heap_size -= PAGE_SIZE;
    }

    kernel_heap_addr_end_set(heap, kernel_heap_addr_start(heap) + new_size);
}

static inline void *
kernel_heap_allocate(s_kernel_heap_t *heap, uint32 req_size)
{
    uint32 expand_size;
    ptr_t usable_addr;
    s_ordered_array_t *ordered;
    s_kernel_heap_header_t *header;

    kassert(req_size);
    kassert(kernel_heap_legal_p(heap));

    if (req_size < KHEAP_USER_MIN_SIZE) {
        req_size = KHEAP_USER_MIN_SIZE;
    }

    ordered = kernel_heap_ordered_array(heap);
    header = kernel_heap_minimal_hole_obtain(heap, req_size, &usable_addr);

    if (header == PTR_INVALID) { /* no suitable hole */
        expand_size = KHEAP_HOLE_SIZE(req_size);
        kernel_heap_expand(heap, expand_size);
        header = kernel_heap_minimal_hole_obtain(heap, req_size, &usable_addr);

        kassert(header != PTR_INVALID);
    }

    kernel_heap_hole_split(header, req_size, ordered);

    return (void *)usable_addr;
}

static inline s_kernel_heap_footer_t *
kernel_heap_header_to_footer(s_kernel_heap_header_t *header)
{
    ptr_t hole_size;
    ptr_t footer_addr;

    kassert(kernel_heap_header_legal_p(header));

    hole_size = (ptr_t)kernel_heap_hole_size(header);
    footer_addr = (ptr_t)header + hole_size - KHEAP_FOOTER_SIZE;

    return (void *)footer_addr;
}

static inline s_kernel_heap_header_t *
kernel_heap_footer_to_header(s_kernel_heap_footer_t *footer)
{
    kassert(kernel_heap_footer_legal_p(footer));

    return footer->header;
}

static inline s_kernel_heap_header_t *
kernel_heap_header_left_unify(s_kernel_heap_header_t *header)
{
    s_kernel_heap_header_t *left_header;
    s_kernel_heap_footer_t *left_footer;

    kassert(kernel_heap_header_legal_p(header));

    left_footer = kernel_heap_header_to_left_footer(header);

    if (kernel_heap_footer_illegal_p(left_footer)) {
        return NULL;
    }

    left_header = kernel_heap_footer_to_header(left_footer);

    if (kernel_heap_header_illegal_p(left_header)) {
        return NULL;
    }

    if (kernel_heap_header_is_not_hole_p(left_header)) {
        return NULL;
    } else {
        return left_header;
    }
}

static inline s_kernel_heap_header_t *
kernel_heap_footer_right_unify(s_kernel_heap_footer_t *footer)
{
    s_kernel_heap_header_t *right_header;
    s_kernel_heap_footer_t *right_footer;

    kassert(kernel_heap_footer_legal_p(footer));

    right_header = kernel_heap_footer_to_right_header(footer);

    if (kernel_heap_header_illegal_p(right_header)) {
        return NULL;
    }

    right_footer = kernel_heap_header_to_footer(right_header);

    if (kernel_heap_footer_illegal_p(right_footer)) {
        return NULL;
    }

    if (kernel_heap_header_is_not_hole_p(right_header)) {
        return NULL;
    } else {
        return right_header;
    }
}

static inline void
kernel_heap_hole_remove(s_kernel_heap_t *heap, s_kernel_heap_header_t *header)
{
    uint32 i;
    uint32 limit;
    s_ordered_array_t *ordered;

    kassert(kernel_heap_legal_p(heap));
    kassert(kernel_heap_header_legal_p(header));

    i = 0;
    ordered = kernel_heap_ordered_array(heap);
    limit = ordered_array_limit(ordered);

    while (i < limit) {
        if (header == ordered_array_value(ordered, i)) {
            ordered_array_remove(ordered, i);
            return;
        }

        i++;
    }
}

static inline void
kernel_heap_free(s_kernel_heap_t *heap, void *val)
{
    void *hole_addr;
    uint32 hole_size;
    s_kernel_heap_footer_t *footer;
    s_kernel_heap_header_t *header, *left_header, *right_header;

    kassert(val);
    kassert(kernel_heap_legal_p(heap));

    header = KHEAP_USER_TO_HEADER(val);
    footer = kernel_heap_header_to_footer(header);

    hole_size = kernel_heap_hole_size(header);
    kernel_heap_header_is_hole_set(header, /* is_hole = */true);

    left_header = kernel_heap_header_left_unify(header);
    right_header = kernel_heap_footer_right_unify(footer);

    if (left_header && right_header) {
        hole_addr = left_header;
        hole_size += kernel_heap_hole_size(left_header);
        hole_size += kernel_heap_hole_size(right_header);

        kernel_heap_hole_remove(heap, right_header);
        kernel_heap_hole_make((void *)hole_addr, hole_size);
    } else if (left_header) {
        hole_addr = left_header;
        hole_size += kernel_heap_hole_size(left_header);

        kernel_heap_hole_make(hole_addr, hole_size);
    } else if (right_header) {
        hole_addr = header;
        hole_size += kernel_heap_hole_size(right_header);

        kernel_heap_hole_remove(heap, right_header);
        kernel_heap_hole_make(hole_addr, hole_size);
        ordered_array_insert(kernel_heap_ordered_array(heap), hole_addr);
    } else {
        hole_addr = header;

        header = kernel_heap_hole_make(hole_addr, hole_size);
        ordered_array_insert(kernel_heap_ordered_array(heap), header);
    }
}

static inline void *
kernel_heap_realloc(s_kernel_heap_t *heap, void *val, uint32 new_size)
{
    void *new_val;
    uint32 usable_size;
    s_ordered_array_t *ordered;
    s_kernel_heap_header_t *header;

    kassert(val);
    kassert(new_size);
    kassert(kernel_heap_legal_p(heap));

    header = KHEAP_USER_TO_HEADER(val);
    usable_size = kernel_heap_hole_usable_size(header);

    if (new_size + KHEAP_HOLE_MIN_SIZE <= usable_size) {
        ordered = kernel_heap_ordered_array(heap);

        kernel_heap_hole_split(header, new_size, ordered);

        return val;
    } else if (new_size > usable_size) {
        new_val = kernel_heap_allocate(heap, new_size);

        kmemory_copy_i(new_val, val, new_size);
        kernel_heap_free(heap, val);

        return new_val;
    } else {
        return val;
    }
}

void
kernel_heap_initialize(void)
{
    /*
     * Assume we create the page table from KHEAP_START to
     * KHEAP_START + KHEAP_INITIAL_SIZE in page_initialize.
     */
    if (kernel_heap != NULL) {
        kernel_heap_initialize_i(kernel_heap, KHEAP_START,
            KHEAP_START + KHEAP_INITIAL_SIZE, KHEAP_LIMIT);

        printf_vga_tk("Heap initialized.\n");
    }
}

void *
kmalloc(uint32 request_size)
{
    if (kernel_heap_illegal_p(kernel_heap)) {
        return PTR_INVALID;
    } else if (request_size == 0) {
        return PTR_INVALID;
    } else {
        return kernel_heap_allocate(kernel_heap, request_size);
    }
}

void
kfree(void *ptr)
{
    if (ptr == NULL) {
        return;
    } else if (kernel_heap_illegal_p(kernel_heap)) {
        return;
    } else {
        kernel_heap_free(kernel_heap, ptr);
    }
}

void *
krealloc(void *ptr, uint32 new_size)
{
    if (ptr == NULL) {
        return PTR_INVALID;
    } else if (new_size == 0) {
        return PTR_INVALID;
    } else {
        return kernel_heap_realloc(kernel_heap, ptr, new_size);
    }
}

