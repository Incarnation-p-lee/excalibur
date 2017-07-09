#include "common.h"

int
entry(uint32 magic, void *boot_header, void *boot_info)
{
    printf_vga_clear();
    printf_vga_tk("Hello World of OS Development.\n");

    multiboot_env_detect(magic, boot_header, boot_info);

    descriptor_table_gdt_initialize();
    descriptor_table_idt_initialize();

    irq_0_timer_initialize(1000);

    page_initialize();
    kernel_heap_initialize();

    test_main();

    printf_vga_tk("Reach end of entry, will idle.\n");
    return 0x0;
}

