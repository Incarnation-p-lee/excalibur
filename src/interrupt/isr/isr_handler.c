void
isr_handler_main(struct pro_context context)
{
    print_string("Recieved Interrupt: ");
    print_uint32(context.int_nmbr);
    print_string(".\n");
}

void
isr_handler_register(uint8 nmbr, isr_handler_t handler)
{
    interrupt_handler[nmbr] = handler;
}

