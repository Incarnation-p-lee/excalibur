#ifndef HAVE_DEFINED_FILESYSTEM_H
#define HAVE_DEFINED_FILESYSTEM_H

typedef struct vfs_node s_vfs_node_t;

typedef uint32 (*f_read_t)(s_vfs_node_t *, uint32, uint32, uint8 *);
typedef uint32 (*f_write_t)(s_vfs_node_t *, uint32, uint32, uint8 *);
typedef void (*f_open_t)(s_vfs_node_t *);
typedef void (*f_close_t)(s_vfs_node_t *);
typedef s_vfs_node_t * (*f_readdir_t)(s_vfs_node_t *, uint32);
typedef s_vfs_node_t * (*f_finddir_t)(s_vfs_node_t *, char *);

#define FS_NAME_MAX       128

/*
 * Only FS_ROOT indicate the only one root node for all different fs.
 * FS_ROOT | FS_DIRECTORY node means the root node of one fs.
 */
#define FS_FILE           0x1u
#define FS_DIRECTORY      0x2u
#define FS_CHAR_DEVICE    0x3u
#define FS_BLOCK_DEVICE   0x4u
#define FS_PIPE           0x5u
#define FS_SYMBOL_LINK    0x6u
#define FS_MOUNTPOINT     0x8u /* 0x8 for bitwise-OR with FS_DIRECTORY. */
#define FS_ROOT           0x10
#define FS_FLAGS_MAX      0x1f

#define FS_DIRECTORY_MASK 0x7u

/* supported fs name */
#define FS_INITRD         "initrd"

/*
 *     Mountpoint are UNIX way of accessing different filesystem. The filesystem
 * is mounted on a directory, as the root directory of that filesystem. So the
 * directory is told that this is a mountpoint and given a pointer to the root
 * node of the new filesystem.
 */

struct vfs_node {
    char            name[FS_NAME_MAX];
    uint32          flags;
    uint32          mask;
    uint32          uid;
    uint32          gid;
    uint32          length;
    uint32          impl;     /* implementation-defined number */
    uint32          inode;    /* device-specific, identify file */
    f_read_t        read;
    f_write_t       write;
    f_open_t        open;
    f_close_t       close;
    f_readdir_t     readdir;
    f_finddir_t     finddir;
    s_linked_list_t list;     /* only valid if FS_DIRECTORY */
    s_linked_list_t *sub_list;

    union {
        s_vfs_node_t *link;
        s_vfs_node_t *mount;
    };
};

#endif

