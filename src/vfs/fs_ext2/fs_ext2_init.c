static inline void
fs_ext2_dspr_table_append(s_ext2_dspr_table_t *dspr_table,
    s_ext2_dspr_t *dspr)
{
    uint32 index;
    s_ext2_dspr_t **dspr_array;

    kassert(fs_ext2_dspr_table_legal_p(dspr_table));
    kassert(fs_ext2_dspr_legal_p(dspr));
    kassert(!fs_ext2_dspr_table_full_p(dspr_table));

    dspr_array = fs_ext2_dspr_table_dspr_array(dspr_table);
    index = fs_ext2_dspr_table_index(dspr_table);

    dspr_array[index++] = dspr;

    fs_ext2_dspr_table_index_set(dspr_table, index);
}

static inline s_ext2_dspr_t *
fs_ext2_dspr_create(e_disk_id_t device_id, s_disk_pt_t *pt,
    s_ext2_spbk_t *superblock, s_ext2_bgd_t *bgd_table)
{
    uint32 bg_count;
    s_ext2_dspr_t *dspr;

    kassert(bgd_table);
    kassert(disk_partition_legal_p(pt));
    kassert(device_id < disk_descriptor_limit());
    kassert(fs_ext2_superblock_valid_p(superblock));

    bg_count = fs_ext2_superblock_block_group_count(superblock);

    dspr = kmalloc(sizeof(*dspr));
    dspr->map_array = kmalloc(sizeof(dspr->map_array[0]) * bg_count);

    dspr->device_id = device_id;
    dspr->disk_pt = pt;
    dspr->superblock = superblock;
    dspr->bgd_table = bgd_table;
    dspr->bg_count = bg_count;

    return dspr;
}

static inline void
fs_ext2_bgd_map_destroy(s_ext2_bgd_map_t **map)
{
    kassert(map);
    kassert(fs_ext2_bgd_map_legal_p(*map));

    bitmap_destroy(&(*map)->block_bitmap);
    bitmap_destroy(&(*map)->inode_bitmap);

    kfree(*map);

    *map = NULL;
}

static inline void
fs_ext2_dspr_bgd_bitmap_destroy(s_ext2_dspr_t *dspr)
{
    uint32 i;
    uint32 limit;
    s_ext2_bgd_map_t *map;

    kassert(fs_ext2_dspr_legal_p(dspr));

    i = 0;
    limit = fs_ext2_dspr_group_block_count(dspr);

    while (i < limit) {
        map = fs_ext2_dspr_bgd_map(dspr, i);
        fs_ext2_bgd_map_destroy(&map);

        i++;
    }
}

static inline void
fs_ext2_dspr_destroy(s_ext2_dspr_t **dspr)
{
    kassert(dspr);
    kassert(fs_ext2_dspr_legal_p(*dspr));

    fs_ext2_dspr_bgd_bitmap_destroy(*dspr);

    kfree((*dspr)->superblock);
    kfree((*dspr)->bgd_table);
    kfree((*dspr)->map_array);
    kfree(*dspr);

    *dspr = NULL;
}

static inline s_ext2_spbk_t *
fs_ext2_superblock_create(s_disk_buf_t *buf, e_disk_id_t device_id,
    uint32 sector_offset)
{
    uint32 cpy_bytes;
    uint32 read_bytes;
    f_disk_read_t read;
    s_ext2_spbk_t *superblock;

    kassert(sector_offset);
    kassert(disk_buffer_legal_p(buf));

    superblock = kmalloc(sizeof(*superblock));
    read = disk_descriptor_read(device_id);

    read_bytes = read(buf, device_id, sector_offset, sizeof(*superblock));

    if (IS_SIZE_INVALID_P(read_bytes)) {
        KERNEL_PANIC("Failed to read data from device.\n");
    }

    cpy_bytes = disk_buffer_copy(superblock, buf, 0, sizeof(*superblock));

    if (IS_SIZE_INVALID_P(cpy_bytes)) {
        KERNEL_PANIC("Unable to create superblock of ext2 filesystem.\n");
    }

    return superblock;
}

