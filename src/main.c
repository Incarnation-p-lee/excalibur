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
    return;
    uint32 *ptr;

    ptr = (void *)0x80000010; // 64 MB
    *ptr = 0xdeadbeaf;
}

int
entry(uint32 magic, void *boot_header, void *boot_info)
{
    printf_vga_clear();
    printf_vga_tk("Hello, The World of OS.\n");
    detect_boot_up_env(magic, boot_header, boot_info);

    descriptor_table_gdt_init();
    descriptor_table_idt_init();
    irq_0_timer_init(1000);
    paging_initialize();

    test_idt_setup();

    test_paging();

    return 0xdeadbeaf;
}

