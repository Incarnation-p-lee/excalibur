static inline void
fs_ext2_descriptor_table_append(s_ext2_dspr_table_t *ext2_dspr_table,
    s_ext2_dspr_t *ext2_dspr)
{
    uint32 index;
    s_ext2_dspr_t *dspr_array;

    kassert(fs_ext2_descriptor_table_legal_ip(ext2_dspr_table));
    kassert(fs_ext2_descriptor_legal_ip(ext2_dspr));
    kassert(!fs_ext2_descriptor_table_full_p(ext2_dspr_table));

    dspr_array = fs_ext2_descriptor_table_dspr_array_i(ext2_dspr_table);
    index = fs_ext2_descriptor_table_index_i(ext2_dspr_table);

    dspr_array[index++] = ext2_dspr;

    fs_ext2_descriptor_table_index_set_i(ext2_dspr_table, index);
}

static inline s_ext2_dspr_t *
fs_ext2_descriptor_create(e_disk_id_t device_id, uint32 size, s_disk_pt_t *pt)
{
    uint32 bytes_count;
    s_ext2_dspr_t *ext2_dspr;

    kassert(size);
    kassert(disk_partition_legal_p(pt));
    kassert(device_id < disk_descriptor_limit());

    bytes_count = sizeof(ext2_dspr->bg_info_array[0]) * size;

    ext2_dspr = kmalloc(sizeof(*ext2_dspr));
    ext2_dspr->bg_info_array = kmalloc(bytes_count);

    ext2_dspr->device_id = device_id;
    ext2_dspr->disk_pt = pt;
    ext2_dspr->index = 0;
    ext2_dspr->size = size;

    return ext2_dspr;
}

static inline void
fs_ext2_block_group_initialize(s_ext2_dspr_t *ext2_dspr, uint32 secotr_offset)
{
    // uint32 bytes_count;
    // uint32 sector_count, sector_bytes;
    // s_ext2_bg_info_t *bg_info;

    kassert(fs_ext2_descriptor_legal_ip(ext2_dspr));
    kassert(secotr_offset);

    // bg_info = kmalloc(sizeof(*bg_info));
    // sector_bytes = 
    // bytes_count = 

}

static inline void
fs_ext2_partition_initialize(s_disk_pt_t *disk_pt,
    s_ext2_dspr_table_t *ext2_dspr_table, e_disk_id_t device_id)
{
    s_ext2_dspr_t *dspr;
    uint32 sector_offset, sector_limit;

    kassert(disk_partition_legal_p(disk_pt));
    kassert(disk_partition_used_p(disk_pt));
    kassert(fs_ext2_descriptor_table_legal_ip(ext2_dspr_table));
    kassert(device_id < disk_descriptor_limit());

    dspr = fs_ext2_descriptor_create(device_id, EXT2_BLOCK_GROUP_MAX, disk_pt);
    sector_offset = disk_partition_sector_offset(disk_pt);
    sector_limit = sector_offset + disk_partition_sector_count(disk_pt);

    while (sector_offset < sector_limit) {
        sector_offset += fs_ext2_block_group_initialize(dspr, sector_offset);
    }

    fs_ext2_descriptor_table_append(ext2_dspr_table, dspr);
}

static inline void
fs_ext2_device_initialize(s_vfs_node_t *root, e_disk_id_t device_id,
    s_ext2_dspr_table_t *ext2_dspr_table)
{
    uint32 i, limit;
    s_disk_pt_t *disk_pt;
    s_disk_pt_table_t *disk_pt_table;

    kassert(vfs_node_legal_ip(root));
    kassert(disk_descriptor_legal_p(disk_dspt));
    kassert(fs_ext2_descriptor_table_legal_ip(ext2_dspr_table));
    kassert(device_id < disk_descriptor_limit());

    disk_pt_table = disk_descriptor_pt_table(device_id);

    i = 0;
    limit = DISK_PT_TABLE_SIZE;

    while (i < limit) {
        disk_pt = disk_partition_table_entry(disk_pt_table, i);

        if (disk_partition_used_p(disk_pt)) {
            fs_ext2_partition_initialize(disk_pt, ext2_dspr_table, device_id);
        }

        i++;
    }
}

static inline void
fs_ext2_descriptor_table_initialize(s_ext2_dspr_table_t *ext2_dspr_table)
{
    uint32 bytes_count;

    kassert(fs_ext2_descriptor_legal_ip(ext2_dspr_table));

    bytes_count = sizeof(ext2_dspr_table->dspr_array[0]) * EXT2_DESCCRIPTOR_MAX;

    ext2_dspr_table->dspr_array = kmalloc(bytes_count);
    ext2_dspr_table->index = 0;
    ext2_dspr_table->size = EXT2_DESCCRIPTOR_MAX;
}

static inline void
fs_ext2_initialize_i(s_vfs_node_t *root)
{
    uint32 i, limit;
    s_ext2_dspr_table_t *ext2_dspr_table;

    kassert(vfs_node_legal_ip(root));

    ext2_dspr_table = fs_ext2_descriptor_table_obtain();
    fs_ext2_descriptor_table_initialize(ext2_dspr_table);

    i = DEVICE_START;
    limit = disk_descriptor_limit();

    while (i < limit) {
        if (disk_descriptor_is_active_p(i)) {
            fs_ext2_device_initialize(root, i, ext2_dspr_table);
        }

        i++;
    }
}

void
fs_ext2_initialize(s_vfs_node_t *root)
{
    kassert(root);
}

