static inline void
fs_ext2_dspr_print(s_ext2_dspr_t *dspr)
{
    uint32 i, limit;

    kassert(fs_ext2_dspr_legal_p(dspr));

    i = 0;
    limit = fs_ext2_dspr_bg_count(dspr);

    while (i < limit) {

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

