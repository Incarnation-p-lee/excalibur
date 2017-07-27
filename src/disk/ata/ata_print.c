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
ata_device_info_print(s_ata_device_info_t *dev_info)
{
    kassert(dev_info);

    if (dev_info->type != ATA_DEV_UNKNOWN) {
        printf_vga_tk("Detected ATA device:");
        ata_device_info_type_print(ata_device_info_type(dev_info));
        printf_vga(".\n");
    }
}


