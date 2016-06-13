sint32
ordered_array_standard_compare(const void *a, const void *b)
{
    if (!a || !b) {
        KERNEL_PANIC(INVALID_PARAM);
        return 0;
    } else if ((ptr_t)a < (ptr_t)b) {
        return 1;
    } else if ((ptr_t)a < (ptr_t)b) {
        return -1;
    } else {
        return 0;
    }
}

struct ordered_array
ordered_array_create(uint32 max_size, ordered_compare_t compare)
{
    struct ordered_array oa;

    if (!max_size || !compare) {
        KERNEL_PANIC(INVALID_PARAM);
        return oa;
    } else {
        oa.array = kmalloc(max_size * sizeof(void *));
        kmemset(oa.array, 0, max_size * sizeof(void *));

        oa.size = 0;
        oa.max_size = max_size;
        oa.compare = compare;

        return oa;
    }
}

struct ordered_array
ordered_array_place(void *addr, uint32 max_size, ordered_compare_t compare)
{
    struct ordered_array oa;

    if (!addr || !compare || !max_size) {
        KERNEL_PANIC(INVALID_PARAM);
        return oa;
    } else {
        oa.array = (void **)addr;
        kmemset(oa.array, 0, max_size * sizeof(void *));

        oa.size = 0;
        oa.max_size = max_size;
        oa.compare = compare;
        return oa;
    }
}

void
ordered_array_destroy(struct ordered_array *oa)
{
    if (oa && oa->array) {
        // kfree(oa->array);
    }
}

void
ordered_array_insert(struct ordered_array *oa, void *val)
{
    uint32 i;
    uint32 k;

    if (!oa || !val || !oa->array || !oa->compare) {
        KERNEL_PANIC(INVALID_PARAM);
    } else {
        i = 0;
        while (i < oa->size && oa->compare(oa->array[i], val) > 0) {
            i++;
        }

        if (i == oa->size && i < oa->max_size) {
            oa->array[oa->size++] = val;
        } else if (i >= oa->max_size) {
            KERNEL_PANIC(IDX_OVERFLOW);
        } else if (oa->max_size == oa->size) {
            KERNEL_PANIC(ARRAY_FULL);
        } else {
            k = oa->size;

            while (k > i) {
                oa->array[k] = oa->array[k - 1];
                k--;
            }

            oa->array[i] = val;
            oa->size++;
        }
    }
}

void *
ordered_array_lookup(struct ordered_array *oa, uint32 idx)
{
    if (!oa || !oa->array || idx >= oa->size) {
        KERNEL_PANIC(INVALID_PARAM);
    }

    return oa->array[idx];
}

void
ordered_array_remove(struct ordered_array *oa, uint32 idx)
{
    uint32 i;

    if (!oa || !oa->array || idx >= oa->size) {
        KERNEL_PANIC(INVALID_PARAM);
    } else {
        i = idx;
        while (i < oa->size) {
            oa->array[i] = oa->array[i + 1];
            i++;
        }

        oa->size--;
    }
}

