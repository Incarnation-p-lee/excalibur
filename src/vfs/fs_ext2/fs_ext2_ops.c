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
    s_ext2_block_group_t *group)
{
    uint32 index;
    s_ext2_block_group_t **block_group_array;

    /* group == NULL is allowed here */
    kassert(fs_ext2_descriptor_legal_p(dspr));

    block_group_array = fs_ext2_descriptor_block_group_array(dspr);
    index = fs_ext2_descriptor_index(dspr);

    block_group_array[index++] = group;

    fs_ext2_descriptor_index_set(dspr, index);
}

static inline s_ext2_dspr_t *
fs_ext2_descriptor_create(e_disk_id_t device_id, s_disk_pt_t *pt)
{
    uint32 size;
    uint32 bytes_count;
    s_ext2_dspr_t *dspr;

    kassert(disk_partition_legal_p(pt));
    kassert(device_id < disk_descriptor_limit());

    size = EXT2_BLOCK_GROUP_MAX;
    bytes_count = sizeof(dspr->block_group_array[0]) * size;

    dspr = kmalloc(sizeof(*dspr));
    dspr->block_group_array = kmalloc(bytes_count);

    dspr->device_id = device_id;
    dspr->disk_pt = pt;
    dspr->index = 0;
    dspr->size = size;

    return dspr;
}

static inline void
fs_ext2_descriptor_destroy(s_ext2_dspr_t **dspr)
{
    kassert(dspr);
    kassert(*dspr);

    kfree((*dspr)->block_group_array);
    kfree(*dspr);

    *dspr = NULL;
}

static inline s_ext2_block_group_t *
fs_ext2_block_group_create(s_disk_buf_t *disk_buf, e_disk_id_t device_id,
    uint32 sector_offset)
{
    uint32 offset;
    f_disk_read_t read;
    s_ext2_block_group_t *group;

    kassert(sector_offset);
    kassert(disk_buffer_legal_p(disk_buf));

    offset = EXT2_SBLOCK_OFFSET;
    group = kmalloc(sizeof(*group));

    read = disk_descriptor_read(device_id);

    read(disk_buf, device_id, sector_offset, offset + sizeof(*group));
    disk_buffer_copy(group, disk_buf, offset, sizeof(*group));

    return group;
}

static inline void
fs_ext2_block_group_destroy(s_ext2_block_group_t **group)
{
    kassert(group);
    kassert(*group);

    kfree(*group);
    *group = NULL;
}

/*
 * INITIALIZE the rest block groups without primary block. Depending upon the
 * revision of Ext2 used, some or all block groups may also contain a backup
 * copy of the Superblock and the Block Group Descriptor Table.
 */
static inline void
fs_ext2_descriptor_initialize(s_disk_pt_t *disk_pt, e_disk_id_t device_id,
    s_ext2_dspr_table_t *dspr_table, s_disk_buf_t *buf,
    s_ext2_block_group_t *group_primary)
{
    s_ext2_dspr_t *dspr;
    s_ext2_block_group_t *group;
    uint32 sector_offset, sector_limit, sector_step;

    kassert(group_primary);
    kassert(disk_buffer_legal_p(buf));
    kassert(disk_partition_legal_p(disk_pt));
    kassert(device_id < disk_descriptor_limit());
    kassert(fs_ext2_descriptor_table_legal_p(dspr_table));

    dspr = fs_ext2_descriptor_create(device_id, disk_pt);
    fs_ext2_descriptor_block_group_append(dspr, group_primary);

    sector_offset = disk_partition_sector_offset(disk_pt);
    sector_limit = sector_offset + disk_partition_sector_count(disk_pt);
    sector_step = fs_ext2_block_group_sector_count(group_primary, device_id);

    sector_offset += sector_step; /* skip primary block group */

    while (sector_offset < sector_limit) {
        group = fs_ext2_block_group_create(buf, device_id, sector_offset);

        if (fs_ext2_block_group_invalid_p(group)) {
            fs_ext2_block_group_destroy(&group);
        }

        fs_ext2_descriptor_block_group_append(dspr, group);
        sector_offset += sector_step;
    }

    fs_ext2_descriptor_table_append(dspr_table, dspr);
}

static inline void
fs_ext2_partition_initialize(s_disk_pt_t *pt, e_disk_id_t device_id,
    s_ext2_dspr_table_t *dspr_table)
{
    s_disk_buf_t *buf;
    uint32 bytes_count;
    s_ext2_block_group_t *group;
    uint32 sector_bytes, sector_offset;

    kassert(disk_partition_legal_p(pt));
    kassert(disk_partition_used_p(pt));
    kassert(fs_ext2_descriptor_table_legal_p(dspr_table));
    kassert(device_id < disk_descriptor_limit());

    bytes_count = EXT2_SBLOCK_OFFSET;
    sector_bytes = disk_descriptor_sector_bytes(device_id);
    sector_offset = disk_partition_sector_offset(pt);
    bytes_count += ((sizeof(*group) / sector_bytes) + 1) * sector_bytes;

    buf = disk_buffer_create(bytes_count);
    group = fs_ext2_block_group_create(buf, device_id, sector_offset);

    if (fs_ext2_block_group_invalid_p(group)) {
        fs_ext2_block_group_destroy(&group);
    // } else if (disk_partition_bootable_p(pt)) {
    } else {
        fs_ext2_descriptor_initialize(pt, device_id, dspr_table, buf, group);
    }

    disk_buffer_destroy(&buf);
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
            fs_ext2_partition_initialize(disk_pt, device_id, dspr_table);
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

