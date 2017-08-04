void
io_bus_byte_write(uint16 port, uint8 val)
{
    asm volatile (
        "outb %1, %0\n\t"
        :
        :"d"(port), "a"(val));
}

void
io_bus_write_word(uint16 port, uint16 val)
{
    asm volatile (
        "outw %1, %0\n\t"
        :
        :"d"(port), "a"(val));
}

void
io_bus_dword_write(uint16 port, uint32 val)
{
    asm volatile (
        "outl %1, %0\n\t"
        :
        :"d"(port), "a"(val));
}

uint8
io_bus_byte_read(uint16 port)
{
    uint8 retval;

    asm volatile (
        "inb %1, %0\n\t"
        :"=a"(retval)
        :"d"(port));

    return retval;
}

uint16
io_bus_read_word(uint16 port)
{
    uint16 retval;

    asm volatile (
        "inw %1, %0\n\t"
        :"=a"(retval)
        :"d"(port));

    return retval;
}

uint32
io_bus_dword_read(uint16 port)
{
    uint32 retval;

    asm volatile (
        "inl %1, %0\n\t"
        :"=a"(retval)
        :"d"(port));

    return retval;
}

static inline uint32
io_bus_read_i(uint16 port, void *buf, uint32 size)
{
    char *c;
    uint32 count;
    uint32 reminder;

    kassert(buf);
    kassert(size);

    c = buf;
    count = size / sizeof(uint32);
    reminder = size % sizeof(uint32);
    c += count * sizeof(uint32);

    if (count) {
        asm volatile (
            "cld\n\t"
            "rep\n\t"
            "insl\n\t"
            :
            :"D"(buf), "d"(port), "c"(count));
    }

    while (reminder) {
        *c++ = io_bus_byte_read(port);
        reminder--;
    }

    return size;
}

uint32
io_bus_read(uint16 port, void *buf, uint32 size)
{
    if (buf == NULL) {
        return SIZE_INVALID;
    } else if (size == 0) {
        return SIZE_INVALID;
    } else {
        return io_bus_read_i(port, buf, size);
    }
}