static inline void
fs_ext2_superblock_destroy(s_ext2_spbk_t **superblock)
{
    kassert(superblock);
    kassert(*superblock);

    kfree(*superblock);

    *superblock = NULL;
}

static inline s_ext2_bgd_t *
fs_ext2_bgd_table_create(s_disk_buf_t *buf, e_disk_id_t device_id,
    uint32 sector_offset, uint32 size)
{
    uint32 cpy_bytes;
    uint32 read_bytes;
    uint32 bytes_count;
    f_disk_read_t read;
    s_ext2_bgd_t *bgd_table;

    kassert(size);
    kassert(sector_offset);
    kassert(disk_buffer_legal_p(buf));

    bytes_count = sizeof(*bgd_table) * size;
    bgd_table = kmalloc(bytes_count);
    read = disk_descriptor_read(device_id);

    read_bytes = read(buf, device_id, sector_offset, bytes_count);

    if (IS_SIZE_INVALID_P(read_bytes)) {
        KERNEL_PANIC("Failed to read data from device.\n");
    }

    cpy_bytes = disk_buffer_copy(bgd_table, buf, 0, bytes_count);

    if (IS_SIZE_INVALID_P(cpy_bytes)) {
        KERNEL_PANIC("Unable to create bgd table of ext2 filesystem.\n");
    }

    return bgd_table;
}

static inline void
fs_ext2_bgd_table_destroy(s_ext2_bgd_t **bgd_table)
{
    kassert(bgd_table);
    kassert(*bgd_table);

    kfree(*bgd_table);

    *bgd_table = NULL;
}

static inline s_bitmap_t *
fs_ext2_bitmap_place(s_disk_buf_t *buf, e_disk_id_t device_id,
    uint32 sector, uint32 bytes_count)
{
    uint8 *array;
    uint32 cpy_bytes;
    uint32 read_bytes;
    s_bitmap_t *bitmap;
    f_disk_read_t read;

    kassert(bytes_count);
    kassert(sector);
    kassert(disk_buffer_legal_p(buf));

    array = kmalloc(bytes_count);
    read = disk_descriptor_read(device_id);

    read_bytes = read(buf, device_id, sector, bytes_count);

    if (IS_SIZE_INVALID_P(read_bytes)) {
        KERNEL_PANIC("Failed to read data from device.\n");
    }

    cpy_bytes = disk_buffer_copy(array, buf, 0, bytes_count);

    if (IS_SIZE_INVALID_P(cpy_bytes)) {
        KERNEL_PANIC("Unable to create array of bitmap.\n");
    }

    bitmap = bitmap_place(array, bytes_count, bytes_count * 8);

    return bitmap;
}

static inline uint32
fs_ext2_block_addr_to_sector(uint32 block_addr, uint32 block_bytes,
    uint32 sector_offset, uint32 sector_bytes)
{
    uint32 sector;

    kassert(block_bytes);
    kassert(sector_bytes);
    kassert((block_bytes % sector_bytes) == 0);

    sector = sector_offset;
    sector += block_addr * block_bytes / sector_bytes;

    return sector;
}

static inline s_ext2_bgd_map_t *
fs_ext2_bgd_map_create(s_disk_buf_t *buf, e_disk_id_t device_id,
    s_ext2_dspr_t *dspr, s_ext2_bgd_t *bgd)
{
    uint32 addr;
    s_bitmap_t *bitmap;
    uint32 bytes_count;
    s_ext2_bgd_map_t *map;
    uint32 b_count, b_bytes, i_count;
    uint32 sector, s_offset, s_bytes;

    kassert(bgd);
    kassert(disk_buffer_legal_p(buf));
    kassert(fs_ext2_dspr_legal_p(dspr));

    b_bytes = fs_ext2_dspr_block_size(dspr);
    s_offset = fs_ext2_dspr_sector_offset(dspr);
    s_bytes = disk_descriptor_sector_bytes(device_id);

    map = kmalloc(sizeof(*map));

    /* block bitmap */
    addr = fs_ext2_bgd_block_bitmap_addr(bgd);
    b_count = fs_ext2_dspr_group_block_count(dspr);
    bytes_count = arithmetic_rate_up(b_count, 8);
    sector = fs_ext2_block_addr_to_sector(addr, b_bytes, s_offset, s_bytes);

    bitmap = fs_ext2_bitmap_place(buf, device_id, sector, bytes_count);
    fs_ext2_bgd_map_block_bitmap_set(map, bitmap);

    /* inode bitmap */
    addr = fs_ext2_bgd_inode_bitmap_addr(bgd);
    i_count = fs_ext2_dspr_group_inode_count(dspr);
    bytes_count = arithmetic_rate_up(i_count, 8);
    sector = fs_ext2_block_addr_to_sector(addr, b_bytes, s_offset, s_bytes);

    bitmap = fs_ext2_bitmap_place(buf, device_id, sector, bytes_count);
    fs_ext2_bgd_map_inode_bitmap_set(map, bitmap);

    fs_ext2_bgd_map_b_bitmap_is_dirty_set(map, /* is_dirty = */false);
    fs_ext2_bgd_map_i_bitmap_is_dirty_set(map, /* is_dirty = */false);

    return map;
}

