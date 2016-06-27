uint32
detect_physical_memory_size(void)
{
    uint32 memory;

    asm volatile (
        "mov %%cr0, %%eax\n\t"
        "mov %%eax, %0\n\t"
        :"=r"(memory)
        :);

    if (memory & 0x1) {
        printf_vga_ts("In Protect Mode.\n");
    } else {
        printf_vga_ts("In Real Mode.\n");
    }

    return memory;
}

