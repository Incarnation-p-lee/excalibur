static inline bool
fs_ext2_dspr_legal_p(s_ext2_dspr_t *dspr)
{
    if (dspr == NULL) {
        return false;
    } else if (dspr->superblock == NULL) {
        return false;
    } else if (dspr->disk_pt == NULL) {
        return false;
    } else if (dspr->bgd_table == NULL) {
        return false;
    } else if (dspr->map_array == NULL) {
        return false;
    } else if (dspr->bg_count == 0) {
        return false;
    } else {
        return true;
    }
}

static inline bool
fs_ext2_bgd_map_legal_p(s_ext2_bgd_map_t *map)
{
    if (map == NULL) {
        return false;
    } else if (bitmap_illegal_p(map->block_bitmap)) {
        return false;
    } else if (bitmap_illegal_p(map->inode_bitmap)) {
        return false;
    } else {
        return true;
    }
}

static inline bool
fs_ext2_dspr_illegal_p(s_ext2_dspr_t *dspr)
{
    return !fs_ext2_dspr_legal_p(dspr);
}

static inline e_disk_id_t
fs_ext2_dspr_device_id(s_ext2_dspr_t *dspr)
{
    kassert(fs_ext2_dspr_legal_p(dspr));

    return dspr->device_id;
}

static inline void
fs_ext2_dspr_device_id_set(s_ext2_dspr_t *dspr, e_disk_id_t device_id)
{
    kassert(fs_ext2_dspr_legal_p(dspr));

    dspr->device_id = device_id;
}

static inline s_disk_pt_t *
fs_ext2_dspr_disk_pt(s_ext2_dspr_t *dspr)
{
    kassert(fs_ext2_dspr_legal_p(dspr));

    return dspr->disk_pt;
}

static inline void
fs_ext2_dspr_disk_pt_set(s_ext2_dspr_t *dspr, s_disk_pt_t *disk_pt)
{
    kassert(fs_ext2_dspr_legal_p(dspr));

    dspr->disk_pt = disk_pt;
}

static inline s_ext2_spbk_t *
fs_ext2_dspr_superblock(s_ext2_dspr_t *dspr)
{
    kassert(fs_ext2_dspr_legal_p(dspr));

    return dspr->superblock;
}

static inline uint32
fs_ext2_dspr_bg_count(s_ext2_dspr_t *dspr)
{
    kassert(fs_ext2_dspr_legal_p(dspr));

    return dspr->bg_count;
}

static inline s_ext2_bgd_t *
fs_ext2_dspr_bgd_table(s_ext2_dspr_t *dspr)
{
    kassert(fs_ext2_dspr_legal_p(dspr));

    return dspr->bgd_table;
}

static inline s_ext2_bgd_map_t **
fs_ext2_dspr_bgd_map_array(s_ext2_dspr_t *dspr)
{
    kassert(fs_ext2_dspr_legal_p(dspr));

    return dspr->map_array;
}

static inline s_ext2_bgd_t *
fs_ext2_dspr_bgd(s_ext2_dspr_t *dspr, uint32 i)
{
    s_ext2_bgd_t *bgd_table;

    kassert(fs_ext2_dspr_legal_p(dspr));
    kassert(i < fs_ext2_dspr_bg_count(dspr));

    bgd_table = fs_ext2_dspr_bgd_table(dspr);

    return &bgd_table[i];
}

static inline s_ext2_bgd_map_t *
fs_ext2_dspr_bgd_map(s_ext2_dspr_t *dspr, uint32 i)
{
    s_ext2_bgd_map_t **map_array;

    kassert(fs_ext2_dspr_legal_p(dspr));
    kassert(i < fs_ext2_dspr_bg_count(dspr));

    map_array = fs_ext2_dspr_bgd_map_array(dspr);

    return map_array[i];
}

