static inline bool
bitmap_legal_ip(s_bitmap_t *bitmap)
{
    if (bitmap == NULL) {
        return false;
    } else if (bitmap->array == NULL) {
        return false;
    } else if (bitmap->map_size == 0) {
        return false;
    } else if (bitmap->array_size == 0) {
        return false;
    } else {
        return true;
    }
}

static inline bool
bitmap_illegal_ip(s_bitmap_t *bitmap)
{
    return !bitmap_legal_ip(bitmap);
}

bool
bitmap_legal_p(s_bitmap_t *bitmap)
{
    return bitmap_legal_ip(bitmap);
}

bool
bitmap_illegal_p(s_bitmap_t *bitmap)
{
    return !bitmap_legal_ip(bitmap);
}

static inline uint8 *
bitmap_array(s_bitmap_t *bitmap)
{
    kassert(bitmap_legal_ip(bitmap));

    return bitmap->array;
}

static inline void
bitmap_array_set(s_bitmap_t *bitmap, uint8 *array)
{
    kassert(bitmap_legal_ip(bitmap));

    bitmap->array = array;
}

static inline uint32
bitmap_array_size(s_bitmap_t *bitmap)
{
    kassert(bitmap_legal_ip(bitmap));

    return bitmap->array_size;
}

static inline void
bitmap_array_size_set(s_bitmap_t *bitmap, uint32 array_size)
{
    kassert(bitmap_legal_ip(bitmap));

    bitmap->array_size = array_size;
}

static inline uint32
bitmap_map_size(s_bitmap_t *bitmap)
{
    kassert(bitmap_legal_ip(bitmap));

    return bitmap->map_size;
}

static inline void
bitmap_map_size_set(s_bitmap_t *bitmap, uint32 map_size)
{
    kassert(bitmap_legal_ip(bitmap));

    bitmap->map_size = map_size;
}

static inline s_bitmap_t *
bitmap_create_i(uint32 map_size)
{
    uint32 bytes_count;
    s_bitmap_t *bitmap;

    kassert(map_size);

    bitmap = kmalloc(sizeof(*bitmap));

    bytes_count = (map_size / 8 + 1) * 8;
    bitmap->array = kmalloc(bytes_count);

    bitmap->array_size = bytes_count;
    bitmap->map_size = map_size;

    return bitmap;
}

s_bitmap_t *
bitmap_create(uint32 map_size)
{
    if (map_size == 0) {
        return PTR_INVALID;
    } else {
        return bitmap_create_i(map_size);
    }
}

static inline s_bitmap_t *
bitmap_place_i(void *array, uint32 array_size, uint32 map_size)
{
    s_bitmap_t *bitmap;

    kassert(array);
    kassert(map_size);
    kassert(array_size);

    bitmap = kmalloc(sizeof(*bitmap));

    bitmap->array = array;
    bitmap->array_size = array_size;
    bitmap->map_size = map_size;

    return bitmap;
}

s_bitmap_t *
bitmap_place(void *array, uint32 array_size, uint32 map_size)
{
    if (array == NULL) {
        return PTR_INVALID;
    } else if (map_size == 0) {
        return PTR_INVALID;
    } else if (array_size == 0) {
        return PTR_INVALID;
    } else {
        return bitmap_place_i(array, array_size, map_size);
    }
}

static inline void
bitmap_destroy_i(s_bitmap_t **bitmap)
{
    kassert(bitmap);
    kassert(bitmap_legal_ip(*bitmap));

    kfree((*bitmap)->array);
    kfree(*bitmap);

    *bitmap = NULL;
}

void
bitmap_destroy(s_bitmap_t **bitmap)
{
    if (bitmap == NULL) {
        return;
    } else if (bitmap_illegal_ip(*bitmap)) {
        return;
    } else {
        bitmap_destroy_i(bitmap);
    }
}

static inline void
bitmap_set_i(s_bitmap_t *bitmap, uint32 i)
{
    uint32 index;
    uint8 *array;
    uint32 offset;

    kassert(bitmap_legal_ip(bitmap));
    kassert(i < bitmap_map_size(bitmap));

    index = i / 8;
    offset = i % 8;
    array = bitmap_array(bitmap);

    U8_BIT_SET(array[index], offset);
}

void
bitmap_set(s_bitmap_t *bitmap, uint32 i)
{
    if (bitmap_illegal_ip(bitmap)) {
        return;
    } else if (i >= bitmap_map_size(bitmap)) {
        return;
    } else {
        bitmap_set_i(bitmap, i);
    }
}

static inline void
bitmap_clear_i(s_bitmap_t *bitmap, uint32 i)
{
    uint32 index;
    uint8 *array;
    uint32 offset;

    kassert(bitmap_legal_ip(bitmap));
    kassert(i < bitmap_map_size(bitmap));

    index = i / 8;
    offset = i % 8;
    array = bitmap_array(bitmap);

    U8_BIT_CLEAR(array[index], offset);
}

void
bitmap_clear(s_bitmap_t *bitmap, uint32 i)
{
    if (bitmap_illegal_ip(bitmap)) {
        return;
    } else if (i >= bitmap_map_size(bitmap)) {
        return;
    } else {
        bitmap_clear_i(bitmap, i);
    }
}

static inline bool
bitmap_set_ip(s_bitmap_t *bitmap, uint32 i)
{
    uint32 index;
    uint8 *array;
    uint32 offset;

    kassert(bitmap_legal_ip(bitmap));
    kassert(i < bitmap_map_size(bitmap));

    index = i / 8;
    offset = i % 8;
    array = bitmap_array(bitmap);

    if (U8_BIT_GET(array[index], offset) == BIT_SET) {
        return true;
    } else {
        return false;
    }
}

bool
bitmap_set_p(s_bitmap_t *bitmap, uint32 i)
{
    if (bitmap_illegal_ip(bitmap)) {
        return false;
    } else if (i >= bitmap_map_size(bitmap)) {
        return false;
    } else {
        return bitmap_set_ip(bitmap, i);
    }
}

bool
bitmap_clear_p(s_bitmap_t *bitmap, uint32 i)
{
    if (bitmap_illegal_ip(bitmap)) {
        return false;
    } else if (i >= bitmap_map_size(bitmap)) {
        return false;
    } else {
        return !bitmap_set_ip(bitmap, i);
    }
}

