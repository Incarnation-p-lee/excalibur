#ifndef HAVE_DEFINED_FS_INITRD_H
#define HAVE_DEFINED_FS_INITRD_H

static s_initrd_header_t *initrd_header_array = NULL;
static s_vfs_node_t       **fs_node_array;

#define FS_INITRD_NAME   "initrd"
#define FS_INITRD_DEV    "dev"

#endif

