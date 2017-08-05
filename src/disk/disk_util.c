static inline bool
disk_buffer_legal_ip(s_disk_buf_t *disk_buf)
{
    if (disk_buf == NULL) {
        return false;
    } else if (disk_buf->buffer == NULL) {
        return false;
    } else if (disk_buf->index > disk_buf->size) {
        return false;
    } else {
        return true;
    }
}

static inline bool
disk_buffer_illegal_ip(s_disk_buf_t *disk_buf)
{
    return !disk_buffer_legal_ip(disk_buf);
}

bool
disk_buffer_legal_p(s_disk_buf_t *disk_buf)
{
    return disk_buffer_legal_ip(disk_buf);
}

bool
disk_buffer_illegal_p(s_disk_buf_t *disk_buf)
{
    return disk_buffer_illegal_ip(disk_buf);
}

static inline uint32
disk_buffer_size_i(s_disk_buf_t *disk_buf)
{
    kassert(disk_buffer_legal_ip(disk_buf));

    return disk_buf->size;
}

uint32
disk_buffer_size(s_disk_buf_t *disk_buf)
{
    if (disk_buffer_illegal_ip(disk_buf)) {
        return SIZE_INVALID;
    } else {
        return disk_buffer_size_i(disk_buf);
    }
}

static inline uint32
disk_buffer_limit(s_disk_buf_t *disk_buf)
{
    return disk_buffer_index(disk_buf);
}

static inline uint32
disk_buffer_index(s_disk_buf_t *disk_buf)
{
    kassert(disk_buffer_legal_ip(disk_buf));

    return disk_buf->index;
}

static inline void
disk_buffer_index_set_i(s_disk_buf_t *disk_buf, uint32 index)
{
    kassert(disk_buffer_legal_ip(disk_buf));

    disk_buf->index = index;
}

void
disk_buffer_index_set(s_disk_buf_t *disk_buf, uint32 index)
{
    if (disk_buffer_illegal_ip(disk_buf)) {
        return;
    } else {
        disk_buffer_index_set_i(disk_buf, index);
    }
}

static inline void
disk_buffer_dword_append_i(s_disk_buf_t *disk_buf, uint32 val)
{
    uint32 i;

    kassert(disk_buffer_legal_ip(disk_buf));

    i = disk_buffer_limit(disk_buf);
    kassert(i + sizeof(val) < disk_buffer_size(disk_buf));

    *(uint32 *)&disk_buf->buffer[i] = val;
}

void
disk_buffer_dword_append(s_disk_buf_t *disk_buf, uint32 val)
{
    if (disk_buffer_illegal_ip(disk_buf)) {
        return;
    } else if (disk_buffer_limit(disk_buf) + 4 >= disk_buffer_size(disk_buf)) {
        return;
    } else {
        disk_buffer_dword_append_i(disk_buf, val);
    }
}

static inline void *
disk_buffer_obtain_i(s_disk_buf_t *disk_buf)
{
    kassert(disk_buffer_legal_ip(disk_buf));

    return disk_buf->buffer;
}

void *
disk_buffer_obtain(s_disk_buf_t *disk_buf)
{
    if (disk_buffer_illegal_ip(disk_buf)) {
        return PTR_INVALID;
    } else {
        return disk_buffer_obtain_i(disk_buf);
    }
}

