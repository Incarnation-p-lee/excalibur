#ifndef HAVE_DEFINED_FS_EXT2_H
#define HAVE_DEFINED_FS_EXT2_H

#define EXT2_STATE_CLEAN           (uint16)0x1u
#define EXT2_STATE_ERROR           (uint16)0x2u

#define EXT2_ERROR_IGNORE          (uint16)0x1u
#define EXT2_ERROR_REMOUNT_RO      (uint16)0x2u
#define EXT2_ERROR_KPANIC          (uint16)0x3u

#define EXT2_OS_LINUX              (uint32)0x0u
#define EXT2_OS_GNU_HURD           (uint32)0x1u
#define EXT2_OS_MASIX              (uint32)0x2u
#define EXT2_OS_FREEBSD            (uint32)0x3u
#define EXT2_OS_LITES              (uint32)0x4u

/* ext2 file system optional feature */
#define EXT2_FEATURE_OPT_PRE_DIR   (uint32)0x1u /* preallocate block for dir */
#define EXT2_FEATURE_OPT_AFS       (uint32)0x2u
#define EXT2_FEATURE_OPT_JNL       (uint32)0x4u /* fs with journal */
#define EXT2_FEATURE_OPT_EXT_INODE (uint32)0x8u /* extended attribute inode */
#define EXT2_FEATURE_OPT_RESIZE    (uint32)0x10 /* resize fs itself */
#define EXT2_FEATURE_OPT_DIR_HASH  (uint32)0x20 /* directory use hash index */

/* ext2 file system required feature */
#define EXT2_FEATURE_RQD_COMPRESS  (uint32)0x1u /* use compression */
#define EXT2_FEATURE_RQD_DIR_TYPE  (uint32)0x2u /* dir contain type field */
#define EXT2_FEATURE_RQD_JNL_REP   (uint32)0x4u /* replay its journal */
#define EXT2_FEATURE_RQD_JNL_DEV   (uint32)0x8u /* use journal device */

/* ext2 file system read-only feature */
#define EXT2_FEATURE_RO_SPARSE     (uint32)0x1u /* sparse superblock, group */
#define EXT2_FEATURE_RO_FILE_64    (uint32)0x2u /* use 64-bit file size */
#define EXT2_FEATURE_RO_DIR_BTREE  (uint32)0x4u /* dir content in binary tree */

/* inode type */
#define EXT2_INODE_T_FIFO          (uint16)0x1u
#define EXT2_INODE_T_CHAR          (uint16)0x2u
#define EXT2_INODE_T_DIR           (uint16)0x4u
#define EXT2_INODE_T_BLOCK         (uint16)0x6u
#define EXT2_INODE_T_REGULAR       (uint16)0x8u
#define EXT2_INODE_T_SYMBLOLIC     (uint16)0xau
#define EXT2_INODE_T_SOCKET        (uint16)0xcu

/* inode permission */
#define EXT2_INODE_P_OTHER_X       (uint16)0x1u
#define EXT2_INODE_P_OTHER_W       (uint16)0x2u
#define EXT2_INODE_P_OTHER_R       (uint16)0x4u
#define EXT2_INODE_P_GROUP_X       (uint16)0x8u
#define EXT2_INODE_P_GROUP_W       (uint16)0x10u
#define EXT2_INODE_P_GROUP_R       (uint16)0x20u
#define EXT2_INODE_P_USER_X        (uint16)0x40u
#define EXT2_INODE_P_USER_W        (uint16)0x80u
#define EXT2_INODE_P_USER_R        (uint16)0x100u
#define EXT2_INODE_P_STICKY        (uint16)0x200u
#define EXT2_INODE_P_SDID          (uint16)0x400u
#define EXT2_INODE_P_SUID          (uint16)0x800u

/* inode flags */
#define EXT2_INODE_F_SDELETE       (uint32)0x1u
#define EXT2_INODE_F_KEEP          (uint32)0x2u
#define EXT2_INODE_F_COMPRESS      (uint32)0x4u
#define EXT2_INODE_F_SYNC          (uint32)0x8u /* sync update */
#define EXT2_INODE_F_IMMUTE        (uint32)0x10
#define EXT2_INODE_F_APPEND        (uint32)0x20 /* append only */
#define EXT2_INODE_F_NODUMP        (uint32)0x40
#define EXT2_INODE_F_NOACC         (uint32)0x80 /* last acc time not update */
#define EXT2_INODE_F_HASH_DIR      (uint32)0x10000
#define EXT2_INODE_F_AFS_DIR       (uint32)0x20000
#define EXT2_INODE_F_JOURNAL       (uint32)0x40000

