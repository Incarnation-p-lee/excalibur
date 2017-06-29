void
descriptor_table_gdt_initialize(void)
{
    gdt_reg.limit = sizeof(gdt) - 1;
    gdt_reg.base = (uint32)&gdt;

    gdt_entry_set(0, 0, 0, 0, 0);
    gdt_entry_set(1, CODE_BASE, CODE_LIMIT, CODE_ACC, CODE_FLAG);
    gdt_entry_set(2, DATA_BASE, DATA_LIMIT, DATA_ACC, DATA_FLAG);
    gdt_entry_set(3, USR_CODE_BASE, USR_CODE_LIMIT, USR_CODE_ACC, USR_CODE_FLAG);
    gdt_entry_set(4, USR_DATA_BASE, USR_DATA_LIMIT, USR_DATA_ACC, USR_DATA_FLAG);

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

    gdt[i].base_low = U32_BITS_GET(base, BASE_LOW_IDX, BASE_LOW_LEN);
    gdt[i].base_high = (uint8)U32_BITS_GET(base, BASE_HIGH_IDX, BASE_HIGH_LEN);

    gdt[i].limit_low =
        (uint16)U32_BITS_GET(limit, LIMIT_LOW_IDX, LIMIT_LOW_LEN);
    gdt[i].flags.limit_high =
        (uint8)U32_BITS_GET(limit, LIMIT_HIGH_IDX, LIMIT_HIGH_LEN);

    gdt[i].access.acc = (uint8)U32_BIT_GET(acc, ACC_AC_IDX);
    gdt[i].access.rw = (uint8)U32_BIT_GET(acc, ACC_RW_IDX);
    gdt[i].access.dc = (uint8)U32_BIT_GET(acc, ACC_DC_IDX);
    gdt[i].access.ex = (uint8)U32_BIT_GET(acc, ACC_EX_IDX);
    gdt[i].access.dt = (uint8)U32_BIT_GET(acc, ACC_DT_IDX);
    gdt[i].access.dpl = (uint8)U32_BITS_GET(acc, ACC_DPL_IDX, ACC_DPL_LEN);
    gdt[i].access.p = (uint8)U32_BIT_GET(acc, ACC_P_IDX);

    gdt[i].flags.avl = (uint8)U32_BIT_GET(flags, FLAG_A_IDX);
    gdt[i].flags.pack = 0;
    gdt[i].flags.db = (uint8)U32_BIT_GET(flags, FLAG_DB_IDX);
    gdt[i].flags.g = (uint8)U32_BIT_GET(flags, FLAG_G_IDX);
}

static inline void
idt_entry_set(uint32 i, void (*handler)(void), uint16 selector, uint16 attr)
{
    kassert(handler);
    kassert(i < IDT_ENTRY_CNT);

    idt[i].base_l = U32_BITS_GET(handler, 0, 16);
    idt[i].base_h = U32_BITS_GET(handler, 16, 16);

    idt[i].selector = selector;

    idt[i].attr.unused = 0;
    idt[i].attr.type = U32_BITS_GET(attr, IDT_ATTR_TYPE_IDX, IDT_ATTR_TYPE_LEN);
    idt[i].attr.s = U32_BIT_GET(attr, IDT_ATTR_S_IDX);
    idt[i].attr.dpl = U32_BITS_GET(attr, IDT_ATTR_DPL_IDX, IDT_ATTR_TYPE_LEN);
    idt[i].attr.p = U32_BIT_GET(attr, IDT_ATTR_P_IDX);
}

