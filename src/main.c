#include "common.h"

int
entry(uint32 magic, void *boot_header, void *boot_info)
{
    printf_vga_clear();
    printf_vga_tk("Hello, OS Development.\n");

    multiboot_env_detect(magic, boot_header, boot_info);

    gdt_initialize();
    idt_initialize();
    timer_initialize(1000);
    page_initialize();
    kernel_heap_initialize();
    block_initialize();
    vfs_initialize();

    // test_main();

    printf_vga_tk("Reach end of entry, will idle.\n");
    print_buffer_fs_initrd_write();

    return 0x0;
}

