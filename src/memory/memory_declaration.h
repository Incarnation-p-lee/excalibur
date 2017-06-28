#ifndef SRC_MEMORY_DECLARATION_H
#define SRC_MEMORY_DECLARATION_H

static inline bool frame_bitmap_mask_clear_p(ptr_t mask, uint32 i);
static inline bool frame_bitmap_mask_set_p(ptr_t frame_bitmap, uint32 i);
static inline bool kernel_heap_legal_p(s_kernel_heap_t *heap);
static inline ptr_t frame_allocate(s_frame_bitmap_t *frame_bitmap);
static inline ptr_t frame_bitmap_frame_obtain(s_frame_bitmap_t *frame_bitmap, uint32 mask_idx, uint32 bit_idx);
static inline ptr_t frame_bitmap_mask(s_frame_bitmap_t *frame_bitmap, uint32 i);
static inline ptr_t kernel_heap_size(s_kernel_heap_t *heap);
static inline ptr_t page_entry_frame(s_page_entry_t *page_entry);
static inline s_frame_bitmap_t * frame_bitmap_create(ptr_t memory_limit);
static inline s_page_directory_t * page_directory_create(void);
static inline s_page_entry_t * page_directory_page_obtain(s_page_directory_t *page_dirt, ptr_t addr);
static inline s_page_entry_t * page_table_page_entry(s_page_table_t *page_table, uint32 i);
static inline s_page_table_t * page_directory_page_table(s_page_directory_t *page_dirt, uint32 i);
static inline s_page_table_t * page_table_create(void);
static inline uint32 frame_bitmap_limit(s_frame_bitmap_t *frame_bitmap);
static inline uint32 memory_set_fill_dword_element(uint8 v);
static inline void * memory_physical_aligned_allocate(uint32 sz);
static inline void * memory_physical_allocate(uint32 sz);
static inline void * memory_physical_allocate_i(uint32 sz, bool is_page_aligned);
static inline void frame_bitmap_mask_set(s_frame_bitmap_t *frame_bitmap, uint32 mask_idx, uint32 bit_idx);
static inline void memory_copy_in_byte(void *to, void *from, uint32 len);
static inline void memory_copy_in_dword(uint32 *to, uint32 *from, uint32 len);
static inline void memory_set_in_byte(void *base, uint8 v, uint32 len);
static inline void memory_set_in_dword(uint32 *base, uint8 v, uint32 len);
static inline void page_directory_page_table_phys_set(s_page_directory_t *page_dirt, uint32 i, ptr_t page_table_phys);
static inline void page_directory_page_table_set(s_page_directory_t *page_dirt, uint32 i, s_page_table_t *page_table);
static inline void page_directory_switch(s_page_directory_t *page_dirt);
static inline void page_enabled_range_print(ptr_t addr_start, ptr_t addr_end);
static inline void page_entry_attribute_present_set(s_page_entry_t *page_entry, bool is_presented);
static inline void page_entry_attribute_rw_set(s_page_entry_t *page_entry, bool is_writable);
static inline void page_entry_attribute_us_set(s_page_entry_t *page_entry, bool is_user);
static inline void page_entry_frame_set(s_page_entry_t *page_entry, ptr_t frame, bool is_user, bool is_writable);
void * kmalloc(uint32 sz);
void kheap_initialize(void);
void kmemory_copy(void *to, void *from, uint32 len);
void kmemset(void *base, uint8 v, uint32 len);
void page_initialize(void);

#endif
