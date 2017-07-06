#ifndef HAVE_DEFINED_FS_INITRD_H
#define HAVE_DEFINED_FS_INITRD_H

static s_initrd_header_t *initrd_header_array = NULL;

// static s_fs_node_t       *initrd_root;
static s_fs_node_t       *fs_node_dev;
static s_fs_node_t       **fs_node_array;

static s_directory_t     dirt;

#define FS_INITRD_NAME   "initrd"
#define FS_INITRD_DEV    "dev"

#endif

