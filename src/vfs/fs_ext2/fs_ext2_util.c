static inline bool
fs_ext2_descriptor_legal_p(s_ext2_dspr_t *dspr)
{
    if (dspr == NULL) {
        return false;
    } else if (dspr->disk_pt == NULL) {
        return false;
    } else if (dspr->block_group_array == NULL) {
        return false;
    } else if (dspr->size == 0) {
        return false;
    } else {
        return true;
    }
}

static inline bool
fs_ext2_descriptor_illegal_p(s_ext2_dspr_t *dspr)
{
    return !fs_ext2_descriptor_legal_p(dspr);
}

static inline e_disk_id_t
fs_ext2_descriptor_device_id(s_ext2_dspr_t *dspr)
{
    kassert(fs_ext2_descriptor_legal_p(dspr));

    return dspr->device_id;
}

static inline void
fs_ext2_descriptor_device_id_set(s_ext2_dspr_t *dspr, e_disk_id_t device_id)
{
    kassert(fs_ext2_descriptor_legal_p(dspr));

    dspr->device_id = device_id;
}

static inline s_disk_pt_t *
fs_ext2_descriptor_disk_pt(s_ext2_dspr_t *dspr)
{
    kassert(fs_ext2_descriptor_legal_p(dspr));

    return dspr->disk_pt;
}

static inline void
fs_ext2_descriptor_disk_pt_set(s_ext2_dspr_t *dspr, s_disk_pt_t *disk_pt)
{
    kassert(fs_ext2_descriptor_legal_p(dspr));

    dspr->disk_pt = disk_pt;
}

static inline uint32
fs_ext2_descriptor_size(s_ext2_dspr_t *dspr)
{
    kassert(fs_ext2_descriptor_legal_p(dspr));

    return dspr->size;
}

static inline void
fs_ext2_descriptor_size_set(s_ext2_dspr_t *dspr, uint32 size)
{
    kassert(fs_ext2_descriptor_legal_p(dspr));

    dspr->size = size;
}

static inline s_ext2_dspr_table_t *
fs_ext2_descriptor_table_obtain(void)
{
    return &ext2_dspr_table;
}

static inline bool
fs_ext2_descriptor_table_legal_p(s_ext2_dspr_table_t *dspr_table)
{
    if (dspr_table == NULL) {
        return false;
    } else if (dspr_table->index > dspr_table->size) {
        return false;
    } else if (dspr_table->size == 0) {
        return false;
    } else if (dspr_table->dspr_array == NULL) {
        return false;
    } else {
        return true;
    }
}

static inline bool
fs_ext2_descriptor_table_illegal_p(s_ext2_dspr_table_t *dspr_table)
{
    return !fs_ext2_descriptor_table_legal_p(dspr_table);
}

static inline uint32
fs_ext2_descriptor_table_index(s_ext2_dspr_table_t *dspr_table)
{
    kassert(fs_ext2_descriptor_table_legal_p(dspr_table));

    return dspr_table->index;
}

static inline uint32
fs_ext2_descriptor_table_limit(s_ext2_dspr_table_t *dspr_table)
{
    return fs_ext2_descriptor_table_index(dspr_table);
}

static inline void
fs_ext2_descriptor_table_index_set(s_ext2_dspr_table_t *dspr_table,
    uint32 index)
{
    kassert(fs_ext2_descriptor_table_legal_p(dspr_table));

    dspr_table->index = index;
}

static inline uint32
fs_ext2_descriptor_table_size(s_ext2_dspr_table_t *dspr_table)
{
    kassert(fs_ext2_descriptor_table_legal_p(dspr_table));

    return dspr_table->size;
}

static inline void
fs_ext2_descriptor_table_size_set(s_ext2_dspr_table_t *dspr_table,
    uint32 size)
{
    kassert(fs_ext2_descriptor_table_legal_p(dspr_table));

    dspr_table->size = size;
}

static inline s_ext2_dspr_t **
fs_ext2_descriptor_table_dspr_array(s_ext2_dspr_table_t *dspr_table)
{
    kassert(fs_ext2_descriptor_table_legal_p(dspr_table));

    return dspr_table->dspr_array;
}

static inline bool
fs_ext2_descriptor_table_full_p(s_ext2_dspr_table_t *dspr_table)
{
    uint32 size;
    uint32 index;

    kassert(fs_ext2_descriptor_table_legal_p(dspr_table));

    size = fs_ext2_descriptor_table_size(dspr_table);
    index = fs_ext2_descriptor_table_index(dspr_table);

    if (size == index) {
        return true;
    } else {
        return false;
    }
}

static inline uint16
fs_ext2_superblock_signature(s_ext2_spbk_t *spbk)
{
    kassert(spbk);

    return spbk->signature;
}

static inline bool
fs_ext2_superblock_valid_p(s_ext2_spbk_t *spbk)
{
    kassert(spbk);

    if (fs_ext2_superblock_signature(spbk) == EXT2_SIGNATURE) {
        return true;
    } else {
        return false;
    }
}

static inline s_ext2_spbk_t *
fs_ext2_block_group_superblock(s_ext2_block_group_t *group)
{
    kassert(group);

    return &group->superblock;
}

