#ifndef SRC_DISK_DECLARATION_H
#define SRC_DISK_DECLARATION_H

bool disk_buffer_illegal_p(s_disk_buf_t *disk_buffer);
bool disk_buffer_legal_p(s_disk_buf_t *disk_buffer);
bool disk_partition_bootable_p(s_disk_pt_t *disk_pt);
bool disk_partition_illegal_p(s_disk_pt_t *disk_pt);
bool disk_partition_legal_p(s_disk_pt_t *disk_pt);
bool disk_partition_table_illegal_p(s_disk_pt_table_t *disk_pt_table);
bool disk_partition_table_legal_p(s_disk_pt_table_t *disk_pt_table);
s_disk_buf_t * disk_buffer_create(uint32 size);
s_disk_pt_t * disk_partition_table_array(s_disk_pt_table_t *disk_pt_table);
s_disk_pt_t * disk_partition_table_entry(s_disk_pt_table_t *disk_pt_table, uint32 i);
static inline bool disk_buffer_illegal_ip(s_disk_buf_t *disk_buffer);
static inline bool disk_buffer_legal_ip(s_disk_buf_t *disk_buffer);
static inline bool disk_partition_bootable_ip(s_disk_pt_t *disk_pt);
static inline bool disk_partition_illegal_ip(s_disk_pt_t *disk_pt);
static inline bool disk_partition_legal_ip(s_disk_pt_t *disk_pt);
static inline bool disk_partition_table_illegal_ip(s_disk_pt_table_t *disk_pt_table);
static inline bool disk_partition_table_legal_ip(s_disk_pt_table_t *disk_pt_table);
static inline bool disk_partition_unused_p(s_disk_pt_t *disk_pt);
static inline bool disk_partition_used_p(s_disk_pt_t *disk_pt);
static inline s_disk_buf_t * disk_buffer_create_i(uint32 size);
static inline s_disk_pt_t * disk_partition_table_array_i(s_disk_pt_table_t *disk_pt_table);
static inline s_disk_pt_t * disk_partition_table_entry_i(s_disk_pt_table_t *disk_pt_table, uint32 i);
static inline uint16 disk_partition_cylinder_end_i(s_disk_pt_t *disk_pt);
static inline uint16 disk_partition_cylinder_start_i(s_disk_pt_t *disk_pt);
static inline uint16 disk_partition_sector_end_i(s_disk_pt_t *disk_pt);
static inline uint16 disk_partition_sector_start_i(s_disk_pt_t *disk_pt);
static inline uint32 disk_buffer_copy_i(void *d, s_disk_buf_t *disk_buf, uint32 offset, uint32 size);
static inline uint32 disk_buffer_index_i(s_disk_buf_t *disk_buffer);
static inline uint32 disk_buffer_limit_i(s_disk_buf_t *disk_buffer);
static inline uint32 disk_buffer_size_i(s_disk_buf_t *disk_buffer);
static inline uint32 disk_partition_sector_count_i(s_disk_pt_t *disk_pt);
static inline uint32 disk_partition_sector_offset_i(s_disk_pt_t *disk_pt);
static inline uint8 * disk_buffer_array_i(s_disk_buf_t *disk_buffer);
static inline uint8 disk_partition_boot_i(s_disk_pt_t *disk_pt);
static inline uint8 disk_partition_head_end_i(s_disk_pt_t *disk_pt);
static inline uint8 disk_partition_head_start_i(s_disk_pt_t *disk_pt);
static inline uint8 disk_partition_system_id_i(s_disk_pt_t *disk_pt);
static inline void disk_buffer_array_set_i(s_disk_buf_t *disk_buffer, uint8 *array);
static inline void disk_buffer_destroy_i(s_disk_buf_t *disk_buf);
static inline void disk_buffer_dword_append_i(s_disk_buf_t *disk_buf, uint32 val);
static inline void disk_buffer_index_set_i(s_disk_buf_t *disk_buffer, uint32 index);
static inline void disk_buffer_size_set_i(s_disk_buf_t *disk_buffer, uint32 size);
static inline void disk_partition_boot_set_i(s_disk_pt_t *disk_pt, uint8 boot);
static inline void disk_partition_cylinder_end_set_i(s_disk_pt_t *disk_pt, uint16 cylinder_end);
static inline void disk_partition_cylinder_start_set_i(s_disk_pt_t *disk_pt, uint16 cylinder_start);
static inline void disk_partition_head_end_set_i(s_disk_pt_t *disk_pt, uint8 head_end);
static inline void disk_partition_head_start_set_i(s_disk_pt_t *disk_pt, uint8 head_start);
static inline void disk_partition_sector_count_set_i(s_disk_pt_t *disk_pt, uint32 sector_count);
static inline void disk_partition_sector_end_set_i(s_disk_pt_t *disk_pt, uint16 sector_end);
static inline void disk_partition_sector_offset_set_i(s_disk_pt_t *disk_pt, uint32 sector_offset);
static inline void disk_partition_sector_start_set_i(s_disk_pt_t *disk_pt, uint16 sector_start);
static inline void disk_partition_system_id_set_i(s_disk_pt_t *disk_pt, uint8 system_id);
static inline void disk_partition_table_entry_print(s_disk_pt_t *disk_pt, uint32 i);
static inline void disk_partition_table_print_i(s_disk_pt_table_t *pt_table);
uint16 disk_partition_cylinder_end(s_disk_pt_t *disk_pt);
uint16 disk_partition_cylinder_start(s_disk_pt_t *disk_pt);
uint16 disk_partition_sector_end(s_disk_pt_t *disk_pt);
uint16 disk_partition_sector_start(s_disk_pt_t *disk_pt);
uint32 disk_buffer_copy(void *d, s_disk_buf_t *disk_buf, uint32 offset, uint32 size);
uint32 disk_buffer_index(s_disk_buf_t *disk_buffer);
uint32 disk_buffer_limit(s_disk_buf_t *disk_buffer);
uint32 disk_buffer_size(s_disk_buf_t *disk_buffer);
uint32 disk_partition_sector_count(s_disk_pt_t *disk_pt);
uint32 disk_partition_sector_offset(s_disk_pt_t *disk_pt);
uint8 * disk_buffer_array(s_disk_buf_t *disk_buffer);
uint8 disk_partition_head_end(s_disk_pt_t *disk_pt);
uint8 disk_partition_head_start(s_disk_pt_t *disk_pt);
uint8 disk_partition_system_id(s_disk_pt_t *disk_pt);
void disk_buffer_array_set(s_disk_buf_t *disk_buffer, uint8 *array);
void disk_buffer_destroy(s_disk_buf_t **disk_buf);
void disk_buffer_dword_append(s_disk_buf_t *disk_buf, uint32 val);
void disk_buffer_index_set(s_disk_buf_t *disk_buffer, uint32 index);
void disk_buffer_size_set(s_disk_buf_t *disk_buffer, uint32 size);
void disk_initialize(void);
void disk_partition_cylinder_end_set(s_disk_pt_t *disk_pt, uint16 cylinder_end);
void disk_partition_cylinder_start_set(s_disk_pt_t *disk_pt, uint16 cylinder_start);
void disk_partition_head_end_set(s_disk_pt_t *disk_pt, uint8 head_end);
void disk_partition_head_start_set(s_disk_pt_t *disk_pt, uint8 head_start);
void disk_partition_sector_count_set(s_disk_pt_t *disk_pt, uint32 sector_count);
void disk_partition_sector_end_set(s_disk_pt_t *disk_pt, uint16 sector_end);
void disk_partition_sector_offset_set(s_disk_pt_t *disk_pt, uint32 sector_offset);
void disk_partition_sector_start_set(s_disk_pt_t *disk_pt, uint16 sector_start);
void disk_partition_system_id_set(s_disk_pt_t *disk_pt, uint8 system_id);
void disk_partition_table_print(s_disk_pt_table_t *pt_table);

#endif
