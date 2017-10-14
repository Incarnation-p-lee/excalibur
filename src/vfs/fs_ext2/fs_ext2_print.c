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

static inline void
fs_ext2_vfs_node_tree_print(s_vfs_node_t *vfs_root)
{
    uint32 i;
    char buf[256];
    s_stack_t *stack_slave;
    s_stack_t *stack_master;
    s_vfs_node_t *node, *child;

    kassert(vfs_node_legal_p(vfs_root));

    stack_slave = stack_create();
    stack_master = stack_create();

    stack_push(stack_master, vfs_root);

    while (!stack_empty_p(stack_master)) {
        i = 0;
        node = stack_pop(stack_master);

        if (fs_ext2_vfs_node_obvious_dir_p(node)) {
            i += string_copy(buf + i, vfs_node_name(node));
            i--;
            i += string_copy(buf + i, " -> ");
            i--;

            child = vfs_sub_list_first(node);

            while (child != NULL) {
                i += string_copy(buf + i, vfs_node_name(child));
                buf[i - 1] = ' ';
                stack_push(stack_slave, child);
                child = vfs_node_next(child);
            }

            buf[i] = CHAR_NULL;
            printf_vga_tk("%s\n", buf);
        }

        if (stack_empty_p(stack_master)) {
            stack_fill(stack_master, stack_slave);
        }
    }
}

