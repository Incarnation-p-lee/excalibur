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
ata_device_info_type_detect(s_ata_dev_info_t *dev_info)
{
    uint16 type;
    uint16 status_port, cy_low_port, cy_high_port;

    kassert(ata_device_info_legal_p(dev_info));

    status_port = ata_device_info_status_port(dev_info);
    kassert(ata_device_status_available_p(io_bus_byte_read(status_port)));

    cy_low_port = ata_device_info_cylinder_low_port(dev_info);
    cy_high_port = ata_device_info_cylinder_high_port(dev_info);

    ata_device_loop_util_available(status_port);

    /* the signature reused cylinder field for drive */
    type = io_bus_byte_read(cy_low_port) | io_bus_byte_read(cy_high_port) << 8;
    ata_device_info_type_set(dev_info, type);
}

static inline void
ata_device_info_mbr_detect(s_ata_dev_info_t *dev_info)
{
    s_disk_buf_t *disk_buf;
    s_disk_pt_table_t *pt_table;

    kassert(ata_device_info_legal_p(dev_info));

    pt_table = ata_device_info_pt_table(dev_info);
    disk_buf = disk_buffer_create(ata_device_info_sector_bytes(dev_info));

    ata_device_sector_lba_read_i(disk_buf, dev_info, 0);
    disk_buffer_copy(pt_table, disk_buf, DISK_PT_OFFSET, DISK_PT_TABLE_BYTES);

    disk_buffer_destroy(&disk_buf);
}

static inline void
ata_device_info_drive_detect(s_ata_dev_info_t *dev_info)
{
    uint8 status;

    kassert(ata_device_info_legal_p(dev_info));

    ata_device_software_reset(ata_device_info_control_port(dev_info));

    status = ata_device_drive_identify(dev_info);

    if (status == ATA_ID_NO_DRIVE) {
        return;
    } else {
        ata_device_info_type_detect(dev_info);
        ata_device_info_mbr_detect(dev_info);
    }
}

static inline void
ata_device_info_detect(void)
{
    uint32 i;
    uint32 limit;
    s_ata_dev_info_t *dev_info;

    i = 0;
    limit = ata_device_info_limit();

    while (i < limit) {
        dev_info = ata_device_info(i);
        ata_device_info_drive_detect(dev_info);
        ata_device_info_drive_print(dev_info, i);

        i++;
    }

}

static inline void
ata_device_loop_util_data_ready(uint16 status_port)
{
    uint8 status;

    status = io_bus_byte_read(status_port); /* waiting util data is ready */

    while (ata_device_status_unreadable_p(status)) {
        status = io_bus_byte_read(status_port);
    }
}

static inline void
ata_device_loop_util_available(uint16 status_port)
{
    uint8 status;

    status = io_bus_byte_read(status_port); /* waiting util data is ready */

    while (ata_device_status_unavailable_p(status)) {
        status = io_bus_byte_read(status_port);
    }
}

static inline uint32
ata_device_sector_chs_read_i(s_disk_buf_t *disk_buf, s_ata_dev_info_t *dev_info,
    uint16 cylinder, uint8 head, uint8 sector)
{
    uint16 port;
    uint8 config;
    uint32 sector_size;
    uint8 cyl_low, cyl_high;

    kassert(disk_buffer_legal_p(disk_buf));
    kassert(ata_device_info_legal_p(dev_info));
    kassert(head < ATA_HEADER_MAX);
    kassert(sector < ATA_TRACK_SECTOR_MAX);

    sector_size = ata_device_info_sector_bytes(dev_info);
    kassert(sector_size <= disk_buffer_size(disk_buf));

    /* set head, CHS mode */
    config = ATA_CHS_MODE;
    config |= head | ata_device_info_drive_id(dev_info);
    io_bus_byte_write(ata_device_info_control_port(dev_info), config);
    ata_device_disable_drive_irq(ata_device_info_control_port(dev_info));

    /* set count and number (actually sector wanted) to read */
    io_bus_byte_write(ata_device_info_sector_count_port(dev_info), 1);
    io_bus_byte_write(ata_device_info_sector_nmbr_port(dev_info), sector);

    /* set low and high of cylinder */
    cyl_low = ATA_CYL_LOW(cylinder);
    cyl_high = ATA_CYL_HIGH(cylinder);
    io_bus_byte_write(ata_device_info_cylinder_low_port(dev_info), cyl_low);
    io_bus_byte_write(ata_device_info_cylinder_high_port(dev_info), cyl_high);

    /* set read command */
    io_bus_byte_write(ata_device_info_cmd_port(dev_info), ATA_CMD_READ_RETRY);
    ata_device_loop_util_data_ready(ata_device_info_cmd_port(dev_info));

    port = ata_device_info_data_port(dev_info);
    io_bus_read(port, disk_buffer_array(disk_buf), sector_size);
    disk_buffer_index_set(disk_buf, sector_size);

    return sector_size;
}

