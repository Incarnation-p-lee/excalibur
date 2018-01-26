static inline void
block_buffer_dword_append_i(s_block_buf_t *block_buf, uint32 val)
{
    uint32 i;

    kassert(block_buffer_legal_ip(block_buf));

    i = block_buffer_limit(block_buf);
    kassert(i + sizeof(val) < block_buffer_size(block_buf));

    *(uint32 *)&block_buf->array[i] = val;
}

void
block_buffer_dword_append(s_block_buf_t *block_buf, uint32 val)
{
    if (block_buffer_illegal_ip(block_buf)) {
        return;
    } else if (block_buffer_limit(block_buf) + 4 >= block_buffer_size(block_buf)) {
        return;
    } else {
        block_buffer_dword_append_i(block_buf, val);
    }
}

static inline s_block_buf_t *
block_buffer_create_i(uint32 size)
{
    s_block_buf_t *block_buf;

    kassert(size);

    block_buf = kmalloc(sizeof(*block_buf));
    block_buf->array = kmalloc(sizeof(block_buf->array[0]) * size);

    block_buf->index = 0;
    block_buf->size = size;

    return block_buf;
}

s_block_buf_t *
block_buffer_create(uint32 size)
{
    if (size == 0) {
        return PTR_INVALID;
    } else {
        return block_buffer_create_i(size);
    }
}

static inline void
block_buffer_destroy_i(s_block_buf_t *block_buf)
{
    kassert(block_buffer_legal_ip(block_buf));

    kfree(block_buffer_array(block_buf));
    kfree(block_buf);
}

void
block_buffer_destroy(s_block_buf_t **block_buf)
{
    if (block_buf == NULL) {
        return;
    } else if (block_buffer_illegal_ip(*block_buf)) {
        return;
    } else {
        block_buffer_destroy_i(*block_buf);
        *block_buf = NULL;
    }
}

static inline uint32
block_buffer_copy_i(void *d, s_block_buf_t *block_buf, uint32 offset, uint32 size)
{
    void *array;

    kassert(d);
    kassert(size);
    kassert(block_buffer_legal_ip(block_buf));
    kassert(offset < block_buffer_limit_i(block_buf));
    kassert(offset + size <= block_buffer_limit_i(block_buf));

    array = block_buffer_array_i(block_buf);

    kmemory_copy(d, array + offset, size);

    return size;
}

uint32
block_buffer_copy(void *d, s_block_buf_t *block_buf, uint32 offset, uint32 size)
{
    if (d == NULL) {
        return SIZE_INVALID;
    } else if (block_buffer_illegal_ip(block_buf)) {
        return SIZE_INVALID;
    } else if (offset >= block_buffer_limit_i(block_buf)) {
        return SIZE_INVALID;
    } else if (size == 0) {
        return SIZE_INVALID;
    } else if (offset + size > block_buffer_limit_i(block_buf)) {
        return SIZE_INVALID;
    } else {
        return block_buffer_copy_i(d, block_buf, offset, size);
    }
}

