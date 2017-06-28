#ifndef HAVE_DEFINED_MEMORY_PHYSICAL_H
#define HAVE_DEFINED_MEMORY_PHYSICAL_H

/*
 * Physical memory layout before paging
 *
 * +----------------+ <- address 0x0
 * |  Real Mode     |
 * |  Boot Loader   |
 * +----------------+ <- 1M
 * |                |
 * |  OS image      |
 * |                |
 * +----------------+ <- end
 * |  Frame bitmap  |
 * +----------------+
 * |  Page dirt     |
 * |  Page table    |
 * +----------------+ <- after all done, placement_phys stay here.
 * |                |
 * |                |
 */

struct frame_bitmap {
    ptr_t  *bitmap;
    uint32 size;
    uint32 frame_limit;
};

static ptr_t placement_phys = (ptr_t)&end;

static s_frame_bitmap_t *frame_bitmap;

#endif

