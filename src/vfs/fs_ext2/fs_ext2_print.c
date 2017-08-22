static inline void
fs_ext2_block_group_print(s_ext2_block_group_t *block_group, uint32 i)
{
    kassert(block_group);

    printf_vga_tk("Block-group %d\n", i);
    printf_vga_tk("    Total block count %d\n",
        fs_ext2_block_group_total_block_count(block_group));
    printf_vga_tk("    Group block count  %d\n",
        fs_ext2_block_group_block_count(block_group));
    printf_vga_tk("    Major version: %d\n",
        fs_ext2_block_group_major_version(block_group));
}

static inline void
fs_ext2_descriptor_print(s_ext2_dspr_t *dspr)
{
    uint32 i, limit;
    s_ext2_block_group_t *block_group;

    kassert(fs_ext2_descriptor_legal_p(dspr));

    i = 0;
    limit = fs_ext2_descriptor_limit(dspr);

    while (i < limit) {
        block_group = fs_ext2_descriptor_block_group_entry(dspr, i);
        fs_ext2_block_group_print(block_group, i);

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

