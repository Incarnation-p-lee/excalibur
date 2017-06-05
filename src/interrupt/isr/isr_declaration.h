#ifndef SRC_INTERRUPT_ISR_DECLARATION_H
#define SRC_INTERRUPT_ISR_DECLARATION_H

static inline void irq_0_timer_callback(s_pro_context_t context);
static inline void isr_handler_0_divide_by_zero(s_pro_context_t context);
static inline void isr_handler_14_paging_fault(s_pro_context_t context);
static inline void isr_handler_3_breakpoint(s_pro_context_t context);
void irq_0_timer_init(uint32 freq);
void irq_handler_main(s_pro_context_t context);
void isr_handler_main(s_pro_context_t context);
void isr_handler_register(uint8 nmbr, isr_handler_t handler);

#endif
