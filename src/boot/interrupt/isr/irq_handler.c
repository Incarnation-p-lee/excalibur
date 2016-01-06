void
irq_handler_main(struct pro_context context)
{
    isr_handler_t handler;

    pic_send_eoi(context.int_nmbr);

    if (NULL != interrupt_handler[context.int_nmbr]) {
        handler = interrupt_handler[context.int_nmbr];
        handler(context);
    } else {
        print_string("IRQ handler of ISR number: ");
        print_uint32(context.int_nmbr);
        print_string(" is not available.\n");
    }
}