static inline uint32
ata_device_sector_lba_read_i(s_disk_buf_t *disk_buf, s_ata_dev_info_t *dev_info,
    uint32 a)
{
    uint16 port;
    uint8 config;
    uint32 sector_size;

    kassert(disk_buffer_legal_p(disk_buf));
    kassert(ata_device_info_legal_p(dev_info));

    sector_size = ata_device_info_sector_bytes(dev_info);
    kassert(sector_size <= disk_buffer_size(disk_buf));

    /* set the ata drive with LBA mode */
    config = ATA_LBA_MODE;
    config |= ATA_LBA_HEAD(a) | ata_device_info_drive_id(dev_info);
    io_bus_byte_write(ata_device_info_control_port(dev_info), config);
    ata_device_disable_drive_irq(ata_device_info_control_port(dev_info));

    /* set count of sector to read */
    io_bus_byte_write(ata_device_info_sector_count_port(dev_info), 1);

    /* set lba low, mid and high */
    io_bus_byte_write(ata_device_info_lba_low_port(dev_info), ATA_LBA_LOW(a));
    io_bus_byte_write(ata_device_info_lba_mid_port(dev_info), ATA_LBA_MID(a));
    io_bus_byte_write(ata_device_info_lba_high_port(dev_info), ATA_LBA_HIGH(a));

    /* set read command */
    io_bus_byte_write(ata_device_info_cmd_port(dev_info), ATA_CMD_READ_RETRY);
    ata_device_loop_util_data_ready(ata_device_info_cmd_port(dev_info));

    port = ata_device_info_data_port(dev_info);
    io_bus_read(port, disk_buffer_array(disk_buf), sector_size);
    disk_buffer_index_set(disk_buf, sector_size);

    return sector_size;
}

uint32
ata_device_sector_lba_read(s_disk_buf_t *disk_buf, uint32 device_id, uint32 lba)
{
    s_ata_dev_info_t *dev_info;

    if (disk_buffer_illegal_p(disk_buf)) {
        return SIZE_INVALID;
    } else if (device_id >= ATA_DEVICE_LIMIT) {
        return SIZE_INVALID;
    } else {
        dev_info = ata_device_info(device_id);
        return ata_device_sector_lba_read_i(disk_buf, dev_info, lba);
    }
}

uint32
ata_device_sector_chs_read(s_disk_buf_t *disk_buf, uint32 device_id,
    uint16 c, uint8 h, uint8 s)
{
    s_ata_dev_info_t *dev_info;

    if (disk_buffer_illegal_p(disk_buf)) {
        return SIZE_INVALID;
    } else if (device_id >= ATA_DEVICE_LIMIT) {
        return SIZE_INVALID;
    } else if (h >= ATA_HEADER_MAX) {
        return SIZE_INVALID;
    } else if (s >= ATA_TRACK_SECTOR_MAX) {
        return SIZE_INVALID;
    } else {
        dev_info = ata_device_info(device_id);
        return ata_device_sector_chs_read_i(disk_buf, dev_info, c, h, s);
    }
}

void
ata_device_initialize(void)
{
    ata_device_info_detect();
}

