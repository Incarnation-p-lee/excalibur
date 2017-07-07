#ifndef HAVE_DEFINED_MEMORY_PHYSICAL_H
#define HAVE_DEFINED_MEMORY_PHYSICAL_H

/*
 * Memory Layout
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
 * |  Kernel heap   |
 * +----------------+
 * |  Page dirt     |
 * |  Page table    |
 * +----------------+ <- after all done, placement_phys stay here
 * |                | All physical memory related end here too.
 * |                |
 * |                |
 * |                |
 * |                |
 * |                |
 * +----------------+ <- 0xC0000000 heap start address, virtual memory.
 * |                |
 * |                |
 * |                |
 * +----------------+ <- 0xCFFFF000 heap start address max.
 */

struct frame_bitmap {
    ptr_t  *bitmap;
    uint32 size;
    uint32 frame_limit;
};

static ptr_t placement_phys = 0;

static s_frame_bitmap_t *frame_bitmap;

#endif

