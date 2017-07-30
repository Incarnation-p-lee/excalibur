void
io_bus_byte_write(uint16 port, uint8 val)
{
    asm volatile (
        "outb %1, %0\n\t"
        :
        :"dN"(port), "a"(val));
    /*
     * N: Constant in range 0 to 255, x86 platform only
     */
}

// To-do refactor write_byte -> byte_write.
void
io_bus_write_word(uint16 port, uint16 val)
{
    asm volatile (
        "outw %1, %0\n\t"
        :
        :"dN"(port), "a"(val));
}

void
io_bus_dword_write(uint16 port, uint32 val)
{
    asm volatile (
        "outl %1, %0\n\t"
        :
        :"dN"(port), "a"(val));
}

uint8
io_bus_byte_read(uint16 port)
{
    uint8 retval;

    asm volatile (
        "inb %1, %0\n\t"
        :"=a"(retval)
        :"dN"(port));

    return retval;
}

uint16
io_bus_read_word(uint16 port)
{
    uint16 retval;

    asm volatile (
        "inw %1, %0\n\t"
        :"=a"(retval)
        :"dN"(port));

    return retval;
}

uint32
io_bus_dword_read(uint16 port)
{
    uint32 retval;

    asm volatile (
        "inl %1, %0\n\t"
        :"=a"(retval)
        :"dN"(port));

    return retval;
}