/* ext2 directory entry type */
#define EXT2_DIR_ENTRY_T_UNKNOWN   (uint8)0x0
#define EXT2_DIR_ENTRY_T_REGULAR   (uint8)0x1
#define EXT2_DIR_ENTRY_T_DIR       (uint8)0x2
#define EXT2_DIR_ENTRY_T_CHAR      (uint8)0x3
#define EXT2_DIR_ENTRY_T_BLOCK     (uint8)0x4
#define EXT2_DIR_ENTRY_T_FIFO      (uint8)0x5
#define EXT2_DIR_ENTRY_T_SOCKET    (uint8)0x6
#define EXT2_DIR_ENTRY_T_SYMBOLIC  (uint8)0x7

#define EXT2_FS_ID_SIZE            16u
#define EXT2_JOURNAL_ID_SIZE       16u
#define EXT2_VOLUME_NAME_SIZE      16u
#define EXT2_VOLUME_PATH_SIZE      64u
#define EXT2_DIRECT_BLOCK_SIZE     12u

#define EXT2_SIGNATURE             0xef53u
#define EXT2_SBLOCK_BYTES          1024u
#define EXT2_SBLOCK_OFFSET         1024u
#define EXT2_BGD_BYTES             32u
#define EXT2_DESCCRIPTOR_MAX       64u
#define EXT2_BLOCK_GROUP_MAX       128u
#define EXT2_ROOT_DIR_INODE        2u
#define EXT2_BUFFER_MAX            4096u
#define EXT2_INODE_ADDR_NULL       0u    /* inode addr start at 1 */
#define EXT2_OS_SV2_SIZE           12u
#define EXT2_MOUNT_NAME_LEN        32u

#define EXT2_DIR_CURRENT           "."
#define EXT2_DIR_PARENT            ".."

#define EXT2_INODE_INDEX(i)        ((i) - 1)

typedef struct fs_ext2_superblock                 s_ext2_spbk_t;
typedef struct fs_ext2_inode                      s_ext2_inode_t;
typedef struct fs_ext2_extended_superblock        s_ext2_ext_spbk_t;
typedef struct fs_ext2_dir                        s_ext2_dir_t;
typedef struct fs_ext2_block_group_descriptor     s_ext2_bgd_t;

typedef struct fs_ext2_block_group_descriptor_map s_ext2_bgd_map_t;
typedef struct fs_ext2_descriptor                 s_ext2_dspr_t;
typedef struct fs_ext2_descriptor_table           s_ext2_dspr_table_t;

/*
 *     Physical layout of the ext2 file system
 * +--------+---------+---------+- ... -+---------+
 * | boot   | block   | block   |  ...  | block   |
 * | sector | group 1 | group 2 |  ...  | group N |
 * +--------+---------+---------+- ... -+---------+
 *
 * For each block group:
 *
 * +-------+------------+--------+--------+-------+--------+
 * | super | group      | block  | inode  | inode | data   |
 * | block | descriptor | bitmap | bitmap | table | blocks |
 * +-------+------------+--------+--------+-------+--------+
 *
 */

/*
 * only available if major version >= 1.
 */
struct fs_ext2_extended_superblock {
    uint32 first_non_reserved_inode; /* fixed to 11 if major < 1 */
    uint16 inode_bytes;              /* fixed to 128 if major < 1 */
    uint16 block_group;
    uint32 optional_feature;
    uint32 required_feature;
    uint32 not_supported_feature;
    char   fs_id[EXT2_FS_ID_SIZE];
    char   volume_name[EXT2_VOLUME_NAME_SIZE];
    char   volume_path[EXT2_VOLUME_PATH_SIZE];
    uint32 compress_algorithm;
    uint8  prealloc_file_block_count;
    uint8  prealloc_dir_block_count;
    uint16 unused;
    char   journal_id[EXT2_JOURNAL_ID_SIZE];
    uint32 journal_inode;
    uint32 journal_device;
    uint32 orphan_inode_list;
} __attribute__((packed));

/*
 *     SUPERBLOCK contains all information about the layout of the filesystem.
 * The superblock is always located at byte 1024 from the begining of the volume
 * and is exactly 1024 bytes in length.
 *
 */
struct fs_ext2_superblock {
    union {
        struct {
            uint32 total_inode_count;
            uint32 total_block_count;
            uint32 superblock_reserved_count;
            uint32 unalloc_block_count;
            uint32 unalloc_inode_count;
            uint32 superblock_nmbr;
            uint32 block_size;           /* log2(block_size) - 10 */
            uint32 fragment_size;        /* log2(fragment_size) - 10 */
            uint32 group_block_count;
            uint32 group_fragment_count;
            uint32 group_inode_count;
            uint32 last_mount_time;      /* POSIX time */
            uint32 last_write_time;
            uint16 mount_times;          /* mount times before last fsck */
            uint16 max_mount_times;      /* max mount times befor fsck */
            uint16 signature;
            uint16 state;
            uint16 error_ops;            /* what to do when error detected */
            uint16 minor_version;
            uint32 last_fsck_time;
            uint32 fsck_interval;
            uint32 os_id;
            uint32 major_version;
            uint16 user_id_for_reserved;
            uint16 group_id_for_reserved;

