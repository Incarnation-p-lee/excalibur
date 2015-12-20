#include "external.h"
#include "define.h"

/*
 * From start symbol to main, here has one stack come from grub.
 * but we will setup one new stack at gdt initialize, so we should
 * fake some value in old stack and make sure return fucntion works
 * as expected in C code.
 *
 * call main, pushed 4 byte
 * push %ebp, pushed 4 byte
 * total 8 byte
 *
 * This function implement very closed to main function, and should
 * be call once under main. Any other way invoke this function is
 * illegal to above design.
 */
static inline uint32
stack_obtain_base_address(void)
{
    uint32 base;

    asm volatile (
        "mov %%esp, %0\n\t"
        "add  $0x8, %0\n\t"
        :"=r"(base)
        :);

    return base;
}

int
main(void)
{
    uint32 esp_base;

    esp_base = stack_obtain_base_address();

    print_clear();
    print_string("Hello, The world of OS.\n");

    descriptor_table_gdt_init(esp_base);
    descriptor_table_idt_init();
    print_string("GDT & IDT table initialized.\n");

    asm volatile (
        "int $0x0\n\t"
        "int $0x1\n\t"
        "int $0x2\n\t"
        "int $0x3\n\t"
        "int $0x4\n\t");

    return 0xdeadbaba;
}

