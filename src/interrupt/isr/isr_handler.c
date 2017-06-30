void
isr_handler_main(s_pro_context_t context)
{
    isr_handler_t handler;
    e_interrupt_nmbr_t int_nmbr;

    int_nmbr = context.int_nmbr;
    handler = isr_handler_array[int_nmbr];

    if (handler) {
        handler(&context);
    } else {
        printf_vga_tk("Unsupported isq %d -> %x.\n", int_nmbr, context.eip);
        KERNEL_PANIC("Unsupported ISR\n");
    }
}

static inline void
isr_0_divide_by_zero_handler(s_pro_context_t *context)
{
    printf_vga_tk("    Divide by zero at eip -> %x.\n", context->eip);
}

static inline void
isr_3_breakpoint_handler(s_pro_context_t *context)
{
    printf_vga_tk("    Breakpoint at eip -> %x.\n", context->eip);
}

static inline void
isr_6_invalid_opcode_handler(s_pro_context_t *context)
{
    printf_vga_tk("Invalid opcode at eip -> %x.\n", context->eip);
    KERNEL_PANIC("invlid opcoden\n");
}

static inline void
isr_12_stack_fault_handler(s_pro_context_t *context)
{
    printf_vga_tk("Stack fault at eip -> %x.\n", context->eip);
}

static inline void
isr_14_paging_fault_handler(s_pro_context_t *context)
{
    uint32 err_code;
    ptr_t fault_addr;

    printf_vga_tk("Page fault triggered -> %x.\n", context->eip);

    asm volatile (
        "mov %%cr2, %0\n\t"
        :"=r"(fault_addr));

    err_code = context->err_code;

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

