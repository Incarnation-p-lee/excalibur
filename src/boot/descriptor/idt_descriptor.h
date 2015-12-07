#ifndef HAVE_DEFINED_IDT_DESCRIPTOR_H
#define HAVE_DEFINED_IDT_DESCRIPTOR_H

/*
 * Interrupt Descriptor Table Register
 * 47                         16 15                 0
 * +----------------------------+-------------------+
 * | 32-bit Linear Base Address | 16-bit Table Limit|
 * +----------------------------+-------------------+
 */
struct idt_register {
    uint16 limit;
    uint32 base;
} __attribute__((packed));



/*
 * Descriptor Attribute
 *   7  6   5  4  3     0 7                  0
 * +---+-----+---+------+ +------------------+
 * | P | DPL | S | type | | unused, always 0 |
 * +---+-----+---+------+ +------------------+
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
 * +-----------+-----------+----------+----------+
 * | base high | attribute | selector | base low |
 * +-----------+-----------+----------+----------+
 */
struct idt_entry {
    uint16 base_l;
    uint16 selector;
    struct idt_attribute attr;
    uint16 base_h;
} __attribute__((packed));

#define IDT_ENTRY_CNT     256

#define IDT_ATTR_TYPE_IDX 8
#define IDT_ATTR_TYPE_LEN 4
#define IDT_ATTR_S_IDX    12
#define IDT_ATTR_DPL_IDX  13
#define IDT_ATTR_DPL_LEN  2
#define IDT_ATTR_P_IDX    15

#endif

