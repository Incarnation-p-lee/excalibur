static inline uint32
ata_device_info_type(s_ata_device_info_t *dev_info)
{
    kassert(dev_info);

    return dev_info->type;
}

static inline void
ata_device_info_type_set(s_ata_device_info_t *dev_info, uint32 type)
{
    kassert(dev_info);

    dev_info->type = type;
}

static inline s_ata_device_info_t *
ata_device_info(void)
{
    return &ata_dev_info;
}

static inline bool
ata_device_status_busy_p(uint8 status)
{
    if ((status & ATA_STATUS_BUSY) != 0) {
        return true;
    } else {
        return false;
    }
}

static inline bool
ata_device_status_error_p(uint8 status)
{
    if ((status & ATA_STATUS_ERROR) != 0) {
        return true;
    } else {
        return false;
    }
}

static inline bool
ata_device_status_device_ready_p(uint8 status)
{
    if ((status & ATA_STATUS_DRDY) != 0) {
        return true;
    } else {
        return false;
    }
}

static inline bool
ata_device_status_readable_p(uint8 status)
{
    if (ata_device_status_busy_p(status)) {
        return false;
    } else if (ata_device_status_error_p(status)) {
        return false;
    } else {
        return ata_device_status_device_ready_p(status);
    }
}

static inline bool
ata_device_status_valid_p(uint8 status)
{
    if (status == ATA_STATUS_INVALID) {
        return false;
    } else {
        return true;
    }
}

