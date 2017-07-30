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
disk_buffer_size(s_disk_buf_t *disk_buf)
{
    kassert(disk_buffer_legal_ip(disk_buf));

    return disk_buf->size;
}

static inline uint32
disk_buffer_limit(s_disk_buf_t *disk_buf)
{
    kassert(disk_buffer_legal_ip(disk_buf));

    return disk_buf->index;
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

