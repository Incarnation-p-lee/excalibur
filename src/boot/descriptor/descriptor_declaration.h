#ifndef SRC_BOOT_DESCRIPTOR_DECLARATION_H
#define SRC_BOOT_DESCRIPTOR_DECLARATION_H

static inline void descriptor_table_gdt_entry_set(uint32 index, uint32 base, uint32 lmt, uint16 acc, uint8 flags);
static inline void descriptor_table_idt_entry_set(uint32 index, void (*handler)(void), uint16 selector, uint16 attr);
static inline void pic_remap(void);
void descriptor_table_gdt_initialize(void);
void descriptor_table_idt_initialize(void);
void pic_send_eoi(uint32 irq);

#endif
