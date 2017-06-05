#ifndef SRC_MEMORY_MEMORY_DECLARATION_H
#define SRC_MEMORY_MEMORY_DECLARATION_H

bool frame_available_p(ptr_t frame);
s_kheap_t * kheap_create(ptr_t addr_start, ptr_t addr_end, ptr_t addr_max, bool supervisor, bool read_only);
static inline bool kheap_hole_legal_p(void *hole_addr);
static inline bool kheap_legal_p(s_kheap_t *heap);
static inline ptr_t kheap_obtain_minimal_hole(s_kheap_t *heap, ptr_t *useable_addr, uint32 request_size, bool page_align);
static inline ptr_t kheap_size(s_kheap_t *heap);
static inline s_kheap_footer_t * kheap_make_hole(void *hole_addr, uint32 size);
static inline s_page_entry_t * paging_get(ptr_t addr, bool make, s_page_directory_t *dirt);
static inline sint32 kheap_compare(void *a, void *b);
static inline uint32 kheap_find_hole(s_kheap_t *heap, void *val);
static inline uint32 memory_set_fill_dword_element(uint8 v);
static inline void * kheap_obtain_footer(s_kheap_header_t *header);
static inline void * kmalloc_int(uint32 sz, bool align, ptr_t *phys);
static inline void kheap_handle_hole_unavailable(s_kheap_t *heap, uint32 hole_size);
static inline void kheap_make_block(void *hole_addr, uint32 size);
static inline void kheap_resize(s_kheap_t *heap, uint32 new_size);
static inline void memory_copy_in_byte(void *to, void *from, uint32 len);
static inline void memory_copy_in_dword(uint32 *to, uint32 *from, uint32 len);
static inline void memory_set_in_byte(void *base, uint8 v, uint32 len);
static inline void memory_set_in_dword(uint32 *base, uint8 v, uint32 len);
static inline void paging_directory_switch(s_page_directory_t *dirt);
static ptr_t frame_first(void);
static void frame_allocate(s_page_entry_t *page, bool kernel, bool write);
static void frame_clear(ptr_t frame);
static void frame_free(s_page_entry_t *page);
static void frame_set(ptr_t frame);
void * kheap_allocate(s_kheap_t *heap, uint32 request_size, bool page_align);
void * kmalloc(uint32 sz);
void * kmalloc_algn(uint32 sz);
void * kmalloc_algn_with_phys(uint32 sz, ptr_t *phys);
void * kmalloc_phys(uint32 sz, ptr_t *phys);
void kheap_free(s_kheap_t *heap, void *val);
void kheap_initialize(void);
void kmemory_copy(void *to, void *from, uint32 len);
void kmemset(void *base, uint8 v, uint32 len);
void paging_initialize(void);

#endif
