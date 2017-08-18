#ifndef SRC_VFS_FS_EXT2_DECLARATION_H
#define SRC_VFS_FS_EXT2_DECLARATION_H

bool fs_ext2_descriptor_illegal_p(s_ext2_dspr_t *ext2_dspr);
bool fs_ext2_descriptor_legal_p(s_ext2_dspr_t *ext2_dspr);
bool fs_ext2_descriptor_table_illegal_p(s_ext2_dspr_table_t *ext2_dspr_table);
bool fs_ext2_descriptor_table_legal_p(s_ext2_dspr_table_t *ext2_dspr_table);
e_disk_id_t fs_ext2_descriptor_device_id(s_ext2_dspr_t *ext2_dspr);
s_disk_pt_t * fs_ext2_descriptor_disk_pt(s_ext2_dspr_t *ext2_dspr);
s_ext2_bg_info_t * fs_ext2_descriptor_bg_info_array(s_ext2_dspr_t *ext2_dspr);
s_ext2_dspr_t * fs_ext2_descriptor_table_dspr_array(s_ext2_dspr_table_t *ext2_dspr_table);
static inline bool fs_ext2_descriptor_illegal_ip(s_ext2_dspr_t *ext2_dspr);
static inline bool fs_ext2_descriptor_legal_ip(s_ext2_dspr_t *ext2_dspr);
static inline bool fs_ext2_descriptor_table_full_p(s_ext2_dspr_table_t *ext2_dspr_table);
static inline bool fs_ext2_descriptor_table_illegal_ip(s_ext2_dspr_table_t *ext2_dspr_table);
static inline bool fs_ext2_descriptor_table_legal_ip(s_ext2_dspr_table_t *ext2_dspr_table);
static inline e_disk_id_t fs_ext2_descriptor_device_id_i(s_ext2_dspr_t *ext2_dspr);
static inline s_disk_pt_t * fs_ext2_descriptor_disk_pt_i(s_ext2_dspr_t *ext2_dspr);
static inline s_ext2_bg_info_t * fs_ext2_descriptor_bg_info_array_i(s_ext2_dspr_t *ext2_dspr);
static inline s_ext2_dspr_t * fs_ext2_descriptor_create(e_disk_id_t device_id, uint32 size, s_disk_pt_t *pt);
static inline s_ext2_dspr_t * fs_ext2_descriptor_table_dspr_array_i(s_ext2_dspr_table_t *ext2_dspr_table);
static inline s_ext2_dspr_table_t * fs_ext2_descriptor_table_obtain(void);
static inline uint32 fs_ext2_descriptor_bg_info_size_i(s_ext2_dspr_t *ext2_dspr);
static inline uint32 fs_ext2_descriptor_table_index_i(s_ext2_dspr_table_t *ext2_dspr_table);
static inline uint32 fs_ext2_descriptor_table_size_i(s_ext2_dspr_table_t *ext2_dspr_table);
static inline void fs_ext2_block_group_initialize(s_ext2_dspr_t *ext2_dspr, uint32 secotr_offset);
static inline void fs_ext2_descriptor_bg_info_array_set_i(s_ext2_dspr_t *ext2_dspr, s_ext2_bg_info_t *bg_info_array);
static inline void fs_ext2_descriptor_bg_info_size_set_i(s_ext2_dspr_t *ext2_dspr, uint32 size);
static inline void fs_ext2_descriptor_device_id_set_i(s_ext2_dspr_t *ext2_dspr, e_disk_id_t device_id);
static inline void fs_ext2_descriptor_disk_pt_set_i(s_ext2_dspr_t *ext2_dspr, s_disk_pt_t *disk_pt);
static inline void fs_ext2_descriptor_table_append(s_ext2_dspr_table_t *ext2_dspr_table, s_ext2_dspr_t *ext2_dspr);
static inline void fs_ext2_descriptor_table_dspr_array_set_i(s_ext2_dspr_table_t *ext2_dspr_table, s_ext2_dspr_t *dspr_array);
static inline void fs_ext2_descriptor_table_index_set_i(s_ext2_dspr_table_t *ext2_dspr_table, uint32 index);
static inline void fs_ext2_descriptor_table_initialize(s_ext2_dspr_table_t *ext2_dspr_table);
static inline void fs_ext2_descriptor_table_size_set_i(s_ext2_dspr_table_t *ext2_dspr_table, uint32 size);
static inline void fs_ext2_device_initialize(s_vfs_node_t *root, e_disk_id_t device_id, s_ext2_dspr_table_t *ext2_dspr_table);
static inline void fs_ext2_initialize_i(s_vfs_node_t *root);
static inline void fs_ext2_partition_initialize(s_disk_pt_t *disk_pt, s_ext2_dspr_table_t *ext2_dspr_table, e_disk_id_t device_id);
uint32 fs_ext2_descriptor_bg_info_size(s_ext2_dspr_t *ext2_dspr);
uint32 fs_ext2_descriptor_table_index(s_ext2_dspr_table_t *ext2_dspr_table);
uint32 fs_ext2_descriptor_table_size(s_ext2_dspr_table_t *ext2_dspr_table);
void fs_ext2_descriptor_bg_info_array_set(s_ext2_dspr_t *ext2_dspr, s_ext2_bg_info_t *bg_info_array);
void fs_ext2_descriptor_bg_info_size_set(s_ext2_dspr_t *ext2_dspr, uint32 size);
void fs_ext2_descriptor_device_id_set(s_ext2_dspr_t *ext2_dspr, e_disk_id_t device_id);
void fs_ext2_descriptor_disk_pt_set(s_ext2_dspr_t *ext2_dspr, s_disk_pt_t *disk_pt);
void fs_ext2_descriptor_table_dspr_array_set(s_ext2_dspr_table_t *ext2_dspr_table, s_ext2_dspr_t *dspr_array);
void fs_ext2_descriptor_table_index_set(s_ext2_dspr_table_t *ext2_dspr_table, uint32 index);
void fs_ext2_descriptor_table_size_set(s_ext2_dspr_table_t *ext2_dspr_table, uint32 size);
void fs_ext2_initialize(s_vfs_node_t *root);

#endif
