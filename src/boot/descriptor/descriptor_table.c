void
descriptor_table_gdt_init(void)
{
    detect_physical_memory_size();

    gdt_reg.limit = sizeof(gdt_entry_list) - 1;
    gdt_reg.base = (uint32)&gdt_entry_list;

    descriptor_table_gdt_entry_set(0, 0, 0, 0, 0);
    descriptor_table_gdt_entry_set(1, CODE_SEG_BASE, CODE_SEG_LMT, CODE_SEG_ACC,
        CODE_SEG_FLAG);
    descriptor_table_gdt_entry_set(2, DATA_SEG_BASE, DATA_SEG_LMT, DATA_SEG_ACC,
        DATA_SEG_FLAG);
    descriptor_table_gdt_entry_set(3, 0, USR_CODE_SEG_LMT, USR_CODE_SEG_ACC,
        USR_CODE_SEG_FLAG);
    descriptor_table_gdt_entry_set(4, 0, USR_DATA_SEG_LMT, USR_DATA_SEG_ACC,
        USR_DATA_SEG_FLAG);

    gdt_table_flush((uint32)&gdt_reg);

    printf_vga_ts("GDT table initialized.\n");
}

void
descriptor_table_idt_init(void)
{
    uint32 index;

    idt_reg.limit = sizeof(idt_entry_list) - 1;
    idt_reg.base = (ptr_t)&idt_entry_list;

    kmemset(&idt_entry_list, 0, sizeof(idt_entry_list));
    pic_remap();

    index = 0;
    while (index < ARRAY_CNT_OF(isr_handler)) {
        descriptor_table_idt_entry_set(index, isr_handler[index],
            IDT_CODE_SEL, ATTR_INT_32);
        index++;
    }

    idt_table_flush((uint32)&idt_reg);

    printf_vga_ts("IDT table initialized.\n");
}

static inline void
descriptor_table_gdt_entry_set(uint32 index, uint32 base, uint32 lmt,
    uint16 acc, uint8 flags)
{
    kassert(index < GDT_ENTRY_CNT);

    gdt_entry_list[index].base_l = U32_BITS(base, 0, 24);
    gdt_entry_list[index].base_h = (uint8)U32_BITS(base, 24, 8);

    gdt_entry_list[index].lmt_l = (uint16)U32_BITS(lmt, 0, 16);
    gdt_entry_list[index].flags.lmt_h = (uint8)U32_BITS(lmt, 16, 4);

    gdt_entry_list[index].access.acc = (uint8)U32_BIT(acc, ACC_AC_IDX);
    gdt_entry_list[index].access.rw = (uint8)U32_BIT(acc, ACC_RW_IDX);
    gdt_entry_list[index].access.dc = (uint8)U32_BIT(acc, ACC_DC_IDX);
    gdt_entry_list[index].access.ex = (uint8)U32_BIT(acc, ACC_EX_IDX);
    gdt_entry_list[index].access.dt = (uint8)U32_BIT(acc, ACC_DT_IDX);
    gdt_entry_list[index].access.dpl = (uint8)U32_BITS(acc, ACC_DPL_IDX, ACC_DPL_LEN);
    gdt_entry_list[index].access.p = (uint8)U32_BIT(acc, ACC_P_IDX);

    gdt_entry_list[index].flags.avl = (uint8)U32_BIT(flags, FLAG_A_IDX);
    gdt_entry_list[index].flags.pack = 0;
    gdt_entry_list[index].flags.db = (uint8)U32_BIT(flags, FLAG_DB_IDX);
    gdt_entry_list[index].flags.g = (uint8)U32_BIT(flags, FLAG_G_IDX);
}

static inline void
descriptor_table_idt_entry_set(uint32 index, void (*handler)(void),
    uint16 selector, uint16 attr)
{
    kassert(NULL != handler);
    kassert(index < IDT_ENTRY_CNT);

    idt_entry_list[index].base_l = U32_BITS(handler, 0, 16);
    idt_entry_list[index].base_h = U32_BITS(handler, 16, 16);

    idt_entry_list[index].selector = selector;

    idt_entry_list[index].attr.unused = 0;
    idt_entry_list[index].attr.type = U32_BITS(attr, IDT_ATTR_TYPE_IDX, IDT_ATTR_TYPE_LEN);
    idt_entry_list[index].attr.s = U32_BIT(attr, IDT_ATTR_S_IDX);
    idt_entry_list[index].attr.dpl = U32_BITS(attr, IDT_ATTR_DPL_IDX, IDT_ATTR_TYPE_LEN);
    idt_entry_list[index].attr.p = U32_BIT(attr, IDT_ATTR_P_IDX);
}

