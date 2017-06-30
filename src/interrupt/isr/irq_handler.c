static inline uint32
irq_handler_nmbr_isr_to_irq(uint32 isr_nmbr)
{
    kassert(isr_nmbr >= IRQ_BASE);

    return isr_nmbr - IRQ_BASE;
}

static inline void
irq_0_timer_handler(s_pro_context_t *context)
{
    tick++;

    if (false) {
        printf_vga_tk("Triggered Time Tick -> eip %x.\n", context->eip);
    }
}

static inline void
irq_1_keyboard_handler(s_pro_context_t *context)
{
    if (false) {
        printf_vga_tk("Triggered keyboard -> eip %x.\n", context->eip);
    }
}

static inline void
irq_7_handler(s_pro_context_t *context)
{
    if (false) {
        printf_vga_tk("pli28 triggered irq 7 -> eip %x esp %x\n", context->eip);
    }
}

void
irq_0_timer_initialize(uint32 freq)
{
    uint32 divisor;
    uint8 low;
    uint8 high;

    if (0 == freq) {
        freq = IRQ_0_DIVISOR;
    }

    divisor = IRQ_0_TIMER_FREQ / freq;
    low = (uint8)(divisor & 0xFF);
    high = (uint8)((divisor >> 8) & 0xFF);

    io_bus_write_byte(IRQ_0_TIMER_CMD, IRQ_0_TIMER_REPEAT);
    io_bus_write_byte(IRQ_0_TIMER_DATA, low);
    io_bus_write_byte(IRQ_0_TIMER_DATA, high);

    printf_vga_tk("IRQ timer initialized.\n");
}

uint32
irq_0_timer_tick(void)
{
    return tick;
}

void
irq_handler_main(s_pro_context_t context)
{
    uint32 irq_nmbr;
    uint32 isr_nmbr;
    isr_handler_t handler;

    isr_nmbr = context.int_nmbr;
    irq_nmbr = irq_handler_nmbr_isr_to_irq(isr_nmbr);
    handler = isr_handler_array[isr_nmbr];

    pic_send_eoi(irq_nmbr);

    if (handler) {
        handler(&context);
    } else {
        printf_vga_tk("Unsupported irq %d within isr %d\n", irq_nmbr, isr_nmbr);
        KERNEL_PANIC("Unsupported IRQ\n");
    }
}

