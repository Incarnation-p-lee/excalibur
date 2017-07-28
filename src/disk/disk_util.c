static inline bool
disk_buffer_legal_ip(s_disk_buf_t *sector_buf)
{
    if (sector_buf == NULL) {
        return false;
    } else if (sector_buf->buffer == NULL) {
        return false;
    } else if (sector_buf->index > sector_buf->size) {
        return false;
    } else {
        return true;
    }
}

static inline bool
disk_buffer_illegal_ip(s_disk_buf_t *sector_buf)
{
    return !disk_buffer_legal_ip(sector_buf);
}

bool
disk_buffer_legal_p(s_disk_buf_t *sector_buf)
{
    return disk_buffer_legal_ip(sector_buf);
}

bool
disk_buffer_illegal_p(s_disk_buf_t *sector_buf)
{
    return disk_buffer_illegal_ip(sector_buf);
}

