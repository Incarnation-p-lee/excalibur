static inline bool
disk_partition_legal_ip(s_disk_pt_t *disk_pt)
{
    if (disk_pt == NULL) {
        return false;
    } else if (disk_pt->head_start > disk_pt->head_end) {
        return false;
    } else if (disk_pt->cylinder_start > disk_pt->cylinder_end) {
        return false;
    } else if (disk_pt->sector_count == 0) {
        return false;
    } else {
        return true;
    }
}

static inline bool
disk_partition_illegal_ip(s_disk_pt_t *disk_pt)
{
    return !disk_partition_legal_ip(disk_pt);
}

bool
disk_partition_legal_p(s_disk_pt_t *disk_pt)
{
    return disk_partition_legal_ip(disk_pt);
}

bool
disk_partition_illegal_p(s_disk_pt_t *disk_pt)
{
    return !disk_partition_legal_ip(disk_pt);
}

static inline uint8
disk_partition_boot_i(s_disk_pt_t *disk_pt)
{
    kassert(disk_partition_legal_ip(disk_pt));

    return disk_pt->boot;
}

static inline void
disk_partition_boot_set_i(s_disk_pt_t *disk_pt, uint8 boot)
{
    kassert(disk_partition_legal_ip(disk_pt));

    disk_pt->boot = boot;
}

static inline bool
disk_partition_bootable_ip(s_disk_pt_t *disk_pt)
{
    kassert(disk_partition_legal_ip(disk_pt));

    if (disk_partition_boot_i(disk_pt) == DISK_PT_BOOT_MASK) {
        return true;
    } else {
        return false;
    }
}

bool
disk_partition_bootable_p(s_disk_pt_t *disk_pt)
{
    if (disk_partition_illegal_ip(disk_pt)) {
        return false;
    } else {
        return disk_partition_bootable_ip(disk_pt);
    }
}

static inline uint8
disk_partition_head_start_i(s_disk_pt_t *disk_pt)
{
    kassert(disk_partition_legal_ip(disk_pt));

    return disk_pt->head_start;
}

static inline void
disk_partition_head_start_set_i(s_disk_pt_t *disk_pt, uint8 head_start)
{
    kassert(disk_partition_legal_ip(disk_pt));

    disk_pt->head_start = head_start;
}

uint8
disk_partition_head_start(s_disk_pt_t *disk_pt)
{
    if (disk_partition_illegal_ip(disk_pt)) {
        return SIZE_INVALID;
    } else {
        return disk_partition_head_start_i(disk_pt);
    }
}

void
disk_partition_head_start_set(s_disk_pt_t *disk_pt, uint8 head_start)
{
    if (disk_partition_illegal_ip(disk_pt)) {
        return;
    } else {
        disk_partition_head_start_set_i(disk_pt, head_start);
    }
}

static inline uint16
disk_partition_sector_start_i(s_disk_pt_t *disk_pt)
{
    kassert(disk_partition_legal_ip(disk_pt));

    return disk_pt->sector_start;
}

static inline void
disk_partition_sector_start_set_i(s_disk_pt_t *disk_pt, uint16 sector_start)
{
    kassert(disk_partition_legal_ip(disk_pt));

    disk_pt->sector_start = sector_start;
}

uint16
disk_partition_sector_start(s_disk_pt_t *disk_pt)
{
    if (disk_partition_illegal_ip(disk_pt)) {
        return SIZE_INVALID;
    } else {
        return disk_partition_sector_start_i(disk_pt);
    }
}

void
disk_partition_sector_start_set(s_disk_pt_t *disk_pt, uint16 sector_start)
{
    if (disk_partition_illegal_ip(disk_pt)) {
        return;
    } else {
        disk_partition_sector_start_set_i(disk_pt, sector_start);
    }
}

static inline uint16
disk_partition_cylinder_start_i(s_disk_pt_t *disk_pt)
{
    kassert(disk_partition_legal_ip(disk_pt));

    return disk_pt->cylinder_start;
}

static inline void
disk_partition_cylinder_start_set_i(s_disk_pt_t *disk_pt, uint16 cylinder_start)
{
    kassert(disk_partition_legal_ip(disk_pt));

    disk_pt->cylinder_start = cylinder_start;
}

uint16
disk_partition_cylinder_start(s_disk_pt_t *disk_pt)
{
    if (disk_partition_illegal_ip(disk_pt)) {
        return SIZE_INVALID;
    } else {
        return disk_partition_cylinder_start_i(disk_pt);
    }
}