static inline void
fs_ext2_dspr_bgd_map_set(s_ext2_dspr_t *dspr, uint32 i, s_ext2_bgd_map_t *map)
{
    s_ext2_bgd_map_t **map_array;

    kassert(fs_ext2_dspr_legal_p(dspr));
    kassert(fs_ext2_bgd_map_legal_p(map));
    kassert(i < fs_ext2_dspr_bg_count(dspr));

    map_array = fs_ext2_dspr_bgd_map_array(dspr);

    map_array[i] = map;
}

static inline uint32
fs_ext2_dspr_sector_offset(s_ext2_dspr_t *dspr)
{
    s_disk_pt_t *pt;

    kassert(fs_ext2_dspr_legal_p(dspr));

    pt = fs_ext2_dspr_disk_pt(dspr);

    return disk_partition_sector_offset(pt);
}

static inline s_ext2_dspr_table_t *
fs_ext2_dspr_table_obtain(void)
{
    return &ext2_dspr_table;
}

static inline bool
fs_ext2_dspr_table_legal_p(s_ext2_dspr_table_t *dspr_table)
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
fs_ext2_dspr_table_illegal_p(s_ext2_dspr_table_t *dspr_table)
{
    return !fs_ext2_dspr_table_legal_p(dspr_table);
}

static inline uint32
fs_ext2_dspr_table_index(s_ext2_dspr_table_t *dspr_table)
{
    kassert(fs_ext2_dspr_table_legal_p(dspr_table));

    return dspr_table->index;
}

static inline uint32
fs_ext2_dspr_table_limit(s_ext2_dspr_table_t *dspr_table)
{
    return fs_ext2_dspr_table_index(dspr_table);
}

static inline void
fs_ext2_dspr_table_index_set(s_ext2_dspr_table_t *dspr_table,
    uint32 index)
{
    kassert(fs_ext2_dspr_table_legal_p(dspr_table));

    dspr_table->index = index;
}

static inline uint32
fs_ext2_dspr_table_size(s_ext2_dspr_table_t *dspr_table)
{
    kassert(fs_ext2_dspr_table_legal_p(dspr_table));

    return dspr_table->size;
}

static inline void
fs_ext2_dspr_table_size_set(s_ext2_dspr_table_t *dspr_table,
    uint32 size)
{
    kassert(fs_ext2_dspr_table_legal_p(dspr_table));

    dspr_table->size = size;
}

static inline s_ext2_dspr_t **
fs_ext2_dspr_table_dspr_array(s_ext2_dspr_table_t *dspr_table)
{
    kassert(fs_ext2_dspr_table_legal_p(dspr_table));

    return dspr_table->dspr_array;
}

static inline bool
fs_ext2_dspr_table_full_p(s_ext2_dspr_table_t *dspr_table)
{
    uint32 size;
    uint32 index;

    kassert(fs_ext2_dspr_table_legal_p(dspr_table));

    size = fs_ext2_dspr_table_size(dspr_table);
    index = fs_ext2_dspr_table_index(dspr_table);

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

    if (spbk == NULL) {
        return false;
    } else if (fs_ext2_superblock_signature(spbk) != EXT2_SIGNATURE) {
        return false;
    } else {
        return true;
    }
}

static inline bool
fs_ext2_superblock_invalid_p(s_ext2_spbk_t *spbk)
{
    return !fs_ext2_superblock_valid_p(spbk);
}

static inline void
fs_ext2_bgd_map_block_bitmap_set(s_ext2_bgd_map_t *map, s_bitmap_t *bitmap)
{
    kassert(bitmap_legal_p(bitmap));
    kassert(fs_ext2_bgd_map_legal_p(map));

    map->block_bitmap = bitmap;
}

static inline void
fs_ext2_bgd_map_inode_bitmap_set(s_ext2_bgd_map_t *map, s_bitmap_t *bitmap)
{
    kassert(bitmap_legal_p(bitmap));
    kassert(fs_ext2_bgd_map_legal_p(map));

    map->inode_bitmap = bitmap;
}

static inline uint32
fs_ext2_superblock_group_block_count(s_ext2_spbk_t *spbk)
{
    kassert(spbk);

    return spbk->group_block_count;
}

