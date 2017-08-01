void
irq_14_ata_channel_primary(s_pro_context_t *context)
{
    kassert(context);

    printf_vga_tk("Triggered ATA primary channel -> eip %x.\n", context->eip);
}

