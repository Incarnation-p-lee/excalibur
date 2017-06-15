// static inline bool
// kheap_legal_p(s_kheap_t *heap)
// {
//     if (NULL == heap) {
//         return false;
//     } else if (!ordered_array_legal_p(&heap->ordered)) {
//         return false;
//     } else if (heap->addr_start > heap->addr_end) {
//         return false;
//     } else if (heap->addr_end > heap->addr_max) {
//         return false;
//     } else {
//         return true;
//     }
// }
// 
// static inline ptr_t
// kheap_size(s_kheap_t *heap)
// {
//     kassert(kheap_legal_p(heap));
//     return heap->addr_end - heap->addr_start;
// }
// 
// static inline uint32
// kheap_find_hole(s_kheap_t *heap, void *val)
// {
//     uint32 i;
// 
//     kassert(NULL != val);
//     kassert(kheap_legal_p(heap));
// 
//     i = 0;
//     while (i < heap->ordered.size) {
//         if (val == ordered_array_lookup(&heap->ordered, i)) {
//             return i;
//         }
//         i++;
//     }
// 
//     return IDX_INVALID;
// }
// 
// static inline sint32
// kheap_compare(void *a, void *b)
// {
//     s_kheap_header_t *ka;
//     s_kheap_header_t *kb;
// 
//     kassert(NULL != a);
//     kassert(NULL != b);
// 
//     ka = a;
//     kb = b;
// 
//     if (ka->size < kb->size) {
//         return 1;
//     } else if (ka->size > kb->size) {
//         return -1;
//     } else {
//         return 0;
//     }
// }
// 
// s_kheap_t *
// kheap_create(ptr_t addr_start, ptr_t addr_end, ptr_t addr_max,
//     bool supervisor, bool read_only)
// {
//     s_kheap_t *heap;
// 
//     if (addr_start > addr_end || 0 == addr_max) {
//         return NULL;
//     } else if (0 != (addr_start & 0xfff)) {
//         return NULL;
//     } else if (0 != (addr_end & 0xfff)) {
//         return NULL;
//     } else {
//         heap = kmalloc(sizeof(*heap));
//         heap->ordered = ordered_array_place((void *)addr_start, KHEAP_IDX_SIZE, &kheap_compare);
//         addr_start += sizeof(void *) * KHEAP_IDX_SIZE;
// 
//         if (0 != (addr_start & 0xfff)) {
//             addr_start &= ((ptr_t)-1 << 12);
//             addr_start += PAGE_SIZE;
//         }
// 
//         heap->addr_start = addr_start;
//         heap->addr_end = addr_end;
//         heap->addr_max = addr_max;
//         heap->supervisor = supervisor;
//         heap->read_only = read_only;
// 
//         kheap_make_hole((void *)addr_start, addr_end - addr_start);
//         ordered_array_insert(&heap->ordered, (void *)addr_start);
//         // Fix-Me, no footer here ?
// 
//         return heap;
//     }
// }
// 
// static inline ptr_t
// kheap_obtain_minimal_hole(s_kheap_t *heap, ptr_t *useable_addr,
//     uint32 request_size, bool page_align)
// {
//     uint32 i;
//     ptr_t hole_addr;
//     ptr_t tmp_addr;
//     uint32 hole_size;
//     s_kheap_header_t *header;
// 
//     kassert(kheap_legal_p(heap));
//     kassert(0 != request_size);
//     kassert(NULL != useable_addr);
// 
//     i = 0;
//     while (i < heap->ordered.size) {
//         header = (void *)ordered_array_lookup(&heap->ordered, i);
//         hole_addr = (ptr_t)header;
//         tmp_addr = hole_addr + sizeof(s_kheap_header_t);
// 
//         if (page_align) {
//             if (!PAGE_ALIGN_P(tmp_addr)) {
//                 tmp_addr = (tmp_addr & PAGE_ALIGN_MASK) + PAGE_SIZE;
//             }
// 
//             hole_size = tmp_addr - hole_addr + request_size;
//             hole_size += sizeof(s_kheap_footer_t);
// 
//             if (header->size >= hole_size) {
//                 goto FOUND;
//             }
//         } else if (header->size >= request_size) {
//             goto FOUND;
//         }
//         i++;
//     }
// 
//     *useable_addr = PTR_INVALID;
//     return PTR_INVALID;
// 
// FOUND:
//     *useable_addr = tmp_addr;
//     ordered_array_remove(&heap->ordered, i);
//     kassert(kheap_hole_legal_p((void *)hole_addr));
// 
//     return hole_addr;
// }
// 
// static inline bool
// kheap_hole_legal_p(void *hole_addr)
// {
//     s_kheap_header_t *header;
//     s_kheap_footer_t *footer;
// 
//     kassert(NULL != hole_addr && (void *)PTR_INVALID != hole_addr);
// 
//     header = hole_addr;
//     footer = kheap_obtain_footer(header);
// 
//     if (KHEAP_MAGIC != footer->magic || KHEAP_MAGIC != header->magic) {
//         return false;
//     } else if (footer->header != header) {
//         return false;
//     } else {
//         return true;
//     }
// }
// 
// static inline s_kheap_footer_t *
// kheap_make_hole(void *hole_addr, uint32 size)
// {
//     s_kheap_header_t *hole_header;
//     s_kheap_footer_t *hole_footer;
// 
//     kassert(NULL != hole_addr && (void *)PTR_INVALID != hole_addr);
//     kassert(size >= KHEAP_HOLE_MIN_SIZE);
// 
//     hole_header = (void *)hole_addr;
//     hole_footer = (void *)(hole_addr + size - sizeof(s_kheap_footer_t));
// 
//     hole_header->magic = KHEAP_MAGIC;
//     hole_header->is_hole = true;
//     hole_header->size = size;
// 
//     hole_footer->magic = KHEAP_MAGIC;
//     hole_footer->header = hole_header;
// 
//     kassert(kheap_hole_legal_p(hole_addr));
//     return hole_footer;
// }
// 
// static inline void
// kheap_make_block(void *hole_addr, uint32 size)
// {
//     s_kheap_header_t *hole_header;
// 
//     kassert(NULL != hole_addr && (void *)PTR_INVALID != hole_addr);
//     kassert(size >= KHEAP_HOLE_MIN_SIZE);
// 
//     kheap_make_hole(hole_addr, size);
// 
//     hole_header = (void *)hole_addr;
//     hole_header->is_hole = false;
// }
// 
// static inline void
// kheap_handle_hole_unavailable(s_kheap_t *heap, uint32 hole_size)
// {
//     uint32 i;
//     uint32 idx;
//     ptr_t hole_addr;
//     ptr_t heap_size;
//     ptr_t last_addr;
//     ptr_t added_size;
//     s_kheap_header_t *header;
// 
//     kassert(kheap_legal_p(heap));
//     kassert(hole_size >= KHEAP_MIN_SIZE);
// 
//     heap_size = heap->addr_end - heap->addr_start;
//     kheap_resize(heap, heap_size + hole_size);
//     kassert(heap->addr_end - heap->addr_start > heap_size);
// 
//     i = 0;
//     last_addr = 0;
//     idx = IDX_INVALID;
//     added_size = heap->addr_end - heap->addr_start - heap_size;
// 
//     // optimize here, add one field addr_last
//     while (i < heap->ordered.size) {
//         hole_addr = (ptr_t)ordered_array_lookup(&heap->ordered, i);
//         if (hole_addr > last_addr) {
//             last_addr = hole_addr;
//             idx = i;
//         }
//         i++;
//     }
// 
//     if (IDX_INVALID == idx) { // If no hole in orderred array
//         header = (s_kheap_header_t *)heap->addr_end;
//         kheap_make_block(header, added_size);
//         ordered_array_insert(&heap->ordered, header);
//     } else {
//         // Bug here ? if memory is block in use, which has bigger address than last_addr.
//         header = (void *)last_addr;
//         kheap_make_hole(header, header->size + added_size);
//     }
// }
// 
// void *
// kheap_allocate(s_kheap_t *heap, uint32 request_size, bool page_align)
// {
//     ptr_t hole_addr;
//     ptr_t split_addr;
//     uint32 hole_size;
//     uint32 rest_size;
//     ptr_t useable_addr;
//     uint32 lead_blank_size;
// 
//     kassert(0 != request_size);
//     kassert(kheap_legal_p(heap));
// 
//     hole_addr = kheap_obtain_minimal_hole(heap, &useable_addr, request_size, page_align);
// 
//     if (PTR_INVALID == hole_addr) {
//         hole_size = request_size + KHEAP_INFO_SIZE;
//         if (page_align) {
//             hole_size += PAGE_SIZE;
//         }
// 
//         kheap_handle_hole_unavailable(heap, hole_size);
//         return kheap_allocate(heap, request_size, page_align);
//     } else {
//         hole_size = ((s_kheap_header_t *)hole_addr)->size;
//         lead_blank_size = (uint32)(useable_addr - hole_addr);
//         lead_blank_size -= sizeof(s_kheap_header_t);
// 
//         if (lead_blank_size >= KHEAP_HOLE_MIN_SIZE) {
//             split_addr = hole_addr;
//             hole_addr += lead_blank_size;
//             hole_size -= lead_blank_size;
//             kheap_make_hole((void *)split_addr, lead_blank_size);
//             ordered_array_insert(&heap->ordered, (void *)split_addr);
//         }
// 
//         rest_size = (uint32)(useable_addr - hole_addr) + request_size;
//         rest_size = hole_size - rest_size - sizeof(s_kheap_footer_t);
// 
//         if (rest_size >= KHEAP_HOLE_MIN_SIZE) {
//             split_addr = hole_addr + (hole_size - rest_size);
//             hole_size -= rest_size;
//             kheap_make_hole((void *)split_addr, rest_size);
//             ordered_array_insert(&heap->ordered, (void *)split_addr);
//         }
// 
//         kheap_make_block((void *)hole_addr, hole_size);
//         return (void *)useable_addr;
//     }
// }
// 
// static inline void *
// kheap_obtain_footer(s_kheap_header_t *header)
// {
//     kassert(NULL != header);
//     kassert(KHEAP_MAGIC == header->magic);
//     kassert(header->size >= KHEAP_HOLE_MIN_SIZE);
// 
//     return (void *)((ptr_t)header + header->size - sizeof(s_kheap_footer_t));
// }
// 
// void
// kheap_free(s_kheap_t *heap, void *val)
// {
//     uint32 idx;
//     ptr_t heap_size;
//     uint32 hole_size;
//     bool insert_needed;
//     ptr_t deleted_size;
//     s_kheap_header_t *header;
//     s_kheap_footer_t *footer;
//     s_kheap_header_t *next_header;
//     s_kheap_footer_t *last_footer;
// 
//     kassert(NULL != val);
//     kassert(kheap_legal_p(heap));
// 
//     insert_needed = true;
//     header = (void *)((ptr_t)val - sizeof(s_kheap_header_t));
//     header->is_hole = true;
//     footer = kheap_obtain_footer(header);
// 
//     kassert(KHEAP_MAGIC == header->magic && KHEAP_MAGIC == footer->magic);
// 
//     last_footer = (void *)((ptr_t)header - sizeof(s_kheap_footer_t));
//     if (KHEAP_MAGIC == last_footer->magic && last_footer->header->is_hole) {
//         insert_needed = false;
//         hole_size = last_footer->header->size + header->size;
//         footer = kheap_make_hole(last_footer->header, hole_size);
//         header = footer->header;
//     }
// 
//     next_header = (void *)((ptr_t)header + header->size);
//     if (KHEAP_MAGIC == next_header->magic && next_header->is_hole) {
//         idx = kheap_find_hole(heap, next_header);
//         ordered_array_remove(&heap->ordered, idx);
// 
//         hole_size = header->size + next_header->size;
//         footer = kheap_make_hole(header, hole_size);
//     }
// 
//     // If last hole in kheap
//     if ((ptr_t)footer + sizeof(s_kheap_footer_t) == heap->addr_end) {
//         heap_size = kheap_size(heap);
//         kheap_resize(heap, (ptr_t)header - heap->addr_start);
//         deleted_size = heap_size - kheap_size(heap);
// 
//         if (header->size >= deleted_size + KHEAP_HOLE_MIN_SIZE) {
//             kheap_make_hole(header, header->size - deleted_size);
//         } else if (header->size >= deleted_size) {
//             idx = kheap_find_hole(heap, header);
//             ordered_array_remove(&heap->ordered, idx);
//             // May leave at most KHEAP_HOLE_MIN_SIZE
//             return;
//         } else {
//             KERNEL_PANIC(MEM_OVERWRITE);
//         }
//     }
// 
//     if (insert_needed) {
//         ordered_array_insert(&heap->ordered, header);
//     } else {
//         idx = kheap_find_hole(heap, header);
//         ordered_array_adjust(&heap->ordered, idx);
//     }
// }
// 
// static inline void
// kheap_resize(s_kheap_t *heap, uint32 new_size)
// {
//     ptr_t i;
//     s_page_entry_t *pe;
// 
//     kassert(kheap_legal_p(heap));
// 
//     if (0 != (new_size & 0xfff)) {
//         new_size &= ((ptr_t)-1 << 12);
//         new_size += PAGE_SIZE;
//     }
// 
//     i = heap->addr_end - heap->addr_start;
//     kassert(0 == (i & 0xfff));
// 
//     if (new_size + heap->addr_start <= heap->addr_end) {
//         // contract space
//         if (new_size < KHEAP_MIN_SIZE) {
//             new_size = KHEAP_MIN_SIZE;
//         }
// 
//         while (new_size < i) {
//             i -= PAGE_SIZE;
//             pe = paging_get(heap->addr_start + i, false, kernel_dirt);
//             frame_free(pe);
//         }
//     } else {
//         // expand space
//         kassert(new_size + heap->addr_start <= heap->addr_max);
// 
//         while (i < new_size) {
//             pe = paging_get(heap->addr_start + i, true, kernel_dirt);
//             frame_allocate(pe, heap->supervisor, !heap->read_only);
//             i += PAGE_SIZE;
//         }
//     }
// 
//     kassert(i == new_size);
//     heap->addr_end = heap->addr_start + new_size;
// }

void
kheap_initialize(void)
{


}

void *
kmalloc(uint32 sz)
{
    printf_vga_tk("pli28 heap allocate size %d.\n", sz);
    return NULL;
}

