#ifndef HAVE_DEFINE_DISK_H
#define HAVE_DEFINE_DISK_H

typedef struct disk_partition       s_disk_pt_t;
typedef struct disk_partition_table s_disk_pt_table_t;
typedef struct disk_buffer          s_disk_buf_t;
typedef enum   disk_device_id       e_disk_dev_id_t;

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

struct disk_buffer {
    uint8  *array;
    uint32 index;
    uint32 size;
};

enum disk_device_id {
    ATA_0_DEVICE_0 = 0x0, /* primary bus with first disk */
    ATA_0_DEVICE_1 = 0x1,
    ATA_DEVICE_LIMIT,
};

#endif

