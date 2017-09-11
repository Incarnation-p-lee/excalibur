static inline void
fs_ext2_descriptor_table_append(s_ext2_dspr_table_t *dspr_table,
    s_ext2_dspr_t *dspr)
{
    uint32 index;
    s_ext2_dspr_t **dspr_array;

    kassert(fs_ext2_descriptor_table_legal_p(dspr_table));
    kassert(fs_ext2_descriptor_legal_p(dspr));
    kassert(!fs_ext2_descriptor_table_full_p(dspr_table));

    dspr_array = fs_ext2_descriptor_table_dspr_array(dspr_table);
    index = fs_ext2_descriptor_table_index(dspr_table);

    dspr_array[index++] = dspr;

    fs_ext2_descriptor_table_index_set(dspr_table, index);
}

static inline s_ext2_dspr_t *
fs_ext2_descriptor_create(e_disk_id_t device_id, s_disk_pt_t *pt,
    s_ext2_bg_info_t *info)
{
    uint32 size;
    uint32 bytes_count;
    s_ext2_dspr_t *dspr;

    kassert(disk_partition_legal_p(pt));
    kassert(fs_ext2_bg_info_valid_p(info));
    kassert(device_id < disk_descriptor_limit());

    size = EXT2_BLOCK_GROUP_MAX;
    bytes_count = sizeof(dspr->bg_data_array[0]) * size;

    dspr = kmalloc(sizeof(*dspr));
    dspr->bg_data_array = kmalloc(bytes_count);

    dspr->device_id = device_id;
    dspr->disk_pt = pt;
    dspr->bg_info = info;
    dspr->index = 0;
    dspr->size = size;

    return dspr;
}

static inline void
fs_ext2_descriptor_destroy(s_ext2_dspr_t **dspr)
{
    kassert(dspr);
    kassert(*dspr);

    kfree((*dspr)->bg_data_array);
    kfree((*dspr)->bg_info);
    kfree(*dspr);

    *dspr = NULL;
}

static inline s_ext2_bg_info_t *
fs_ext2_bg_info_create(s_disk_buf_t *disk_buf, e_disk_id_t device_id,
    uint32 sector_offset)
{
    uint32 offset;
    f_disk_read_t read;
    s_ext2_bg_info_t *info;

    kassert(sector_offset);
    kassert(disk_buffer_legal_p(disk_buf));

    offset = EXT2_SBLOCK_OFFSET;
    info = kmalloc(sizeof(*info));
    read = disk_descriptor_read(device_id);

    read(disk_buf, device_id, sector_offset, offset + sizeof(*info));
    disk_buffer_copy(info, disk_buf, offset, sizeof(*info));

    return info;
}

static inline void
fs_ext2_bg_info_destroy(s_ext2_bg_info_t **info)
{
    kassert(info);
    kassert(*info);

    kfree(*info);

    *info = NULL;
}

static inline s_vfs_node_t *
fs_ext2_descriptor_vfs_tree_build(s_ext2_dspr_t *dspr)
{
    s_vfs_node_t *ext2_root;

    kassert(fs_ext2_descriptor_legal_p(dspr));

    ext2_root = vfs_dir_node_create(FS_DIR_ROOT, (void *)1, (void *)1);
    vfs_node_inode_set(ext2_root, EXT2_ROOT_DIR_INODE);

    return ext2_root;
}

static inline s_bitmap_t *
fs_ext2_bitmap_place(s_disk_buf_t *buf, e_disk_id_t device_id,
    uint32 sector, uint32 bytes_count)
{
    uint8 *array;
    s_bitmap_t *bitmap;
    f_disk_read_t read;

    kassert(bytes_count);
    kassert(sector);
    kassert(disk_buffer_legal_p(buf));

    array = kmalloc(bytes_count);
    read = disk_descriptor_read(device_id);

    read(buf, device_id, sector, bytes_count);
    disk_buffer_copy(array, buf, 0, bytes_count);
    bitmap = bitmap_place(array, bytes_count, bytes_count * 8);

    return bitmap;
}

