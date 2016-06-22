#ifndef MEMORY_DECLARATION_H
#define MEMORY_DECLARATION_H

bool frame_available_p(ptr_t frame);
sint32 kheap_compare(void *a, void *b);
static inline struct page_entry * paging_get(ptr_t addr, bool make, struct page_directory *dirt);
static inline uint32 memory_set_fill_dword_element(uint8 v);
static inline void * kmalloc_int(uint32 sz, bool align, ptr_t *phys);
static inline void memory_copy_in_byte(void *to, void *from, uint32 len);
static inline void memory_copy_in_dword(uint32 *to, uint32 *from, uint32 len);
static inline void memory_set_in_byte(void *base, uint8 v, uint32 len);
static inline void memory_set_in_dword(uint32 *base, uint8 v, uint32 len);
static inline void paging_directory_switch(struct page_directory *dirt);
static ptr_t frame_first(void);
static void frame_allocate(struct page_entry *page, bool kernel, bool write);
static void frame_clear(ptr_t frame);
static void frame_free(struct page_entry *page);
static void frame_set(ptr_t frame);
struct kheap * kheap_create(ptr_t addr_start, ptr_t addr_end, ptr_t addr_max, bool supervisor, bool read_only);
uint32 kheap_find_minimal_hole(uint32 size, bool page_align, struct kheap *heap);
void * kmalloc(uint32 sz);
void * kmalloc_algn(uint32 sz);
void * kmalloc_algn_with_phys(uint32 sz, ptr_t *phys);
void * kmalloc_phys(uint32 sz, ptr_t *phys);
void kheap_resize(struct kheap *heap, uint32 new_size);
void kmemory_copy(void *to, void *from, uint32 len);
void kmemset(void *base, uint8 v, uint32 len);
void paging_initialize(void);

#endif
