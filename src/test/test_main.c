static inline void
test_isr(void)
{
    printf_vga_tk("Test isr:\n");

    asm volatile (
        "int $0x0\n\t"
        "int $0x3\n\t"
        "int $0x0\n\t");

    printf_vga_tk("Test isr ................ OK.\n");
}

static inline void
test_page(void)
{
    uint32 tmp;
    uint32 *ptr;

    printf_vga_tk("Test page:\n");

    ptr = (void *)&end;
    tmp = *ptr;
    printf_vga_tk("    Access address %x, value %x.\n", ptr, tmp);

    ptr = (void *)KHEAP_START;
    tmp = *ptr;
    printf_vga_tk("    Access address %x, value %x.\n", ptr, tmp);

    printf_vga_tk("Test page ............... OK.\n");
}

static inline void
test_heap(void)
{
    uint32 *p_a, *p_b, *p_c;

    printf_vga_tk("Test heap:\n");

    p_a = kmalloc(8);
    p_b = kmalloc(8);
    printf_vga_tk("    Allocate 8 bytes at %x.\n", p_a);
    printf_vga_tk("    Allocate 8 bytes at %x.\n", p_b);

    kfree(p_a);
    kfree(p_b);
    printf_vga_tk("    Free %x.\n", p_a);
    printf_vga_tk("    Free %x.\n", p_b);

    p_c = kmalloc(16);
    printf_vga_tk("    Allocate 16 bytes at %x.\n", p_c);

    kfree(p_c);
    printf_vga_tk("    Free %x.\n", p_c);

    printf_vga_tk("Test heap ............... OK.\n");
}

void
test_main(void)
{
    test_isr();
    test_page();
    test_heap();
}

