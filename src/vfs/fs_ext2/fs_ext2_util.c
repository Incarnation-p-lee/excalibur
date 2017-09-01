static inline bool
fs_ext2_descriptor_legal_p(s_ext2_dspr_t *dspr)
{
    if (dspr == NULL) {
        return false;
    } else if (dspr->disk_pt == NULL) {
        return false;
    } else if (dspr->bg_data_array == NULL) {
        return false;
    } else if (dspr->bg_info == NULL) {
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
fs_ext2_bg_info_superblock(s_ext2_bg_info_t *bg_info)
{
    kassert(bg_info);

    return &bg_info->superblock;
}

static inline s_ext2_bgd_t *
fs_ext2_bg_info_decriptor(s_ext2_bg_info_t *bg_info)
{
    kassert(bg_info);

    return &bg_info->block_group_dspt;
}

static inline bool
fs_ext2_bg_info_valid_p(s_ext2_bg_info_t *bg_info)
{
    s_ext2_spbk_t *spbk;

    kassert(bg_info);

    spbk = fs_ext2_bg_info_superblock(bg_info);

    return fs_ext2_superblock_valid_p(spbk);
}

static inline bool
fs_ext2_bg_info_invalid_p(s_ext2_bg_info_t *bg_info)
{
    return !fs_ext2_bg_info_valid_p(bg_info);
}

static inline uint32
fs_ext2_superblock_group_block_count(s_ext2_spbk_t *spbk)
{
    kassert(spbk);

    return spbk->group_block_count;
}

static inline uint32
fs_ext2_bg_info_block_count(s_ext2_bg_info_t *bg_info)
{
    s_ext2_spbk_t *spbk;

    kassert(bg_info);

    spbk = fs_ext2_bg_info_superblock(bg_info);

    return fs_ext2_superblock_group_block_count(spbk);
}

static inline uint32
fs_ext2_superblock_unallocated_block_count(s_ext2_spbk_t *spbk)
{
    kassert(spbk);

    return spbk->unalloc_block_count;
}

static inline uint32
fs_ext2_bg_info_unallocated_block_count(s_ext2_bg_info_t *bg_info)
{
    s_ext2_spbk_t *spbk;

    kassert(bg_info);

    spbk = fs_ext2_bg_info_superblock(bg_info);

    return fs_ext2_superblock_unallocated_block_count(spbk);
}

static inline uint32
fs_ext2_superblock_unallocated_inode_count(s_ext2_spbk_t *spbk)
{
    kassert(spbk);

    return spbk->unalloc_inode_count;
}

static inline uint32
fs_ext2_bg_info_unallocated_inode_count(s_ext2_bg_info_t *bg_info)
{
    s_ext2_spbk_t *spbk;

    kassert(bg_info);

    spbk = fs_ext2_bg_info_superblock(bg_info);

    return fs_ext2_superblock_unallocated_inode_count(spbk);
}

static inline uint32
fs_ext2_superblock_block_nmbr(s_ext2_spbk_t *spbk)
{
    kassert(spbk);

    return spbk->superblock_nmbr;
}

static inline uint32
fs_ext2_bg_info_superblock_nmbr(s_ext2_bg_info_t *bg_info)
{
    s_ext2_spbk_t *spbk;

    kassert(bg_info);

    spbk = fs_ext2_bg_info_superblock(bg_info);

    return fs_ext2_superblock_block_nmbr(spbk);
}

static inline uint32
fs_ext2_superblock_reserved_count(s_ext2_spbk_t *spbk)
{
    kassert(spbk);

    return spbk->superblock_reserved_count;
}

static inline uint32
fs_ext2_bg_info_superblock_reserved_count(s_ext2_bg_info_t *bg_info)
{
    s_ext2_spbk_t *spbk;

    kassert(bg_info);

    spbk = fs_ext2_bg_info_superblock(bg_info);

    return fs_ext2_superblock_reserved_count(spbk);
}

static inline uint32
fs_ext2_block_descriptor_block_bitmap_addr(s_ext2_bgd_t *bgd)
{
    kassert(bgd);

    return bgd->block_bitmap_addr;
}

static inline uint32
fs_ext2_bg_info_block_bitmap_addr(s_ext2_bg_info_t *bg_info)
{
    s_ext2_bgd_t *bgd;

    kassert(bg_info);

    bgd = fs_ext2_bg_info_decriptor(bg_info);

    return fs_ext2_block_descriptor_block_bitmap_addr(bgd);
}

static inline uint32
fs_ext2_block_descriptor_inode_bitmap_addr(s_ext2_bgd_t *bgd)
{
    kassert(bgd);

    return bgd->inode_bitmap_addr;
}

static inline uint32
fs_ext2_bg_info_inode_bitmap_addr(s_ext2_bg_info_t *bg_info)
{
    s_ext2_bgd_t *bgd;

    kassert(bg_info);

    bgd = fs_ext2_bg_info_decriptor(bg_info);

    return fs_ext2_block_descriptor_inode_bitmap_addr(bgd);
}

static inline uint32
fs_ext2_block_descriptor_inode_table_addr(s_ext2_bgd_t *bgd)
{
    kassert(bgd);

    return bgd->inode_table_addr;
}

static inline uint32
fs_ext2_bg_info_inode_table_addr(s_ext2_bg_info_t *bg_info)
{
    s_ext2_bgd_t *bgd;

    kassert(bg_info);

    bgd = fs_ext2_bg_info_decriptor(bg_info);

    return fs_ext2_block_descriptor_inode_table_addr(bgd);
}

static inline uint32
fs_ext2_superblock_block_size(s_ext2_spbk_t *spbk)
{
    kassert(spbk);

    return 1 << (spbk->block_size + 10); /* log2(block_size) - 10 */
}

static inline uint32
fs_ext2_block_group_block_size(s_ext2_bg_info_t *bg_info)
{
    s_ext2_spbk_t *spbk;

    kassert(bg_info);

    spbk = fs_ext2_bg_info_superblock(bg_info);

    return fs_ext2_superblock_block_size(spbk);
}

static inline uint32
fs_ext2_superblock_total_block_count(s_ext2_spbk_t *spbk)
{
    kassert(spbk);

    return spbk->total_block_count;
}

static inline uint32
fs_ext2_bg_info_total_block_count(s_ext2_bg_info_t *bg_info)
{
    s_ext2_spbk_t *spbk;

    kassert(bg_info);

    spbk = fs_ext2_bg_info_superblock(bg_info);

    return fs_ext2_superblock_total_block_count(spbk);
}

static inline uint32
fs_ext2_superblock_major_version(s_ext2_spbk_t *spbk)
{
    kassert(spbk);

    return spbk->major_version;
}

static inline uint32
fs_ext2_block_group_major_version(s_ext2_bg_info_t *bg_info)
{
    s_ext2_spbk_t *spbk;

    kassert(bg_info);

    spbk = fs_ext2_bg_info_superblock(bg_info);

    return fs_ext2_superblock_major_version(spbk);
}

static inline uint32
fs_ext2_superblock_group_inode_count(s_ext2_spbk_t *spbk)
{
    kassert(spbk);

    return spbk->group_inode_count;
}

static inline uint32
fs_ext2_bg_info_inode_count(s_ext2_bg_info_t *bg_info)
{
    s_ext2_spbk_t *spbk;

    kassert(bg_info);

    spbk = fs_ext2_bg_info_superblock(bg_info);

    return fs_ext2_superblock_group_inode_count(spbk);
}

static inline uint32
fs_ext2_descriptor_group_inode_count(s_ext2_dspr_t *dspr)
{
    s_ext2_bg_info_t *bg_info;

    kassert(fs_ext2_descriptor_legal_p(dspr));

    bg_info = fs_ext2_descriptor_block_group_info(dspr);

    return fs_ext2_bg_info_inode_count(bg_info);
}

static inline uint32
fs_ext2_block_group_sector_count(s_ext2_bg_info_t *bg_info,
    e_disk_id_t device_id)
{
    uint32 sector_bytes;
    uint32 sector_count;
    uint32 block_size, block_count;

    kassert(bg_info);

    sector_bytes = disk_descriptor_sector_bytes(device_id);
    block_size = fs_ext2_block_group_block_size(bg_info);
    block_count = fs_ext2_bg_info_block_count(bg_info);
    sector_count = block_size * block_count / sector_bytes;

    kassert(block_size * block_count % sector_bytes == 0);

    return sector_count;
}

static inline s_ext2_bg_data_t **
fs_ext2_descriptor_block_group_data_array(s_ext2_dspr_t *dspr)
{
    kassert(fs_ext2_descriptor_legal_p(dspr));

    return dspr->bg_data_array;
}

static inline s_ext2_bg_data_t *
fs_ext2_descriptor_block_group_data_entry(s_ext2_dspr_t *dspr, uint32 i)
{
    s_ext2_bg_data_t **bg_data_array;

    kassert(fs_ext2_descriptor_legal_p(dspr));
    kassert(i < fs_ext2_descriptor_limit(dspr));

    bg_data_array = fs_ext2_descriptor_block_group_data_array(dspr);

    return bg_data_array[i];
}

static inline s_ext2_bg_info_t *
fs_ext2_descriptor_block_group_info(s_ext2_dspr_t *dspr)
{
    kassert(fs_ext2_descriptor_legal_p(dspr));

    return dspr->bg_info;
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

