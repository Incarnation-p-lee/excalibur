sint32
ordered_array_standard_compare(const void *a, const void *b)
{
    if (!a || !b) {
        KERNEL_PANIC(INVALID_PARAM);
    }

    if ((ptr_t)a < (ptr_t)b) {
        return 1;
    } else if ((ptr_t)a < (ptr_t)b) {
        return -1;
    } else {
        return 0;
    }
}

static inline bool
ordered_array_legal_ip(s_ordered_array_t *ordered)
{
    if (ordered == NULL) {
        return false;
    } else if (ordered->index > ordered->size) {
        return false;
    } else if (ordered->array == NULL) {
        return false;
    } else if (ordered->compare == NULL) {
        return false;
    } else {
        return true;
    }
}

static inline uint32
ordered_array_size(s_ordered_array_t *ordered_array)
{
    kassert(ordered_array_legal_ip(ordered_array));

    return ordered_array->size;
}

static inline uint32
ordered_array_limit_i(s_ordered_array_t *ordered_array)
{
    kassert(ordered_array_legal_ip(ordered_array));

    return ordered_array->index;
}

uint32
ordered_array_limit(s_ordered_array_t *ordered_array)
{
    if (ordered_array_illegal_ip(ordered_array)) {
        return LIMIT_INVALID;
    } else {
        return ordered_array_limit_i(ordered_array);
    }
}

static inline bool
ordered_array_illegal_ip(s_ordered_array_t *ordered)
{
    return !ordered_array_legal_ip(ordered);
}

bool
ordered_array_legal_p(s_ordered_array_t *ordered)
{
    return ordered_array_legal_ip(ordered);
}

bool
ordered_array_illegal_p(s_ordered_array_t *ordered)
{
    return !ordered_array_legal_ip(ordered);
}

void *
ordered_array_place(s_ordered_array_t *ordered_array, void *addr, uint32 size,
    ordered_compare_t compare)
{
    uint32 bytes_count;

    if (ordered_array == NULL) {
        return addr;
    } else if (addr == NULL) {
        return addr;
    } else if (size == 0) {
        return addr;
    } else {
        bytes_count = sizeof(*ordered_array->array) * size;
        kmemset(addr, 0, bytes_count);

        ordered_array->array = addr;
        ordered_array->index = 0;
        ordered_array->size = size;
        ordered_array->compare = compare;

        return (void *)((ptr_t)addr + bytes_count);
    }
}

s_ordered_array_t *
ordered_array_create(uint32 size, ordered_compare_t compare)
{
    uint32 bytes_count;
    s_ordered_array_t *ordered_array;

    if (size == 0 || compare == NULL) {
        KERNEL_PANIC(INVALID_PARAM);
        return NULL;
    } else {
        bytes_count = size * sizeof(ordered_array->array[0]);
        ordered_array = kmalloc(sizeof(*ordered_array));
        ordered_array->array = kmalloc(bytes_count);

        kmemset(ordered_array->array, 0, bytes_count);
        ordered_array->size = size;
        ordered_array->index = 0;
        ordered_array->compare = compare;

        return ordered_array;
    }
}

void
ordered_array_destroy(s_ordered_array_t *oa)
{
    if (oa && oa->array) {
        // kfree(oa->array);
    }
}

static inline uint32
ordered_array_value_index_find_i(s_ordered_array_t *ordered_array, void *val)
{
    uint32 i;
    uint32 limit;

    kassert(ordered_array_legal_ip(ordered_array));

    i = 0;
    limit = ordered_array_limit_i(ordered_array);

    while (i < limit) {
        if (val == ordered_array_value_i(ordered_array, i)) {
            return i;
        }

        i++;
    }

    return INDEX_INVALID;
}

uint32
ordered_array_value_index_find(s_ordered_array_t *ordered_array, void *val)
{
    if (ordered_array_illegal_ip(ordered_array)) {
        return INDEX_INVALID;
    } else {
        return ordered_array_value_index_find_i(ordered_array, val);
    }
}

static inline bool
ordered_array_empty_p(s_ordered_array_t *ordered_array)
{
    kassert(ordered_array_legal_ip(ordered_array));

    if (ordered_array->index == 0) {
        return true;
    } else {
        return false;
    }
}

static inline bool
ordered_array_full_p(s_ordered_array_t *ordered)
{
    kassert(ordered_array_legal_ip(ordered));

    if (ordered_array_limit_i(ordered) == ordered_array_size(ordered)) {
        return true;
    } else {
        return false;
    }
}

