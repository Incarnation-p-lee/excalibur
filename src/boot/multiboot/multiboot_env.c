void
multiboot_env_cpu_detect(void)
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

    if (U32_BIT_GET(cr0, 31) == 1) {
        printf_vga_tk("Page enabled.\n");
    } else {
        printf_vga_tk("Page disabled.\n");
    }
}

static inline void
multiboot_env_stack_detect(void)
{
    uint32 esp;

    asm volatile (
        "mov %%esp, %0\n\t"
        :"=r"(esp)
        :);

    printf_vga_tk("Stack base %x.\n", esp);
}

static inline void
multiboot_env_os_image_detect(void)
{
    ptr_t image_start, image_end;

    image_start = (ptr_t)&boot;
    image_end = (ptr_t)&end;

    printf_vga_tk("OS image load: %x -> %x.\n", image_start, image_end);
}

static inline void
multiboot_data_initialize(void)
{
    multiboot_data.valid_mask = 0u;
}

static inline void
multiboot_env_data_detect_physical_memory(void)
{
    uint32 memory_lower;
    uint32 memory_upper;

    memory_lower = multiboot_data_info_physical_memory_lower();
    memory_upper = multiboot_data_info_physical_memory_upper();

    printf_vga_tk("Physical memory %d KB -> %d KB.\n", memory_lower, memory_upper);
}

static inline void
multiboot_env_data_detect_boot_modules(void)
{
    uint32 i;
    uint32 limit;
    s_boot_module_t *module;

    kassert(multiboot_data_info_flag_enabled_p(MULTIBOOT_FLAG_MODS));

    i = 0;
    limit = multiboot_data_info_boot_modules_count_i();

    while (i < limit) {
        module = multiboot_data_info_boot_module(i);
        printf_vga_tk("Multi-Boot module %d -> %s.\n", i, module->string);

        i++;
    }
}

static inline void
multiboot_env_data_detect(s_multiboot_header_t *header, s_multiboot_info_t *info)
{
    kassert(header);
    kassert(info);

    multiboot_data_initialize();
    multiboot_data_header_initialize(header);
    multiboot_data_info_initialize(info);

    multiboot_env_data_detect_physical_memory();
    multiboot_env_data_detect_boot_modules();
}

void
multiboot_env_detect(uint32 magic, void *boot_header, void *boot_info)
{
    printf_vga_tk("Boot loader magic -> %x.\n", magic);

    multiboot_env_cpu_detect();
    multiboot_env_os_image_detect();
    multiboot_env_stack_detect();

    if (boot_header && boot_info) {
        multiboot_env_data_detect(boot_header, boot_info);
    }

    memory_physical_placement_set(multiboot_data_info_end_address());
}

