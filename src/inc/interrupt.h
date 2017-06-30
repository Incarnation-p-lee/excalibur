#ifndef HAVE_DEFINED_INTERRUPT_H
#define HAVE_DEFINED_INTERRUPT_H

typedef enum interrupt_nmbr e_interrupt_nmbr_t;
typedef struct pro_context  s_pro_context_t;

enum interrupt_nmbr { /* for ISR (interrupt service runtine */
    DIV_BY_Z,     /*   0 Division by zero exception */
    DBG_EXPT,     /*   1 Debug exception */
    NON_MSK_INT,  /*   2 Non maskable interrupt */
    BRK_EXPT,     /*   3 Breakpoint exception */
    DTT_OF,       /*   4 Into detected overflow */
    OF_BND_EXPT,  /*   5 Out of bounds exception */
    INV_OPC_EXPT, /*   6 Invalid opcode exception */
    NO_CP_EXPT,   /*   7 No coprocessor exception */
    DBL_FAL,      /*   8 Double fault (pushes an error code) */
    CP_SEG_OR,    /*   9 Coprocessor segment overrun */
    BD_TSS,       /*  10 Bad TSS (pushes an error code) */
    SEG_NO_PRST,  /*  11 Segment not present (pushes an error code) */
    STK_FAL,      /*  12 Stack fault (pushes an error code) */
    GNL_PRTT_FAL, /*  13 General protection fault (pushes an error code) */
    PAGE_FAL,     /*  14 Page fault (pushes an error code) */
    UKN_INT_EXPT, /*  15 Unknown interrupt exception */
    CP_FAL,       /*  16 Coprocessor fault */
    AGN_CHK_EXPT, /*  17 Alignment check exception */
    MAH_CHK_EXPT, /*  18 Machine check exception */
    PLACEHOLDER_19,
    PLACEHOLDER_20,
    PLACEHOLDER_21,
    PLACEHOLDER_22,
    PLACEHOLDER_23,
    PLACEHOLDER_24,
    PLACEHOLDER_25,
    PLACEHOLDER_26,
    PLACEHOLDER_27,
    PLACEHOLDER_28,
    PLACEHOLDER_29,
    PLACEHOLDER_30,
    PLACEHOLDER_31,
    IRQ_0_TIMER,  /*  32 timer */
    IRQ_1_KEYBOARD,
    IRQ_2_PS,
    IRQ_3_PS,
    IRQ_4_PS,
    IRQ_5_PS,
    IRQ_6_PS,
    IRQ_7_PS,
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
    uint32 int_nmbr;
    uint32 err_code;

    uint32 eip;
    uint32 cs;
    uint32 eflags;
    uint32 usr_esp;
    uint32 ss;
} __attribute__((packed));

#define PAGE_FAULT_PRST        0x1
#define PAGE_FAULT_WRITE       0x2
#define PAGE_FAULT_USER        0x4
#define PAGE_FAULT_RSVD        0x8
#define PAGE_FAULT_FETCH       0x10

#define IRQ_BASE           32
#define IRQ_0              IRQ_BASE
#define IRQ_1              33
#define IRQ_2              34
#define IRQ_3              35
#define IRQ_4              36
#define IRQ_5              37
#define IRQ_6              38
#define IRQ_7              39
#define IRQ_8              40
#define IRQ_9              41
#define IRQ_10             42
#define IRQ_11             43
#define IRQ_12             44
#define IRQ_13             45
#define IRQ_14             46
#define IRQ_15             47

#define INT_HANDLER_CNT    256
#define IRQ_0_TIMER_FREQ   1193180
#define IRQ_0_DIVISOR      1000
#define IRQ_0_TIMER_CMD    0x43
#define IRQ_0_TIMER_DATA   0x40
#define IRQ_0_TIMER_REPEAT 0x36

#endif

