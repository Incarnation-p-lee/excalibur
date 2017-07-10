#ifndef SRC_INTERRUPT_ISR_IRQ_DECLARATION_H
#define SRC_INTERRUPT_ISR_IRQ_DECLARATION_H

static inline uint32 irq_handler_nmbr_isr_to_irq(uint32 isr_nmbr);
uint32 irq_0_timer_tick(void);
void irq_0_timer_handler(s_pro_context_t *context);
void irq_0_timer_initialize(uint32 freq);
void irq_1_keyboard_handler(s_pro_context_t *context);
void irq_7_handler(s_pro_context_t *context);
void irq_handler_main(s_pro_context_t context);

#endif