void
disk_partition_cylinder_start_set(s_disk_pt_t *disk_pt, uint16 cylinder_start)
{
    if (disk_partition_illegal_ip(disk_pt)) {
        return;
    } else {
        disk_partition_cylinder_start_set_i(disk_pt, cylinder_start);
    }
}

static inline uint8
disk_partition_system_id_i(s_disk_pt_t *disk_pt)
{
    kassert(disk_partition_legal_ip(disk_pt));

    return disk_pt->system_id;
}

static inline void
disk_partition_system_id_set_i(s_disk_pt_t *disk_pt, uint8 system_id)
{
    kassert(disk_partition_legal_ip(disk_pt));

    disk_pt->system_id = system_id;
}

uint8
disk_partition_system_id(s_disk_pt_t *disk_pt)
{
    if (disk_partition_illegal_ip(disk_pt)) {
        return SIZE_INVALID;
    } else {
        return disk_partition_system_id_i(disk_pt);
    }
}

void
disk_partition_system_id_set(s_disk_pt_t *disk_pt, uint8 system_id)
{
    if (disk_partition_illegal_ip(disk_pt)) {
        return;
    } else {
        disk_partition_system_id_set_i(disk_pt, system_id);
    }
}

static inline uint8
disk_partition_head_end_i(s_disk_pt_t *disk_pt)
{
    kassert(disk_partition_legal_ip(disk_pt));

    return disk_pt->head_end;
}

static inline void
disk_partition_head_end_set_i(s_disk_pt_t *disk_pt, uint8 head_end)
{
    kassert(disk_partition_legal_ip(disk_pt));

    disk_pt->head_end = head_end;
}

uint8
disk_partition_head_end(s_disk_pt_t *disk_pt)
{
    if (disk_partition_illegal_ip(disk_pt)) {
        return SIZE_INVALID;
    } else {
        return disk_partition_head_end_i(disk_pt);
    }
}

void
disk_partition_head_end_set(s_disk_pt_t *disk_pt, uint8 head_end)
{
    if (disk_partition_illegal_ip(disk_pt)) {
        return;
    } else {
        disk_partition_head_end_set_i(disk_pt, head_end);
    }
}

static inline uint16
disk_partition_sector_end_i(s_disk_pt_t *disk_pt)
{
    kassert(disk_partition_legal_ip(disk_pt));

    return disk_pt->sector_end;
}

static inline void
disk_partition_sector_end_set_i(s_disk_pt_t *disk_pt, uint16 sector_end)
{
    kassert(disk_partition_legal_ip(disk_pt));

    disk_pt->sector_end = sector_end;
}

uint16
disk_partition_sector_end(s_disk_pt_t *disk_pt)
{
    if (disk_partition_illegal_ip(disk_pt)) {
        return SIZE_INVALID;
    } else {
        return disk_partition_sector_end_i(disk_pt);
    }
}

void
disk_partition_sector_end_set(s_disk_pt_t *disk_pt, uint16 sector_end)
{
    if (disk_partition_illegal_ip(disk_pt)) {
        return;
    } else {
        disk_partition_sector_end_set_i(disk_pt, sector_end);
    }
}

static inline uint16
disk_partition_cylinder_end_i(s_disk_pt_t *disk_pt)
{
    kassert(disk_partition_legal_ip(disk_pt));

    return disk_pt->cylinder_end;
}

static inline void
disk_partition_cylinder_end_set_i(s_disk_pt_t *disk_pt, uint16 cylinder_end)
{
    kassert(disk_partition_legal_ip(disk_pt));

    disk_pt->cylinder_end = cylinder_end;
}

uint16
disk_partition_cylinder_end(s_disk_pt_t *disk_pt)
{
    if (disk_partition_illegal_ip(disk_pt)) {
        return SIZE_INVALID;
    } else {
        return disk_partition_cylinder_end_i(disk_pt);
    }
}

void
disk_partition_cylinder_end_set(s_disk_pt_t *disk_pt, uint16 cylinder_end)
{
    if (disk_partition_illegal_ip(disk_pt)) {
        return;
    } else {
        disk_partition_cylinder_end_set_i(disk_pt, cylinder_end);
    }
}

static inline uint32
disk_partition_sector_count_i(s_disk_pt_t *disk_pt)
{
    kassert(disk_partition_legal_ip(disk_pt));

    return disk_pt->sector_count;
}

static inline void
disk_partition_sector_count_set_i(s_disk_pt_t *disk_pt, uint32 sector_count)
{
    kassert(disk_partition_legal_ip(disk_pt));

    disk_pt->sector_count = sector_count;
}