static inline uint32
fs_ext2_dspr_group_block_count(s_ext2_dspr_t *dspr)
{
    s_ext2_spbk_t *spbk;

    kassert(fs_ext2_dspr_legal_p(dspr));

    spbk = fs_ext2_dspr_superblock(dspr);

    return fs_ext2_superblock_group_block_count(spbk);
}

static inline uint32
fs_ext2_superblock_unallocated_block_count(s_ext2_spbk_t *spbk)
{
    kassert(spbk);

    return spbk->unalloc_block_count;
}

static inline uint32
fs_ext2_superblock_unallocated_inode_count(s_ext2_spbk_t *spbk)
{
    kassert(spbk);

    return spbk->unalloc_inode_count;
}

static inline uint32
fs_ext2_superblock_block_nmbr(s_ext2_spbk_t *spbk)
{
    kassert(spbk);

    return spbk->superblock_nmbr;
}

static inline uint32
fs_ext2_superblock_reserved_count(s_ext2_spbk_t *spbk)
{
    kassert(spbk);

    return spbk->superblock_reserved_count;
}

static inline uint32
fs_ext2_superblock_block_group_count(s_ext2_spbk_t *spbk)
{
    uint32 group_block_count;
    uint32 total_block_count;

    kassert(fs_ext2_superblock_valid_p(spbk));

    group_block_count = fs_ext2_superblock_group_block_count(spbk);
    total_block_count = fs_ext2_superblock_total_block_count(spbk);

    return arithmetic_rate_up(total_block_count, group_block_count);
}

static inline uint32
fs_ext2_bgd_block_bitmap_addr(s_ext2_bgd_t *bgd)
{
    kassert(bgd);

    return bgd->block_bitmap_addr;
}

static inline uint32
fs_ext2_bgd_inode_bitmap_addr(s_ext2_bgd_t *bgd)
{
    kassert(bgd);

    return bgd->inode_bitmap_addr;
}

static inline uint32
fs_ext2_bgd_inode_table_addr(s_ext2_bgd_t *bgd)
{
    kassert(bgd);

    return bgd->inode_table_addr;
}

static inline uint32
fs_ext2_superblock_block_size(s_ext2_spbk_t *spbk)
{
    kassert(spbk);

    return 1 << (spbk->block_size + 10); /* log2(block_size) - 10 */
}

static inline uint32
fs_ext2_dspr_block_size(s_ext2_dspr_t *dspr)
{
    s_ext2_spbk_t *spbk;

    kassert(fs_ext2_dspr_legal_p(dspr));

    spbk = fs_ext2_dspr_superblock(dspr);

    return fs_ext2_superblock_block_size(spbk);
}

static inline uint32
fs_ext2_superblock_total_block_count(s_ext2_spbk_t *spbk)
{
    kassert(spbk);

    return spbk->total_block_count;
}

static inline uint32
fs_ext2_superblock_major_version(s_ext2_spbk_t *spbk)
{
    kassert(spbk);

    return spbk->major_version;
}

static inline uint32
fs_ext2_superblock_group_inode_count(s_ext2_spbk_t *spbk)
{
    kassert(spbk);

    return spbk->group_inode_count;
}

static inline uint32
fs_ext2_dspr_group_inode_count(s_ext2_dspr_t *dspr)
{
    s_ext2_spbk_t *spbk;

    kassert(fs_ext2_dspr_legal_p(dspr));

    spbk = fs_ext2_dspr_superblock(dspr);

    return fs_ext2_superblock_group_inode_count(spbk);
}

static inline s_ext2_dspr_t *
fs_ext2_dspr_table_entry(s_ext2_dspr_table_t *dspr_table, uint32 i)
{
    s_ext2_dspr_t **dspr_array;

    kassert(fs_ext2_dspr_table_legal_p(dspr_table));
    kassert(i < fs_ext2_dspr_table_limit(dspr_table));

    dspr_array = fs_ext2_dspr_table_dspr_array(dspr_table);

    return dspr_array[i];
}

