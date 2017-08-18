static inline bool
fs_ext2_descriptor_legal_ip(s_ext2_dspr_t *ext2_dspr)
{
    if (ext2_dspr == NULL) {
        return false;
    } else if (ext2_dspr->disk_pt == NULL) {
        return false;
    } else if (ext2_dspr->bg_info_array == NULL) {
        return false;
    } else if (ext2_dspr->bg_info_size == 0) {
        return false;
    } else {
        return true;
    }
}

static inline bool
fs_ext2_descriptor_illegal_ip(s_ext2_dspr_t *ext2_dspr)
{
    return !fs_ext2_descriptor_legal_ip(ext2_dspr);
}

bool
fs_ext2_descriptor_legal_p(s_ext2_dspr_t *ext2_dspr)
{
    return fs_ext2_descriptor_legal_ip(ext2_dspr);
}

bool
fs_ext2_descriptor_illegal_p(s_ext2_dspr_t *ext2_dspr)
{
    return !fs_ext2_descriptor_legal_ip(ext2_dspr);
}

static inline e_disk_id_t
fs_ext2_descriptor_device_id_i(s_ext2_dspr_t *ext2_dspr)
{
    assert(fs_ext2_descriptor_legal_ip(ext2_dspr));

    return ext2_dspr->device_id;
}

static inline void
fs_ext2_descriptor_device_id_set_i(s_ext2_dspr_t *ext2_dspr, e_disk_id_t device_id)
{
    assert(fs_ext2_descriptor_legal_ip(ext2_dspr));

    ext2_dspr->device_id = device_id;
}

e_disk_id_t
fs_ext2_descriptor_device_id(s_ext2_dspr_t *ext2_dspr)
{
    if (fs_ext2_descriptor_illegal_ip(ext2_dspr)) {
        return;
    } else {
        return fs_ext2_descriptor_device_id_i(ext2_dspr);
    }
}

void
fs_ext2_descriptor_device_id_set(s_ext2_dspr_t *ext2_dspr, e_disk_id_t device_id)
{
    if (fs_ext2_descriptor_illegal_ip(ext2_dspr)) {
        return;
    } else {
        fs_ext2_descriptor_device_id_set_i(ext2_dspr, device_id);
    }
}

static inline s_disk_pt_t *
fs_ext2_descriptor_disk_pt_i(s_ext2_dspr_t *ext2_dspr)
{
    assert(fs_ext2_descriptor_legal_ip(ext2_dspr));

    return ext2_dspr->disk_pt;
}

static inline void
fs_ext2_descriptor_disk_pt_set_i(s_ext2_dspr_t *ext2_dspr, s_disk_pt_t *disk_pt)
{
    assert(fs_ext2_descriptor_legal_ip(ext2_dspr));

    ext2_dspr->disk_pt = disk_pt;
}

s_disk_pt_t *
fs_ext2_descriptor_disk_pt(s_ext2_dspr_t *ext2_dspr)
{
    if (fs_ext2_descriptor_illegal_ip(ext2_dspr)) {
        return;
    } else {
        return fs_ext2_descriptor_disk_pt_i(ext2_dspr);
    }
}

void
fs_ext2_descriptor_disk_pt_set(s_ext2_dspr_t *ext2_dspr, s_disk_pt_t *disk_pt)
{
    if (fs_ext2_descriptor_illegal_ip(ext2_dspr)) {
        return;
    } else {
        fs_ext2_descriptor_disk_pt_set_i(ext2_dspr, disk_pt);
    }
}

static inline s_ext2_bg_info_t *
fs_ext2_descriptor_bg_info_array_i(s_ext2_dspr_t *ext2_dspr)
{
    assert(fs_ext2_descriptor_legal_ip(ext2_dspr));

    return ext2_dspr->bg_info_array;
}

