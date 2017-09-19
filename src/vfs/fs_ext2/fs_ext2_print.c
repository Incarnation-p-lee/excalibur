static inline void
fs_ext2_superblock_print(s_ext2_spbk_t *superblock)
{
    kassert(fs_ext2_superblock_valid_p(superblock));

    printf_vga_tk("Reading superblock information done.\n");
    printf_vga_tk("Total block %d of %d groups(block %d, inode %d).\n",
        fs_ext2_superblock_total_block_count(superblock),
        fs_ext2_superblock_block_group_count(superblock),
        fs_ext2_superblock_group_block_count(superblock),
        fs_ext2_superblock_group_inode_count(superblock));
}

static inline void
fs_ext2_bgd_print(s_ext2_bgd_t *bgd, uint32 i)
{
    kassert(bgd);

    printf_vga_tk("    Block group descriptor for group <%d>.\n", i);
    printf_vga_tk("    Block bitmap %d, inode bitmap %d, inode table %d\n",
        fs_ext2_bgd_block_bitmap_addr(bgd),
        fs_ext2_bgd_inode_bitmap_addr(bgd),
        fs_ext2_bgd_inode_table_addr(bgd));
    printf_vga_tk("    Free block %d, free inode %d, directory %d\n",
        fs_ext2_bgd_unalloc_block_count(bgd),
        fs_ext2_bgd_unalloc_inode_count(bgd),
        fs_ext2_bgd_dir_count(bgd));
}

static inline void
fs_ext2_dspr_print(s_ext2_dspr_t *dspr)
{
    uint32 i, limit;
    s_ext2_bgd_t *bgd;

    kassert(fs_ext2_dspr_legal_p(dspr));

    fs_ext2_superblock_print(fs_ext2_dspr_superblock(dspr));

    i = 0;
    limit = fs_ext2_dspr_bg_count(dspr);

    while (i < limit) {
        bgd = fs_ext2_dspr_bgd(dspr, i);
        fs_ext2_bgd_print(bgd, i);

        i++;
    }
}

static inline void
fs_ext2_dspr_table_print(s_ext2_dspr_table_t *dspr_table)
{
    uint32 i, limit;
    s_ext2_dspr_t *dspr;

    kassert(fs_ext2_dspr_table_legal_p(dspr_table));

    i = 0;
    limit = fs_ext2_dspr_table_limit(dspr_table);

    while (i < limit) {
        dspr = fs_ext2_dspr_table_entry(dspr_table, i);
        fs_ext2_dspr_print(dspr);

        i++;
    }

    printf_vga_tk("Ext2 filesystem initialized.\n");
}