uint32
disk_partition_sector_count(s_disk_pt_t *disk_pt)
{
    if (disk_partition_illegal_ip(disk_pt)) {
        return SIZE_INVALID;
    } else {
        return disk_partition_sector_count_i(disk_pt);
    }
}

void
disk_partition_sector_count_set(s_disk_pt_t *disk_pt, uint32 sector_count)
{
    if (disk_partition_illegal_ip(disk_pt)) {
        return;
    } else {
        disk_partition_sector_count_set_i(disk_pt, sector_count);
    }
}

static inline uint32
disk_partition_sector_offset_i(s_disk_pt_t *disk_pt)
{
    kassert(disk_partition_legal_ip(disk_pt));

    return disk_pt->sector_offset;
}

static inline void
disk_partition_sector_offset_set_i(s_disk_pt_t *disk_pt, uint32 sector_offset)
{
    kassert(disk_partition_legal_ip(disk_pt));

    disk_pt->sector_offset = sector_offset;
}

uint32
disk_partition_sector_offset(s_disk_pt_t *disk_pt)
{
    if (disk_partition_illegal_ip(disk_pt)) {
        return SIZE_INVALID;
    } else {
        return disk_partition_sector_offset_i(disk_pt);
    }
}

void
disk_partition_sector_offset_set(s_disk_pt_t *disk_pt, uint32 sector_offset)
{
    if (disk_partition_illegal_ip(disk_pt)) {
        return;
    } else {
        disk_partition_sector_offset_set_i(disk_pt, sector_offset);
    }
}

static inline bool
disk_partition_table_legal_ip(s_disk_pt_table_t *disk_pt_table)
{
    if (disk_pt_table == NULL) {
        return false;
    } else {
        return true;
    }
}

static inline bool
disk_partition_table_illegal_ip(s_disk_pt_table_t *disk_pt_table)
{
    return !disk_partition_table_legal_ip(disk_pt_table);
}

bool
disk_partition_table_legal_p(s_disk_pt_table_t *disk_pt_table)
{
    return disk_partition_table_legal_ip(disk_pt_table);
}

bool
disk_partition_table_illegal_p(s_disk_pt_table_t *disk_pt_table)
{
    return !disk_partition_table_legal_ip(disk_pt_table);
}

static inline s_disk_pt_t *
disk_partition_table_array_i(s_disk_pt_table_t *disk_pt_table)
{
    kassert(disk_partition_table_legal_ip(disk_pt_table));

    return disk_pt_table->array;
}

s_disk_pt_t *
disk_partition_table_array(s_disk_pt_table_t *disk_pt_table)
{
    if (disk_partition_table_illegal_ip(disk_pt_table)) {
        return PTR_INVALID;
    } else {
        return disk_partition_table_array_i(disk_pt_table);
    }
}

static inline s_disk_pt_t *
disk_partition_table_entry_i(s_disk_pt_table_t *disk_pt_table, uint32 i)
{
    s_disk_pt_t *array;

    kassert(disk_partition_table_legal_ip(disk_pt_table));
    kassert(i < DISK_PT_TABLE_SIZE);

    array = disk_partition_table_array_i(disk_pt_table);

    return &array[i];
}

s_disk_pt_t *
disk_partition_table_entry(s_disk_pt_table_t *disk_pt_table, uint32 i)
{
    if (disk_partition_table_illegal_ip(disk_pt_table)) {
        return PTR_INVALID;
    } else if (i >= DISK_PT_TABLE_SIZE) {
        return PTR_INVALID;
    } else {
        return disk_partition_table_entry_i(disk_pt_table, i);
    }
}

static inline bool
disk_partition_used_ip(s_disk_pt_t *disk_pt)
{
    kassert(disk_partition_legal_ip(disk_pt));

    if (disk_pt->system_id == 0) {
       return false;
    } else {
       return true;
    }
}

static inline bool
disk_partition_unused_ip(s_disk_pt_t *disk_pt)
{
    return !disk_partition_used_ip(disk_pt);
}

bool
disk_partition_used_p(s_disk_pt_t *disk_pt)
{
    if (disk_partition_illegal_ip(disk_pt)) {
        return false;
    } else {
        return disk_partition_used_ip(disk_pt);
    }
}

bool
disk_partition_unused_p(s_disk_pt_t *disk_pt)
{
    if (disk_partition_illegal_ip(disk_pt)) {
        return false;
    } else {
        return disk_partition_unused_ip(disk_pt);
    }
}

