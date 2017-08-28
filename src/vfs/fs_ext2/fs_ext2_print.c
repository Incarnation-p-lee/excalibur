static inline void
fs_ext2_block_group_info_print(s_ext2_bg_info_t *bg_info)
{
    uint32 total_block_count;
    uint32 block_unallocated, inode_unallocated;
    uint32 block_count, inode_count, group_count;

    kassert(bg_info);
    kassert(fs_ext2_block_group_info_valid_p(bg_info));

    block_count = fs_ext2_block_group_info_block_count(bg_info);
    inode_count = fs_ext2_block_group_info_inode_count(bg_info);
    total_block_count = fs_ext2_block_group_info_total_block_count(bg_info);
    block_unallocated = fs_ext2_block_group_info_unallocated_block_count(bg_info);
    inode_unallocated = fs_ext2_block_group_info_unallocated_inode_count(bg_info);

    group_count = total_block_count / block_count;

    if (total_block_count % block_count != 0) {
        group_count++;
    }

    printf_vga_tk("Reading block group information done.\n");
    printf_vga_tk("    Total block count %d\n", total_block_count);
    printf_vga_tk("    Block count %d\n", block_count);
    printf_vga_tk("    Inode count %d\n", inode_count);
    printf_vga_tk("    Unallocated block count %d\n", block_unallocated);
    printf_vga_tk("    Unallocated inode count %d\n", inode_unallocated);
    printf_vga_tk("    Group count %d\n", group_count);
}

static inline void
fs_ext2_descriptor_print(s_ext2_dspr_t *dspr)
{
    uint32 i, limit;
    // s_ext2_bg_data_t *bg_data;

    kassert(fs_ext2_descriptor_legal_p(dspr));

    fs_ext2_block_group_info_print(fs_ext2_descriptor_block_group_info(dspr));

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

