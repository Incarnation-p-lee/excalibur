#ifndef HAVE_DEFINED_ATA_DEVICE_H
#define HAVE_DEFINED_ATA_DEVICE_H

/*
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
typedef struct ata_device_info s_ata_device_info_t;

#define ATA_0_PORT_START      0x1f0
#define ATA_0_DATA_PORT       (ATA_0_PORT_START + 0x0)
#define ATA_0_FEATURE_PORT    (ATA_0_PORT_START + 0x1)
#define ATA_0_SECTOR_CNT_PORT (ATA_0_PORT_START + 0x2)
#define ATA_0_SECTOR_NUM_PORT (ATA_0_PORT_START + 0x3)
#define ATA_0_CYL_LOW_PORT    (ATA_0_PORT_START + 0x4)
#define ATA_0_CYL_HIGH_PORT   (ATA_0_PORT_START + 0x5)
#define ATA_0_HEAD_PORT       (ATA_0_PORT_START + 0x6)
#define ATA_0_CMD_PORT        (ATA_0_PORT_START + 0x7)

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

#define ATA_STATUS_INVALID   0xff

enum ata_device_type {
    ATA_DEV_UNKNOWN  = 0xffff,
    ATA_DEV_PATAPI   = 0xeb14,
    ATA_DEV_SATAPI   = 0x9669,
    ATA_DEV_PATA     = 0x0,
    ATA_DEV_SATA     = 0xc33c,
};

struct ata_device_info {
    uint32 type;
};

static s_ata_device_info_t ata_dev_info = {
    ATA_DEV_UNKNOWN,
};

#endif

