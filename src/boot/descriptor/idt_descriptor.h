#ifndef HAVE_DEFINED_IDT_DESCRIPTOR_H
#define HAVE_DEFINED_IDT_DESCRIPTOR_H

/*
 * Interrupt Descriptor Table Register
 * 47                         16 15                 0
 * --------------------------------------------------
 * | 32-bit Linear Base Address | 16-bit Table Limit|
 * --------------------------------------------------
 */
struct idt_register {
    uint16 limit;
    uint32 base;
} __attribute__((packed));



/*
 * Descriptor Attribute
 *   7  6   5  4  3     0 7                  0
 * ---------------------- --------------------
 * | P | DPL | S | type | | unused, always 0 |
 * ---------------------- --------------------
 */
struct idt_attribute {
    uint8 unused;
    uint8 type:4;
    uint8 s:1;
    uint8 dpl:2;
    uint8 p:1;
} __attribute__((packed));


/*
 * Interrupt Descriptor Table Entry
 * Each represent a segment in GDT.
 * 63           47          31        15         0
 * -----------------------------------------------
 * | base high | attribute | selector | base low |
 * -----------------------------------------------
 */
struct idt_entry {
    uint16 base_l;
    uint16 selector;
    struct idt_attribute attr;
    uint16 base_h;
} __attribute__((packed));

#define IDT_CODE_SEL      0x8
#define IDT_ENTRY_CNT     256

#define IDT_ATTR_TYPE_IDX 8
#define IDT_ATTR_TYPE_LEN 4
#define IDT_ATTR_S_IDX    12
#define IDT_ATTR_DPL_IDX  13
#define IDT_ATTR_DPL_LEN  2
#define IDT_ATTR_P_IDX    15

#define ATTR_TYPE_TASK_32 (0x5 << IDT_ATTR_TYPE_IDX)
#define ATTR_TYPE_INTR_16 (0x6 << IDT_ATTR_TYPE_IDX)
#define ATTR_TYPE_TRAP_16 (0x7 << IDT_ATTR_TYPE_IDX)
#define ATTR_TYPE_INTR_32 (0xe << IDT_ATTR_TYPE_IDX)
#define ATTR_TYPE_TRAP_32 (0xf << IDT_ATTR_TYPE_IDX)
#define ATTR_STOR_SEG     (ATTR_CLR << IDT_ATTR_S_IDX)
#define ATTR_DPL_RING_0   (DPL_RING_0 << IDT_ATTR_DPL_IDX)
#define ATTR_DPL_RING_1   (DPL_RING_1 << IDT_ATTR_DPL_IDX)
#define ATTR_DPL_RING_2   (DPL_RING_2 << IDT_ATTR_DPL_IDX)
#define ATTR_DPL_RING_3   (DPL_RING_3 << IDT_ATTR_DPL_IDX)
#define ATTR_PRST         (ATTR_SET << IDT_ATTR_P_IDX)

#define ATTR_INT_32       (ATTR_TYPE_INTR_32 | ATTR_PRST)

static struct idt_entry    idt_entry_list[IDT_ENTRY_CNT];
static struct idt_register idt_reg;

extern void idt_table_flush(uint32);

/*
 * When processor receives an interrupt, it saves contents of registers to
 * the stack, then find the interrupt handler location and jump to it.
 */
extern void isr_handler_0(void);
extern void isr_handler_1(void);
extern void isr_handler_2(void);
extern void isr_handler_3(void);
extern void isr_handler_4(void);
extern void isr_handler_5(void);
extern void isr_handler_6(void);
extern void isr_handler_7(void);
extern void isr_handler_8(void);
extern void isr_handler_9(void);
extern void isr_handler_10(void);
extern void isr_handler_11(void);
extern void isr_handler_12(void);
extern void isr_handler_13(void);
extern void isr_handler_14(void);
extern void isr_handler_15(void);
extern void isr_handler_16(void);
extern void isr_handler_17(void);
extern void isr_handler_18(void);
extern void isr_handler_19(void);
extern void isr_handler_20(void);
extern void isr_handler_21(void);
extern void isr_handler_22(void);
extern void isr_handler_23(void);
extern void isr_handler_24(void);
extern void isr_handler_25(void);
extern void isr_handler_26(void);
extern void isr_handler_27(void);
extern void isr_handler_28(void);
extern void isr_handler_29(void);
extern void isr_handler_30(void);
extern void isr_handler_31(void);

static void (*isr_handler[])(void) = {
    &isr_handler_0,
    &isr_handler_1,
    &isr_handler_2,
    &isr_handler_3,
    &isr_handler_4,
    &isr_handler_5,
    &isr_handler_6,
    &isr_handler_7,
    &isr_handler_8,
    &isr_handler_9,
    &isr_handler_10,
    &isr_handler_11,
    &isr_handler_12,
    &isr_handler_13,
    &isr_handler_14,
    &isr_handler_15,
    &isr_handler_16,
    &isr_handler_17,
    &isr_handler_18,
    &isr_handler_19,
    &isr_handler_20,
    &isr_handler_21,
    &isr_handler_22,
    &isr_handler_23,
    &isr_handler_24,
    &isr_handler_25,
    &isr_handler_26,
    &isr_handler_27,
    &isr_handler_28,
    &isr_handler_29,
    &isr_handler_30,
    &isr_handler_31,
};

#endif

