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
    uint32 size;
    uint32 *p_a, *p_b, *p_c;

    printf_vga_tk("Test heap:\n");

    size = 8;

    p_a = kmalloc(size);
    p_b = kmalloc(size);
    printf_vga_tk("    Allocate %x bytes at %x.\n", size, p_a);
    printf_vga_tk("    Allocate %x bytes at %x.\n", size, p_b);
    kfree(p_a);
    kfree(p_b);
    printf_vga_tk("    Free %x.\n", p_a);
    printf_vga_tk("    Free %x.\n", p_b);

    size = 0xf;

    p_c = kmalloc(size);
    printf_vga_tk("    Allocate %x bytes at %x.\n", size, p_c);
    kfree(p_c);
    printf_vga_tk("    Free %x.\n", p_c);

    size = 0x400000;

    p_a = kmalloc(0x400000);
    printf_vga_tk("    Allocate %x bytes at %x.\n", size, p_a);
    kfree(p_a);
    printf_vga_tk("    Free %x.\n", p_a);

    printf_vga_tk("Test heap ............... OK.\n");
}

void
test_main(void)
{
    test_isr();
    test_page();
    test_heap();
}

