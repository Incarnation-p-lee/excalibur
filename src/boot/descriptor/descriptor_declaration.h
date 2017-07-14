#ifndef SRC_BOOT_DESCRIPTOR_DECLARATION_H
#define SRC_BOOT_DESCRIPTOR_DECLARATION_H

static inline void gdt_entry_set(uint32 i, uint32 base, uint32 limit, uint16 acc, uint8 flags);
static inline void idt_entry_set(uint32 i, void (*handler)(void), uint16 selector, uint16 attr);
static inline void pic_remap(void);
void gdt_initialize(void);
void idt_initialize(void);
void pic_send_eoi(uint32 irq);

#endif
