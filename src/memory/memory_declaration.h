#ifndef MEMORY_DECLARATION_H
#define MEMORY_DECLARATION_H

static bool frame_available_p(ptr_t frame);
static inline struct page_entry * paging_get(ptr_t addr, bool make, struct page_directory *dirt);
static inline void * kmalloc_int(uint32 sz, bool align, ptr_t *phys);
static inline void paging_directory_switch(struct page_directory *dirt);
static inline void paging_fault_handler(struct pro_context context);
static ptr_t frame_first(void);
static void frame_allocate(struct page_entry *page, bool kernel, bool write);
static void frame_clear(ptr_t frame);
static void frame_set(ptr_t frame);
void * kmalloc(uint32 sz);
void * kmalloc_algn(uint32 sz);
void * kmalloc_algn_with_phys(uint32 sz, ptr_t *phys);
void * kmalloc_phys(uint32 sz, ptr_t *phys);
void frame_free(struct page_entry *page);
void paging_initialize(void);

#endif