static inline void
ordered_array_value_append(s_ordered_array_t *ordered_array, void *val)
{
    kassert(ordered_array_legal_ip(ordered_array));

    ordered_array->array[ordered_array->index++] = val;
}

static inline void
ordered_array_value_set(s_ordered_array_t *ordered_array, uint32 i, void *val)
{
    kassert(ordered_array_legal_ip(ordered_array));
    kassert(i < ordered_array_size(ordered_array));

    ordered_array->array[i] = val;
}

static inline void
ordered_array_inc(s_ordered_array_t *ordered_array)
{
    kassert(ordered_array_legal_ip(ordered_array));
    kassert(!ordered_array_full_p(ordered_array));

    ordered_array->index++;
}

static inline void
ordered_array_dec(s_ordered_array_t *ordered_array)
{
    kassert(ordered_array_legal_ip(ordered_array));
    kassert(!ordered_array_empty_p(ordered_array));

    ordered_array->index--;
}

static inline void
ordered_array_insert_i(s_ordered_array_t *ordered_array, void *val)
{
    uint32 i, k;
    void *value_tmp;
    uint32 array_size, array_limit;

    kassert(ordered_array_legal_ip(ordered_array));

    if (ordered_array_empty_p(ordered_array)) {
        ordered_array_value_append(ordered_array, val);
    } else {
        i = 0;
        array_size = ordered_array_size(ordered_array);
        array_limit = ordered_array_limit_i(ordered_array);

        while (i < array_limit) {
            value_tmp = ordered_array_value_i(ordered_array, i);

            if (ordered_array->compare(value_tmp, val) > 0) {
                break;
            }

            i++;
        }

        if (i == array_limit && i < array_size) {
            ordered_array_value_append(ordered_array, val);
        } else if (array_size == array_limit) {
            KERNEL_PANIC(ARRAY_FULL);
        } else {
            k = array_limit;

            while (k > i) {
                value_tmp = ordered_array_value_i(ordered_array, k - 1);
                ordered_array_value_set(ordered_array, k, value_tmp);
                k--;
            }

            ordered_array_value_set(ordered_array, i, val);
            ordered_array_inc(ordered_array);
        }
    }
}

void
ordered_array_insert(s_ordered_array_t *ordered_array, void *val)
{
    if (ordered_array_legal_ip(ordered_array)) {
        return ordered_array_insert_i(ordered_array, val);
    }
}

static inline void *
ordered_array_value_i(s_ordered_array_t *ordered_array, uint32 i)
{
    kassert(ordered_array_legal_p(ordered_array));
    kassert(i < ordered_array_limit_i(ordered_array));

    return ordered_array->array[i];
}

void *
ordered_array_value(s_ordered_array_t *ordered_array, uint32 i)
{
    if (ordered_array_illegal_ip(ordered_array)) {
        KERNEL_PANIC(INVALID_PARAM);
        return NULL;
    } else if (i >= ordered_array_limit_i(ordered_array)) {
        KERNEL_PANIC(INVALID_PARAM);
        return NULL;
    } else {
        return ordered_array_value_i(ordered_array, i);
    }
}

static inline bool
ordered_array_prev_suitable_p(s_ordered_array_t *ordered_array, uint32 i)
{
    void *val;
    void *val_prev;

    kassert(ordered_array_legal_ip(ordered_array));
    kassert(i < ordered_array_limit_i(ordered_array));
    kassert(i > 0);

    val = ordered_array_value_i(ordered_array, i);
    val_prev = ordered_array_value_i(ordered_array, i - 1);

    if (ordered_array->compare(val_prev, val) <= 0) {
        return true;
    } else {
        return false;
    }
}

static inline bool
ordered_array_next_suitable_p(s_ordered_array_t *ordered_array, uint32 i)
{
    void *val;
    void *val_next;

    kassert(ordered_array_legal_ip(ordered_array));
    kassert(i < ordered_array_index_last(ordered_array));

    val = ordered_array_value_i(ordered_array, i);
    val_next = ordered_array_value_i(ordered_array, i + 1);

    if (ordered_array->compare(val, val_next) <= 0) {
        return true;
    } else {
        return false;
    }
}

static inline uint32
ordered_array_index_last(s_ordered_array_t *ordered_array)
{
    kassert(ordered_array_legal_ip(ordered_array));
    kassert(!ordered_array_empty_p(ordered_array));

    return ordered_array_limit_i(ordered_array) - 1;
}

