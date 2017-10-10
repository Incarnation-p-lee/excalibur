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
vfs_node_directory_ip(s_vfs_node_t *vfs_node)
{
    kassert(vfs_node_legal_ip(vfs_node));

    if ((vfs_node->flags & FS_DIRECTORY_MASK) == FS_DIRECTORY) {
        return true;
    } else {
        return false;
    }
}

bool
vfs_node_directory_p(s_vfs_node_t *vfs_node)
{
    if (vfs_node_illegal_ip(vfs_node)) {
        return false;
    } else {
        return vfs_node_directory_ip(vfs_node);
    }
}

static inline bool
vfs_node_not_directory_p(s_vfs_node_t *vfs_node)
{
    return !vfs_node_directory_ip(vfs_node);
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

void
vfs_node_flags_add(s_vfs_node_t *vfs_node, uint32 flags)
{
    if (flags >= FS_FLAGS_MAX) {
        return;
    } else if (vfs_node_illegal_ip(vfs_node)) {
        return;
    } else {
        vfs_node_flags_add_i(vfs_node, flags);
    }
}

static inline void
vfs_node_flags_add_i(s_vfs_node_t *vfs_node, uint32 flags)
{
    uint32 flags_tmp;

    kassert(flags < FS_FLAGS_MAX);
    kassert(vfs_node_legal_ip(vfs_node));

    flags_tmp = vfs_node_flags_i(vfs_node) | flags;

    vfs_node_flags_set_i(vfs_node, flags_tmp);
}

static inline void
vfs_node_flags_set_i(s_vfs_node_t *vfs_node, uint32 flags)
{
    kassert(vfs_node_legal_ip(vfs_node));
    kassert(flags < FS_FLAGS_MAX);

    vfs_node->flags = flags;
}

static inline uint32
vfs_node_flags_i(s_vfs_node_t *vfs_node)
{
    kassert(vfs_node_legal_ip(vfs_node));

    return vfs_node->flags;
}

uint32
vfs_node_flags(s_vfs_node_t *vfs_node)
{
    if (vfs_node_illegal_ip(vfs_node)) {
        return FS_FLAGS_INVALID;
    } else {
        return vfs_node_flags_i(vfs_node);
    }
}

static inline s_linked_list_t *
vfs_node_list(s_vfs_node_t *vfs_node)
{
    kassert(vfs_node_legal_ip(vfs_node));

    return &vfs_node->list;
}

static inline s_linked_list_t *
vfs_node_sub_list(s_vfs_node_t *vfs_node)
{
    kassert(vfs_node_legal_ip(vfs_node));

    return vfs_node->sub_list;
}

static inline void
vfs_node_sub_list_set(s_vfs_node_t *vfs_node, s_linked_list_t *list)
{
    kassert(vfs_node_legal_ip(vfs_node));

    vfs_node->sub_list = list;
}

static inline void
vfs_node_sub_list_insert_after(s_vfs_node_t *vfs_node, s_vfs_node_t *inserted)
{
    s_linked_list_t *list;
    s_linked_list_t *sub_list;

    kassert(vfs_node_legal_ip(vfs_node));
    kassert(vfs_node_legal_ip(inserted));
    kassert(vfs_node_sub_list(vfs_node) != NULL);

    list = vfs_node_list(inserted);
    sub_list = vfs_node_sub_list(vfs_node);

    linked_list_insert_after(sub_list, list);
}

void
vfs_sub_list_add(s_vfs_node_t *vfs_node, s_vfs_node_t *added)
{
    if (vfs_node_illegal_ip(vfs_node)) {
        return;
    } else if (vfs_node_illegal_ip(vfs_node)) {
        return;
    } else {
        vfs_sub_list_add_i(vfs_node, added);
    }
}

static inline void
vfs_sub_list_add_i(s_vfs_node_t *vfs_node, s_vfs_node_t *added)
{
    kassert(vfs_node_legal_ip(vfs_node));
    kassert(vfs_node_legal_ip(added));

    if (vfs_node->sub_list == NULL) {
        vfs_node_sub_list_set(vfs_node, vfs_node_list(added));
    } else {
        vfs_node_sub_list_insert_after(vfs_node, added);
    }
}

static inline s_vfs_node_t *
vfs_list_to_node(s_linked_list_t *linked_list)
{
    if (linked_list_legal_p(linked_list)) {
        return CONTAINER_OF(linked_list, s_vfs_node_t, list);
    } else {
        return NULL;
    }
}

s_vfs_node_t *
vfs_sub_list_first(s_vfs_node_t *vfs_node)
{
    if (vfs_node_illegal_ip(vfs_node)) {
        return PTR_INVALID;
    } else {
        return vfs_sub_list_first_i(vfs_node);
    }
}

static inline s_vfs_node_t *
vfs_sub_list_first_i(s_vfs_node_t *vfs_node)
{
    s_linked_list_t *list;

    kassert(vfs_node_legal_ip(vfs_node));

    list = vfs_node_sub_list(vfs_node);

    return vfs_list_to_node(list);
}

static inline s_vfs_node_t *
vfs_node_next_i(s_vfs_node_t *vfs_node)
{
    s_linked_list_t *linked_list;

    kassert(vfs_node_legal_ip(vfs_node));

    linked_list = vfs_node_list(vfs_node);

    return vfs_list_to_node(linked_list->next);
}

s_vfs_node_t *
vfs_node_next(s_vfs_node_t *vfs_node)
{
    if (vfs_node_illegal_ip(vfs_node)) {
        return PTR_INVALID;
    } else {
        return vfs_node_next_i(vfs_node);
    }
}

static inline char *
vfs_node_name_i(s_vfs_node_t *vfs_node)
{
    kassert(vfs_node_legal_ip(vfs_node));

    return vfs_node->name;
}

char *
vfs_node_name(s_vfs_node_t *vfs_node)
{
    if (vfs_node_illegal_ip(vfs_node)) {
        return PTR_INVALID;
    } else {
        return vfs_node_name_i(vfs_node);
    }
}

static inline bool
vfs_node_file_ip(s_vfs_node_t *vfs_node)
{
    kassert(vfs_node_legal_ip(vfs_node));

    if ((vfs_node->flags & FS_FILE) == FS_FILE) {
        return true;
    } else {
        return false;
    }
}

bool
vfs_node_file_p(s_vfs_node_t *vfs_node)
{
    if (vfs_node_illegal_ip(vfs_node)) {
        return false;
    } else {
        return vfs_node_file_ip(vfs_node);
    }
}

static inline void
vfs_node_length_set_i(s_vfs_node_t *vfs_node, uint32 length)
{
    kassert(vfs_node_legal_ip(vfs_node));

    vfs_node->length = length;
}

void
vfs_node_length_set(s_vfs_node_t *vfs_node, uint32 length)
{
    if (vfs_node_illegal_ip(vfs_node)) {
        return;
    } else {
        vfs_node_length_set_i(vfs_node, length);
    }
}

static inline void
vfs_node_inode_set_i(s_vfs_node_t *vfs_node, uint32 inode)
{
    kassert(vfs_node_legal_ip(vfs_node));

    vfs_node->inode = inode;
}

void
vfs_node_inode_set(s_vfs_node_t *vfs_node, uint32 inode)
{
    if (vfs_node_illegal_ip(vfs_node)) {
        return;
    } else {
        vfs_node_inode_set_i(vfs_node, inode);
    }
}

