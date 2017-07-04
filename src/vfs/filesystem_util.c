static inline bool
filesystem_node_legal_p(s_fs_node_t *fs_node)
{
    if (fs_node == NULL) {
        return false;
    } else if (fs_node->flags > FS_FLAGS_MAX) {
        return false;
    } else {
        return true;
    }
}

static inline bool
filesystem_node_illegal_p(s_fs_node_t *fs_node)
{
    return !filesystem_node_legal_p(fs_node);
}

static inline bool
filesystem_node_readable_p(s_fs_node_t *fs_node)
{
    kassert(filesystem_node_legal_p(fs_node));

    if (fs_node->read) {
        return true;
    } else {
        return false;
    }
}

static inline bool
filesystem_node_unreadable_p(s_fs_node_t *fs_node)
{
    return !filesystem_node_readable_p(fs_node);
}

static inline bool
filesystem_node_writable_p(s_fs_node_t *fs_node)
{
    kassert(filesystem_node_legal_p(fs_node));

    if (fs_node->write) {
        return true;
    } else {
        return false;
    }
}

static inline bool
filesystem_node_unwritable_p(s_fs_node_t *fs_node)
{
    return !filesystem_node_writable_p(fs_node);
}

static inline bool
filesystem_node_openable_p(s_fs_node_t *fs_node)
{
    kassert(filesystem_node_legal_p(fs_node));

    if (fs_node->open) {
        return true;
    } else {
        return false;
    }
}

static inline bool
filesystem_node_unopenable_p(s_fs_node_t *fs_node)
{
    return !filesystem_node_openable_p(fs_node);
}

static inline bool
filesystem_node_closable_p(s_fs_node_t *fs_node)
{
    kassert(filesystem_node_legal_p(fs_node));

    if (fs_node->close) {
        return true;
    } else {
        return false;
    }
}

static inline bool
filesystem_node_unclosable_p(s_fs_node_t *fs_node)
{
    return !filesystem_node_closable_p(fs_node);
}

static inline bool
filesystem_node_dir_readable_p(s_fs_node_t *fs_node)
{
    kassert(filesystem_node_legal_p(fs_node));

    if (fs_node->readdir) {
        return true;
    } else {
        return false;
    }
}

static inline bool
filesystem_node_dir_unreadable_p(s_fs_node_t *fs_node)
{
    return !filesystem_node_dir_readable_p(fs_node);
}

static inline bool
filesystem_node_dir_findable_p(s_fs_node_t *fs_node)
{
    kassert(filesystem_node_legal_p(fs_node));

    if (fs_node->finddir) {
        return true;
    } else {
        return false;
    }
}

static inline bool
filesystem_node_dir_unfindable_p(s_fs_node_t *fs_node)
{
    return !filesystem_node_dir_findable_p(fs_node);
}

static inline bool
filesystem_node_directory_p(s_fs_node_t *fs_node)
{
    kassert(filesystem_node_legal_p(fs_node));

    if ((fs_node->flags & FS_DIRECTORY_MASK) == FS_DIRECTORY) {
        return true;
    } else {
        return false;
    }
}

static inline bool
filesystem_node_not_directory_p(s_fs_node_t *fs_node)
{
    return !filesystem_node_directory_p(fs_node);
}

