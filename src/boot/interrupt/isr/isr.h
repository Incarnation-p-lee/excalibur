#ifndef HAVE_DEFINED_ISR_H
#define HAVE_DEFINED_ISR_H

struct pro_context {
    uint32 gs;
    uint32 fs;
    uint32 es;
    uint32 ds;

    uint32 edi;
    uint32 esi;
    uint32 ebp;
    uint32 esp;
    uint32 ebx;
    uint32 edx;
    uint32 ecx;
    uint32 eax;
    uint32 int_nmbr;
    uint32 err_code;

    uint32 eip;
    uint32 cs;
    uint32 eflags;
    uint32 usr_esp;
    uint32 ss;
} __attribute__((packed));

#endif

