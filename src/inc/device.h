#ifndef HAVE_DEFINE_DEVICE_H
#define HAVE_DEFINE_DEVICE_H

typedef enum device_id         e_dev_id_t;

enum device_id {
    DEVICE_START     = 0x0,
    ATA_DEVICE_START = 0x0,
    ATA_0_DEVICE_0   = 0x0, /* primary bus with first disk */
    ATA_0_DEVICE_1   = 0x1,
    ATA_DEVICE_LIMIT,
    DEVICE_LIMIT     = ATA_DEVICE_LIMIT,
    DEVICE_INVALID,
};


#endif

