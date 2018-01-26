#ifndef HAVE_DEFINE_DISK_H
#define HAVE_DEFINE_DISK_H

typedef struct disk_partition       s_disk_pt_t;
typedef struct disk_partition_table s_disk_pt_table_t;
typedef struct disk_descriptor      s_disk_dspt_t;

typedef uint32 (*f_disk_read_t)(s_block_buf_t *, e_dev_id_t, uint32, uint32);

/* disk partition offset of MBR */
#define DISK_PT_OFFSET              DISK_PT_0_OFFSET
#define DISK_PT_0_OFFSET            0x1be
#define DISK_PT_1_OFFSET            0x1ce
#define DISK_PT_2_OFFSET            0x1de
#define DISK_PT_3_OFFSET            0x1ee

#define DISK_PT_BOOT_MASK           0x80
#define DISK_PT_SIZE                0x10
#define DISK_PT_TABLE_SIZE          0x4
#define DISK_PT_TABLE_BYTES         (DISK_PT_SIZE * DISK_PT_TABLE_SIZE)

struct disk_partition {
    uint8 boot;

    uint8 head_start;
    struct {
        uint16 sector_start:6;
        uint16 cylinder_start:10;
    };

    uint8 system_id;

    uint8 head_end;
    struct {
        uint16 sector_end:6;
        uint16 cylinder_end:10;
    };

    uint32 sector_offset;        /* offset of sector from disk start */
    uint32 sector_count;
} __attribute__((packed));


struct disk_partition_table {
    s_disk_pt_t array[DISK_PT_TABLE_SIZE];
};

struct disk_descriptor {
    e_dev_id_t        id;
    bool              is_active;
    uint32            sector_bytes;
    f_disk_read_t     read;
    char              mount[FS_NAME_MAX];
    s_disk_pt_table_t pt_table;
};

#endif

