#ifndef HAVE_DEFINE_DISK_DATA_H
#define HAVE_DEFINE_DISK_DATA_H

static s_disk_dspt_t disk_descripotr[] = {
    {ATA_0_DEVICE_0, &ata_device_lba_byte_read},
    {ATA_0_DEVICE_1, &ata_device_lba_byte_read},
};

#endif

