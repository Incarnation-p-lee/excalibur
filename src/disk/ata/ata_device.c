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
ata_device_type_detect(void)
{
    uint8 status;
    uint16 signature;

    ata_device_software_reset(ATA_0_DEV_CR_PORT);
    ata_device_drive_set(ATA_0_DRIVE_PORT, ATA_DRIVE_0_HEAD_0);
    status = io_bus_read_byte(ATA_0_STATUS_PORT);

    if (ata_device_status_valid_p(status)) {
        /* the signature reused cylinder field for drive */
        signature = ata_device_cylinder_read(ATA_0_STATUS_PORT,
            ATA_0_CYL_LOW_PORT, ATA_0_CYL_HIGH_PORT);
        ata_device_info_type_set(dev_info, signature);
        ata_device_info_port_set(dev_info, ATA_0_DEVICE_MASTER);
    }
}

void
ata_device_detect(void)
{
    ata_device_type_detect();
    ata_device_info_print();
}

static inline void
ata_device_sector_read_i(s_disk_buf_t *disk_buf, uint32 device_id, uint32 cylinder,
    uint32 header, uint32 sector)
{
    s_ata_device_info_t *dev_info;

    kassert(disk_buffer_legal_p(disk_buf));
    kassert(device_id < ATA_DEVICE_LIMIT);
    kassert(cylinder < ATA_CYLINDER_MAX);
    kassert(header < ATA_HEADER_MAX);
    kassert(sector < ATA_TRACK_SECTOR_MAX);
}

void
ata_device_sector_read(s_disk_buf_t *disk_buf, uint32 device_id, uint32 cylinder,
    uint32 header, uint32 sector)
{
    if (disk_buffer_illegal_p(disk_buf)) {
        return;
    } else if (device_id >= ATA_DEVICE_LIMIT) {
        return;
    } else if (cylinder >= ATA_CYLINDER_MAX) {
        return;
    } else if (header >= ATA_HEADER_MAX) {
        return;
    } else if (sector >= ATA_TRACK_SECTOR_MAX) {
        return;
    } else {
        ata_device_sector_read_i(disk_buf, cylinder, header, sector);
    }
}

