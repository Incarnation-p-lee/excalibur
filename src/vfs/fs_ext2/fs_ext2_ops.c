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

static inline void
fs_ext2_descriptor_block_group_append(s_ext2_dspr_t *dspr,
    s_ext2_block_group_t *block_group)
{
    uint32 index;
    s_ext2_block_group_t **block_group_array;

    kassert(block_group);
    kassert(fs_ext2_descriptor_legal_p(dspr));

    block_group_array = fs_ext2_descriptor_block_group_array(dspr);
    index = fs_ext2_descriptor_index(dspr);

    block_group_array[index++] = block_group;

    fs_ext2_descriptor_index_set(dspr, index);
}

static inline s_ext2_dspr_t *
fs_ext2_descriptor_create(e_disk_id_t device_id, uint32 size, s_disk_pt_t *pt)
{
    uint32 bytes_count;
    s_ext2_dspr_t *dspr;

    kassert(size);
    kassert(disk_partition_legal_p(pt));
    kassert(device_id < disk_descriptor_limit());

    bytes_count = sizeof(dspr->block_group_array[0]) * size;

    dspr = kmalloc(sizeof(*dspr));
    dspr->block_group_array = kmalloc(bytes_count);

    dspr->device_id = device_id;
    dspr->disk_pt = pt;
    dspr->index = 0;
    dspr->size = size;

    return dspr;
}

static inline s_ext2_block_group_t *
fs_ext2_block_group_create(s_ext2_dspr_t *dspr, s_disk_buf_t *disk_buf,
    uint32 secotr_offset)
{
    f_disk_read_t read;
    e_disk_id_t device_id;
    s_ext2_block_group_t *block_group;

    kassert(secotr_offset);
    kassert(disk_buffer_legal_p(disk_buf));
    kassert(fs_ext2_descriptor_legal_p(dspr));

    device_id = fs_ext2_descriptor_device_id(dspr);
    read = disk_descriptor_read(device_id);

    block_group = kmalloc(sizeof(*block_group));

    read(disk_buf, device_id, secotr_offset, sizeof(*block_group));
    disk_buffer_copy(block_group, disk_buf, 0, sizeof(*block_group));

    return block_group;
}

static inline void
fs_ext2_block_group_destroy(s_ext2_block_group_t **block_group)
{
    kassert(block_group);
    kassert(*block_group);

    kfree(*block_group);
    *block_group = NULL;
}

static inline void
fs_ext2_partition_initialize(s_disk_pt_t *disk_pt,
    s_ext2_dspr_table_t *dspr_table, e_disk_id_t device_id)
{
    uint32 s_bytes;
    uint32 bytes_count;
    s_ext2_dspr_t *dspr;
    s_disk_buf_t *disk_buf;
    uint32 s_offset, s_limit; /* s -> sector */
    s_ext2_block_group_t *block_group;

    kassert(disk_partition_legal_p(disk_pt));
    kassert(disk_partition_used_p(disk_pt));
    kassert(fs_ext2_descriptor_table_legal_p(dspr_table));
    kassert(device_id < disk_descriptor_limit());

    s_bytes = disk_descriptor_sector_bytes(device_id);
    bytes_count = ((sizeof(*block_group) / s_bytes) + 1) * s_bytes;
    disk_buf = disk_buffer_create(bytes_count);

    dspr = fs_ext2_descriptor_create(device_id, EXT2_BLOCK_GROUP_MAX, disk_pt);
    s_offset = disk_partition_sector_offset(disk_pt);
    block_group = fs_ext2_block_group_create(dspr, disk_buf, s_offset);

    if (!fs_ext2_block_group_is_ext2_p(block_group)) {
        fs_ext2_block_group_destroy(&block_group);
    } else {
        s_limit = s_offset + disk_partition_sector_count(disk_pt);
        s_offset += fs_ext2_block_group_sector_count(block_group, s_bytes);
        fs_ext2_descriptor_block_group_append(dspr, block_group);

        while (s_offset < s_limit) {
            block_group = fs_ext2_block_group_create(dspr, disk_buf, s_offset);
            fs_ext2_descriptor_block_group_append(dspr, block_group);

            s_offset += fs_ext2_block_group_sector_count(block_group, s_bytes);
        }

        fs_ext2_descriptor_table_append(dspr_table, dspr);
    }

    disk_buffer_destroy(&disk_buf);
}

static inline void
fs_ext2_device_initialize(s_vfs_node_t *root, e_disk_id_t device_id,
    s_ext2_dspr_table_t *dspr_table)
{
    uint32 i, limit;
    s_disk_pt_t *disk_pt;
    s_disk_pt_table_t *disk_pt_table;

    kassert(vfs_node_legal_p(root));
    kassert(fs_ext2_descriptor_table_legal_p(dspr_table));
    kassert(device_id < disk_descriptor_limit());

    disk_pt_table = disk_descriptor_pt_table(device_id);

    i = 0;
    limit = DISK_PT_TABLE_SIZE;

    while (i < limit) {
        disk_pt = disk_partition_table_entry(disk_pt_table, i);

        if (disk_partition_used_p(disk_pt)) {
            fs_ext2_partition_initialize(disk_pt, dspr_table, device_id);
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

    printf_vga_tk("Ext2 fs initialized.\n");
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