static inline void
fs_ext2_descriptor_bg_info_array_set_i(s_ext2_dspr_t *ext2_dspr,
    s_ext2_bg_info_t *bg_info_array)
{
    assert(fs_ext2_descriptor_legal_ip(ext2_dspr));

    ext2_dspr->bg_info_array = bg_info_array;
}

s_ext2_bg_info_t *
fs_ext2_descriptor_bg_info_array(s_ext2_dspr_t *ext2_dspr)
{
    if (fs_ext2_descriptor_illegal_ip(ext2_dspr)) {
        return;
    } else {
        return fs_ext2_descriptor_bg_info_array_i(ext2_dspr);
    }
}

void
fs_ext2_descriptor_bg_info_array_set(s_ext2_dspr_t *ext2_dspr,
    s_ext2_bg_info_t *bg_info_array)
{
    if (fs_ext2_descriptor_illegal_ip(ext2_dspr)) {
        return;
    } else {
        fs_ext2_descriptor_bg_info_array_set_i(ext2_dspr, bg_info_array);
    }
}

static inline uint32
fs_ext2_descriptor_bg_info_size_i(s_ext2_dspr_t *ext2_dspr)
{
    assert(fs_ext2_descriptor_legal_ip(ext2_dspr));

    return ext2_dspr->bg_info_size;
}

static inline void
fs_ext2_descriptor_bg_info_size_set_i(s_ext2_dspr_t *ext2_dspr, uint32 size)
{
    assert(fs_ext2_descriptor_legal_ip(ext2_dspr));

    ext2_dspr->bg_info_size = size;
}

uint32
fs_ext2_descriptor_bg_info_size(s_ext2_dspr_t *ext2_dspr)
{
    if (fs_ext2_descriptor_illegal_ip(ext2_dspr)) {
        return;
    } else {
        return fs_ext2_descriptor_bg_info_size_i(ext2_dspr);
    }
}

void
fs_ext2_descriptor_bg_info_size_set(s_ext2_dspr_t *ext2_dspr, uint32 size)
{
    if (fs_ext2_descriptor_illegal_ip(ext2_dspr)) {
        return;
    } else {
        fs_ext2_descriptor_bg_info_size_set_i(ext2_dspr, size);
    }
}

static inline s_ext2_dspr_table_t *
fs_ext2_descriptor_table_obtain(void)
{
    return &ext2_dspr_table;
}

static inline bool
fs_ext2_descriptor_table_legal_ip(s_ext2_dspr_table_t *ext2_dspr_table)
{
    if (ext2_dspr_table == NULL) {
        return false;
    } else if (ext2_dspr_table->index > ext2_dspr_table->size) {
        return false;
    } else if (ext2_dspr_table->size == 0) {
        return false;
    } else if (ext2_dspr_table->dspr_array == NULL) {
        return false;
    } else {
        return true;
    }
}

static inline bool
fs_ext2_descriptor_table_illegal_ip(s_ext2_dspr_table_t *ext2_dspr_table)
{
    return !fs_ext2_descriptor_table_legal_ip(ext2_dspr_table);
}

bool
fs_ext2_descriptor_table_legal_p(s_ext2_dspr_table_t *ext2_dspr_table)
{
    return fs_ext2_descriptor_table_legal_ip(ext2_dspr_table);
}

bool
fs_ext2_descriptor_table_illegal_p(s_ext2_dspr_table_t *ext2_dspr_table)
{
    return !fs_ext2_descriptor_table_legal_ip(ext2_dspr_table);
}

static inline uint32
fs_ext2_descriptor_table_index_i(s_ext2_dspr_table_t *ext2_dspr_table)
{
    assert(fs_ext2_descriptor_table_legal_ip(ext2_dspr_table));

    return ext2_dspr_table->index;
}

static inline void
fs_ext2_descriptor_table_index_set_i(s_ext2_dspr_table_t *ext2_dspr_table,
    uint32 index)
{
    assert(fs_ext2_descriptor_table_legal_ip(ext2_dspr_table));

    ext2_dspr_table->index = index;
}

