static inline uint32
fs_initrd_read(s_fs_node_t *fs_node, uint32 offset, uint32 size, uint8 *buf)
{
    uint32 inode;
    uint32 file_length;
    s_initrd_header_t *header;

    kassert(filesystem_node_legal_p(fs_node));
    kassert(size);
    kassert(buf);

    inode = filesystem_node_inode(fs_node);
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
fs_initrd_write(s_fs_node_t *fs_node, uint32 offset, uint32 size, uint8 *buf)
{

    kassert(filesystem_node_legal_p(fs_node));
    kassert(size);
    kassert(buf);
    kassert(offset);

    return 0;
}

static inline s_directory_t *
fs_initrd_readdir(s_fs_node_t *fs_node, uint32 index)
{
    kassert(filesystem_node_legal_p(fs_node));

    if (fs_node == fs_node_dev && index == 0) {
        string_copy(dirt.name, FS_INITRD_DEV);
        dirt.inode = 0;
    } else {
        string_copy(dirt.name, fs_node_array[index]->name);
        dirt.inode = fs_node_array[index]->inode;
    }

    return &dirt;
}

static inline s_fs_node_t *
fs_initrd_finddir(s_fs_node_t *fs_node, char *name)
{
    kassert(name);
    kassert(filesystem_node_legal_p(fs_node));

    return fs_node_dev;
}

static inline s_fs_node_t *
fs_initrd_dir_node_create(char *name, f_readdir_t readdir, f_finddir_t finddir)
{
    s_fs_node_t *fs_node;

    kassert(name);
    kassert(readdir);
    kassert(finddir);

    fs_node = kmalloc(sizeof(*fs_node));
    string_copy(fs_node->name, name);

    fs_node->mask = 0;
    fs_node->gid = 0;
    fs_node->length = 0;
    fs_node->inode = 0;
    fs_node->flags = FS_DIRECTORY;
    fs_node->read = fs_node->write = NULL;
    fs_node->open = fs_node->close = NULL;
    fs_node->readdir = readdir;
    fs_node->finddir = finddir;
    fs_node->link = NULL;
    fs_node->impl = 0;

    return fs_node;
}

static inline s_fs_node_t *
fs_initrd_file_node_create(char *name, f_read_t read, f_write_t write)
{
    s_fs_node_t *fs_node;

    kassert(name);
    kassert(read);
    kassert(write);

    fs_node = kmalloc(sizeof(*fs_node));
    string_copy(fs_node->name, name);

    fs_node->mask = 0;
    fs_node->gid = 0;
    fs_node->length = 0;
    fs_node->inode = 0;
    fs_node->flags = FS_FILE;
    fs_node->read = read;
    fs_node->write = write;
    fs_node->open = fs_node->close = NULL;
    fs_node->readdir = NULL;
    fs_node->finddir = NULL;
    fs_node->link = NULL;
    fs_node->impl = 0;

    return fs_node;
}

static inline s_fs_node_t *
fs_initrd_initialize_i(ptr_t location)
{
    uint32 i;
    uint32 count;
    s_fs_node_t *fs_node_root;
    s_initrd_header_t *header;

    kassert(location);

    count = fs_initrd_header_count(location);
    fs_initrd_header_set(location + sizeof(count));

    fs_node_root = fs_initrd_dir_node_create(FS_INITRD_NAME,
        &fs_initrd_readdir, &fs_initrd_finddir);
    fs_node_dev = fs_initrd_dir_node_create(FS_INITRD_DEV,
        &fs_initrd_readdir, &fs_initrd_finddir);
    fs_node_array = kmalloc(sizeof(*fs_node_array) * count);

    i = 0;

    while (i < count) {
        header = fs_initrd_header(i);
        fs_node_array[i] = fs_initrd_file_node_create(header->name,
            &fs_initrd_read, &fs_initrd_write);

        i++;
    }

    return fs_node_root;
}

s_fs_node_t *
fs_initrd_initialize(ptr_t location)
{
    if (location == 0) {
        return PTR_INVALID;
    } else {
        return fs_initrd_initialize_i(location);
    }
}

