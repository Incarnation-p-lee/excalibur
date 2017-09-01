static inline void
fs_ext2_bg_info_print(s_ext2_bg_info_t *bg_info)
{
    uint32 total_b_count;
    uint32 b_unallocated, i_unallocated;
    uint32 b_count, i_count, group_count;
    uint32 sblock_nmbr, sblock_reserved;

    kassert(bg_info);
    kassert(fs_ext2_bg_info_valid_p(bg_info));

    b_count = fs_ext2_bg_info_block_count(bg_info);
    i_count = fs_ext2_bg_info_inode_count(bg_info);
    total_b_count = fs_ext2_bg_info_total_block_count(bg_info);
    b_unallocated = fs_ext2_bg_info_unallocated_block_count(bg_info);
    i_unallocated = fs_ext2_bg_info_unallocated_inode_count(bg_info);
    sblock_nmbr = fs_ext2_bg_info_superblock_nmbr(bg_info);
    sblock_reserved = fs_ext2_bg_info_superblock_reserved_count(bg_info);

    group_count = total_b_count / b_count;

    if (total_b_count % b_count != 0) {
        group_count++;
    }

    printf_vga_tk("Reading block group information done.\n");
    printf_vga_tk("    Total block count %d\n", total_b_count);
    printf_vga_tk("    Block count %d\n", b_count);
    printf_vga_tk("    Inode count %d\n", i_count);
    printf_vga_tk("    Unallocated block count %d\n", b_unallocated);
    printf_vga_tk("    Unallocated inode count %d\n", i_unallocated);
    printf_vga_tk("    Group count %d\n", group_count);
    printf_vga_tk("    Super block number %d\n", sblock_nmbr);
    printf_vga_tk("    Super block reserved %d\n", sblock_reserved);
}

static inline void
fs_ext2_descriptor_print(s_ext2_dspr_t *dspr)
{
    uint32 i, limit;
    // s_ext2_bg_data_t *bg_data;

    kassert(fs_ext2_descriptor_legal_p(dspr));

    fs_ext2_bg_info_print(fs_ext2_descriptor_block_group_info(dspr));

    i = 0;
    limit = fs_ext2_descriptor_limit(dspr);

    while (i < limit) {
        // bg_data = fs_ext2_descriptor_block_group_data_entry(dspr, i);

        i++;
    }
}

static inline void
fs_ext2_descriptor_table_print(s_ext2_dspr_table_t *dspr_table)
{
    uint32 i, limit;
    s_ext2_dspr_t *dspr;

    kassert(fs_ext2_descriptor_table_legal_p(dspr_table));

    i = 0;
    limit = fs_ext2_descriptor_table_limit(dspr_table);

    while (i < limit) {
        dspr = fs_ext2_descriptor_table_entry(dspr_table, i);
        fs_ext2_descriptor_print(dspr);

        i++;
    }

    printf_vga_tk("Ext2 filesystem initialized.\n");
}