uint32
fs_ext2_descriptor_table_index(s_ext2_dspr_table_t *ext2_dspr_table)
{
    if (fs_ext2_descriptor_table_illegal_ip(ext2_dspr_table)) {
        return;
    } else {
        return fs_ext2_descriptor_table_index_i(ext2_dspr_table);
    }
}

void
fs_ext2_descriptor_table_index_set(s_ext2_dspr_table_t *ext2_dspr_table,
    uint32 index)
{
    if (fs_ext2_descriptor_table_illegal_ip(ext2_dspr_table)) {
        return;
    } else {
        fs_ext2_descriptor_table_index_set_i(ext2_dspr_table, index);
    }
}

static inline uint32
fs_ext2_descriptor_table_size_i(s_ext2_dspr_table_t *ext2_dspr_table)
{
    assert(fs_ext2_descriptor_table_legal_ip(ext2_dspr_table));

    return ext2_dspr_table->size;
}

static inline void
fs_ext2_descriptor_table_size_set_i(s_ext2_dspr_table_t *ext2_dspr_table,
    uint32 size)
{
    assert(fs_ext2_descriptor_table_legal_ip(ext2_dspr_table));

    ext2_dspr_table->size = size;
}

uint32
fs_ext2_descriptor_table_size(s_ext2_dspr_table_t *ext2_dspr_table)
{
    if (fs_ext2_descriptor_table_illegal_ip(ext2_dspr_table)) {
        return;
    } else {
        return fs_ext2_descriptor_table_size_i(ext2_dspr_table);
    }
}

void
fs_ext2_descriptor_table_size_set(s_ext2_dspr_table_t *ext2_dspr_table,
    uint32 size)
{
    if (fs_ext2_descriptor_table_illegal_ip(ext2_dspr_table)) {
        return;
    } else {
        fs_ext2_descriptor_table_size_set_i(ext2_dspr_table, size);
    }
}

static inline s_ext2_dspr_t *
fs_ext2_descriptor_table_dspr_array_i(s_ext2_dspr_table_t *ext2_dspr_table)
{
    assert(fs_ext2_descriptor_table_legal_ip(ext2_dspr_table));

    return ext2_dspr_table->dspr_array;
}

static inline void
fs_ext2_descriptor_table_dspr_array_set_i(s_ext2_dspr_table_t *ext2_dspr_table,
    s_ext2_dspr_t *dspr_array)
{
    assert(fs_ext2_descriptor_table_legal_ip(ext2_dspr_table));

    ext2_dspr_table->dspr_array = dspr_array;
}

s_ext2_dspr_t *
fs_ext2_descriptor_table_dspr_array(s_ext2_dspr_table_t *ext2_dspr_table)
{
    if (fs_ext2_descriptor_table_illegal_ip(ext2_dspr_table)) {
        return;
    } else {
        return fs_ext2_descriptor_table_dspr_array_i(ext2_dspr_table);
    }
}

void
fs_ext2_descriptor_table_dspr_array_set(s_ext2_dspr_table_t *ext2_dspr_table,
    s_ext2_dspr_t *dspr_array)
{
    if (fs_ext2_descriptor_table_illegal_ip(ext2_dspr_table)) {
        return;
    } else {
        fs_ext2_descriptor_table_dspr_array_set_i(ext2_dspr_table, dspr_array);
    }
}

static inline bool
fs_ext2_descriptor_table_full_p(s_ext2_dspr_table_t *ext2_dspr_table)
{
    uint32 size;
    uint32 index;

    kassert(fs_ext2_descriptor_table_legal_ip(ext2_dspr_table));

    size = fs_ext2_descriptor_table_size_i(ext2_dspr_table);
    index = fs_ext2_descriptor_table_index_i(ext2_dspr_table);

    if (size == index) {
        return true;
    } else {
        return false;
    }
}

