static inline void
ata_device_info_type_print(uint32 type)
{
    switch (type) {
        case ATA_DEV_PATAPI:
            printf_vga("PATAPI");
            break;
        case ATA_DEV_SATAPI:
            printf_vga("SATAPI");
            break;
        case ATA_DEV_PATA:
            printf_vga("PATA");
            break;
        case ATA_DEV_SATA:
            printf_vga("SATA");
            break;
        default:
            kassert_not_reached("Unknown ATA device type.\n");
            break;
    }
}

static inline void
ata_device_info_print(void)
{
    uint32 i;
    uint32 limit;
    s_ata_dev_info_t *dev_info;

    i = 0;
    limit = ata_device_info_limit();

    while (i < limit) {
        dev_info = ata_device_info(i);

        if (ata_device_info_type(dev_info) != ATA_DEV_UNKNOWN) {
            printf_vga_tk("Detected ATA device %d: ", i);
            ata_device_info_type_print(ata_device_info_type(dev_info));
            printf_vga(".");
            printf_vga(" c %d, h %d, s/t %d, s byte %d",
                ata_device_info_cylinder_count(dev_info),
                ata_device_info_head_count(dev_info),
                ata_device_info_track_sector(dev_info),
                ata_device_info_sector_bytes(dev_info));
            printf_vga(".\n");
        }

        i++;
    }
}

