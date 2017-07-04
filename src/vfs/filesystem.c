uint32
filesystem_read(s_fs_node_t *fs_node, uint32 offset, uint32 size, uint8 *buf)
{
    if (filesystem_node_illegal_p(fs_node)) {
        return 0;
    } else if (filesystem_node_unreadable_p(fs_node)) {
        return 0;
    } else if (buf == NULL) {
        return 0;
    } else if (size == 0) {
        return 0;
    } else {
        return fs_node->read(fs_node, offset, size, buf);
    }
}

uint32
filesystem_write(s_fs_node_t *fs_node, uint32 offset, uint32 size, uint8 *buf)
{
    if (filesystem_node_illegal_p(fs_node)) {
        return 0;
    } else if (filesystem_node_unwritable_p(fs_node)) {
        return 0;
    } else if (buf == NULL) {
        return 0;
    } else if (size == 0) {
        return 0;
    } else {
        return fs_node->write(fs_node, offset, size, buf);
    }
}

uint32
filesystem_open(s_fs_node_t *fs_node)
{
    if (filesystem_node_illegal_p(fs_node)) {
        return 0;
    } else if (filesystem_node_unopenable_p(fs_node)) {
        return 0;
    } else {
        fs_node->open(fs_node);
        return 1;
    }
}

uint32
filesystem_close(s_fs_node_t *fs_node)
{
    if (filesystem_node_illegal_p(fs_node)) {
        return 0;
    } else if (filesystem_node_unopenable_p(fs_node)) {
        return 0;
    } else {
        fs_node->close(fs_node);
        return 1;
    }
}

s_directory_t *
filesystem_readdir(s_fs_node_t *fs_node, uint32 index)
{
    if (filesystem_node_illegal_p(fs_node)) {
        return PTR_INVALID;
    } else if (filesystem_node_dir_unreadable_p(fs_node)) {
        return PTR_INVALID;
    } else if (filesystem_node_not_directory_p(fs_node)) {
        return PTR_INVALID;
    } else {
        return fs_node->readdir(fs_node, index);
    }
}

