#ifndef HAVE_DEFINED_KERNEL_HEAP_INTERNAL_H
#define HAVE_DEFINED_KERNEL_HEAP_INTERNAL_H

#define KHEAP_HOLE_COUNT        0x10000
#define KHEAP_INITIAL_SIZE      0x400000 /* 4 MB */
#define KHEAP_MAGIC             0xA5A55A5A

#define KHEAP_HEADER_SIZE       sizeof(s_kernel_heap_header_t)
#define KHEAP_FOOTER_SIZE       sizeof(s_kernel_heap_footer_t)
#define KHEAP_INFO_SIZE         (KHEAP_HEADER_SIZE + KHEAP_FOOTER_SIZE)
#define KHEAP_USER_MIN_SIZE     sizeof(ptr_t)
#define KHEAP_HOLE_MIN_SIZE     (KHEAP_USER_MIN_SIZE + KHEAP_INFO_SIZE)

#define KHEAP_HOLE_SIZE(s)      ((s) + KHEAP_INFO_SIZE)
#define KHEAP_USER_TO_HEADER(u) (void *)((ptr_t)(u) - (ptr_t)KHEAP_HEADER_SIZE)

static s_kernel_heap_t *kernel_heap = NULL;

#endif