static inline uint32
disk_descriptor_limit_i(void)
{
    return ARRAY_CNT_OF(disk_descripotr);
}

uint32
disk_descriptor_limit(void)
{
    return disk_descriptor_limit_i();
}

static inline s_disk_dspt_t *
disk_descriptor_entry(e_disk_id_t device_id)
{
    kassert(device_id < disk_descriptor_limit_i());

    return &disk_descripotr[device_id];
}

static inline bool
disk_descriptor_legal_ip(s_disk_dspt_t *disk_dspt)
{
    if (disk_dspt == NULL) {
        return false;
    } else if (disk_dspt->id >= disk_descriptor_limit_i()) {
        return false;
    } else if (disk_dspt->read == NULL) {
        return false;
    } else if (disk_dspt->mount == NULL) {
        return false;
    } else {
        return true;
    }
}

static inline bool
disk_descriptor_illegal_ip(s_disk_dspt_t *disk_dspt)
{
    return !disk_descriptor_legal_ip(disk_dspt);
}

static inline bool
disk_descriptor_is_active_ip(e_disk_id_t device_id)
{
    s_disk_dspt_t *disk_dspt;

    kassert(device_id < disk_descriptor_limit_i());

    disk_dspt = disk_descriptor_entry(device_id);

    return disk_dspt->is_active;
}

static inline void
disk_descriptor_is_active_set_i(e_disk_id_t device_id, bool is_active)
{
    s_disk_dspt_t *disk_dspt;

    kassert(device_id < disk_descriptor_limit_i());

    disk_dspt = disk_descriptor_entry(device_id);

    disk_dspt->is_active = is_active;
}

bool
disk_descriptor_is_active_p(e_disk_id_t device_id)
{
    if (device_id >= disk_descriptor_limit_i()) {
        return false;
    } else {
        return disk_descriptor_is_active_ip(device_id);
    }
}

void
disk_descriptor_is_active_set(e_disk_id_t device_id, bool is_active)
{
    if (device_id >= disk_descriptor_limit_i()) {
        return;
    } else {
        disk_descriptor_is_active_set_i(device_id, is_active);
    }
}

static inline f_disk_read_t
disk_descriptor_read_i(e_disk_id_t device_id)
{
    s_disk_dspt_t *disk_dspt;

    kassert(device_id < disk_descriptor_limit_i());

    disk_dspt = disk_descriptor_entry(device_id);

    return disk_dspt->read;
}

f_disk_read_t
disk_descriptor_read(e_disk_id_t device_id)
{
    if (device_id >= disk_descriptor_limit_i()) {
        return PTR_INVALID;
    } else {
        return disk_descriptor_read_i(device_id);
    }
}

static inline void
disk_descriptor_sector_bytes_set_i(e_disk_id_t device_id, uint32 sector_bytes)
{
    s_disk_dspt_t *disk_dspt;

    kassert(device_id < disk_descriptor_limit_i());

    disk_dspt = disk_descriptor_entry(device_id);

    disk_dspt->sector_bytes = sector_bytes;
}

void
disk_descriptor_sector_bytes_set(e_disk_id_t device_id, uint32 bytes)
{
    if (device_id >= disk_descriptor_limit_i()) {
        return;
    } else {
        return disk_descriptor_sector_bytes_set_i(device_id, bytes);
    }
}

static inline uint32
disk_descriptor_sector_bytes_i(e_disk_id_t device_id)
{
    s_disk_dspt_t *disk_dspt;

    kassert(device_id < disk_descriptor_limit_i());

    disk_dspt = disk_descriptor_entry(device_id);

    return disk_dspt->sector_bytes;
}

uint32
disk_descriptor_sector_bytes(e_disk_id_t device_id)
{
    if (device_id >= disk_descriptor_limit_i()) {
        return SIZE_INVALID;
    } else {
        return disk_descriptor_sector_bytes_i(device_id);
    }
}

static inline s_disk_pt_table_t *
disk_descriptor_pt_table_i(e_disk_id_t device_id)
{
    s_disk_dspt_t *disk_dspt;

    kassert(device_id < disk_descriptor_limit_i());

    disk_dspt = disk_descriptor_entry(device_id);

    return &disk_dspt->pt_table;
}

s_disk_pt_table_t *
disk_descriptor_pt_table(e_disk_id_t device_id)
{
    if (device_id >= disk_descriptor_limit_i()) {
        return PTR_INVALID;
    } else {
        return disk_descriptor_pt_table_i(device_id);
    }
}

