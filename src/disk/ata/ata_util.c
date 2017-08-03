static inline bool
ata_device_info_legal_p(s_ata_dev_info_t *dev_info)
{
    if (dev_info == NULL) {
        return false;
    } else if (dev_info->drive_id == ATA_DRIVE_0) {
        return true;
    } else if (dev_info->drive_id == ATA_DRIVE_1) {
        return true;
    } else {
        return false;
    }
}

static inline bool
ata_device_info_io_port_legal_p(s_ata_dev_io_port_t *io_port)
{
    if (io_port == NULL) {
        return false;
    } else {
        return true;
    }
}

static inline uint32
ata_device_info_type(s_ata_dev_info_t *dev_info)
{
    kassert(ata_device_info_legal_p(dev_info));

    return dev_info->type;
}

static inline uint32
ata_device_info_limit(void)
{
    return ARRAY_CNT_OF(dev_info_array);
}

static inline void
ata_device_info_type_set(s_ata_dev_info_t *dev_info, uint32 type)
{
    kassert(ata_device_info_legal_p(dev_info));

    dev_info->type = type;
}

static inline s_ata_dev_info_t *
ata_device_info(uint32 i)
{
    kassert(i < ata_device_info_limit());

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
ata_device_status_data_requested_p(uint8 status)
{
    if ((status & ATA_STATUS_DRQ) != 0) {
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
    } else if (!ata_device_status_data_requested_p(status)) {
        return false;
    } else {
        return ata_device_status_device_ready_p(status);
    }
}

static inline bool
ata_device_status_seek_complete_p(uint8 status)
{
    if ((status & ATA_STATUS_DSC) != 0) {
        return true;
    } else {
        return false;
    }
}

static inline uint16
ata_device_info_io_control_port(s_ata_dev_io_port_t *io_port)
{
    kassert(ata_device_info_io_port_legal_p(io_port));

    return io_port->control_port;
}

static inline uint16
ata_device_info_io_drive_port(s_ata_dev_io_port_t *io_port)
{
    kassert(ata_device_info_io_port_legal_p(io_port));

    return io_port->drive_head_port;
}

static inline uint16
ata_device_info_io_status_port(s_ata_dev_io_port_t *io_port)
{
    kassert(ata_device_info_io_port_legal_p(io_port));

    return io_port->status_port;
}

static inline uint16
ata_device_info_io_cylinder_low_port(s_ata_dev_io_port_t *io_port)
{
    kassert(ata_device_info_io_port_legal_p(io_port));

    return io_port->cylinder_low_port;
}

static inline uint16
ata_device_info_io_cylinder_high_port(s_ata_dev_io_port_t *io_port)
{
    kassert(ata_device_info_io_port_legal_p(io_port));

    return io_port->cylinder_high_port;
}

static inline uint16
ata_device_info_io_lba_low_port(s_ata_dev_io_port_t *io_port)
{
    kassert(ata_device_info_io_port_legal_p(io_port));

    return io_port->lba_low;
}

static inline uint16
ata_device_info_io_cmd_port(s_ata_dev_io_port_t *io_port)
{
    kassert(ata_device_info_io_port_legal_p(io_port));

    return io_port->cmd_port;
}

static inline uint16
ata_device_info_io_data_port(s_ata_dev_io_port_t *io_port)
{
    kassert(ata_device_info_io_port_legal_p(io_port));

    return io_port->data_port;
}

static inline uint16
ata_device_info_io_sector_count_port(s_ata_dev_io_port_t *io_port)
{
    kassert(ata_device_info_io_port_legal_p(io_port));

    return io_port->sector_count_port;
}

static inline s_ata_dev_io_port_t *
ata_device_info_io_port(s_ata_dev_info_t *dev_info)
{
    kassert(ata_device_info_legal_p(dev_info));

    return &dev_info->io_port;
}

static inline uint16
ata_device_info_control_port(s_ata_dev_info_t *dev_info)
{
    s_ata_dev_io_port_t *io_port;

    kassert(ata_device_info_legal_p(dev_info));

    io_port = ata_device_info_io_port(dev_info);

    return ata_device_info_io_control_port(io_port);
}

static inline uint16
ata_device_info_drive_port(s_ata_dev_info_t *dev_info)
{
    s_ata_dev_io_port_t *io_port;

    kassert(ata_device_info_legal_p(dev_info));

    io_port = ata_device_info_io_port(dev_info);

    return ata_device_info_io_drive_port(io_port);
}

static inline uint16
ata_device_info_status_port(s_ata_dev_info_t *dev_info)
{
    s_ata_dev_io_port_t *io_port;

    kassert(ata_device_info_legal_p(dev_info));

    io_port = ata_device_info_io_port(dev_info);

    return ata_device_info_io_status_port(io_port);
}

static inline uint16
ata_device_info_cylinder_low_port(s_ata_dev_info_t *dev_info)
{
    s_ata_dev_io_port_t *io_port;

    kassert(ata_device_info_legal_p(dev_info));

    io_port = ata_device_info_io_port(dev_info);

    return ata_device_info_io_cylinder_low_port(io_port);
}

static inline uint16
ata_device_info_cylinder_high_port(s_ata_dev_info_t *dev_info)
{
    s_ata_dev_io_port_t *io_port;

    kassert(ata_device_info_legal_p(dev_info));

    io_port = ata_device_info_io_port(dev_info);

    return ata_device_info_io_cylinder_high_port(io_port);
}

static inline uint16
ata_device_info_drive_id(s_ata_dev_info_t *dev_info)
{
    kassert(ata_device_info_legal_p(dev_info));

    return dev_info->drive_id;
}

static inline uint16
ata_device_info_sector_count_port(s_ata_dev_info_t *dev_info)
{
    s_ata_dev_io_port_t *io_port;

    kassert(ata_device_info_legal_p(dev_info));

    io_port = ata_device_info_io_port(dev_info);

    return ata_device_info_io_sector_count_port(io_port);
}

static inline uint16
ata_device_info_lba_low_port(s_ata_dev_info_t *dev_info)
{
    s_ata_dev_io_port_t *io_port;

    kassert(ata_device_info_legal_p(dev_info));

    io_port = ata_device_info_io_port(dev_info);

    return ata_device_info_io_lba_low_port(io_port);
}

static inline uint16
ata_device_info_lba_mid_port(s_ata_dev_info_t *dev_info)
{
    return ata_device_info_cylinder_low_port(dev_info);
}

static inline uint16
ata_device_info_lba_high_port(s_ata_dev_info_t *dev_info)
{
    return ata_device_info_cylinder_high_port(dev_info);
}

static inline uint16
ata_device_info_cmd_port(s_ata_dev_info_t *dev_info)
{
    s_ata_dev_io_port_t *io_port;

    kassert(ata_device_info_legal_p(dev_info));

    io_port = ata_device_info_io_port(dev_info);

    return ata_device_info_io_cmd_port(io_port);
}

static inline uint16
ata_device_info_data_port(s_ata_dev_info_t *dev_info)
{
    s_ata_dev_io_port_t *io_port;

    kassert(ata_device_info_legal_p(dev_info));

    io_port = ata_device_info_io_port(dev_info);

    return ata_device_info_io_data_port(io_port);
}

static inline uint16
ata_device_info_cylinder_count(s_ata_dev_info_t *dev_info)
{
    kassert(ata_device_info_legal_p(dev_info));

    return dev_info->cylinder_count;
}

static inline void
ata_device_info_cylinder_count_set(s_ata_dev_info_t *dev_info, uint16 count)
{
    kassert(ata_device_info_legal_p(dev_info));

    dev_info->cylinder_count = count;
}

static inline uint16
ata_device_info_head_count(s_ata_dev_info_t *dev_info)
{
    kassert(ata_device_info_legal_p(dev_info));

    return dev_info->head_count;
}

static inline void
ata_device_info_head_count_set(s_ata_dev_info_t *dev_info, uint16 count)
{
    kassert(ata_device_info_legal_p(dev_info));

    dev_info->head_count = count;
}

static inline uint16
ata_device_info_track_sector(s_ata_dev_info_t *dev_info)
{
    kassert(ata_device_info_legal_p(dev_info));

    return dev_info->track_sector;
}

static inline void
ata_device_info_track_sector_set(s_ata_dev_info_t *dev_info, uint16 val)
{
    kassert(ata_device_info_legal_p(dev_info));

    dev_info->track_sector = val;
}

static inline uint16
ata_device_info_sector_bytes(s_ata_dev_info_t *dev_info)
{
    kassert(ata_device_info_legal_p(dev_info));

    return dev_info->sector_bytes;
}

static inline void
ata_device_info_sector_bytes_set(s_ata_dev_info_t *dev_info, uint16 val)
{
    kassert(ata_device_info_legal_p(dev_info));

    dev_info->sector_bytes = val;
}