            s_ext2_ext_spbk_t extended_super_block;
        };
        uint8 padding[EXT2_SBLOCK_BYTES];
    };
} __attribute__((packed));

/*
 *     BLOCK graoup descriptor table contains a descriptor for each block group
 * within file system. The table is located in the block immediately following
 * the superblock. Blocks are numbered staring at 0.
 */
struct fs_ext2_block_group_descriptor {
    union {
        struct {
            uint32 block_bitmap_addr; /* addressed in block */
            uint32 inode_bitmap_addr;
            uint32 inode_table_addr;
            uint16 unalloc_block_count;
            uint16 unalloc_inode_count;
            uint16 dir_count;
        };
        uint8 padding[EXT2_BGD_BYTES];
    };
} __attribute__((packed));

/*
 *     INODE is one structure that on disk represents a file, directory or link.
 * Inodes do not contain the data of the file or directory that they represent.
 * Instead, they link to the blocks that actually contain the data.
 *     INODE link blocks, each inode has a numberical address, inode address
 * start at 1. With ext2 major version 1, inode 1 to 10 are reserved and should
 * be in an allocated state. Inode has fixed 128 bytes for version 0 of ext2.
 *
 *     block-group     = (inode - 1) / INODE_PER_GROUP
 *     index           = (inode - 1) % INODE_PER_GROUP
 *     contained-block = (inode * INODE_SIZE) / BLOCK_SIZE
 *
 *     EACH inode contains 12 direct pointers, one singly indirect pointer, one
 * doubly indirect pointer and one triply indirect pointer.
 *     Direct pointer: 12 pointers, is the block address of a block.
 */
struct fs_ext2_inode {
    struct {
        uint16 type:4;
        uint16 permission:12;
    };
    uint16 usr_id;
    uint32 bytes_size_low;
    uint32 last_acc_time;
    uint32 create_time;
    uint32 last_mod_time;
    uint32 delete_time;
    uint16 group_id;
    uint16 hard_link_count;
    uint32 disk_sector_count; /* not count the actual inode structure linked */
    uint32 flags;
    uint32 os_sp_val_1;       /* os specific value */
    uint32 direct_block_pointer[EXT2_DIRECT_BLOCK_SIZE];
    uint32 singly_indirect_pointer;
    uint32 doubly_indirect_pointer;
    uint32 triply_indirect_pointer;
    uint32 gen_number;
    uint32 extended_attr_block; /* only availabe in Version >= 1 */
    uint32 bytes_size_high;     /* only availabe in Version >= 1 */
    uint32 fragment_block_addr;
    uint8  os_sp_val_2[EXT2_OS_SV2_SIZE];
} __attribute__((packed));

struct fs_ext2_block_group_descriptor_map {
    bool           b_bitmap_is_dirty;
    bool           i_bitmap_is_dirty;
    s_bitmap_t     *block_bitmap;
    s_bitmap_t     *inode_bitmap;
};

struct fs_ext2_descriptor {
    e_disk_id_t      device_id;
    uint32           bg_count;
    s_ext2_spbk_t    *superblock;
    s_ext2_bgd_t     *bgd_table;
    s_ext2_bgd_map_t **map_array;
    s_disk_pt_t      *disk_pt;
};

struct fs_ext2_descriptor_table {
    char          mountpoint[EXT2_MOUNT_NAME_LEN];
    uint32        index;
    uint32        size;
    s_ext2_dspr_t **dspr_array;
};

/*
 *     DIRECTORY are inodes, which contains some number of "entries" as their
 * contents. These entries are nothing more than a name/inode pair. A directory
 * inode stores these entries in a linked-list in its contents block.
 *     THE root directory is inode 2.
 *     DIRECTORY entries are not allowed to span multiple blocks.
 */
struct fs_ext2_dir {
    uint32    inode_nmbr;
    uint16    size;
    uint8     name_length_least; /* least-significant 8 bits */
    union {
        uint8 type;
        uint8 name_length_most;
    };
    char      name[0];
} __attribute__((packed));


/* It will trigger kernel panic if size is invalid. */
#define PANIC_IF_INV_SIZE(size) if (IS_SIZE_INVALID_P(size)) {       \
                                    KERNEL_PANIC("Invalid size.\n"); \
                                }

#endif

