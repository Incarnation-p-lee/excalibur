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
ata_device_type_detect_i(s_ata_dev_info_t *dev_info)
{
    uint16 type, port;
    uint8 val, status;
    uint16 status_port, cy_low_port, cy_high_port;

    kassert(ata_device_info_legal_p(dev_info));

    port = ata_device_info_control_port(dev_info);
    ata_device_software_reset(port); /* reset ata bus */

    port = ata_device_info_drive_port(dev_info);
    val = ata_device_info_drive_id(dev_info); /* active one drive in bus */
    ata_device_drive_set(port, val);

    port = ata_device_info_status_port(dev_info);
    status = io_bus_read_byte(port);

    if (ata_device_status_valid_p(status)) {
        status_port = ata_device_info_status_port(dev_info);
        cy_low_port = ata_device_info_cylinder_low_port(dev_info);
        cy_high_port = ata_device_info_cylinder_high_port(dev_info);

        /* the signature reused cylinder field for drive */
        type = ata_device_cylinder_read(status_port, cy_low_port, cy_high_port);
        ata_device_info_type_set(dev_info, type);
    }
}

static inline void
ata_device_type_detect(void)
{
    uint32 i;
    uint32 limit;
    s_ata_dev_info_t *dev_info;

    i = 0;
    limit = ata_device_info_limit();

    while (i < limit) {
        dev_info = ata_device_info(i);
        ata_device_type_detect_i(dev_info);

        i++;
    }
}

void
ata_device_detect(void)
{
    ata_device_type_detect();
    ata_device_info_print();
}

// static inline void
// ata_device_sector_read_i(s_disk_buf_t *disk_buf, uint32 device_id, uint32 cylinder,
//     uint32 header, uint32 sector)
// {
//     kassert(disk_buffer_legal_p(disk_buf));
//     kassert(device_id < ATA_DEVICE_LIMIT);
//     kassert(cylinder < ATA_CYLINDER_MAX);
//     kassert(header < ATA_HEADER_MAX);
//     kassert(sector < ATA_TRACK_SECTOR_MAX);
// }

// void
// ata_device_sector_read(s_disk_buf_t *disk_buf, uint32 device_id, uint32 cylinder,
//     uint32 header, uint32 sector)
// {
//     if (disk_buffer_illegal_p(disk_buf)) {
//         return;
//     } else if (device_id >= ATA_DEVICE_LIMIT) {
//         return;
//     } else if (cylinder >= ATA_CYLINDER_MAX) {
//         return;
//     } else if (header >= ATA_HEADER_MAX) {
//         return;
//     } else if (sector >= ATA_TRACK_SECTOR_MAX) {
//         return;
//     } else {
//         ata_device_sector_read_i(disk_buf, cylinder, header, sector);
//     }
// }

