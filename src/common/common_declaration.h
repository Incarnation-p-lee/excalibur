#ifndef SRC_COMMON_DECLARATION_H
#define SRC_COMMON_DECLARATION_H

bool assert_complain(const char *msg, const char *file, const char *fun, uint32 line, bool exp);
static inline void detect_cpu_mode(void);
static inline void detect_multiboot_data(s_multiboot_header_t *header, s_multiboot_info_t *info);
static inline void detect_stack_base(void);
uint32 string_len_k(char *s);
uint64 time_stamp_counter(void);
void detect_boot_up_env(uint32 magic, void *boot_header, void *boot_info);

#endif
