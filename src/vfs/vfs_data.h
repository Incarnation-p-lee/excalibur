#ifndef HAVE_DEFINED_FILESYSTEM_DATA_H
#define HAVE_DEFINED_FILESYSTEM_DATA_H

typedef enum fs_type e_fs_type_t;
enum fs_type {
    FS_TYPE_INITRD,
    FS_TYPE_EXT2,
};

static s_vfs_node_t vfs_root;
static s_vfs_dspr_t vfs_descriptor_array[] = {
    [FS_TYPE_INITRD] = {FS_INITRD, NULL, &fs_initrd_initialize},
};

#endif

