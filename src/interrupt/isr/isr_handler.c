void
isr_handler_main(struct pro_context context)
{
    enum interrupt_num int_nmbr;

    int_nmbr = context.int_nmbr;

    printf_vga("Recieved Interrupt: %x.\n", int_nmbr);

    switch (int_nmbr) {
        case DIV_BY_Z:
            isr_handler_0_divide_by_zero(context);
            break;
        case BRK_EXPT:
            isr_handler_3_breakpoint(context);
            break;
        case PAGE_FAL:
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

void
isr_handler_14_page_fault(struct pro_context context)
{


}

