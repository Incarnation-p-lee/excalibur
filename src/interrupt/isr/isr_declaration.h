#ifndef SRC_INTERRUPT_ISR_DECLARATION_H
#define SRC_INTERRUPT_ISR_DECLARATION_H

isr_handler_t isr_handler_get(uint32 i);
static inline isr_handler_t isr_handler_get_i(uint32 i);
static inline void isr_0_divide_by_zero_handler(s_pro_context_t *context);
static inline void isr_12_stack_fault_handler(s_pro_context_t *context);
static inline void isr_14_paging_fault_handler(s_pro_context_t *context);
static inline void isr_3_breakpoint_handler(s_pro_context_t *context);
static inline void isr_6_invalid_opcode_handler(s_pro_context_t *context);
void isr_handler_main(s_pro_context_t context);

#endif
