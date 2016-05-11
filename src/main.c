#include "external.h"
#include "define.h"

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
    printf_vga("Hello, The World of Operation System.\n");

    descriptor_table_gdt_init();
    descriptor_table_idt_init();
    printf_vga("GDT & IDT table initialized.\n");

    test_idt_setup();
    irq_0_timer_init(1000);

    test_paging();

    return 0xdeadbeaf;
}

