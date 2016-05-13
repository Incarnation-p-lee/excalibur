bool
assert_complain(const char *msg, const char *file, const char *fun,
    uint32 line, bool exp)
{
    if (!exp) {
        printf_vga("Assertion: %s fail, at function %s:%d in file %s\n",
            msg, fun, line, file);
        printf_vga("Enter Kernel PANIC ... T.T ...\n");
        asm volatile (
            "infloop:\n\t"
            "jmp infloop\n\t"
            );
    }

    return exp;
}

