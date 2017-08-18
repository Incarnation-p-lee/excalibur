#ifndef HAVE_DEFINE_DISK_DATA_H
#define HAVE_DEFINE_DISK_DATA_H

static s_disk_dspt_t disk_descripotr[] = {
    [ATA_0_DEVICE_0] = {
        ATA_0_DEVICE_0,
        false, /* is_active */
        0,
        &ata_device_lba_byte_read,
        FS_EXT2_ROOT,
        { /* s_disk_pt_table_t */
            {
                {0, 0, {0}, 0, 0, {0}, 0, 0},
                {0, 0, {0}, 0, 0, {0}, 0, 0},
                {0, 0, {0}, 0, 0, {0}, 0, 0},
                {0, 0, {0}, 0, 0, {0}, 0, 0},
            },
        },
    },

    [ATA_0_DEVICE_1] = {
        ATA_0_DEVICE_1,
        false, /* is_active */
        0,
        &ata_device_lba_byte_read,
        FS_EXT2_HOME,
        { /* s_disk_pt_table_t */
            {
                {0, 0, {0}, 0, 0, {0}, 0, 0},
                {0, 0, {0}, 0, 0, {0}, 0, 0},
                {0, 0, {0}, 0, 0, {0}, 0, 0},
                {0, 0, {0}, 0, 0, {0}, 0, 0},
            },
        },
    },
};

#endif

