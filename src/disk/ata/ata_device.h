#ifndef HAVE_DEFINED_ATA_DEVICE_H
#define HAVE_DEFINED_ATA_DEVICE_H

/*
 *     ATA channel 0 master device I/O port layout.
 * +-------+------------+------------------------------------------------+
 * | Port  | Read/Write | Comments                                       |
 * +-------+------------+------------------------------------------------+
 * | 0x1f0 | R/W        | Data register.                                 |
 * +-------+------------+------------------------------------------------+
 * | 0x1f1 | R          | Error register.                                |
 * +-------+------------+------------------------------------------------+
 * | 0x1f2 | R/W        | Sector count, how many sector to read/write.   |
 * +-------+------------+------------------------------------------------+
 * | 0x1f3 | R/W        | Sector number, actually sector wanted.         |
 * +-------+------------+------------------------------------------------+
 * | 0x1f4 | R/W        | Cylinder low.                                  |
 * +-------+------------+------------------------------------------------+
 * | 0x1f5 | R/W        | Cylinder high.                                 |
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

typedef enum ata_device_type   e_ata_device_type_t;
typedef enum ata_device_id     e_ata_device_id_t;
typedef struct ata_device_info s_ata_device_info_t;

/*
 *    CURRENT disk controller chips support 2 ATA buses per-chip. There is a
 * standardized set of I/O port to control the disk bues. The first two buses
 * are called the primary an secondary ATA bus. And almost always controlled by
 * IO port 0x1f0 ~ 0x1f7 and 0x170 ~ 0x177. With the associated Device control
 * IO port 0x3f6 and 0x376.
 *    THERE is one wire dedicated to select which drive on each bus is active.
 * Master and slave devices.
 */

/* ata channel 0 master device port */
#define ATA_0_PORT_MASTER     0x1f0
#define ATA_0_DATA_PORT       (ATA_0_PORT_MASTER + 0x0)
#define ATA_0_FEATURE_PORT    (ATA_0_PORT_MASTER + 0x1)
#define ATA_0_SECTOR_CNT_PORT (ATA_0_PORT_MASTER + 0x2)
#define ATA_0_SECTOR_NUM_PORT (ATA_0_PORT_MASTER + 0x3)
#define ATA_0_CYL_LOW_PORT    (ATA_0_PORT_MASTER + 0x4)
#define ATA_0_CYL_HIGH_PORT   (ATA_0_PORT_MASTER + 0x5)
#define ATA_0_HEAD_PORT       (ATA_0_PORT_MASTER + 0x6)
#define ATA_0_CMD_PORT        (ATA_0_PORT_MASTER + 0x7)

#define ATA_0_ERROR_PORT      ATA_0_FEATURE_PORT
#define ATA_0_LBA_LO_PORT     ATA_0_SECTOR_CNT_PORT
#define ATA_0_LBA_MID_PORT    ATA_0_CYL_LOW_PORT
#define ATA_0_LBA_HIGH_PORT   ATA_0_CYL_HIGH_PORT
#define ATA_0_DRIVE_PORT      ATA_0_HEAD_PORT
#define ATA_0_STATUS_PORT     ATA_0_CMD_PORT
#define ATA_0_DEV_CR_PORT     0x3f6 /* primary device control register port */
#define ATA_1_DEV_CR_PORT     0x376 /* secondary device control register port */

#define ATA_DRIVE_0           0xA
#define ATA_DRIVE_1           0xB
#define ATA_HEAD_0            0x0
#define ATA_DRIVE_0_HEAD_0    ((ATA_DRIVE_0 << 4) | ATA_HEAD_0)
#define ATA_DRIVE_1_HEAD_0    ((ATA_DRIVE_1 << 4) | ATA_HEAD_0)

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
    ATA_0_DEVICE_MASTER = 0x0,
    ATA_0_DEVICE_SLAVE  = 0x1,
    ATA_DEVICE_LIMIT,
};

struct ata_device_info {
    uint32 type;

    uint16 data_port;
    uint16 error_port;
    uint16 sector_count_port;
    uint16 sector_number_port;
    uint16 cylinder_low_port;
    uint16 cylinder_high_port;
    uint16 drive_head_port;
    uint16 status_port;
};

static s_ata_device_info_t dev_info_array[] = {
    [ATA_0_DEVICE_MASTER] = {ATA_DEV_UNKNOWN, 0,},
};

#endif

