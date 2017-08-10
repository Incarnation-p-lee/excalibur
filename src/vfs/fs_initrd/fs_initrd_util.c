static inline s_initrd_header_t *
fs_initrd_header(uint32 i)
{
    return &initrd_header_array[i];
}

static inline char *
fs_initrd_header_name(s_initrd_header_t *header)
{
    kassert(fs_initrd_header_legal_p(header));

    return header->name;
}

static inline bool
fs_initrd_header_legal_p(s_initrd_header_t *header)
{
    if (header == NULL) {
        return false;
    } else if (header->magic != INITRD_MAGIC) {
        return false;
    } else {
        return true;
    }
}

static inline uint32
fs_initrd_header_length(s_initrd_header_t *header)
{
    kassert(fs_initrd_header_legal_p(header));

    return header->length;
}

static inline void
fs_initrd_header_length_set(s_initrd_header_t *header, uint32 length)
{
    kassert(fs_initrd_header_legal_p(header));

    header->length = length;
}

static inline uint32
fs_initrd_header_count(ptr_t location)
{
    kassert(location);

    return *(uint32 *)location;
}

static inline void
fs_initrd_header_set(ptr_t location)
{
    kassert(location);

    initrd_header_array = (void *)location;
}

static inline ptr_t
fs_initrd_addr_start(void)
{
    kassert(initrd_addr_start);

    return initrd_addr_start;
}

static inline void
fs_initrd_addr_start_set(ptr_t addr)
{
    kassert(addr);

    initrd_addr_start = addr;
}

static inline uint32
fs_initrd_inode(void)
{
    return initrd_inode;
}

static inline void
fs_initrd_inode_set(uint32 inode)
{
    initrd_inode = inode;
}

static inline uint32
fs_initrd_inode_allocate(void)
{
    return initrd_inode++;
}

static inline uint32
fs_initrd_header_offset(s_initrd_header_t *header)
{
    kassert(fs_initrd_header_legal_p(header));

    return header->offset;
}

static inline uint32
fs_initrd_header_inode_to_offset(uint32 inode)
{
    uint32 offset;
    uint32 last_inode;
    s_initrd_header_t *header;

    kassert(inode <= fs_initrd_inode());
    kassert(inode);

    last_inode = inode - 1;
    header = fs_initrd_header(last_inode);

    offset = fs_initrd_header_offset(header);
    offset += fs_initrd_header_length(header);

    return offset;
}

static inline void
fs_initrd_header_initialize(s_initrd_header_t *header, s_vfs_node_t *vfs_node)
{
    kassert(header);
    kassert(vfs_node_legal_p(vfs_node));

    header->magic = INITRD_MAGIC;
    header->length = vfs_node_length(vfs_node);
    header->flags = vfs_node_flags(vfs_node);
    header->sub_list = NULL;
    header->offset = fs_initrd_header_inode_to_offset(vfs_node_inode(vfs_node));

    linked_list_initialize(&header->list);
    string_copy(header->name, vfs_node_name(vfs_node));
}

static inline void
fs_initrd_header_name_copy(s_initrd_header_t *header, char *name)
{
    kassert(name);
    kassert(fs_initrd_header_legal_p(header));

}

static inline void
fs_initrd_header_magic_set(s_initrd_header_t *header)
{
    kassert(fs_initrd_header_legal_p(header));

    header->magic = INITRD_MAGIC;
}

static inline void
fs_initrd_header_count_inc(void)
{
    uint32 *header_count;

    header_count = (void *)fs_initrd_addr_start();

    *header_count += 1;
}

static inline void
fs_initrd_vfs_root_node_set(s_vfs_node_t *node)
{
    kassert(vfs_node_legal_p(node));

    initrd_root = node;
}

static inline s_vfs_node_t *
fs_initrd_vfs_node_root_i(void)
{
    return initrd_root;
}

s_vfs_node_t *
fs_initrd_vfs_node_root(void)
{
    s_vfs_node_t *vfs_root;

    vfs_root = fs_initrd_vfs_node_root_i();

    if (vfs_root == NULL) {
        return PTR_INVALID;
    } else {
        return vfs_root;
    }
}

