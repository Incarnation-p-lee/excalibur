static inline s_vfs_node_t *
fs_ext2_dspr_vfs_tree_build(s_ext2_dspr_t *dspr)
{
    s_vfs_node_t *ext2_root;

    kassert(fs_ext2_dspr_legal_p(dspr));

    ext2_root = vfs_dir_node_create(FS_DIR_ROOT, (void *)1, (void *)1);
    vfs_node_inode_set(ext2_root, EXT2_ROOT_DIR_INODE);

    return ext2_root;
}