static inline bool
fs_ext2_block_group_valid_p(s_ext2_block_group_t *group)
{
    s_ext2_spbk_t *spbk;

    kassert(group);

    spbk = fs_ext2_block_group_superblock(group);

    return fs_ext2_superblock_valid_p(spbk);
}

static inline bool
fs_ext2_block_group_invalid_p(s_ext2_block_group_t *group)
{
    return !fs_ext2_block_group_valid_p(group);
}

static inline uint32
fs_ext2_superblock_group_block_count(s_ext2_spbk_t *spbk)
{
    kassert(spbk);

    return spbk->group_block_count;
}

static inline uint32
fs_ext2_block_group_block_count(s_ext2_block_group_t *group)
{
    s_ext2_spbk_t *spbk;

    kassert(group);

    spbk = fs_ext2_block_group_superblock(group);

    return fs_ext2_superblock_group_block_count(spbk);
}

static inline uint32
fs_ext2_superblock_unallocated_block_count(s_ext2_spbk_t *spbk)
{
    kassert(spbk);

    return spbk->unalloc_block_count;
}

static inline uint32
fs_ext2_block_group_unallocated_block_count(s_ext2_block_group_t *group)
{
    s_ext2_spbk_t *spbk;

    kassert(group);

    spbk = fs_ext2_block_group_superblock(group);

    return fs_ext2_superblock_unallocated_block_count(spbk);
}

static inline uint32
fs_ext2_superblock_block_size(s_ext2_spbk_t *spbk)
{
    kassert(spbk);

    return 1 << (spbk->block_size + 10); /* log2(block_size) - 10 */
}

static inline uint32
fs_ext2_block_group_block_size(s_ext2_block_group_t *group)
{
    s_ext2_spbk_t *spbk;

    kassert(group);

    spbk = fs_ext2_block_group_superblock(group);

    return fs_ext2_superblock_block_size(spbk);
}

static inline uint32
fs_ext2_superblock_total_block_count(s_ext2_spbk_t *spbk)
{
    kassert(spbk);

    return spbk->total_block_count;
}

static inline uint32
fs_ext2_block_group_total_block_count(s_ext2_block_group_t *group)
{
    s_ext2_spbk_t *spbk;

    kassert(group);

    spbk = fs_ext2_block_group_superblock(group);

    return fs_ext2_superblock_total_block_count(spbk);
}

static inline uint32
fs_ext2_superblock_major_version(s_ext2_spbk_t *spbk)
{
    kassert(spbk);

    return spbk->major_version;
}

static inline uint32
fs_ext2_block_group_major_version(s_ext2_block_group_t *group)
{
    s_ext2_spbk_t *spbk;

    kassert(group);

    spbk = fs_ext2_block_group_superblock(group);

    return fs_ext2_superblock_major_version(spbk);
}

static inline uint32
fs_ext2_block_group_sector_count(s_ext2_block_group_t *group,
    e_disk_id_t device_id)
{
    uint32 sector_bytes;
    uint32 sector_count;
    uint32 block_size, block_count;

    kassert(group);

    sector_bytes = disk_descriptor_sector_bytes(device_id);
    block_size = fs_ext2_block_group_block_size(group);
    block_count = fs_ext2_block_group_block_count(group);
    sector_count = block_size * block_count / sector_bytes;

    kassert(block_size * block_count % sector_bytes == 0);

    return sector_count;
}

static inline s_ext2_block_group_t **
fs_ext2_descriptor_block_group_array(s_ext2_dspr_t *dspr)
{
    kassert(fs_ext2_descriptor_legal_p(dspr));

    return dspr->block_group_array;
}

static inline s_ext2_block_group_t *
fs_ext2_descriptor_block_group_entry(s_ext2_dspr_t *dspr, uint32 i)
{
    s_ext2_block_group_t **block_group_array;

    kassert(fs_ext2_descriptor_legal_p(dspr));
    kassert(i < fs_ext2_descriptor_limit(dspr));

    block_group_array = fs_ext2_descriptor_block_group_array(dspr);

    return block_group_array[i];
}

static inline uint32
fs_ext2_descriptor_index(s_ext2_dspr_t *dspr)
{
    kassert(fs_ext2_descriptor_legal_p(dspr));

    return dspr->index;
}

static inline uint32
fs_ext2_descriptor_limit(s_ext2_dspr_t *dspr)
{
    return fs_ext2_descriptor_index(dspr);
}

static inline void
fs_ext2_descriptor_index_set(s_ext2_dspr_t *dspr, uint32 index)
{
    kassert(fs_ext2_descriptor_legal_p(dspr));

    dspr->index = index;
}

static inline s_ext2_dspr_t *
fs_ext2_descriptor_table_entry(s_ext2_dspr_table_t *dspr_table, uint32 i)
{
    s_ext2_dspr_t **dspr_array;

    kassert(fs_ext2_descriptor_table_legal_p(dspr_table));
    kassert(i < fs_ext2_descriptor_table_limit(dspr_table));

    dspr_array = fs_ext2_descriptor_table_dspr_array(dspr_table);

    return dspr_array[i];
}

