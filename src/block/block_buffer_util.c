static inline bool
block_buffer_legal_ip(s_block_buf_t *block_buffer)
{
    if (block_buffer == NULL) {
        return false;
    } else if (block_buffer->array == NULL) {
        return false;
    } else if (block_buffer->index > block_buffer->size) {
        return false;
    } else if (block_buffer->size == 0) {
        return false;
    } else {
        return true;
    }
}

static inline bool
block_buffer_illegal_ip(s_block_buf_t *block_buffer)
{
    return !block_buffer_legal_ip(block_buffer);
}

bool
block_buffer_legal_p(s_block_buf_t *block_buffer)
{
    return block_buffer_legal_ip(block_buffer);
}

bool
block_buffer_illegal_p(s_block_buf_t *block_buffer)
{
    return !block_buffer_legal_ip(block_buffer);
}

static inline uint8 *
block_buffer_array_i(s_block_buf_t *block_buffer)
{
    kassert(block_buffer_legal_ip(block_buffer));

    return block_buffer->array;
}

static inline void
block_buffer_array_set_i(s_block_buf_t *block_buffer, uint8 *array)
{
    kassert(block_buffer_legal_ip(block_buffer));

    block_buffer->array = array;
}

uint8 *
block_buffer_array(s_block_buf_t *block_buffer)
{
    if (block_buffer_illegal_ip(block_buffer)) {
        return PTR_INVALID;
    } else {
        return block_buffer_array_i(block_buffer);
    }
}

void
block_buffer_array_set(s_block_buf_t *block_buffer, uint8 *array)
{
    if (block_buffer_illegal_ip(block_buffer)) {
        return;
    } else {
        block_buffer_array_set_i(block_buffer, array);
    }
}

static inline uint32
block_buffer_index_i(s_block_buf_t *block_buffer)
{
    kassert(block_buffer_legal_ip(block_buffer));

    return block_buffer->index;
}

static inline void
block_buffer_index_set_i(s_block_buf_t *block_buffer, uint32 index)
{
    kassert(block_buffer_legal_ip(block_buffer));

    block_buffer->index = index;
}


static inline uint32
block_buffer_limit_i(s_block_buf_t *block_buffer)
{
    return block_buffer_index_i(block_buffer);
}

uint32
block_buffer_limit(s_block_buf_t *block_buffer)
{
    if (block_buffer_illegal_ip(block_buffer)) {
        return SIZE_INVALID;
    } else {
        return block_buffer_limit_i(block_buffer);
    }
}

uint32
block_buffer_index(s_block_buf_t *block_buffer)
{
    if (block_buffer_illegal_ip(block_buffer)) {
        return SIZE_INVALID;
    } else {
        return block_buffer_index_i(block_buffer);
    }
}

void
block_buffer_index_set(s_block_buf_t *block_buffer, uint32 index)
{
    if (block_buffer_illegal_ip(block_buffer)) {
        return;
    } else {
        block_buffer_index_set_i(block_buffer, index);
    }
}

static inline uint32
block_buffer_size_i(s_block_buf_t *block_buffer)
{
    kassert(block_buffer_legal_ip(block_buffer));

    return block_buffer->size;
}

static inline void
block_buffer_size_set_i(s_block_buf_t *block_buffer, uint32 size)
{
    kassert(block_buffer_legal_ip(block_buffer));

    block_buffer->size = size;
}

uint32
block_buffer_size(s_block_buf_t *block_buffer)
{
    if (block_buffer_illegal_ip(block_buffer)) {
        return SIZE_INVALID;
    } else {
        return block_buffer_size_i(block_buffer);
    }
}

void
block_buffer_size_set(s_block_buf_t *block_buffer, uint32 size)
{
    if (block_buffer_illegal_ip(block_buffer)) {
        return;
    } else {
        block_buffer_size_set_i(block_buffer, size);
    }
}

