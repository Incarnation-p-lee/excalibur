#include "common.h"

static inline void
test_idt_setup(void)
{
    asm volatile (
        "int $0x0\n\t"
        "int $0x3\n\t"
        "int $0x0\n\t");
}

static inline void
test_paging(void)
{
    uint32 *ptr;

    // ptr = (void *)0x800000;
    // *ptr = 0xdeadbeaf;
    ptr = (void *)0x4ffffffc;
    *ptr = 0xdeadbeaf;
}

static inline void
entry_initialize(void)
{
    descriptor_table_gdt_initialize();
    descriptor_table_idt_initialize();
    irq_0_timer_initialize(1000);

    page_initialize();

    uint32 *p;
    // 0x50000000 limit, 4ffffffc will trigger page fault
    // 1280 MB
    // p = (void *)0x4ffffffc;
    p = (void *)0x50000000;
    *p = 0xa;
    printf_vga_tk("pli28 heap memory touched\n");
    kernel_heap_initialize();
}

int
entry(uint32 magic, void *boot_header, void *boot_info)
{
    printf_vga_clear();
    printf_vga_tk("Hello, The World of OS.\n");

    multiboot_env_detect(magic, boot_header, boot_info);
    entry_initialize();

    test_idt_setup();

    test_paging();

    printf_vga_tk("Reach end of entry, will idle.\n");

    return 0x0;
}

