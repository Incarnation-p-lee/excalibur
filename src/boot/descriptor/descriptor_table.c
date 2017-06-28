void
descriptor_table_gdt_initialize(void)
{
    gdt_reg.limit = sizeof(gdt) - 1;
    gdt_reg.base = (uint32)&gdt;

    gdt_entry_set(0, 0, 0, 0, 0);
    gdt_entry_set(1, CODE_SEG_BASE, CODE_SEG_LMT, CODE_SEG_ACC, CODE_SEG_FLAG);
    gdt_entry_set(2, DATA_SEG_BASE, DATA_SEG_LMT, DATA_SEG_ACC, DATA_SEG_FLAG);
    gdt_entry_set(3, 0, USR_CODE_SEG_LMT, USR_CODE_SEG_ACC, USR_CODE_SEG_FLAG);
    gdt_entry_set(4, 0, USR_DATA_SEG_LMT, USR_DATA_SEG_ACC, USR_DATA_SEG_FLAG);

    gdt_table_flush((uint32)&gdt_reg);

    printf_vga_tk("GDT table initialized.\n");
}

void
descriptor_table_idt_initialize(void)
{
    uint32 i;

    idt_reg.limit = sizeof(idt) - 1;
    idt_reg.base = (ptr_t)&idt;

    kmemset(&idt, 0, sizeof(idt));
    pic_remap();

    i = 0;

    while (i < ARRAY_CNT_OF(isr_handler)) {
        idt_entry_set(i, isr_handler[i], IDT_CODE_SEL, ATTR_INT_32);

        i++;
    }

    idt_table_flush((uint32)&idt_reg);

    printf_vga_tk("IDT table initialized.\n");
}

static inline void
gdt_entry_set(uint32 i, uint32 base, uint32 limit, uint16 acc, uint8 flags)
{
    kassert(i < GDT_ENTRY_CNT);

    gdt[i].base_l = U32_BITS(base, 0, 24);
    gdt[i].base_h = (uint8)U32_BITS(base, 24, 8);

    gdt[i].lmt_l = (uint16)U32_BITS(limit, 0, 16);
    gdt[i].flags.lmt_h = (uint8)U32_BITS(limit, 16, 4);

    gdt[i].access.acc = (uint8)U32_BIT(acc, ACC_AC_IDX);
    gdt[i].access.rw = (uint8)U32_BIT(acc, ACC_RW_IDX);
    gdt[i].access.dc = (uint8)U32_BIT(acc, ACC_DC_IDX);
    gdt[i].access.ex = (uint8)U32_BIT(acc, ACC_EX_IDX);
    gdt[i].access.dt = (uint8)U32_BIT(acc, ACC_DT_IDX);
    gdt[i].access.dpl = (uint8)U32_BITS(acc, ACC_DPL_IDX, ACC_DPL_LEN);
    gdt[i].access.p = (uint8)U32_BIT(acc, ACC_P_IDX);

    gdt[i].flags.avl = (uint8)U32_BIT(flags, FLAG_A_IDX);
    gdt[i].flags.pack = 0;
    gdt[i].flags.db = (uint8)U32_BIT(flags, FLAG_DB_IDX);
    gdt[i].flags.g = (uint8)U32_BIT(flags, FLAG_G_IDX);
}

static inline void
idt_entry_set(uint32 i, void (*handler)(void), uint16 selector, uint16 attr)
{
    kassert(NULL != handler);
    kassert(i < IDT_ENTRY_CNT);

    idt[i].base_l = U32_BITS(handler, 0, 16);
    idt[i].base_h = U32_BITS(handler, 16, 16);

    idt[i].selector = selector;

    idt[i].attr.unused = 0;
    idt[i].attr.type = U32_BITS(attr, IDT_ATTR_TYPE_IDX, IDT_ATTR_TYPE_LEN);
    idt[i].attr.s = U32_BIT(attr, IDT_ATTR_S_IDX);
    idt[i].attr.dpl = U32_BITS(attr, IDT_ATTR_DPL_IDX, IDT_ATTR_TYPE_LEN);
    idt[i].attr.p = U32_BIT(attr, IDT_ATTR_P_IDX);
}

