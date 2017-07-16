bool
assert_complain(const char *msg, const char *file, const char *fun,
    uint32 line, bool exp)
{
    if (!(exp)) {
        printf_vga("Assertion: %s fail.\n  at function %s\n  in file %s:%d\n",
            msg, fun, file, line);
        printf_vga("Enter KERNEL PANIC T.T ...\n");
        asm volatile (
            "infloop:\n\t"
            "hlt\n\t"
            "jmp infloop\n\t"
            );
    }

    return exp;
}

