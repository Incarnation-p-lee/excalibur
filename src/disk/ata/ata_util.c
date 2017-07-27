static inline void
ata_device_info_type_set(s_ata_device_info_t *dev_info, uint32 type)
{
    kassert(dev_info);

    dev_info->type = type;
}

