void
descriptor_table_init(void)
{
    descriptor_table_gdt_init();

}

static inline void
descriptor_table_gdt_init(void)
{
    gdt_reg.limit = (sizeof(gdt_entry_list)) - 1;
    gdt_reg.base = (uint32)&gdt_entry_list;

    descriptor_table_gdt_entry_set(0, 0, 0, 0, 0);
    descriptor_table_gdt_entry_set(1, 0, CODE_SEG_LMT, CODE_SEG_ACC,
        CODE_SEG_FLAG);
    descriptor_table_gdt_entry_set(2, 0, DATA_SEG_LMT, DATA_SEG_ACC,
        DATA_SEG_FLAG);
    descriptor_table_gdt_entry_set(3, 0, USR_CODE_SEG_LMT, USR_CODE_SEG_ACC,
        USR_CODE_SEG_FLAG);
    descriptor_table_gdt_entry_set(4, 0, USR_DATA_SEG_LMT, USR_DATA_SEG_ACC,
        USR_DATA_SEG_FLAG);

    gdt_table_flush((uint32)&gdt_reg);
}

static inline void
descriptor_table_gdt_entry_set(uint32 index, uint32 base, uint32 lmt,
    uint16 acc, uint8 flags)
{
    // assert(index < GDT_ENTRY_CNT);

    gdt_entry_list[index].base_l = U32_BITS(base, 0, 24);
    gdt_entry_list[index].base_h = (uint8)U32_BITS(base, 24, 8);

    gdt_entry_list[index].lmt_l = (uint16)U32_BITS(lmt, 0, 16);
    gdt_entry_list[index].lmt_h = (uint8)U32_BITS(lmt, 16, 8);

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

