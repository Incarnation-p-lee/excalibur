static inline bool
vfs_node_legal_ip(s_vfs_node_t *vfs_node)
{
    if (vfs_node == NULL) {
        return false;
    } else if (vfs_node->flags > FS_FLAGS_MAX) {
        return false;
    } else {
        return true;
    }
}

bool
vfs_node_legal_p(s_vfs_node_t *vfs_node)
{
    return vfs_node_legal_ip(vfs_node);
}

static inline bool
vfs_node_illegal_ip(s_vfs_node_t *vfs_node)
{
    return !vfs_node_legal_ip(vfs_node);
}

bool
vfs_node_illegal_p(s_vfs_node_t *vfs_node)
{
    return !vfs_node_legal_ip(vfs_node);
}

static inline bool
vfs_node_readable_p(s_vfs_node_t *vfs_node)
{
    kassert(vfs_node_legal_ip(vfs_node));

    if (vfs_node->read) {
        return true;
    } else {
        return false;
    }
}

static inline bool
vfs_node_unreadable_p(s_vfs_node_t *vfs_node)
{
    return !vfs_node_readable_p(vfs_node);
}

static inline bool
vfs_node_writable_p(s_vfs_node_t *vfs_node)
{
    kassert(vfs_node_legal_ip(vfs_node));

    if (vfs_node->write) {
        return true;
    } else {
        return false;
    }
}

static inline bool
vfs_node_unwritable_p(s_vfs_node_t *vfs_node)
{
    return !vfs_node_writable_p(vfs_node);
}

static inline bool
vfs_node_openable_p(s_vfs_node_t *vfs_node)
{
    kassert(vfs_node_legal_ip(vfs_node));

    if (vfs_node->open) {
        return true;
    } else {
        return false;
    }
}

static inline bool
vfs_node_unopenable_p(s_vfs_node_t *vfs_node)
{
    return !vfs_node_openable_p(vfs_node);
}

static inline bool
vfs_node_closable_p(s_vfs_node_t *vfs_node)
{
    kassert(vfs_node_legal_ip(vfs_node));

    if (vfs_node->close) {
        return true;
    } else {
        return false;
    }
}

static inline bool
vfs_node_unclosable_p(s_vfs_node_t *vfs_node)
{
    return !vfs_node_closable_p(vfs_node);
}

static inline bool
vfs_node_dir_readable_p(s_vfs_node_t *vfs_node)
{
    kassert(vfs_node_legal_ip(vfs_node));

    if (vfs_node->readdir) {
        return true;
    } else {
        return false;
    }
}

static inline bool
vfs_node_dir_unreadable_p(s_vfs_node_t *vfs_node)
{
    return !vfs_node_dir_readable_p(vfs_node);
}

static inline bool
vfs_node_dir_findable_p(s_vfs_node_t *vfs_node)
{
    kassert(vfs_node_legal_ip(vfs_node));

    if (vfs_node->finddir) {
        return true;
    } else {
        return false;
    }
}

static inline bool
vfs_node_dir_unfindable_p(s_vfs_node_t *vfs_node)
{
    return !vfs_node_dir_findable_p(vfs_node);
}

static inline bool
vfs_node_directory_p(s_vfs_node_t *vfs_node)
{
    kassert(vfs_node_legal_ip(vfs_node));

    if ((vfs_node->flags & FS_DIRECTORY_MASK) == FS_DIRECTORY) {
        return true;
    } else {
        return false;
    }
}

static inline bool
vfs_node_not_directory_p(s_vfs_node_t *vfs_node)
{
    return !vfs_node_directory_p(vfs_node);
}

static inline uint32
vfs_node_inode_i(s_vfs_node_t *vfs_node)
{
    kassert(vfs_node_legal_ip(vfs_node));

    return vfs_node->inode;
}

uint32
vfs_node_inode(s_vfs_node_t *vfs_node)
{
    if (vfs_node_illegal_ip(vfs_node)) {
        return INODE_INVALID;
    } else {
        return vfs_node_inode_i(vfs_node);
    }
}

static inline uint32
vfs_node_length_i(s_vfs_node_t *vfs_node)
{
    kassert(vfs_node_legal_ip(vfs_node));

    return vfs_node->length;
}

uint32
vfs_node_length(s_vfs_node_t *vfs_node)
{
    if (vfs_node_illegal_ip(vfs_node)) {
        return INODE_INVALID;
    } else {
        return vfs_node_length_i(vfs_node);
    }
}

static inline void
vfs_node_flags_add(s_vfs_node_t *vfs_node, uint32 flags)
{
    kassert(flags < FS_FLAGS_MAX);
    kassert(vfs_node_legal_ip(vfs_node));

    vfs_node->flags |= flags;
}

