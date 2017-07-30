#ifndef HAVE_DEFINED_ATA_DEVICE_H
#define HAVE_DEFINED_ATA_DEVICE_H

/*
 *     ATA device I/O port layout sample
 * +-------+------------+------------------------------------------------+
 * | Port  | Read/Write | Comments                                       |
 * +-------+------------+------------------------------------------------+
 * | 0x1f0 | R/W        | Data register.                                 |
 * +-------+------------+------------------------------------------------+
 * | 0x1f1 | R          | Error register.                                |
 * +-------+------------+------------------------------------------------+
 * |       |            | feature register.                              |
 * +-------+------------+------------------------------------------------+
 * | 0x1f2 | R/W        | Sector count, how many sector to read/write.   |
 * +-------+------------+------------------------------------------------+
 * | 0x1f3 | R/W        | Sector number, actually sector wanted.         |
 * +-------+------------+------------------------------------------------+
 * |       |            | LBA_low. Logical block address.                |
 * +-------+------------+------------------------------------------------+
 * | 0x1f4 | R/W        | Cylinder low.                                  |
 * +-------+------------+------------------------------------------------+
 * |       |            | LBA_mid.                                       |
 * +-------+------------+------------------------------------------------+
 * | 0x1f5 | R/W        | Cylinder high.                                 |
 * +-------+------------+------------------------------------------------+
 * |       |            | LBA_high.                                      |
 * +-------+------------+------------------------------------------------+
 * | 0x1f6 | R/W        | Drive/Head.                                    |
 * +-------+------------+------------------------------------------------+
 * |       |            | bit 7 - 5, 0b101                               |
 * +-------+------------+------------------------------------------------+
 * |       |            | bit 4    , 0 -> drive 0, 1 -> drive 1          |
 * +-------+------------+------------------------------------------------+
 * |       |            | bit 3 - 0, head select bits                    |
 * +-------+------------+------------------------------------------------+
 * | 0x1f7 | R          | Status register                                |
 * +-------+------------+------------------------------------------------+
 * |       |            | bit 7, controller is excuting cmd, busy.       |
 * +-------+------------+------------------------------------------------+
 * |       |            | bit 6, drive is ready.                         |
 * +-------+------------+------------------------------------------------+
 * |       |            | bit 5, write fault.                            |
 * +-------+------------+------------------------------------------------+
 * |       |            | bit 4, seek complete.                          |
 * +-------+------------+------------------------------------------------+
 * |       |            | bit 3, sector buffer require servicing.        |
 * +-------+------------+------------------------------------------------+
 * |       |            | bit 2, disk data read corected.                |
 * +-------+------------+------------------------------------------------+
 * |       |            | bit 1, index, set to 1 each revolution.        |
 * +-------+------------+------------------------------------------------+
 * |       |            | bit 0, previous command ended in an error.     |
 * +-------+------------+------------------------------------------------+
 * | 0x1f7 | W          | Command register                               |
 * +-------+------------+------------------------------------------------+
 * |       |            | 0x50, format track.                            |
 * +-------+------------+------------------------------------------------+
 * |       |            | 0x20, read sectors with re-try.                |
 * +-------+------------+------------------------------------------------+
 * |       |            | 0x21, read sectors without re-try.             |
 * +-------+------------+------------------------------------------------+
 * |       |            | 0x22, read long with re-try.                   |
 * +-------+------------+------------------------------------------------+
 * |       |            | 0x23, read long without re-try.                |
 * +-------+------------+------------------------------------------------+
 * |       |            | 0x30, write sectors with re-try.               |
 * +-------+------------+------------------------------------------------+
 * |       |            | 0x31, write sectors without re-try.            |
 * +-------+------------+------------------------------------------------+
 * |       |            | 0x30, write long with re-try.                  |
 * +-------+------------+------------------------------------------------+
 * |       |            | 0x31, write long without re-try.               |
 * +-------+------------+------------------------------------------------+
 */

typedef enum ata_device_type      e_ata_dev_type_t;
typedef enum ata_device_id        e_ata_dev_id_t;
typedef struct ata_device_info    s_ata_dev_info_t;
typedef struct ata_device_io_port s_ata_dev_io_port_t;

/*
 *    CURRENT disk controller chips support 2 ATA buses per-chip. There is a
 * standardized set of I/O port to control the disk bues. The first two buses
 * are called the primary an secondary ATA bus. And almost always controlled by
 * IO port 0x1f0 ~ 0x1f7 and 0x170 ~ 0x177. With the associated Device control
 * IO port 0x3f6 and 0x376.
 *    THERE is one wire dedicated to select which drive on each bus is active.
 * Master and slave devices. So one ATA chip has 2 buses, and there can be
 * 2 device connect to one ATA bus, but only one is active at the same time.
 */

