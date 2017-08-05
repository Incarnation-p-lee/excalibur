static inline void
ata_device_software_reset(uint16 port)
{
    io_bus_byte_write(port, ATA_DEV_CR_SRST);
    io_bus_byte_write(port, ATA_DEV_CR_NULL);
}

static inline void
ata_device_disable_drive_irq(uint16 port)
{
    io_bus_byte_write(port, ATA_DEV_CR_NIEN);
}

static inline void
ata_device_drive_set(uint16 port, uint8 val)
{
    io_bus_byte_write(port, val);
}

static inline uint16
ata_device_cylinder_read(uint16 status_port, uint16 low_port, uint16 high_port)
{
    uint8 status;
    uint16 cylinder;
    uint8 cylinder_low;
    uint8 cylinder_high;

    status = io_bus_byte_read(status_port);

    while (ata_device_status_unavailable_p(status)) {
        status = io_bus_byte_read(status_port);
    }

    cylinder_low = io_bus_byte_read(low_port);
    cylinder_high = io_bus_byte_read(high_port);
    cylinder = (cylinder_high << 8) | cylinder_low;

    return cylinder;
}

static inline void
ata_device_drive_info_indentify(s_ata_dev_info_t *dev)
{
    uint16 val;
    uint16 port;
    uint16 identify_buf[ATA_ID_SIZE];

    kassert(ata_device_info_legal_p(dev));
    kassert(ata_device_status_device_ready_p(ata_device_info_status_port(dev)));

    port = ata_device_info_data_port(dev);
    io_bus_read(port, identify_buf, sizeof(identify_buf));

    val = identify_buf[ATA_ID_CYL_CNT_IDX];
    ata_device_info_cylinder_count_set(dev, val);

    val = identify_buf[ATA_ID_HEAD_CNT_IDX];
    ata_device_info_head_count_set(dev, val);

    val = identify_buf[ATA_ID_ST_BYTE_IDX];
    ata_device_info_sector_bytes_set(dev, val);

    val = identify_buf[ATA_ID_TK_ST_IDX];
    ata_device_info_track_sector_set(dev, val);
}

static inline uint16
ata_device_drive_identify(s_ata_dev_info_t *dev_info)
{
    uint8 config, status;

    kassert(ata_device_info_legal_p(dev_info));

    /* active one drive in bus */
    config = ata_device_info_drive_id(dev_info) | ATA_LBA_MODE;
    ata_device_drive_set(ata_device_info_drive_port(dev_info), config);

    /* disable drive irq */
    ata_device_disable_drive_irq(ata_device_info_control_port(dev_info));

    io_bus_byte_write(ata_device_info_sector_count_port(dev_info), 0);
    io_bus_byte_write(ata_device_info_lba_low_port(dev_info), 0);
    io_bus_byte_write(ata_device_info_lba_mid_port(dev_info), 0);
    io_bus_byte_write(ata_device_info_lba_high_port(dev_info), 0);

    io_bus_byte_write(ata_device_info_cmd_port(dev_info), ATA_CMD_IDENTIFY);

    status = io_bus_byte_read(ata_device_info_status_port(dev_info));

    if (status != 0) { /* drive existed */
        ata_device_loop_util_data_ready(ata_device_info_status_port(dev_info));
        ata_device_drive_info_indentify(dev_info);
    }

    return status;
}

static inline void
ata_device_type_detect_i(s_ata_dev_info_t *dev_info)
{
    uint16 type;
    uint8 status;
    uint16 status_port, cy_low_port, cy_high_port;

    kassert(ata_device_info_legal_p(dev_info));

    ata_device_software_reset(ata_device_info_control_port(dev_info));

    status = ata_device_drive_identify(dev_info);

    if (status != ATA_ID_NO_DRIVE) {
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

static inline void
ata_device_loop_util_data_ready(uint16 status_port)
{
    uint8 status;

    status = io_bus_byte_read(status_port); /* waiting util data is ready */

    while (!ata_device_status_readable_p(status)) {
        status = io_bus_byte_read(status_port);
    }
}

static inline uint32
ata_device_sector_read_i(s_disk_buf_t *disk_buf, uint32 device_id, uint32 a)
{
    uint16 port;
    uint8 config;
    uint16 sector_size;
    s_ata_dev_info_t *dev_info;

    kassert(disk_buffer_legal_p(disk_buf));
    kassert(device_id < ATA_DEVICE_LIMIT);

    /* set the ata drive with LBA mode */
    dev_info = ata_device_info(device_id);
    config = ATA_LBA_MODE;
    config = config | ATA_LBA_HEAD(a) | ata_device_info_drive_id(dev_info);
    io_bus_byte_write(ata_device_info_control_port(dev_info), config);

    /* set number of sector to read */
    io_bus_byte_write(ata_device_info_sector_count_port(dev_info), 1);

    /* set lba low, mid and high */
    io_bus_byte_write(ata_device_info_lba_low_port(dev_info), ATA_LBA_LOW(a));
    io_bus_byte_write(ata_device_info_lba_mid_port(dev_info), ATA_LBA_MID(a));
    io_bus_byte_write(ata_device_info_lba_high_port(dev_info), ATA_LBA_HIGH(a));

    /* set read command */
    io_bus_byte_write(ata_device_info_cmd_port(dev_info), ATA_CMD_READ_RETRY);
    ata_device_loop_util_data_ready(ata_device_info_cmd_port(dev_info));

    sector_size = ata_device_info_sector_bytes(dev_info);
    kassert(sector_size <= disk_buffer_size(disk_buf));

    port = ata_device_info_data_port(dev_info);
    io_bus_read(port, disk_buffer_obtain(disk_buf), sector_size);
    disk_buffer_index_set(disk_buf, sector_size);

    return sector_size;
}

uint32
ata_device_sector_read(s_disk_buf_t *disk_buf, uint32 device_id, uint32 lba)
{
    if (disk_buffer_illegal_p(disk_buf)) {
        return SIZE_INVALID;
    } else if (device_id >= ATA_DEVICE_LIMIT) {
        return SIZE_INVALID;
    } else {
        return ata_device_sector_read_i(disk_buf, device_id, lba);
    }
}

void
ata_device_detect(void)
{
    ata_device_type_detect();
    ata_device_info_print();
}