static inline uint32
fs_ext2_block_addr_to_sector(s_disk_pt_t *pt, uint32 b_addr, uint32 b_bytes,
    uint32 sector_bytes)
{
    uint32 sector;

    kassert(b_bytes);
    kassert(sector_bytes);
    kassert(disk_partition_legal_p(pt));
    kassert((b_addr * b_bytes % sector_bytes) == 0);

    sector = disk_partition_sector_offset(pt);
    sector += b_addr * b_bytes / sector_bytes;

    return sector;
}

static inline s_ext2_bg_data_t *
fs_ext2_bg_data_create(s_ext2_bg_info_t *info, s_disk_buf_t *buf,
    uint32 sector_offset, e_disk_id_t device_id)
{
    s_bitmap_t *bitmap;
    uint32 b_count, i_count;
    s_ext2_bg_data_t *bg_data;
    uint32 sector, bytes_count, sector_bytes;

    kassert(info);
    kassert(disk_buffer_legal_p(buf));

    sector = sector_offset;
    bg_data = kmalloc(sizeof(*bg_data));
    sector_bytes = disk_descriptor_sector_bytes(device_id);

    /* block bitmap */
    b_count = fs_ext2_bg_info_block_count(info);
    bytes_count = arithmetic_rate_up(b_count, 8);
    bitmap = fs_ext2_bitmap_place(buf, device_id, sector, bytes_count);
    fs_ext2_bg_data_block_bitmap_set(bg_data, bitmap);
    sector += arithmetic_rate_up(bytes_count, sector_bytes);

    /* inode bitmap */
    i_count = fs_ext2_bg_info_inode_count(info);
    bytes_count = arithmetic_rate_up(b_count, 8);
    bitmap = fs_ext2_bitmap_place(buf, device_id, sector, bytes_count);
    fs_ext2_bg_data_inode_bitmap_set(bg_data, bitmap);
    sector += arithmetic_rate_up(bytes_count, sector_bytes);

    /* inode table sector addr */
    fs_ext2_bg_data_inode_sector_addr_set(bg_data, sector);
    bytes_count = sizeof(s_ext2_inode_t) * i_count;
    sector += arithmetic_rate_up(bytes_count, sector_bytes);

    /* block table sector addr */
    fs_ext2_bg_data_block_sector_addr_set(bg_data, sector);

    return bg_data;
}

static inline void
fs_ext2_bg_data_initialize(s_ext2_dspr_t *dspr, s_disk_pt_t *pt,
    e_disk_id_t device_id)
{
    s_disk_buf_t *buf;
    s_ext2_bg_data_t *data;
    uint32 i, block_limit, group_blocks;
    s_ext2_bg_info_t *info, *info_primary;
    uint32 sector, block_bytes, sector_bytes, tmp;

    kassert(fs_ext2_descriptor_legal_p(dspr));
    kassert(disk_partition_legal_p(pt));
    kassert(disk_partition_used_p(pt));

    buf = disk_buffer_create(EXT2_BUFFER_MAX);
    info_primary = fs_ext2_descriptor_bg_info(dspr);
    block_bytes = fs_ext2_bg_block_size(info_primary);
    sector_bytes = disk_descriptor_sector_bytes(device_id);

    i = 0;
    block_limit = fs_ext2_bg_info_total_block_count(info_primary);
    group_blocks = fs_ext2_bg_info_block_count(info_primary);

    while (i < block_limit) {
        sector = fs_ext2_block_addr_to_sector(pt, i, block_bytes, sector_bytes);
        info = fs_ext2_bg_info_create(buf, device_id, sector);

        if (fs_ext2_bg_info_valid_p(info)) { /* skip superblock and bgd */
            tmp = EXT2_SBLOCK_OFFSET + sizeof(*info);
            tmp = arithmetic_rate_up(tmp, block_bytes); /* block count */
            sector += tmp * block_bytes / sector_bytes;
        }

        data = fs_ext2_bg_data_create(info_primary, buf, sector, device_id);
        fs_ext2_descriptor_bg_data_appned(dspr, data);

        fs_ext2_bg_info_destroy(&info);
        i += group_blocks;
    }

    disk_buffer_destroy(&buf);
}

