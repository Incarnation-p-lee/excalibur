static inline void
disk_buffer_dword_append_i(s_disk_buf_t *disk_buf, uint32 val)
{
    uint32 i;

    kassert(disk_buffer_legal_ip(disk_buf));

    i = disk_buffer_limit(disk_buf);
    kassert(i + sizeof(val) < disk_buffer_size(disk_buf));

    *(uint32 *)&disk_buf->array[i] = val;
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

static inline s_disk_buf_t *
disk_buffer_create_i(uint32 size)
{
    s_disk_buf_t *disk_buf;

    kassert(size);

    disk_buf = kmalloc(sizeof(*disk_buf));
    disk_buf->array = kmalloc(sizeof(disk_buf->array[0]) * size);

    disk_buf->index = 0;
    disk_buf->size = size;

    return disk_buf;
}

s_disk_buf_t *
disk_buffer_create(uint32 size)
{
    if (size == 0) {
        return PTR_INVALID;
    } else {
        return disk_buffer_create_i(size);
    }
}

static inline void
disk_buffer_destroy_i(s_disk_buf_t *disk_buf)
{
    kassert(disk_buffer_legal_ip(disk_buf));

    kfree(disk_buffer_array(disk_buf));
    kfree(disk_buf);
}

void
disk_buffer_destroy(s_disk_buf_t **disk_buf)
{
    if (disk_buf == NULL) {
        return;
    } else if (disk_buffer_illegal_ip(*disk_buf)) {
        return;
    } else {
        disk_buffer_destroy_i(*disk_buf);
        *disk_buf = NULL;
    }
}

static inline uint32
disk_buffer_copy_i(void *d, s_disk_buf_t *disk_buf, uint32 offset, uint32 size)
{
    void *array;

    kassert(d);
    kassert(size);
    kassert(disk_buffer_legal_ip(disk_buf));
    kassert(offset < disk_buffer_limit_i(disk_buf));
    kassert(offset + size <= disk_buffer_limit_i(disk_buf));

    array = disk_buffer_array_i(disk_buf);

    kmemory_copy(d, array + offset, size);

    return size;
}

uint32
disk_buffer_copy(void *d, s_disk_buf_t *disk_buf, uint32 offset, uint32 size)
{
    if (d == NULL) {
        return SIZE_INVALID;
    } else if (disk_buffer_illegal_ip(disk_buf)) {
        return SIZE_INVALID;
    } else if (offset >= disk_buffer_limit_i(disk_buf)) {
        return SIZE_INVALID;
    } else if (size == 0) {
        return SIZE_INVALID;
    } else if (offset + size > disk_buffer_limit_i(disk_buf)) {
        return SIZE_INVALID;
    } else {
        return disk_buffer_copy_i(d, disk_buf, offset, size);
    }
}

