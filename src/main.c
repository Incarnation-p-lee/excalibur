#include "external.h"
#include "define.h"

int
main(void)
{
    print_clear();
    print_string("Hello, The world of OS.\n");

    descriptor_table_init();
    print_string("GDT & IDT table initialized.\n");

    asm volatile (
        "int $0x0\n\t"
        "int $0x1\n\t"
        "int $0x2\n\t"
        "int $0x3\n\t"
        "int $0x4\n\t");

    return 0xdeadbaba;
}

