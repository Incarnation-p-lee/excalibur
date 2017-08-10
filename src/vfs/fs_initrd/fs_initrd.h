#ifndef HAVE_DEFINED_FS_INITRD_H
#define HAVE_DEFINED_FS_INITRD_H

static ptr_t initrd_addr_start = 0;
static uint32 initrd_inode = 0;

static s_vfs_node_t *initrd_root;
static s_initrd_header_t *initrd_header_array;

#endif

