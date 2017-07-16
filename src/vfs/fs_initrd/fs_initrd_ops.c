static inline uint32
fs_initrd_read(s_vfs_node_t *fs_node, uint32 offset, uint32 size, uint8 *buf)
{
    ptr_t addr;
    uint32 inode;
    uint32 file_length;
    s_initrd_header_t *header;

    kassert(buf);
    kassert(size);
    kassert(vfs_node_legal_p(fs_node));

    inode = vfs_node_inode(fs_node);
    header = fs_initrd_header(inode);
    file_length = fs_initrd_header_length(header);

    if (offset > file_length) {
        return 0;
    } else if (offset + size > file_length) {
        size = file_length - offset;
    }

    addr = fs_initrd_addr_start() + (ptr_t)(header->offset + offset);
    kmemory_copy(buf, (void *)addr, size);

    return size;
}

static inline uint32
fs_initrd_write(s_vfs_node_t *fs_node, uint32 offset, uint32 size, uint8 *buf)
{
    kassert(size);
    kassert(buf);
    kassert(offset);
    kassert(vfs_node_legal_p(fs_node));

    return 0;
}

static inline s_vfs_node_t *
fs_initrd_readdir(s_vfs_node_t *fs_node, uint32 index)
{
    kassert(vfs_node_legal_p(fs_node));

    if (index == 0) {
    }

    return fs_node;
}

static inline s_vfs_node_t *
fs_initrd_finddir(s_vfs_node_t *fs_node, char *name)
{
    kassert(name);
    kassert(vfs_node_legal_p(fs_node));

    return fs_node;
}

static inline s_vfs_node_t *
fs_initrd_initialize_i(ptr_t location)
{
    uint32 i;
    uint32 count;
    s_vfs_node_t *root;
    s_vfs_node_t *vfs_node;
    s_initrd_header_t *header;

    kassert(location);

    count = fs_initrd_header_count(location);
    fs_initrd_header_set(location + sizeof(count));
    fs_initrd_addr_start_set(location);

    root = vfs_dir_node_create(FS_INITRD, &fs_initrd_readdir,
        &fs_initrd_finddir);
    vfs_node_flags_add(root, FS_ROOT);

    i = 0;

    while (i < count) {
        header = fs_initrd_header(i);
        vfs_node = vfs_file_node_create(fs_initrd_header_name(header),
            &fs_initrd_read, &fs_initrd_write);
        vfs_sub_node_add(root, vfs_node);
        vfs_node_length_set(vfs_node, fs_initrd_header_length(header));
        vfs_node_inode_set(vfs_node, i);

        i++;
    }

    printf_vga_tk("Initrd filesystem initialized.\n");

    return root;
}

s_vfs_node_t *
fs_initrd_initialize(ptr_t location)
{
    if (location == 0) {
        return PTR_INVALID;
    } else {
        return fs_initrd_initialize_i(location);
    }
}