static inline bool
ordered_array_index_last_p(s_ordered_array_t *ordered_array, uint32 i)
{
    kassert(ordered_array_legal_ip(ordered_array));
    kassert(!ordered_array_empty_p(ordered_array));

    if (i == ordered_array_index_last(ordered_array)) {
        return true;
    } else {
        return false;
    }
}

static inline bool
ordered_array_suitable_p(s_ordered_array_t *ordered_array, uint32 i)
{
    kassert(ordered_array_legal_ip(ordered_array));
    kassert(i < ordered_array_limit_i(ordered_array));

    if (i == 0 && ordered_array_limit_i(ordered_array) == 1) {
        return true;
    } else if (i == 0 && ordered_array_next_suitable_p(ordered_array, i)) {
        return true;
    } else if (ordered_array_index_last_p(ordered_array, i)
        && ordered_array_prev_suitable_p(ordered_array, i)) {
        return true;
    } else if (ordered_array_prev_suitable_p(ordered_array, i)
        && ordered_array_next_suitable_p(ordered_array, i)) {
        return true;
    } else {
        return false;
    }
}

static inline void
ordered_array_prev_adjust(s_ordered_array_t *ordered_array, uint32 i)
{
    void *val;
    void *val_tmp;

    kassert(ordered_array_legal_ip(ordered_array));
    kassert(i < ordered_array_limit_i(ordered_array));

    val = ordered_array_value_i(ordered_array, i);

    while (i > 0) {
        val_tmp = ordered_array_value_i(ordered_array, i - 1);

        if (ordered_array->compare(val_tmp, val) > 0) {
            ordered_array_value_set(ordered_array, i, val_tmp);
        } else {
            break;
        }

        i--;
    }

    ordered_array_value_set(ordered_array, i, val);
}

static inline void
ordered_array_next_adjust(s_ordered_array_t *ordered_array, uint32 i)
{
    void *val;
    void *val_tmp;

    kassert(ordered_array_legal_ip(ordered_array));
    kassert(i < ordered_array_index_last(ordered_array));

    val = ordered_array_value_i(ordered_array, i);

    while (i < ordered_array_index_last(ordered_array)) {
        val_tmp = ordered_array_value_i(ordered_array, i + 1);

        if (ordered_array->compare(val, val_tmp) > 0) {
            ordered_array_value_set(ordered_array, i, val_tmp);
        } else {
            break;
        }

        i++;
    }

    ordered_array_value_set(ordered_array, i, val);
}

static inline void
ordered_array_adjust_i(s_ordered_array_t *ordered_array, uint32 i)
{
    kassert(ordered_array_legal_ip(ordered_array));
    kassert(i < ordered_array_limit_i(ordered_array));

    if (ordered_array_suitable_p(ordered_array, i)) {
        return;
    } else if (!ordered_array_prev_suitable_p(ordered_array, i)) {
        ordered_array_prev_adjust(ordered_array, i);
    } else if (!ordered_array_next_suitable_p(ordered_array, i)) {
        ordered_array_next_adjust(ordered_array, i);
    } else {
        KERNEL_PANIC(NOT_REACHED);
    }
}

void
ordered_array_adjust(s_ordered_array_t *ordered_array, uint32 i)
{
    if (ordered_array_illegal_ip(ordered_array)) {
        KERNEL_PANIC(INVALID_PARAM);
    } else if (i >= ordered_array_limit_i(ordered_array)) {
        KERNEL_PANIC(INVALID_PARAM);
    } else {
        return ordered_array_adjust_i(ordered_array, i);
    }
}

static inline void
ordered_array_remove_i(s_ordered_array_t *ordered_array, uint32 i)
{
    void *val;
    uint32 limit;

    kassert(ordered_array_legal_p(ordered_array));
    kassert(i < ordered_array_limit_i(ordered_array));

    limit = ordered_array_limit_i(ordered_array);

    while (i + 1 < limit) {
        val = ordered_array_value_i(ordered_array, i + 1);
        ordered_array_value_set(ordered_array, i, val);

        i++;
    }

    ordered_array_dec(ordered_array);
}

void
ordered_array_remove(s_ordered_array_t *ordered_array, uint32 i)
{
    if (ordered_array_illegal_ip(ordered_array)) {
        KERNEL_PANIC(INVALID_PARAM);
    } else if (i >= ordered_array_limit_i(ordered_array)) {
        KERNEL_PANIC(INVALID_PARAM);
    } else {
        ordered_array_remove_i(ordered_array, i);
    }
}

