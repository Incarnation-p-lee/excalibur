static inline s_frame_bitmap_t *
frame_bitmap_create(ptr_t memory_limit)
{
    uint32 size;
    uint32 frame_limit;
    uint32 bytes_count;
    s_frame_bitmap_t *frame_bitmap;

    kassert(memory_limit);

    frame_bitmap = memory_physical_allocate(sizeof(*frame_bitmap));

    frame_limit = memory_limit / PAGE_SIZE;
    size = frame_limit / BIT_WIDTH(*frame_bitmap->bitmap) + 1;
    frame_bitmap->size = size;
    frame_bitmap->frame_limit = frame_limit;

    bytes_count = size * BIT_WIDTH(*frame_bitmap->bitmap);
    frame_bitmap->bitmap = memory_physical_allocate(bytes_count);
    kmemset(frame_bitmap->bitmap, 0, bytes_count);

    return frame_bitmap;
}

static inline uint32
frame_bitmap_frame_mask_index(s_frame_bitmap_t *frame_bitmap, ptr_t frame)
{
    kassert(frame_bitmap);

    return frame / (sizeof(frame_bitmap->bitmap[0]) * 8);
}

static inline uint32
frame_bitmap_frame_bit_index(s_frame_bitmap_t *frame_bitmap, ptr_t frame)
{
    kassert(frame_bitmap);

    return frame % (sizeof(frame_bitmap->bitmap[0]) * 8);
}

static inline void
frame_bitmap_mask_set(s_frame_bitmap_t *frame_bitmap, uint32 mask_idx,
    uint32 bit_idx)
{
    kassert(frame_bitmap);
    kassert(mask_idx < frame_bitmap_limit(frame_bitmap));
    kassert(bit_idx < BIT_WIDTH(frame_bitmap->bitmap[0]));

    frame_bitmap->bitmap[mask_idx] |= (ptr_t)1 << bit_idx;
}

static inline void
frame_bitmap_mask_clear(s_frame_bitmap_t *frame_bitmap, uint32 mask_idx,
    uint32 bit_idx)
{
    kassert(frame_bitmap);
    kassert(mask_idx < frame_bitmap_limit(frame_bitmap));
    kassert(bit_idx < BIT_WIDTH(frame_bitmap->bitmap[0]));

    frame_bitmap->bitmap[mask_idx] &= ~((ptr_t)1 << bit_idx);
}

static inline ptr_t
frame_bitmap_frame_obtain(s_frame_bitmap_t *frame_bitmap,
    uint32 mask_idx, uint32 bit_idx)
{
    ptr_t frame;

    kassert(frame_bitmap);
    kassert(mask_idx < frame_bitmap_limit(frame_bitmap));
    kassert(bit_idx < BIT_WIDTH(frame_bitmap->bitmap[0]));

    frame_bitmap_mask_set(frame_bitmap, mask_idx, bit_idx);
    frame = (ptr_t)(mask_idx * BIT_WIDTH(ptr_t) + bit_idx);
    kassert(frame < frame_bitmap->frame_limit);

    return frame;
}

static inline bool
frame_bitmap_mask_set_p(ptr_t frame_bitmap, uint32 i)
{
    kassert(i < BIT_WIDTH(frame_bitmap));

    if (U32_BIT_GET(frame_bitmap, i) == FRAME_BITMAP_SET) {
        return true;
    } else {
        return false;
    }
}

static inline bool
frame_bitmap_mask_clear_p(ptr_t mask, uint32 i)
{
    return !frame_bitmap_mask_set_p(mask, i);
}

static inline uint32
frame_bitmap_limit(s_frame_bitmap_t *frame_bitmap)
{
    return frame_bitmap->size;
}

static inline ptr_t
frame_bitmap_mask(s_frame_bitmap_t *frame_bitmap, uint32 i)
{
    kassert(frame_bitmap);
    kassert(i < frame_bitmap_limit(frame_bitmap));

    return frame_bitmap->bitmap[i];
}

static inline ptr_t
frame_allocate(void)
{
    uint32 i;
    uint32 j;
    ptr_t mask;
    uint32 limit;

    i = 0;
    limit = frame_bitmap_limit(frame_bitmap);

    while (i < limit) {
        mask = frame_bitmap_mask(frame_bitmap, i);

        if (mask == (ptr_t)-1) {
            i++;
            continue;
        }

        j = 0;

        while (j < BIT_WIDTH(ptr_t)) {
            if (frame_bitmap_mask_clear_p(mask, j)) {
                return frame_bitmap_frame_obtain(frame_bitmap, i, j);
            }

            j++;
        }

        i++;
    }

    KERNEL_PANIC(NO_FRAME);
    return FRAME_INVALID;
}

