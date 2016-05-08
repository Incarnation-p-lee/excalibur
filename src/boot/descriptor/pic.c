void
pic_send_eoi(uint8 irq)
{
    assert_k(irq < 16);

    if (irq >= 8) {
        io_bus_write_byte(PIC_SLAVE_CMD, PIC_CMD_EOI);
    }

    io_bus_write_byte(PIC_MASTER_CMD, PIC_CMD_EOI);
}

static inline void
pic_remap(void)
{
    uint8 mask_master;
    uint8 mask_slave;

    // disable maskable interrupt
    asm volatile ("cli\n\t");

    // Save current IRQ mask
    mask_master = io_bus_read_byte(PIC_MASTER_DATA);
    mask_slave = io_bus_read_byte(PIC_SLAVE_DATA);

    // Initialize Master and Slave PIC
    io_bus_write_byte(PIC_MASTER_CMD, PIC_CMD_INIT);
    io_bus_write_byte(PIC_SLAVE_CMD, PIC_CMD_INIT);

    // Set Master and Slave PIC offset
    io_bus_write_byte(PIC_MASTER_DATA, PIC_MASTER_REMAP_OFFSET);
    io_bus_write_byte(PIC_SLAVE_DATA, PIC_SLAVE_REMAP_OFFSET);

    // Tell Master PIC there is a slave PIC at IRQ2
    io_bus_write_byte(PIC_MASTER_DATA, 4);
    // Tell Slave PIC its cascade identity 0x2
    io_bus_write_byte(PIC_SLAVE_DATA, 2);

    io_bus_write_byte(PIC_MASTER_DATA, PIC_8086);
    io_bus_write_byte(PIC_SLAVE_DATA, PIC_8086);

    // Restore saved IRQ mask
    io_bus_write_byte(PIC_MASTER_DATA, mask_master);
    io_bus_write_byte(PIC_SLAVE_DATA, mask_slave);

    // enable maskable interrupt
    asm volatile ("sti\n\t");
}

