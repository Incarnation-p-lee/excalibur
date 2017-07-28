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

static inline void
ata_device_info_port_set_i(s_ata_device_info_t *dev_info, uint16 port_start)
{
    kassert(dev_info);

    dev_info->data_port = port_start++;
    dev_info->error_port = port_start++;
    dev_info->sector_count_port = port_start++;
    dev_info->sector_number_port = port_start++;
    dev_info->cylinder_low_port = port_start++;
    dev_info->cylinder_high_port = port_start++;
    dev_info->drive_head_port = port_start++;
    dev_info->status_port = port_start++;
}

static inline void
ata_device_info_port_set(s_ata_device_info_t *dev_info, uint32 device)
{
    kassert(dev_info);

    switch (device) {
        case ATA_0_DEVICE_MASTER:
            ata_device_info_port_set(dev_info, ATA_0_PORT_MASTER);
            break;
        default:
            break;
    }
}

static inline s_ata_device_info_t *
ata_device_info(uint32 i)
{
    kassert(i < ATA_DEVICE_LIMIT);

    return &dev_info_array[i];
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

