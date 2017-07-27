static inline void
ata_device_software_reset(uint16 port)
{
    io_bus_write_byte(port, ATA_DEV_CR_SRST);
    io_bus_write_byte(port, ATA_SEC_CR_NULL);
}

static inline s_ata_device_info_t *
ata_device_information(void)
{
    return &ata_dev_info;
}

static inline void
ata_device_drive_set(uint16 port, uint8 val)
{
    io_bus_write_byte(port, val);
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

static inline uint16
ata_device_cylinder_read(uint16 status_port, uint16 port_low, uint16 port_high)
{
    uint8 status;
    uint16 cylinder;
    uint8 cylinder_low;
    uint8 cylinder_high;

    status = io_bus_read_byte(status_port);

    while (!ata_device_status_readable_p(status)) {
        status = io_bus_read_byte(status_port);
    }

    cylinder_low = io_bus_read_byte(port_low);
    cylinder_high = io_bus_read_byte(port_high);
    cylinder = (cylinder_high << 8) | cylinder_low;

    return cylinder;
}

static inline void
ata_device_type_detect(s_ata_device_info_t *dev_info)
{
    uint16 signature;

    kassert(dev_info);

    ata_device_drive_set(ATA_DRIVE_PORT, ATA_PRI_DRIVE_HEAD_0);
    /* the signature reused cylinder field for drive */
    signature = ata_device_cylinder_read(ATA_STATUS_PORT, ATA_CYL_LOW_PORT,
        ATA_CYL_HIGH_PORT);
    ata_device_info_type_set(dev_info, signature);

    if (signature == 0) {
        printf_vga_tk("Detect PATA device\n");
    }
}

void
ata_device_detect(void)
{
    s_ata_device_info_t *dev_info;

    dev_info = ata_device_information();

    ata_device_software_reset(ATA_PRI_DEV_CR_PORT);

    ata_device_type_detect(dev_info);
}

