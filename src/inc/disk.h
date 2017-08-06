#ifndef HAVE_DEFINE_DISK_H
#define HAVE_DEFINE_DISK_H

typedef struct disk_partition       s_disk_pt_t;
typedef struct disk_partition_table s_disk_pt_table_t;
typedef struct disk_buffer          s_disk_buf_t;

/* disk partition offset of MBR */
#define DISK_PT_0_OFFSET            0x1be
#define DISK_PT_1_OFFSET            0x1ce
#define DISK_PT_2_OFFSET            0x1de
#define DISK_PT_3_OFFSET            0x1ee

#define DISK_PT_SIZE                0x10
#define DISK_PT_TABLE_SIZE          0x4

struct disk_partition {
    uint8 boot;

    uint8 head_start;
    union {
        uint16 sector_start:6;
        uint16 cylinder_start:10;
    };

    uint8 system_id;

    uint8 head_end;
    union {
        uint16 sector_end:6;
        uint16 cylinder_end:10;
    };

    uint32 sector_relative;        /* relative sector */
    uint32 sector_count;
} __attribute__((packed));


struct disk_partition_table {
    s_disk_pt_t table[DISK_PT_TABLE_SIZE];
};

struct disk_buffer {
    uint8  *buffer;
    uint32 index;
    uint32 size;
};

#endif

