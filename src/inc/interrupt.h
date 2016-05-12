#ifndef HAVE_DEFINED_INTERRUPT_H
#define HAVE_DEFINED_INTERRUPT_H

enum interrupt_num {
    DIV_BY_Z,     //   0 Division by zero exception
    DBG_EXPT,     //   1 Debug exception
    NON_MSK_INT,  //   2 Non maskable interrupt
    BRK_EXPT,     //   3 Breakpoint exception
    DTT_OF,       //   4 Into detected overflow
    OF_BND_EXPT,  //   5 Out of bounds exception
    INV_OPC_EXPT, //   6 Invalid opcode exception
    NO_CP_EXPT,   //   7 No coprocessor exception
    DBL_FAL,      //   8 Double fault (pushes an error code)
    CP_SEG_OR,    //   9 Coprocessor segment overrun
    BD_TSS,       //  10 Bad TSS (pushes an error code)
    SEG_NO_PRST,  //  11 Segment not present (pushes an error code)
    STK_FAL,      //  12 Stack fault (pushes an error code)
    GNL_PRTT_FAL, //  13 General protection fault (pushes an error code)
    PAGE_FAL,     //  14 Page fault (pushes an error code)
    UKN_INT_EXPT, //  15 Unknown interrupt exception
    CP_FAL,       //  16 Coprocessor fault
    AGN_CHK_EXPT, //  17 Alignment check exception
    MAH_CHK_EXPT, //  18 Machine check exception
};

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
    uint32 err_code;
    uint32 int_nmbr;

    uint32 eip;
    uint32 cs;
    uint32 eflags;
    uint32 usr_esp;
    uint32 ss;
} __attribute__((packed));

#endif

