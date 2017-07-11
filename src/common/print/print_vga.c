void
printf_vga(char *format, ...)
{
    void *param;

    if (format && ('\0' != *format)) {
        param = (void *)&format + sizeof(format);
        print_format(format, param);
    }
}

void
printf_vga_tk(char *format, ...)
{
    void *param;

    if (format && ('\0' != *format)) {
        printf_vga("[%x] ", irq_0_timer_tick());

        param = (void *)&format + sizeof(format);
        print_format(format, param);
    }
}

