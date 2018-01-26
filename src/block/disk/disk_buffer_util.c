static inline bool
disk_buffer_legal_ip(s_disk_buf_t *disk_buffer)
{
    if (disk_buffer == NULL) {
        return false;
    } else if (disk_buffer->array == NULL) {
        return false;
    } else if (disk_buffer->index > disk_buffer->size) {
        return false;
    } else if (disk_buffer->size == 0) {
        return false;
    } else {
        return true;
    }
}

static inline bool
disk_buffer_illegal_ip(s_disk_buf_t *disk_buffer)
{
    return !disk_buffer_legal_ip(disk_buffer);
}

bool
disk_buffer_legal_p(s_disk_buf_t *disk_buffer)
{
    return disk_buffer_legal_ip(disk_buffer);
}

bool
disk_buffer_illegal_p(s_disk_buf_t *disk_buffer)
{
    return !disk_buffer_legal_ip(disk_buffer);
}

static inline uint8 *
disk_buffer_array_i(s_disk_buf_t *disk_buffer)
{
    kassert(disk_buffer_legal_ip(disk_buffer));

    return disk_buffer->array;
}

static inline void
disk_buffer_array_set_i(s_disk_buf_t *disk_buffer, uint8 *array)
{
    kassert(disk_buffer_legal_ip(disk_buffer));

    disk_buffer->array = array;
}

uint8 *
disk_buffer_array(s_disk_buf_t *disk_buffer)
{
    if (disk_buffer_illegal_ip(disk_buffer)) {
        return PTR_INVALID;
    } else {
        return disk_buffer_array_i(disk_buffer);
    }
}

void
disk_buffer_array_set(s_disk_buf_t *disk_buffer, uint8 *array)
{
    if (disk_buffer_illegal_ip(disk_buffer)) {
        return;
    } else {
        disk_buffer_array_set_i(disk_buffer, array);
    }
}

static inline uint32
disk_buffer_index_i(s_disk_buf_t *disk_buffer)
{
    kassert(disk_buffer_legal_ip(disk_buffer));

    return disk_buffer->index;
}

static inline void
disk_buffer_index_set_i(s_disk_buf_t *disk_buffer, uint32 index)
{
    kassert(disk_buffer_legal_ip(disk_buffer));

    disk_buffer->index = index;
}


static inline uint32
disk_buffer_limit_i(s_disk_buf_t *disk_buffer)
{
    return disk_buffer_index_i(disk_buffer);
}

uint32
disk_buffer_limit(s_disk_buf_t *disk_buffer)
{
    if (disk_buffer_illegal_ip(disk_buffer)) {
        return SIZE_INVALID;
    } else {
        return disk_buffer_limit_i(disk_buffer);
    }
}

uint32
disk_buffer_index(s_disk_buf_t *disk_buffer)
{
    if (disk_buffer_illegal_ip(disk_buffer)) {
        return SIZE_INVALID;
    } else {
        return disk_buffer_index_i(disk_buffer);
    }
}

void
disk_buffer_index_set(s_disk_buf_t *disk_buffer, uint32 index)
{
    if (disk_buffer_illegal_ip(disk_buffer)) {
        return;
    } else {
        disk_buffer_index_set_i(disk_buffer, index);
    }
}

static inline uint32
disk_buffer_size_i(s_disk_buf_t *disk_buffer)
{
    kassert(disk_buffer_legal_ip(disk_buffer));

    return disk_buffer->size;
}

static inline void
disk_buffer_size_set_i(s_disk_buf_t *disk_buffer, uint32 size)
{
    kassert(disk_buffer_legal_ip(disk_buffer));

    disk_buffer->size = size;
}

uint32
disk_buffer_size(s_disk_buf_t *disk_buffer)
{
    if (disk_buffer_illegal_ip(disk_buffer)) {
        return SIZE_INVALID;
    } else {
        return disk_buffer_size_i(disk_buffer);
    }
}

void
disk_buffer_size_set(s_disk_buf_t *disk_buffer, uint32 size)
{
    if (disk_buffer_illegal_ip(disk_buffer)) {
        return;
    } else {
        disk_buffer_size_set_i(disk_buffer, size);
    }
}

