#ifndef HAVE_DEFINED_EXTERNAL_H
#define HAVE_DEFINED_EXTERNAL_H

extern bool assert_complain(const char *msg, const char *file, const char *fun, uint32 line, bool exp);
extern bool frame_available_p(ptr_t frame);
extern uint16 io_bus_read_word(uint16 port);
extern uint32 string_len_k(char *s);
extern uint64 time_stamp_counter(void);
extern uint8 io_bus_read_byte(uint16 port);
extern void * kmalloc(uint32 sz);
extern void * kmalloc_algn(uint32 sz);
extern void * kmalloc_algn_with_phys(uint32 sz, ptr_t *phys);
extern void * kmalloc_phys(uint32 sz, ptr_t *phys);
extern void descriptor_table_gdt_init(void);
extern void descriptor_table_idt_init(void);
extern void io_bus_write_byte(uint16 port, uint8 val);
extern void irq_0_timer_init(uint32 freq);
extern void irq_handler_main(struct pro_context context);
extern void isr_handler_main(struct pro_context context);
extern void isr_handler_register(uint8 nmbr, isr_handler_t handler);
extern void kmemory_copy(void *to, void *from, uint32 len);
extern void kmemset(void *base, uint8 v, uint32 len);
extern void paging_initialize(void);
extern void pic_send_eoi(uint32 irq);
extern void printf_vga(char *format, ...);
extern void printf_vga_ts(char *format, ...);
extern void screen_monitor_clear(void);
extern void screen_monitor_put_char(char c);
extern void screen_monitor_write_string(char *c);
extern void screen_monitor_write_uint32(uint32 u);
extern void screen_monitor_write_uint32_hex(uint32 u);

#endif

