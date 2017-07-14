static inline uint32
fs_initrd_read(s_vfs_node_t *fs_node, uint32 offset, uint32 size, uint8 *buf)
{
    uint32 inode;
    uint32 file_length;
    s_initrd_header_t *header;

    kassert(vfs_node_legal_p(fs_node));
    kassert(size);
    kassert(buf);

    inode = vfs_node_inode(fs_node);
    header = fs_initrd_header(inode);
    file_length = fs_initrd_header_length(header);

    if (offset > file_length) {
        return 0;
    } else if (offset + size > file_length) {
        size = file_length - offset;
    }

    kmemory_copy(buf, (void *)(header->offset + offset), size);

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
    s_vfs_node_t *fs_node_root;
    s_initrd_header_t *header;

    kassert(location);

    count = fs_initrd_header_count(location);
    fs_initrd_header_set(location + sizeof(count));

    fs_node_root = vfs_dir_node_create(FS_INITRD_NAME,
        &fs_initrd_readdir, &fs_initrd_finddir);
    fs_node_array = kmalloc(sizeof(*fs_node_array) * count);

    i = 0;

    while (i < count) {
        header = fs_initrd_header(i);
        fs_node_array[i] = vfs_file_node_create(header->name,
            &fs_initrd_read, &fs_initrd_write);

        i++;
    }

    printf_vga_tk("Initrd filesystem initialized.\n");

    return fs_node_root;
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