static inline void
fs_ext2_dspr_map_array_initialize(s_ext2_dspr_t *dspr, s_disk_buf_t *buf,
    e_disk_id_t device_id)
{
    uint32 i, limit;
    s_ext2_bgd_t *bgd;
    s_ext2_bgd_map_t *map;

    kassert(disk_buffer_legal_p(buf));
    kassert(fs_ext2_dspr_legal_p(dspr));

    i = 0;
    limit = fs_ext2_dspr_bg_count(dspr);

    while (i < limit) {
        bgd = fs_ext2_dspr_bgd(dspr, i);
        map = fs_ext2_bgd_map_create(buf, device_id, dspr, bgd);
        fs_ext2_dspr_bgd_map_set(dspr, i, map);

        i++;
    }
}

static inline s_ext2_dspr_t *
fs_ext2_partition_initialize(s_disk_pt_t *pt, e_disk_id_t device_id)
{
    s_disk_buf_t *buf;
    s_ext2_dspr_t *dspr;
    s_ext2_bgd_t *bgd_table;
    s_ext2_spbk_t *superblock;
    uint32 s_bytes, s_offset, size;

    kassert(disk_partition_legal_p(pt));
    kassert(disk_partition_used_p(pt));
    kassert(device_id < disk_descriptor_limit());

    dspr = NULL;
    s_bytes = disk_descriptor_sector_bytes(device_id);
    s_offset = disk_partition_sector_offset(pt);
    s_offset += EXT2_SBLOCK_OFFSET / s_bytes; /* skip reserved block */

    buf = disk_buffer_create(EXT2_BUFFER_MAX);
    superblock = fs_ext2_superblock_create(buf, device_id, s_offset);

    if (fs_ext2_superblock_invalid_p(superblock)) {
        fs_ext2_superblock_destroy(&superblock);
    } else {
        s_offset += fs_ext2_superblock_block_size(superblock) / s_bytes;
        size = fs_ext2_superblock_block_group_count(superblock);
        bgd_table = fs_ext2_bgd_table_create(buf, device_id, s_offset, size);

        dspr = fs_ext2_dspr_create(device_id, pt, superblock, bgd_table);
        fs_ext2_dspr_map_array_initialize(dspr, buf, device_id);
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
    kassert(fs_ext2_dspr_table_legal_p(dspr_table));
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
            fs_ext2_dspr_table_append(dspr_table, dspr);
        }

        if (dspr && disk_partition_bootable_p(disk_pt)) {
            vfs_node = fs_ext2_dspr_vfs_tree_build(dspr);
            vfs_sub_list_add(root, vfs_node);
        }

        i++;
    }
}

static inline void
fs_ext2_dspr_table_initialize(s_ext2_dspr_table_t *dspr_table)
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

    dspr_table = fs_ext2_dspr_table_obtain();
    fs_ext2_dspr_table_initialize(dspr_table);

    i = DEVICE_START;
    limit = disk_descriptor_limit();

    while (i < limit) {
        if (disk_descriptor_is_active_p(i)) {
            fs_ext2_device_initialize(root, i, dspr_table);
        }

        i++;
    }

    // fs_ext2_dspr_table_print(dspr_table);
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

