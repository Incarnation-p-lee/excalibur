static inline void
fs_ext2_block_group_print(s_ext2_block_group_t *group, uint32 i)
{
    uint32 group_count;
    uint32 block_count;
    uint32 block_unallocated;
    uint32 total_block_count;

    kassert(group);

    block_count = fs_ext2_block_group_block_count(group);
    total_block_count = fs_ext2_block_group_total_block_count(group);
    block_unallocated = fs_ext2_block_group_unallocated_block_count(group);

    group_count = total_block_count / block_count;

    if (total_block_count % block_count != 0) {
        group_count++;
    }

    printf_vga_tk("Reading block group %d done.\n", i);
    printf_vga_tk("    Total block count %d\n", total_block_count);
    printf_vga_tk("    Block count %d\n", block_count);
    printf_vga_tk("    Unallocated block count %d\n", block_unallocated);
    printf_vga_tk("    Group count %d\n", group_count);
}


static inline void
fs_ext2_descriptor_print(s_ext2_dspr_t *dspr)
{
    uint32 i, limit;
    s_ext2_block_group_t *group;

    kassert(fs_ext2_descriptor_legal_p(dspr));

    i = 0;
    limit = fs_ext2_descriptor_limit(dspr);

    while (i < limit) {
        group = fs_ext2_descriptor_block_group_entry(dspr, i);

        if (group != NULL) {
            fs_ext2_block_group_print(group, i);
        }

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

