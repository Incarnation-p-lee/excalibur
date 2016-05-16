static void
frame_set(ptr_t frame)
{
    ptr_t idx;
    ptr_t off;

    kassert(sizeof(frame) == sizeof(ptr_t));

    idx = BM_INDEX(frame);
    off = BM_OFFSET(frame);

    frames_bitmap[idx] |= (0x1 << off);
}

// static void
// frame_clear(ptr_t frame)
// {
//     ptr_t idx;
//     ptr_t off;
// 
//     kassert(sizeof(frame) == sizeof(ptr_t));
// 
//     idx = BM_INDEX(frame);
//     off = BM_OFFSET(frame);
// 
//     frames_bitmap[idx] &= ~(0x1 << off);
// }

bool
frame_available_p(ptr_t frame)
{
    ptr_t idx;
    ptr_t off;

    kassert(sizeof(frame) == sizeof(ptr_t));

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
    ptr_t frame;

    i = 0;
    while (i < BM_INDEX(frames_size)) {
        j = 0;
        if ((ptr_t)-1 != frames_bitmap[i]) {
            while (j < sizeof(ptr_t) * 8) {
                if (FRAME_CLEAR == (frames_bitmap[i] & (0x1 << j))) {
                    frame = i * sizeof(ptr_t) * 8 + j;
                    frame_set(frame);
                    return frame;
                }
                j++;
            }
        }
        i++;
    }

    KERNEL_PANIC("No free frame avaliale now.");
    return 0;
}

static void
frame_allocate(struct page_entry *page, bool kernel, bool write)
{
    kassert(NULL != page);

    if (FRAME_CLEAR == page->frame) {

        page->present = BIT_SET;
        page->rw = write ? BIT_SET : BIT_CLEAR;
        page->user = kernel ? BIT_SET : BIT_CLEAR;
        page->frame = frame_first();
    }
}

// static void
// frame_free(struct page_entry *page)
// {
//     ptr_t frame;
// 
//     kassert(NULL != page);
// 
//     frame = page->frame;
//     if (frame) {
//         frame_clear(frame);
//         page->frame = FRAME_CLEAR;
//     }
// }

