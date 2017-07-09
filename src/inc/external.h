#ifndef HAVE_DEFINED_EXTERNAL_H
#define HAVE_DEFINED_EXTERNAL_H

extern bool assert_complain(const char *msg, const char *file, const char *fun, uint32 line, bool exp);
extern bool filesystem_node_illegal_p(s_fs_node_t *fs_node);
extern bool filesystem_node_legal_p(s_fs_node_t *fs_node);
extern bool ordered_array_illegal_p(s_ordered_array_t *ordered);
extern bool ordered_array_legal_p(s_ordered_array_t *ordered);
extern ptr_t multiboot_data_info_boot_module_start(uint32 i);
extern ptr_t multiboot_data_info_modules_addr(void);
extern ptr_t multiboot_data_info_physical_memory_limit(void);
extern ptr_t multiboot_data_info_physical_memory_lower(void);
extern ptr_t multiboot_data_info_physical_memory_upper(void);
extern s_directory_t * filesystem_readdir(s_fs_node_t *fs_node, uint32 index);
extern s_fs_node_t * fs_initrd_initialize(ptr_t location);
extern s_ordered_array_t * ordered_array_create(uint32 size, ordered_compare_t compare);
extern sint32 ordered_array_standard_compare(const void *a, const void *b);
extern uint16 io_bus_read_word(uint16 port);
extern uint32 filesystem_close(s_fs_node_t *fs_node);
extern uint32 filesystem_node_inode(s_fs_node_t *fs_node);
extern uint32 filesystem_node_length(s_fs_node_t *fs_node);
extern uint32 filesystem_open(s_fs_node_t *fs_node);
extern uint32 filesystem_read(s_fs_node_t *fs_node, uint32 offset, uint32 size, uint8 *buf);
extern uint32 filesystem_write(s_fs_node_t *fs_node, uint32 offset, uint32 size, uint8 *buf);
extern uint32 irq_0_timer_tick(void);
extern uint32 multiboot_data_info_boot_modules_count(void);
extern uint32 ordered_array_limit(s_ordered_array_t *ordered_array);
extern uint32 ordered_array_value_index_find(s_ordered_array_t *ordered_array, void *val);
extern uint32 string_copy(char *d, char *s);
extern uint32 string_len(char *s);
extern uint64 time_stamp_counter(void);
extern uint8 io_bus_read_byte(uint16 port);
extern void * kmalloc(uint32 request_size);
extern void * ordered_array_place(s_ordered_array_t *ordered_array, void *addr, uint32 size, ordered_compare_t compare);
extern void * ordered_array_value(s_ordered_array_t *ordered_array, uint32 i);
extern void descriptor_table_gdt_initialize(void);
extern void descriptor_table_idt_initialize(void);
extern void io_bus_write_byte(uint16 port, uint8 val);
extern void irq_0_timer_initialize(uint32 freq);
extern void irq_handler_main(s_pro_context_t context);
extern void isr_handler_main(s_pro_context_t context);
extern void kernel_heap_initialize(void);
extern void kfree(void *ptr);
extern void kmemory_copy(void *to, void *from, uint32 len);
extern void kmemset(void *base, uint8 v, uint32 len);
extern void kmemset_u16(void *base, uint16 val, uint32 len);
extern void memory_physical_placement_set(ptr_t addr_phys);
extern void multiboot_env_cpu_detect(void);
extern void multiboot_env_detect(uint32 magic, void *boot_header, void *boot_info);
extern void ordered_array_adjust(s_ordered_array_t *ordered_array, uint32 i);
extern void ordered_array_destroy(s_ordered_array_t *oa);
extern void ordered_array_insert(s_ordered_array_t *ordered_array, void *val);
extern void ordered_array_remove(s_ordered_array_t *ordered_array, uint32 i);
extern void page_align(ptr_t *addr);
extern void page_initialize(void);
extern void pic_send_eoi(uint32 irq);
extern void printf_vga(char *format, ...);
extern void printf_vga_tk(char *format, ...);
extern void screen_monitor_clear(void);
extern void screen_monitor_put_char(char c);
extern void screen_monitor_write_string(char *c);
extern void screen_monitor_write_uint32(uint32 u);
extern void screen_monitor_write_uint32_hex(uint32 u);
extern void test_main(void);

#endif