/* ata channel 0 (primary bus) device port */
#define ATA_0_IO_PORT         0x1f0
#define ATA_0_P_DATA          (ATA_0_IO_PORT + 0x0)
#define ATA_0_P_FEATURE       (ATA_0_IO_PORT + 0x1)
#define ATA_0_P_ERROR         (ATA_0_IO_PORT + 0x1)
#define ATA_0_P_SECTOR_CNT    (ATA_0_IO_PORT + 0x2)
#define ATA_0_P_SECTOR_NUM    (ATA_0_IO_PORT + 0x3)
#define ATA_0_P_LBA_LOW       (ATA_0_IO_PORT + 0x3)
#define ATA_0_P_CYL_LOW       (ATA_0_IO_PORT + 0x4)
#define ATA_0_P_LBA_MID       (ATA_0_IO_PORT + 0x4)
#define ATA_0_P_CYL_HIGH      (ATA_0_IO_PORT + 0x5)
#define ATA_0_P_LBA_HIGH      (ATA_0_IO_PORT + 0x5)
#define ATA_0_P_HEAD          (ATA_0_IO_PORT + 0x6)
#define ATA_0_P_DRIVE         (ATA_0_IO_PORT + 0x6)
#define ATA_0_P_CMD           (ATA_0_IO_PORT + 0x7)
#define ATA_0_P_STATUS        (ATA_0_IO_PORT + 0x7)
#define ATA_0_P_DEV_CR        0x3f6

#define ATA_DRIVE_0           (0xA << 4)
#define ATA_DRIVE_1           (0xB << 4)

#define ATA_DEV_CR_NULL       BIT_CLEAR
#define ATA_DEV_CR_NLEN       (BIT_SET << 1) /* set to stop device send int */
#define ATA_DEV_CR_SRST       (BIT_SET << 2) /* set to software reset on bus */
#define ATA_DEV_CR_HOB        (BIT_SET << 7) /* set to read back high order */

#define ATA_STATUS_BUSY       (BIT_SET << 7)
#define ATA_STATUS_DRDY       (BIT_SET << 6) /* device is ready */
#define ATA_STATUS_DRQ        (BIT_SET << 3) /* data request to transfer data */
#define ATA_STATUS_ERROR      (BIT_SET << 0) /* an error occurred of last cmd */

#define ATA_STATUS_INVALID    0xff
#define ATA_PHYS_SECTOR_SIZE  512

/*
 *     ATA read CHS mode has max head 16, max cylinder 65536, with sector is
 * usually always 1-63, and sector 0 reserved, max 255 sector/track.
 *     If 63 sector/track, max disk is up to 31.5GB
 *     If 255 sector/track, max disk is up to 127.5GB
 */
#define ATA_CYLINDER_MAX      65536
#define ATA_HEADER_MAX        16
#define ATA_TRACK_SECTOR_MAX  255

enum ata_device_type {
    ATA_DEV_UNKNOWN  = 0xffff,
    ATA_DEV_PATAPI   = 0xeb14,
    ATA_DEV_SATAPI   = 0x9669,
    ATA_DEV_PATA     = 0x0,
    ATA_DEV_SATA     = 0xc33c,
};

enum ata_device_id {
    ATA_0_DEVICE_0 = 0x0, /* primary bus with first disk */
    ATA_0_DEVICE_1 = 0x1,
    ATA_DEVICE_LIMIT,
};

struct ata_device_io_port {
    uint16 data_port;
    uint16 error_port;
    uint16 sector_count_port;
    union {
        uint16 sector_number_port;
        uint16 lba_low;
    };
    union {
        uint16 cylinder_low_port;
        uint16 lba_mid;
    };
    union {
        uint16 cylinder_high_port;
        uint16 lba_high;
    };
    uint16 drive_head_port;
    union {
        uint16 cmd_port;
        uint16 status_port;
    };
    uint16 control_port;
};

struct ata_device_info {
    uint32              type;
    s_ata_dev_io_port_t io_port;
    uint16              drive_id;
};

static s_ata_dev_info_t dev_info_array[] = {
    [ATA_0_DEVICE_0] = {
        ATA_DEV_UNKNOWN,
        {
            ATA_0_P_DATA,
            ATA_0_P_FEATURE,
            ATA_0_P_SECTOR_CNT,
            {ATA_0_P_LBA_LOW,},
            {ATA_0_P_LBA_MID,},
            {ATA_0_P_LBA_HIGH,},
            ATA_0_P_HEAD,
            {ATA_0_P_CMD,},
            ATA_0_P_DEV_CR,
        },
        ATA_DRIVE_0,
    },
    [ATA_0_DEVICE_1] = {
        ATA_DEV_UNKNOWN,
        {
            ATA_0_P_DATA,
            ATA_0_P_FEATURE,
            ATA_0_P_SECTOR_CNT,
            {ATA_0_P_LBA_LOW,},
            {ATA_0_P_LBA_MID,},
            {ATA_0_P_LBA_HIGH,},
            ATA_0_P_HEAD,
            {ATA_0_P_CMD,},
            ATA_0_P_DEV_CR,
        },
        ATA_DRIVE_1,
    },
};

#endif

