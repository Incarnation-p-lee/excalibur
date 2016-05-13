static void
frame_set(ptr_t frame)
{
    ptr_t idx;
    ptr_t off;

    assert_k(sizeof(frame) == sizeof(ptr_t));

    idx = BM_INDEX(frame);
    off = BM_OFFSET(frame);

    frames_bitmap[idx] |= (0x1 << off);
}

static void
frame_clear(ptr_t frame)
{
    ptr_t idx;
    ptr_t off;

    assert_k(sizeof(frame) == sizeof(ptr_t));

    idx = BM_INDEX(frame);
    off = BM_OFFSET(frame);

    frames_bitmap[idx] &= ~(0x1 << off);
}

bool
frame_available_p(ptr_t frame)
{
    ptr_t idx;
    ptr_t off;

    assert_k(sizeof(frame) == sizeof(ptr_t));

    idx = BM_INDEX(frame);
    off = BM_OFFSET(frame);

    if (FRAME_SET == (frames_bitmap[idx] & (0x1 << off))) {
        return false;
    } else {
        return true;
    }
}

static ptr_t
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

    KERNEL_PANIC("No free frame avaliale now.\n");
    return 0;
}

static void
frame_allocate(struct page_entry *page, bool kernel, bool write)
{
    ptr_t frame;

    assert_k(NULL != page);

    if (FRAME_CLEAR == page->frame) {
        frame = frame_first();
        frame_set(frame);

        page->present = BIT_SET;
        page->rw = write ? BIT_SET : BIT_CLEAR;
        page->user = kernel ? BIT_SET : BIT_CLEAR;
        page->frame = frame;
    }
}

void
frame_free(struct page_entry *page)
{
    ptr_t frame;

    assert_k(NULL != page);

    frame = page->frame;
    if (frame) {
        frame_clear(frame);
        page->frame = FRAME_CLEAR;
    }
}

