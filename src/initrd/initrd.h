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

#define NAME_MAX          128
#define HEADER_MAX        64
#define INITRD_MAGIC      0xbf
#define INITRD_NAME       "initrd.img"

#define RETURN_IF_TRUE(x) if (x) { return ; }
#define ARRAY_CNT_OF(a)   (sizeof(a) / sizeof(a[0]))

typedef struct initrd_header s_initrd_header_t;

struct initrd_header {
    uint8  magic;
    char   name[NAME_MAX];
    uint32 offset;
    uint32 length;
};

static s_initrd_header_t header_array[HEADER_MAX];

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
 */

#endif

