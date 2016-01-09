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

typedef void (*isr_handler_t)(struct pro_context);

#define IRQ_0              32
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

static isr_handler_t
interrupt_handler[INT_HANDLER_CNT];

#endif

