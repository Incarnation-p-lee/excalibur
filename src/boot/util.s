[GLOBAL gdt_table_flush]
gdt_table_flush:
    mov        eax, [esp + 4]
    lgdt       [eax]

    mov        ax, 0x10      ; data segment selector
    mov        ds, ax
    mov        es, ax
    mov        fs, ax
    mov        gs, ax
    mov        ss, ax

    jmp        0x8: .flush   ; will change cs register implicitly
.flush:
    ret

[GLOBAL idt_table_flush]
idt_table_flush:
    mov        eax, [esp + 4]
    lidt       [eax]
    ret

