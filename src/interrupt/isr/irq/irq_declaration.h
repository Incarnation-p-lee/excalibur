#ifndef SRC_INTERRUPT_ISR_IRQ_DECLARATION_H
#define SRC_INTERRUPT_ISR_IRQ_DECLARATION_H

static inline bool irq_1_keyboard_key_pressed_p(uint8 key);
static inline bool irq_1_keyboard_key_shift_pressed_p(void);
static inline bool irq_1_keyboard_key_shifted_p(uint8 key);
static inline bool irq_1_keyboard_pressed_null_key_p(uint32 i);
static inline bool irq_1_keyboard_pressed_sensitive_p(uint8 key);
static inline s_keyboard_pressed_t * irq_1_keyboard_pressed(void);
static inline uint32 irq_handler_nmbr_isr_to_irq(uint32 isr_nmbr);
static inline uint8 irq_1_keyboard_data_key(s_keyboard_data_t *data);
static inline uint8 irq_1_keyboard_data_release(s_keyboard_data_t *data);
static inline uint8 irq_1_keyboard_key_to_ascii(uint8 key);
static inline uint8 irq_1_keyboard_pressed_key(uint32 i);
static inline void irq_1_keyboard_key_release(uint8 key);
static inline void irq_1_keyboard_pressed_key_add(uint8 key);
static inline void irq_1_keyboard_pressed_key_clean(uint32 i);
static inline void irq_1_keyboard_pressed_key_remove(uint8 key);
static inline void irq_1_keyboard_pressed_key_set(uint8 key, uint32 i);
uint32 irq_0_timer_tick(void);
void irq_0_timer_handler(s_pro_context_t *context);
void timer_initialize(uint32 freq);
void irq_14_ata_channel_primary(s_pro_context_t *context);
void irq_1_keyboard_handler(s_pro_context_t *context);
void irq_7_handler(s_pro_context_t *context);
void irq_handler_main(s_pro_context_t context);

#endif
