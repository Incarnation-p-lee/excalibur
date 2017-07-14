static inline s_vfs_node_t *
vfs_dir_node_create_i(char *name, f_readdir_t readdir, f_finddir_t finddir)
{
    s_vfs_node_t *vfs_node;

    kassert(name);
    kassert(readdir);
    kassert(finddir);

    vfs_node = kmalloc(sizeof(*vfs_node));
    string_copy(vfs_node->name, name);

    vfs_node->mask = 0;
    vfs_node->gid = 0;
    vfs_node->length = 0;
    vfs_node->inode = 0;
    vfs_node->flags = FS_DIRECTORY;
    vfs_node->read = vfs_node->write = NULL;
    vfs_node->open = vfs_node->close = NULL;
    vfs_node->readdir = readdir;
    vfs_node->finddir = finddir;
    vfs_node->link = NULL;
    vfs_node->impl = 0;

    linked_list_initialize(&vfs_node->list);

    return vfs_node;
}

s_vfs_node_t *
vfs_dir_node_create(char *name, f_readdir_t readdir, f_finddir_t finddir)
{
    if (name == NULL) {
        return PTR_INVALID;
    } else if (readdir == NULL) {
        return PTR_INVALID;
    } else if (finddir == NULL) {
        return PTR_INVALID;
    } else {
        return vfs_dir_node_create_i(name, readdir, finddir);
    }
}

static inline s_vfs_node_t *
vfs_file_node_create_i(char *name, f_read_t read, f_write_t write)
{
    s_vfs_node_t *vfs_node;

    kassert(name);
    kassert(read);
    kassert(write);

    vfs_node = kmalloc(sizeof(*vfs_node));
    string_copy(vfs_node->name, name);

    vfs_node->mask = 0;
    vfs_node->gid = 0;
    vfs_node->length = 0;
    vfs_node->inode = 0;
    vfs_node->flags = FS_FILE;
    vfs_node->read = read;
    vfs_node->write = write;
    vfs_node->open = vfs_node->close = NULL;
    vfs_node->readdir = NULL;
    vfs_node->finddir = NULL;
    vfs_node->link = NULL;
    vfs_node->impl = 0;

    linked_list_initialize(&vfs_node->list);

    return vfs_node;
}

s_vfs_node_t *
vfs_file_node_create(char *name, f_read_t read, f_write_t write)
{
    if (name == NULL) {
        return PTR_INVALID;
    } else if (read == NULL) {
        return PTR_INVALID;
    } else if (write == NULL) {
        return PTR_INVALID;
    } else {
        return vfs_file_node_create_i(name, read, write);
    }
}

uint32
vfs_read(s_vfs_node_t *vfs_node, uint32 offset, uint32 size, uint8 *buf)
{
    if (vfs_node_illegal_ip(vfs_node)) {
        return 0;
    } else if (vfs_node_unreadable_p(vfs_node)) {
        return 0;
    } else if (buf == NULL) {
        return 0;
    } else if (size == 0) {
        return 0;
    } else {
        return vfs_node->read(vfs_node, offset, size, buf);
    }
}

uint32
vfs_write(s_vfs_node_t *vfs_node, uint32 offset, uint32 size, uint8 *buf)
{
    if (vfs_node_illegal_ip(vfs_node)) {
        return 0;
    } else if (vfs_node_unwritable_p(vfs_node)) {
        return 0;
    } else if (buf == NULL) {
        return 0;
    } else if (size == 0) {
        return 0;
    } else {
        return vfs_node->write(vfs_node, offset, size, buf);
    }
}

uint32
vfs_open(s_vfs_node_t *vfs_node)
{
    if (vfs_node_illegal_ip(vfs_node)) {
        return 0;
    } else if (vfs_node_unopenable_p(vfs_node)) {
        return 0;
    } else {
        vfs_node->open(vfs_node);
        return 1;
    }
}

uint32
vfs_close(s_vfs_node_t *vfs_node)
{
    if (vfs_node_illegal_ip(vfs_node)) {
        return 0;
    } else if (vfs_node_unopenable_p(vfs_node)) {
        return 0;
    } else {
        vfs_node->close(vfs_node);
        return 1;
    }
}

s_vfs_node_t *
vfs_readdir(s_vfs_node_t *vfs_node, uint32 index)
{
    if (vfs_node_illegal_ip(vfs_node)) {
        return PTR_INVALID;
    } else if (vfs_node_dir_unreadable_p(vfs_node)) {
        return PTR_INVALID;
    } else if (vfs_node_not_directory_p(vfs_node)) {
        return PTR_INVALID;
    } else {
        return vfs_node->readdir(vfs_node, index);
    }
}

static inline void
vfs_multiboot_module_initialize(void)
{
    ptr_t addr;
    char *name;
    uint32 i, limit;
    s_boot_module_t *module;

    i = 0;
    limit = multiboot_data_info_boot_modules_count();

    while (i < limit) {
        module = multiboot_data_info_boot_module(i);
        addr = multiboot_env_module_addr_start(module);
        name = string_basename(multiboot_env_module_name(module));

        if (string_compare(INITRD_NAME, name) == 0) {
            fs_initrd_initialize(addr);
        }

        i++;
    }
}

void
vfs_initialize(void)
{

    vfs_multiboot_module_initialize();

    printf_vga_tk("Virtual filesystem initialized.\n");
}

