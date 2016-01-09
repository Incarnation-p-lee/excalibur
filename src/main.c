#include "external.h"
#include "define.h"

int
main(void)
{
    descriptor_table_gdt_init();
    descriptor_table_idt_init();

    print_clear();
    print_string("GDT & IDT table initialized.\n");

    asm volatile (
        "int $0x0\n\t"
        "int $0x1\n\t"
        "int $0x2\n\t"
        "int $0x3\n\t"
        "int $0x4\n\t");

    irq_0_timer_init(1000);

    return 0xdeadbeaf;
}

