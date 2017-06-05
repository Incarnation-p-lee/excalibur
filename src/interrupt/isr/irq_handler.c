static uint32 tick = 0;

void
irq_handler_main(s_pro_context_t context)
{
    isr_handler_t handler;
    uint32 irq_nmbr;

    irq_nmbr = context.int_nmbr - IRQ_BASE;
    pic_send_eoi(irq_nmbr);

    if (NULL != interrupt_handler[context.int_nmbr]) {
        handler = interrupt_handler[context.int_nmbr];
        handler(context);
    }
}

static inline void
irq_0_timer_callback(s_pro_context_t context)
{
    tick++;
    printf_vga("Context address %x\n", context);
    printf_vga("Timer-Tick: %x\r", tick);
}

void
irq_0_timer_init(uint32 freq)
{
    uint32 divisor;
    uint8 low;
    uint8 high;

    isr_handler_register(IRQ_0, &irq_0_timer_callback);

    if (0 == freq) {
        freq = IRQ_0_DIVISOR;
    }

    divisor = IRQ_0_TIMER_FREQ / freq;
    low = (uint8)(divisor & 0xFF);
    high = (uint8)((divisor >> 8) & 0xFF);

    io_bus_write_byte(IRQ_0_TIMER_CMD, IRQ_0_TIMER_REPEAT);
    io_bus_write_byte(IRQ_0_TIMER_DATA, low);
    io_bus_write_byte(IRQ_0_TIMER_DATA, high);

    printf_vga_ts("IRQ timer initialized.\n");
}

