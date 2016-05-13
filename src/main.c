#include "common.h"

static inline void
test_idt_setup(void)
{
    asm volatile (
        "int $0x0\n\t"
        "int $0x1\n\t"
        "int $0x2\n\t"
        "int $0x3\n\t"
        "int $0x4\n\t");
}

static inline void
test_paging(void)
{


}

int
main(void)
{
    printf_vga_clear();
    printf_vga_ts("Hello, The World of OS.\n");

    descriptor_table_gdt_init();
    descriptor_table_idt_init();
    irq_0_timer_init(1000);

    test_idt_setup();
    test_paging();

    return 0xdeadbeaf;
}

