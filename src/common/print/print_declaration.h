#ifndef SRC_COMMON_PRINT_DECLARATION_H
#define SRC_COMMON_PRINT_DECLARATION_H

static inline bool print_format_param_prefix_p(char c);
static inline char * print_buffer_start(void);
static inline s_print_buffer_t * print_buffer(void);
static inline uint32 print_format_placeholder_process(char placeholder, void *param);
static inline void print_buffer_char_copy(char c);
static inline void print_buffer_copy(char *s, uint32 len);
static inline void print_buffer_start_set(void);
static inline void print_buffer_string_copy(char *s);
static inline void print_buffer_uint32_copy(uint32 u);
static inline void print_buffer_uint32_hex_copy(uint32 u);
static inline void print_format(char *format, void *param);
static inline void print_format_vga(void);
void printf_vga(char *format, ...);
void printf_vga_tk(char *format, ...);

#endif
