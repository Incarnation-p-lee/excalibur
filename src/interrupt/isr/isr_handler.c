void
isr_handler_main(struct pro_context context)
{
    enum interrupt_num int_nmbr;

    int_nmbr = context.int_nmbr;
    printf_vga("Recieved ISR: %x.\n", int_nmbr);

    switch (int_nmbr) {
        case DIV_BY_Z:
            isr_handler_0_divide_by_zero(context);
            break;
        case BRK_EXPT:
            isr_handler_3_breakpoint(context);
            break;
        case PAGE_FAL:
            isr_handler_14_paging_fault(context);
            break;
        case GNL_PRTT_FAL:
            break;
        default:
            break;
    }

}

void
isr_handler_register(uint8 nmbr, isr_handler_t handler)
{
    interrupt_handler[nmbr] = handler;
}

static inline void
isr_handler_0_divide_by_zero(struct pro_context context)
{
    printf_vga("Triggered Divide by zero exception at eip: %x\n", context.eip);
}

static inline void
isr_handler_3_breakpoint(struct pro_context context)
{
    printf_vga("Triggered Breakpoint exception at eip: %x\n", context.eip);
}

static inline void
isr_handler_14_paging_fault(struct pro_context context)
{
    ptr_t fault_addr;
    uint32 err_code;

    asm volatile (
        "mov %%cr2, %0\n\t"
        :"=r"(fault_addr));

    err_code = context.err_code;

    if (!(err_code & PAGE_FAULT_PRST)) {
        printf_vga("Page is not present.\n");
    }

    if (err_code & PAGE_FAULT_WRITE) {
        printf_vga("Page is Read-Only.\n");
    }

    if (err_code & PAGE_FAULT_USER) {
        printf_vga("Page is in User-Mode.\n");
    }

    if (err_code & PAGE_FAULT_RSVD) {
        printf_vga("Page overwritten reserved.\n");
    }

    if (err_code & PAGE_FAULT_FETCH) {
        printf_vga("Page in instruction fetch.\n");
    }

    printf_vga("Page Fault at address %x.\n", fault_addr);
    KERNEL_PANIC("Page Fault");
}


