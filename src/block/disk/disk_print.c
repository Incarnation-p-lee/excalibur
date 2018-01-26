static inline void
disk_partition_table_entry_print(s_disk_pt_t *disk_pt, uint32 i)
{
    kassert(i < DISK_PT_TABLE_SIZE);
    kassert(disk_partition_legal_ip(disk_pt));

    printf_vga_tk(
        "Partition %d boot %d, related sector %d, sector count %d\n",
        i,
        disk_partition_bootable_ip(disk_pt),
        disk_partition_sector_offset_i(disk_pt),
        disk_partition_sector_count_i(disk_pt)
    );
}

static inline void
disk_partition_table_print_i(s_disk_pt_table_t *pt_table)
{
    uint32 i, limit;
    s_disk_pt_t *disk_pt;

    kassert(disk_partition_table_legal_ip(pt_table));

    i = 0;
    limit = DISK_PT_TABLE_SIZE;

    while (i < limit) {
        disk_pt = disk_partition_table_entry_i(pt_table, i);

        if (disk_partition_used_p(disk_pt)) {
            disk_partition_table_entry_print(disk_pt, i);
        }

        i++;
    }
}

void
disk_partition_table_print(s_disk_pt_table_t *pt_table)
{
    if (disk_partition_table_illegal_ip(pt_table)) {
        return;
    } else {
        disk_partition_table_print_i(pt_table);
    }
}

