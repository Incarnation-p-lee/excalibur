#ifndef SRC_INTERRUPT_ISR_DECLARATION_H
#define SRC_INTERRUPT_ISR_DECLARATION_H

static inline uint32 irq_handler_nmbr_isr_to_irq(uint32 isr_nmbr);
static inline void irq_0_timer_handler(s_pro_context_t *context);
static inline void irq_1_keyboard_handler(s_pro_context_t *context);
static inline void irq_7_handler(s_pro_context_t *context);
static inline void isr_0_divide_by_zero_handler(s_pro_context_t *context);
static inline void isr_12_stack_fault_handler(s_pro_context_t *context);
static inline void isr_14_paging_fault_handler(s_pro_context_t *context);
static inline void isr_3_breakpoint_handler(s_pro_context_t *context);
static inline void isr_6_invalid_opcode_handler(s_pro_context_t *context);
uint32 irq_0_timer_tick(void);
void irq_0_timer_initialize(uint32 freq);
void irq_handler_main(s_pro_context_t context);
void isr_handler_main(s_pro_context_t context);

#endif
