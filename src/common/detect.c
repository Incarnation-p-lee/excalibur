static inline void
detect_cpu_mode(void)
{
    uint32 cr0;

    asm volatile (
        "mov %%cr0, %%eax\n\t"
        "mov %%eax, %0\n\t"
        :"=r"(cr0)
        :);

    if (cr0 & 0x1) {
        printf_vga_tk("In Protect Mode.\n");
    } else {
        printf_vga_tk("In Real Mode.\n");
    }

    if (U32_BIT(cr0, 31) == 1) {
        printf_vga_tk("Pagine enabled.\n");
    } else {
        printf_vga_tk("Pagine disabled.\n");
    }
}

static inline void
detect_stack_base(void)
{
    uint32 esp;

    asm volatile (
        "mov %%esp, %0\n\t"
        :"=r"(esp)
        :);

    printf_vga_tk("Stack base %x.\n", esp);
}

static inline void
detect_multiboot_data(s_multiboot_header_t *header, s_multiboot_info_t *info)
{
    uint32 memory_lower;
    uint32 memory_upper;

    kassert(header);
    kassert(info);

    multiboot_data_header_initialize(header);
    multiboot_data_info_initialize(info);

    memory_lower = multiboot_data_info_physical_memory_lower();
    memory_upper = multiboot_data_info_physical_memory_upper();

    printf_vga_tk("Physical memory lower -> %d KB.\n", memory_lower);
    printf_vga_tk("Physical memory upper -> %d KB.\n", memory_upper);
}

void
detect_boot_up_env(uint32 magic, void *boot_header, void *boot_info)
{
    printf_vga_tk("Boot loader magic -> %x.\n", magic);

    detect_cpu_mode();
    detect_stack_base();

    if (boot_header && boot_info) {
        detect_multiboot_data(boot_header, boot_info);
    }
}

