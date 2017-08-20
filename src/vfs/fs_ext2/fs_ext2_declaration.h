#ifndef SRC_VFS_FS_EXT2_DECLARATION_H
#define SRC_VFS_FS_EXT2_DECLARATION_H

static inline bool fs_ext2_block_group_is_ext2_p(s_ext2_block_group_t *block_group);
static inline bool fs_ext2_descriptor_illegal_p(s_ext2_dspr_t *dspr);
static inline bool fs_ext2_descriptor_legal_p(s_ext2_dspr_t *dspr);
static inline bool fs_ext2_descriptor_table_full_p(s_ext2_dspr_table_t *dspr_table);
static inline bool fs_ext2_descriptor_table_illegal_p(s_ext2_dspr_table_t *dspr_table);
static inline bool fs_ext2_descriptor_table_legal_p(s_ext2_dspr_table_t *dspr_table);
static inline bool fs_ext2_superblock_is_ext2_p(s_ext2_spbk_t *spbk);
static inline e_disk_id_t fs_ext2_descriptor_device_id(s_ext2_dspr_t *dspr);
static inline s_disk_pt_t * fs_ext2_descriptor_disk_pt(s_ext2_dspr_t *dspr);
static inline s_ext2_block_group_t * fs_ext2_block_group_create(s_ext2_dspr_t *dspr, s_disk_buf_t *disk_buf, uint32 secotr_offset);
static inline s_ext2_block_group_t ** fs_ext2_descriptor_block_group_array(s_ext2_dspr_t *dspr);
static inline s_ext2_dspr_t * fs_ext2_descriptor_create(e_disk_id_t device_id, uint32 size, s_disk_pt_t *pt);
static inline s_ext2_dspr_t ** fs_ext2_descriptor_table_dspr_array(s_ext2_dspr_table_t *dspr_table);
static inline s_ext2_dspr_table_t * fs_ext2_descriptor_table_obtain(void);
static inline s_ext2_spbk_t * fs_ext2_block_group_superblock(s_ext2_block_group_t *block_group);
static inline uint16 fs_ext2_superblock_signature(s_ext2_spbk_t *spbk);
static inline uint32 fs_ext2_block_group_block_count(s_ext2_block_group_t *block_group);
static inline uint32 fs_ext2_block_group_block_size(s_ext2_block_group_t *block_group);
static inline uint32 fs_ext2_block_group_sector_count(s_ext2_block_group_t *block_group, uint32 sector_bytes);
static inline uint32 fs_ext2_descriptor_index(s_ext2_dspr_t *dspr);
static inline uint32 fs_ext2_descriptor_size(s_ext2_dspr_t *dspr);
static inline uint32 fs_ext2_descriptor_table_index(s_ext2_dspr_table_t *dspr_table);
static inline uint32 fs_ext2_descriptor_table_size(s_ext2_dspr_table_t *dspr_table);
static inline uint32 fs_ext2_superblock_block_count(s_ext2_spbk_t *spbk);
static inline uint32 fs_ext2_superblock_block_size(s_ext2_spbk_t *spbk);
static inline void fs_ext2_block_group_destroy(s_ext2_block_group_t **block_group);
static inline void fs_ext2_descriptor_block_group_append(s_ext2_dspr_t *dspr, s_ext2_block_group_t *block_group);
static inline void fs_ext2_descriptor_device_id_set(s_ext2_dspr_t *dspr, e_disk_id_t device_id);
static inline void fs_ext2_descriptor_disk_pt_set(s_ext2_dspr_t *dspr, s_disk_pt_t *disk_pt);
static inline void fs_ext2_descriptor_index_set(s_ext2_dspr_t *dspr, uint32 index);
static inline void fs_ext2_descriptor_size_set(s_ext2_dspr_t *dspr, uint32 size);
static inline void fs_ext2_descriptor_table_append(s_ext2_dspr_table_t *dspr_table, s_ext2_dspr_t *dspr);
static inline void fs_ext2_descriptor_table_index_set(s_ext2_dspr_table_t *dspr_table, uint32 index);
static inline void fs_ext2_descriptor_table_initialize(s_ext2_dspr_table_t *dspr_table);
static inline void fs_ext2_descriptor_table_size_set(s_ext2_dspr_table_t *dspr_table, uint32 size);
static inline void fs_ext2_device_initialize(s_vfs_node_t *root, e_disk_id_t device_id, s_ext2_dspr_table_t *dspr_table);
static inline void fs_ext2_initialize_i(s_vfs_node_t *root);
static inline void fs_ext2_partition_initialize(s_disk_pt_t *disk_pt, s_ext2_dspr_table_t *dspr_table, e_disk_id_t device_id);
void fs_ext2_initialize(s_vfs_node_t *root);

#endif
