#ifndef HAVE_DEFINED_INITRD_H
#define HAVE_DEFINED_INITRD_H

/*
 *     An initrd ramdisk is just a filesystem that is loaded into memory when
 * kerenl boots. For storing drivers and configuration files, before kernel can
 * access the root filesystem.
 *
 *     As we know, initrd do not need too complex operations like delete. Just
 * load or store, we will make it simple.
 */

#define INITRD_NAME_MAX   128
#define INITRD_HEADER_MAX 64
#define INITRD_MAGIC      0xbf

typedef struct initrd_header s_initrd_header_t;

struct initrd_header {
    uint8  magic;
    char   name[INITRD_NAME_MAX];
    uint32 offset;
    uint32 length;
};


/*
 * initrd image layout
 * +--------------+   <-   offset 0
 * | header_array |
 * +--------------+
 * | array count  |
 * +--------------+
 * | file 0       |
 * | file 1       |
 * | file 2       |
 * | ...          |
 * | file n - 1   |
 * +--------------+
 *
 * To-do
 * For now, this structure do not support sub directory, will add it later.
 */

#endif

