#ifndef HAVE_DEFINED_EXTERNAL_H
#define HAVE_DEFINED_EXTERNAL_H

extern bool assert_complain(const char *msg, const char *file, const char *fun, uint32 line, bool exp);
extern bool disk_buffer_illegal_p(s_disk_buf_t *disk_buffer);
extern bool disk_buffer_legal_p(s_disk_buf_t *disk_buffer);
extern bool disk_partition_bootable_p(s_disk_pt_t *disk_pt);
extern bool disk_partition_illegal_p(s_disk_pt_t *disk_pt);
extern bool disk_partition_legal_p(s_disk_pt_t *disk_pt);
extern bool disk_partition_table_illegal_p(s_disk_pt_table_t *disk_pt_table);
extern bool disk_partition_table_legal_p(s_disk_pt_table_t *disk_pt_table);
extern bool linked_list_head_p(s_linked_list_t *node);
extern bool linked_list_legal_p(s_linked_list_t *linked_list);
extern bool linked_list_tail_p(s_linked_list_t *node);
extern bool ordered_array_illegal_p(s_ordered_array_t *ordered);
extern bool ordered_array_legal_p(s_ordered_array_t *ordered);
extern bool vfs_node_file_p(s_vfs_node_t *vfs_node);
extern bool vfs_node_illegal_p(s_vfs_node_t *vfs_node);
extern bool vfs_node_legal_p(s_vfs_node_t *vfs_node);
extern char * multiboot_env_module_name(s_boot_module_t *module);
extern char * string_basename(char *fullname);
extern char * vfs_node_name(s_vfs_node_t *vfs_node);
extern isr_handler_t isr_handler_get(uint32 i);
extern ptr_t multiboot_data_info_modules_addr(void);
extern ptr_t multiboot_data_info_physical_memory_limit(void);
extern ptr_t multiboot_data_info_physical_memory_lower(void);
extern ptr_t multiboot_data_info_physical_memory_upper(void);
extern ptr_t multiboot_env_module_addr_start(s_boot_module_t *module);
extern s_boot_module_t * multiboot_data_info_boot_module(uint32 i);
extern s_disk_buf_t * disk_buffer_create(uint32 size);
extern s_disk_pt_t * disk_partition_table_array(s_disk_pt_table_t *disk_pt_table);
extern s_disk_pt_t * disk_partition_table_entry(s_disk_pt_table_t *disk_pt_table, uint32 i);
extern s_linked_list_t * linked_list_insert_after(s_linked_list_t *node, s_linked_list_t *inserted);
extern s_linked_list_t * linked_list_insert_before(s_linked_list_t *node, s_linked_list_t *inserted);
extern s_linked_list_t * linked_list_next(s_linked_list_t *linked_list);
extern s_linked_list_t * linked_list_prev(s_linked_list_t *linked_list);
extern s_linked_list_t * linked_list_remove(s_linked_list_t *node);
extern s_ordered_array_t * ordered_array_create(uint32 size, ordered_compare_t compare);
extern s_vfs_node_t * fs_initrd_file_create(char *name);
extern s_vfs_node_t * fs_initrd_initialize(char *root_path, ptr_t location);
extern s_vfs_node_t * fs_initrd_vfs_node_root(void);
extern s_vfs_node_t * vfs_dir_node_create(char *name, f_readdir_t readdir, f_finddir_t finddir);
extern s_vfs_node_t * vfs_file_node_create(char *name, f_read_t read, f_write_t write);
extern s_vfs_node_t * vfs_node_next(s_vfs_node_t *vfs_node);
extern s_vfs_node_t * vfs_readdir(s_vfs_node_t *vfs_node, uint32 index);
extern s_vfs_node_t * vfs_sub_list_first(s_vfs_node_t *vfs_node);
extern sint32 ordered_array_standard_compare(const void *a, const void *b);
extern sint32 string_compare(char *a, char *b);
extern uint16 disk_partition_cylinder_end(s_disk_pt_t *disk_pt);
extern uint16 disk_partition_cylinder_start(s_disk_pt_t *disk_pt);
extern uint16 disk_partition_sector_end(s_disk_pt_t *disk_pt);
extern uint16 disk_partition_sector_start(s_disk_pt_t *disk_pt);
extern uint16 io_bus_read_word(uint16 port);
extern uint32 ata_device_info_limit(void);
extern uint32 ata_device_sector_chs_read(s_disk_buf_t *disk_buf, uint32 device_id, uint16 c, uint8 h, uint8 s);
extern uint32 ata_device_sector_lba_read(s_disk_buf_t *disk_buf, uint32 device_id, uint32 lba);
extern uint32 disk_buffer_copy(void *d, s_disk_buf_t *disk_buf, uint32 offset, uint32 size);
extern uint32 disk_buffer_index(s_disk_buf_t *disk_buffer);
extern uint32 disk_buffer_limit(s_disk_buf_t *disk_buffer);
extern uint32 disk_buffer_size(s_disk_buf_t *disk_buffer);
extern uint32 disk_partition_sector_count(s_disk_pt_t *disk_pt);
extern uint32 disk_partition_sector_offset(s_disk_pt_t *disk_pt);
extern uint32 io_bus_dword_read(uint16 port);
extern uint32 io_bus_read(uint16 port, void *buf, uint32 size);
extern uint32 irq_0_timer_tick(void);
extern uint32 multiboot_data_info_boot_modules_count(void);
extern uint32 ordered_array_limit(s_ordered_array_t *ordered_array);
extern uint32 ordered_array_value_index_find(s_ordered_array_t *ordered_array, void *val);
extern uint32 string_copy(char *d, char *s);
extern uint32 string_len(char *s);
extern uint32 vfs_close(s_vfs_node_t *vfs_node);
extern uint32 vfs_node_flags(s_vfs_node_t *vfs_node);
extern uint32 vfs_node_inode(s_vfs_node_t *vfs_node);
extern uint32 vfs_node_length(s_vfs_node_t *vfs_node);
extern uint32 vfs_open(s_vfs_node_t *vfs_node);
extern uint32 vfs_read(s_vfs_node_t *vfs_node, uint32 offset, uint32 size, uint8 *buf);
extern uint32 vfs_write(s_vfs_node_t *vfs_node, uint32 offset, uint32 size, uint8 *buf);
extern uint64 time_stamp_counter(void);
extern uint8 * disk_buffer_array(s_disk_buf_t *disk_buffer);
extern uint8 disk_partition_head_end(s_disk_pt_t *disk_pt);
extern uint8 disk_partition_head_start(s_disk_pt_t *disk_pt);
extern uint8 disk_partition_system_id(s_disk_pt_t *disk_pt);
extern uint8 io_bus_byte_read(uint16 port);
extern void * kmalloc(uint32 request_size);
extern void * ordered_array_place(s_ordered_array_t *ordered_array, void *addr, uint32 size, ordered_compare_t compare);
extern void * ordered_array_value(s_ordered_array_t *ordered_array, uint32 i);
extern void ata_device_initialize(void);
extern void disk_buffer_array_set(s_disk_buf_t *disk_buffer, uint8 *array);
extern void disk_buffer_destroy(s_disk_buf_t **disk_buf);
extern void disk_buffer_dword_append(s_disk_buf_t *disk_buf, uint32 val);
extern void disk_buffer_index_set(s_disk_buf_t *disk_buffer, uint32 index);
extern void disk_buffer_size_set(s_disk_buf_t *disk_buffer, uint32 size);
extern void disk_initialize(void);
extern void disk_partition_cylinder_end_set(s_disk_pt_t *disk_pt, uint16 cylinder_end);
extern void disk_partition_cylinder_start_set(s_disk_pt_t *disk_pt, uint16 cylinder_start);
extern void disk_partition_head_end_set(s_disk_pt_t *disk_pt, uint8 head_end);
extern void disk_partition_head_start_set(s_disk_pt_t *disk_pt, uint8 head_start);
extern void disk_partition_sector_count_set(s_disk_pt_t *disk_pt, uint32 sector_count);
extern void disk_partition_sector_end_set(s_disk_pt_t *disk_pt, uint16 sector_end);
extern void disk_partition_sector_offset_set(s_disk_pt_t *disk_pt, uint32 sector_offset);
extern void disk_partition_sector_start_set(s_disk_pt_t *disk_pt, uint16 sector_start);
extern void disk_partition_system_id_set(s_disk_pt_t *disk_pt, uint8 system_id);
extern void disk_partition_table_print(s_disk_pt_table_t *pt_table);
extern void gdt_initialize(void);
extern void idt_initialize(void);
extern void io_bus_byte_write(uint16 port, uint8 val);
extern void io_bus_dword_write(uint16 port, uint32 val);
extern void io_bus_write_word(uint16 port, uint16 val);
extern void irq_0_timer_handler(s_pro_context_t *context);
extern void irq_14_ata_channel_primary(s_pro_context_t *context);
extern void irq_1_keyboard_handler(s_pro_context_t *context);
extern void irq_7_handler(s_pro_context_t *context);
extern void irq_handler_main(s_pro_context_t context);
extern void isr_handler_main(s_pro_context_t context);
extern void kernel_heap_initialize(void);
extern void kfree(void *ptr);
extern void kmemory_copy(void *to, void *from, uint32 len);
extern void kmemset(void *base, uint8 v, uint32 len);
extern void kmemset_u16(void *base, uint16 val, uint32 len);
extern void linked_list_initialize(s_linked_list_t *node);
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
extern void print_buffer_fs_initrd_write(void);
extern void printf_vga(char *format, ...);
extern void printf_vga_tk(char *format, ...);
extern void screen_monitor_char_write(char c);
extern void screen_monitor_clear(void);
extern void screen_monitor_string_write(char *c);
extern void test_main(void);
extern void timer_initialize(uint32 freq);
extern void vfs_initialize(void);
extern void vfs_node_flags_add(s_vfs_node_t *vfs_node, uint32 flags);
extern void vfs_node_inode_set(s_vfs_node_t *vfs_node, uint32 inode);
extern void vfs_node_length_set(s_vfs_node_t *vfs_node, uint32 length);
extern void vfs_sub_list_add(s_vfs_node_t *vfs_node, s_vfs_node_t *added);

#endif

