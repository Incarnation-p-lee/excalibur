#include "external.h"

int
main(void)
{
    descriptor_table_init();

    screen_monitor_clear();
    screen_monitor_write("Hello, The world of OS\n");

    asm volatile (
        "int $0x0\n\t"
        "int $0x1\n\t"
        "int $0x2\n\t"
        "int $0x3\n\t"
        "int $0x4\n\t");

    return 0xdeadbaba;
}

