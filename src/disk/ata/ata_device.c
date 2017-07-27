static inline void
ata_device_software_reset(uint16 port)
{
    io_bus_write_byte(port, ATA_DEV_CR_SRST);
    io_bus_write_byte(port, ATA_DEV_CR_NULL);
}

static inline void
ata_device_drive_set(uint16 port, uint8 val)
{
    io_bus_write_byte(port, val);
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
    uint8 status;
    uint16 signature;

    kassert(dev_info);

    ata_device_software_reset(ATA_0_DEV_CR_PORT);
    ata_device_drive_set(ATA_0_DRIVE_PORT, ATA_DRIVE_0_HEAD_0);
    status = io_bus_read_byte(ATA_0_STATUS_PORT);

    if (ata_device_status_valid_p(status)) {
        /* the signature reused cylinder field for drive */
        signature = ata_device_cylinder_read(ATA_0_STATUS_PORT,
            ATA_0_CYL_LOW_PORT, ATA_0_CYL_HIGH_PORT);
        ata_device_info_type_set(dev_info, signature);
    }
}

void
ata_device_detect(void)
{
    s_ata_device_info_t *dev_info;

    dev_info = ata_device_info();

    ata_device_type_detect(dev_info);

    ata_device_info_print(dev_info);
}

