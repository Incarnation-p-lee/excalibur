#ifndef HAVE_DEFINED_GDT_DESCRIPTOR_H
#define HAVE_DEFINED_GDT_DESCRIPTOR_H

typedef struct gdt_entry            s_gdt_entry_t;
typedef struct gdt_register         s_gdt_register_t;
typedef struct gdt_attribute_access s_gdt_attribute_access_t;
typedef struct gdt_attribute_flags  s_gdt_attribute_flags_t;

/*
 * Global Descriptor Table Register
 * 47                         16 15                 0
 * +----------------------------+-------------------+
 * | 32-bit Linear Base Address | 16-bit Table Limit|
 * +----------------------------+-------------------+
 */
struct gdt_register {
    uint16 limit;
    uint32 base;
} __attribute__((packed));

/*
 * Descriptor Attribute
 *  15   14   13   12   11             8  7  6   5   4    3    2    1   0
 * +---+-----+---+-----+----------------+---+-----+----+----+----+----+----+
 * | G | D/B | 0 | AVL | Seg limit high | P | DPL | DT | EX | DC | RW | AC |
 * +---+-----+---+-----+----------------+---+-----+----+----+----+----+----+
 */
struct gdt_attribute_access {
    uint8 acc:1; // Segment has been accessed or not
    uint8 rw:1;  // Read-only or Read/Write
    uint8 dc:1;  // Direction for data segment, 0 grow up, 1 grow down or
                 // Execution for code segment, 0 indicate DPL and more DPL
                 //                              1 indicate only the DPL specify
    uint8 ex:1;  // Segment can be executed or not.
    uint8 dt:1;  // Descriptor Type, always 1 for GDT
    uint8 dpl:2; // Descriptor privilege level, ring 0-3
    uint8 p:1;   // Segment is present or not
} __attribute__((packed));

struct gdt_attribute_flags {
    uint8 avl:1;
    uint8 pack:1;
    uint8 db:1;    // Operand size, 0 16-bit 1 32-bit
    uint8 g:1;     // Granularity which defines the limit unit in byte or 4KB
    uint8 lmt_h:4; // High 4 bit of limit, bit <16, 19> of limit
} __attribute__((packed));

/*
 * Global Descriptor Table Entry (Global Descriptor)
 * Each represent a segment in GDT.
 * 63           55      51           47       39         15         0
 * +-----------+-------+------------+--------+----------+-----------+
 * | base high | flags | limit high | access | base low | limit low |
 * +-----------+-------+------------+--------+----------+-----------+
 * base contains  32-bit
 * limit contains 20-bit
 */
struct gdt_entry {
    uint16                      lmt_l;
    uint32                      base_l:24;
    struct gdt_attribute_access access;
    struct gdt_attribute_flags  flags;
    uint8                       base_h;
} __attribute__((packed));

#define GDT_ENTRY_CNT     5

#define ACC_AC_IDX        0
#define ACC_RW_IDX        1
#define ACC_DC_IDX        2
#define ACC_EX_IDX        3
#define ACC_DT_IDX        4
#define ACC_DPL_IDX       5
#define ACC_DPL_LEN       2
#define ACC_P_IDX         7
#define FLAG_A_IDX        0
#define FLAG_DB_IDX       2
#define FLAG_G_IDX        3

#define ACC_ACCESS        ATTR_SET
#define ACC_RO            (ATTR_CLR << ACC_RW_IDX)
#define ACC_RW            (ATTR_SET << ACC_RW_IDX)
#define ACC_DC_GRW_UP     (ATTR_CLR << ACC_DC_IDX)
#define ACC_DC_GRW_DW     (ATTR_SET << ACC_DC_IDX)
#define ACC_DC_DPL_M      (ATTR_CLR << ACC_DC_IDX)
#define ACC_DC_DPL_O      (ATTR_SET << ACC_DC_IDX)
#define ACC_EX_DATA       (ATTR_CLR << ACC_EX_IDX)
#define ACC_EX_CODE       (ATTR_SET << ACC_EX_IDX)
#define ACC_DT_GDT        (ATTR_SET << ACC_DT_IDX)
#define ACC_DPL_RING_0    (DPL_RING_0 << ACC_DPL_IDX)
#define ACC_DPL_RING_1    (DPL_RING_1 << ACC_DPL_IDX)
#define ACC_DPL_RING_2    (DPL_RING_2 << ACC_DPL_IDX)
#define ACC_DPL_RING_3    (DPL_RING_3 << ACC_DPL_IDX)
#define ACC_PRST          (ATTR_SET << ACC_P_IDX)

#define FLAG_AVL          (ATTR_SET << FLAG_A_IDX)
#define FLAG_DB_OPND_16   (ATTR_CLR << FLAG_DB_IDX)
#define FLAG_DB_OPND_32   (ATTR_SET << FLAG_DB_IDX)
#define FLAG_G_BYTE       (ATTR_CLR << FLAG_G_IDX)
#define FLAG_G_4KB        (ATTR_SET << FLAG_G_IDX)

#define CODE_SEG_ACC      (ACC_PRST | ACC_DPL_RING_0 | ACC_DT_GDT | ACC_EX_CODE \
    | ACC_DC_DPL_M | ACC_RW)
#define DATA_SEG_ACC      (ACC_PRST | ACC_DPL_RING_0 | ACC_DT_GDT | ACC_EX_DATA \
    | ACC_DC_DPL_M | ACC_RW)
#define STACK_SEG_ACC     (ACC_PRST | ACC_DPL_RING_0 | ACC_DT_GDT | ACC_EX_DATA \
    | ACC_DC_GRW_DW | ACC_RW)
#define CODE_SEG_FLAG     (FLAG_DB_OPND_32 | FLAG_G_BYTE)
#define DATA_SEG_FLAG     (FLAG_DB_OPND_32 | FLAG_G_BYTE)
#define STACK_SEG_FLAG    (FLAG_DB_OPND_32 | FLAG_G_BYTE)


#define USR_CODE_SEG_ACC  (ACC_PRST | ACC_DPL_RING_3 | ACC_DT_GDT | ACC_EX_CODE \
    | ACC_DC_DPL_M | ACC_RW)
#define USR_DATA_SEG_ACC  (ACC_PRST | ACC_DPL_RING_3 | ACC_DT_GDT | ACC_EX_DATA \
    | ACC_DC_DPL_M | ACC_RW)
#define USR_CODE_SEG_FLAG (FLAG_DB_OPND_32 | FLAG_G_BYTE)
#define USR_DATA_SEG_FLAG (FLAG_DB_OPND_32 | FLAG_G_BYTE)

#define CODE_SEG_BASE             0x0
#define CODE_SEG_LMT              0xfffff

#define DATA_SEG_BASE             0x0
#define DATA_SEG_LMT              0xfffff

#define STACK_SEG_BASE            0x300000
#define STACK_SEG_LMT             0xfffff

#define USR_CODE_SEG_LMT          0xFFFFF
#define USR_CODE_SEG_BASE         0xFFFFF
#define USR_DATA_SEG_LMT          0xFFFFF

static s_gdt_entry_t    gdt[GDT_ENTRY_CNT];
static s_gdt_register_t gdt_reg;

extern void gdt_table_flush(uint32);

#endif