static inline s_ext2_dspr_t *
fs_ext2_partition_initialize(s_disk_pt_t *pt, e_disk_id_t device_id)
{
    s_disk_buf_t *buf;
    uint32 bytes_count;
    s_ext2_dspr_t *dspr;
    s_ext2_bg_info_t *info;
    uint32 s_bytes, s_offset;

    kassert(disk_partition_legal_p(pt));
    kassert(disk_partition_used_p(pt));
    kassert(device_id < disk_descriptor_limit());

    dspr = NULL;
    bytes_count = EXT2_SBLOCK_OFFSET;
    s_bytes = disk_descriptor_sector_bytes(device_id);
    s_offset = disk_partition_sector_offset(pt);
    bytes_count += arithmetic_rate_up(sizeof(*info), s_bytes) * s_bytes;

    buf = disk_buffer_create(bytes_count);
    info = fs_ext2_bg_info_create(buf, device_id, s_offset);

    if (fs_ext2_bg_info_invalid_p(info)) {
        fs_ext2_bg_info_destroy(&info);
    } else {
        dspr = fs_ext2_descriptor_create(device_id, pt, info);
        fs_ext2_bg_data_initialize(dspr, pt, device_id);
    }

    disk_buffer_destroy(&buf);

    return dspr;
}

static inline void
fs_ext2_device_initialize(s_vfs_node_t *root, e_disk_id_t device_id,
    s_ext2_dspr_table_t *dspr_table)
{
    uint32 i, limit;
    s_ext2_dspr_t *dspr;
    s_disk_pt_t *disk_pt;
    s_vfs_node_t *vfs_node;
    s_disk_pt_table_t *disk_pt_table;

    kassert(vfs_node_legal_p(root));
    kassert(fs_ext2_descriptor_table_legal_p(dspr_table));
    kassert(device_id < disk_descriptor_limit());

    disk_pt_table = disk_descriptor_pt_table(device_id);

    i = 0;
    limit = DISK_PT_TABLE_SIZE;

    while (i < limit) {
        dspr = NULL;
        disk_pt = disk_partition_table_entry(disk_pt_table, i);

        if (disk_partition_used_p(disk_pt)) {
            dspr = fs_ext2_partition_initialize(disk_pt, device_id);
        }

        if (dspr) {
            fs_ext2_descriptor_table_append(dspr_table, dspr);
        }

        if (dspr && disk_partition_bootable_p(disk_pt)) {
            vfs_node = fs_ext2_descriptor_vfs_tree_build(dspr);
            vfs_sub_list_add(root, vfs_node);
        }

        i++;
    }
}

static inline void
fs_ext2_descriptor_table_initialize(s_ext2_dspr_table_t *dspr_table)
{
    uint32 bytes_count;

    kassert(dspr_table);

    bytes_count = sizeof(dspr_table->dspr_array[0]) * EXT2_DESCCRIPTOR_MAX;

    dspr_table->dspr_array = kmalloc(bytes_count);
    dspr_table->index = 0;
    dspr_table->size = EXT2_DESCCRIPTOR_MAX;
}

static inline void
fs_ext2_initialize_i(s_vfs_node_t *root)
{
    uint32 i, limit;
    s_ext2_dspr_table_t *dspr_table;

    kassert(vfs_node_legal_p(root));

    dspr_table = fs_ext2_descriptor_table_obtain();
    fs_ext2_descriptor_table_initialize(dspr_table);

    i = DEVICE_START;
    limit = disk_descriptor_limit();

    while (i < limit) {
        if (disk_descriptor_is_active_p(i)) {
            fs_ext2_device_initialize(root, i, dspr_table);
        }

        i++;
    }

    fs_ext2_descriptor_table_print(dspr_table);
}

void
fs_ext2_initialize(s_vfs_node_t *root)
{
    if (vfs_node_illegal_p(root)) {
        return;
    } else {
        fs_ext2_initialize_i(root);
    }
}

