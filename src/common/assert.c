void
assert_complain(const char *msg, const char *file, const char *fun, uint32 line)
{
    printf_vga("Assert expression: %s fail, at function %s:%d\n"
        "    in file %s\n", msg, fun, line, file);
    printf_vga("T.T, Enter Kernel PANIC ...\n");
    asm volatile (
        "infloop:\n\t"
        "jmp infloop\n\t"
        );
}

