#ifndef ISR_DECLARATION_H
#define ISR_DECLARATION_H


void irq_handler_main(struct pro_context context);
void isr_handler_main(struct pro_context context);
void isr_handler_register(uint8 nmbr, isr_handler_t handler);

#endif
