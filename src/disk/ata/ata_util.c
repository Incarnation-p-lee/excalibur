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

