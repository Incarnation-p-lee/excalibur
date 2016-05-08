// For 4GB physcial memory space with 4KB page size, it has 1024 x 1024
// frame entries in all.
ptr_t *frames_bitmap;
ptr_t frames_size;

extern void *placement_ptr;

static void
frame_set(void *frame_addr)
{
    ptr_t idx;
    ptr_t off;
    ptr_t frame;

    assert_k(sizeof(frame_addr) == sizeof(ptr_t));

    frame = (ptr_t)frame_addr / 0x1000;
    idx = BM_INDEX(frame);
    off = BM_OFFSET(frame);

    frames_bitmap[idx] |= (0x1 << off);
}

static void
frame_clear(void *frame_addr)
{
    ptr_t idx;
    ptr_t off;
    ptr_t frame;

    assert_k(sizeof(frame_addr) == sizeof(ptr_t));

    frame = (ptr_t)frame_addr / 0x1000;
    idx = BM_INDEX(frame);
    off = BM_OFFSET(frame);

    frames_bitmap[idx] &= ~(0x1 << off);
}

static bool
frame_avaliable_p(void *frame_addr)
{
    ptr_t idx;
    ptr_t off;
    ptr_t frame;

    assert_k(sizeof(frame_addr) == sizeof(ptr_t));

    frame = (ptr_t)frame_addr / 0x1000;
    idx = BM_INDEX(frame);
    off = BM_OFFSET(frame);

    if (FRAME_SET == (frames_bitmap[idx] & (0x1 << off))) {
        return false;
    } else {
        return true;
    }
}

static void *
frame_first(void)
{
    ptr_t i;
    ptr_t j;

    i = 0;
    while (i < BM_INDEX(frames_size)) {
        if ((ptr_t)-1 != frames_bitmap[i]) {
            j = 0;
            while (j < sizeof(ptr_t) * 8) {
                if (FRAME_CLEAR == (frames_bitmap[i] & (0x1 << j))) {
                    return i * sizeof(ptr_t) * 8 + j;
                }
                j++;
            }
        }
        i++;
    }

    assert_k_not_reached("No free frame avaliale now.\n");
}

void
frame_allocate(struct page_entry *page, bool kernel, bool write)
{


}

