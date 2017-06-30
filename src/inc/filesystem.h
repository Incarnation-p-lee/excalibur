#ifndef HAVE_DEFINED_FILESYSTEM_H
#define HAVE_DEFINED_FILESYSTEM_H

typedef struct filesystem_node s_filesystem_node_t;

#define FS_NODE_NAME_MAX         128

struct filesystem_node {
    char                name[FS_NODE_NAME_MAX];
    uint32              flags;
    uint32              mask;
    uint32              uid;
    uint32              gid;
    uint32              length;
    uint32              impl;     /* implementation-defined number */
    uint32              inode;    /* device-specific, identify file */
                        read;
                        write;
                        open;
                        close
                        readdir;
                        finddir;
    s_filesystem_node_t *link;
};

#endif

