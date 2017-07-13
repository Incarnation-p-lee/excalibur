#ifndef SRC_COMMON_PRINT_DECLARATION_H
#define SRC_COMMON_PRINT_DECLARATION_H

static inline bool print_backup_buffer_illegal_p(s_pr_backup_buf_t *pr_backup_buf);
static inline bool print_backup_buffer_legal_p(s_pr_backup_buf_t *pr_backup_buf);
static inline bool print_buffer_illegal_p(s_pr_buf_t *pr_buf);
static inline bool print_buffer_legal_p(s_pr_buf_t *pr_buf);
static inline bool print_buffer_status_backup_p(s_pr_buf_t *pr_buf);
static inline bool print_buffer_status_busy_p(s_pr_buf_t *pr_buf);
static inline bool print_buffer_status_free_p(s_pr_buf_t *pr_buf);
static inline bool print_format_param_prefix_p(char c);
static inline char * print_backup_buffer_array(s_pr_backup_buf_t *pr_backup_buf);
static inline char * print_buffer_array(s_pr_buf_t *pr_buf);
static inline s_pr_backup_buf_t * print_backup_buffer(s_pr_buf_t *pr_buf);
static inline s_pr_buf_t * print_buffer(void);
static inline uint32 print_backup_buffer_index(s_pr_backup_buf_t *pr_backup_buf);
static inline uint32 print_buffer_critical_size(s_pr_buf_t *pr_buf);
static inline uint32 print_buffer_index(s_pr_buf_t *pr_buf);
static inline uint32 print_buffer_start(s_pr_buf_t *pr_buf);
static inline uint32 print_format_placeholder_process(s_pr_buf_t *pr_buf, char placeholder, void *param);
static inline void print_backup_buffer_index_set(s_pr_backup_buf_t *pr_backup_buf, uint32 index);
static inline void print_buffer_backup(s_pr_buf_t *pr_buf);
static inline void print_buffer_char_copy(s_pr_buf_t *pr_buf, char c);
static inline void print_buffer_copy(s_pr_buf_t *pr_buf, char *s, uint32 len);
static inline void print_buffer_index_advance(s_pr_buf_t *pr_buf, uint32 len);
static inline void print_buffer_index_set(s_pr_buf_t *pr_buf, uint32 index);
static inline void print_buffer_restore(s_pr_buf_t *pr_buf);
static inline void print_buffer_start_set(s_pr_buf_t *pr_buf, uint32 start);
static inline void print_buffer_status_set(s_pr_buf_t *pr_buf, e_pr_buf_status_t status);
static inline void print_buffer_string_copy(s_pr_buf_t *pr_buf, char *s);
static inline void print_buffer_uint32_copy(s_pr_buf_t *pr_buf, uint32 u);
static inline void print_buffer_uint32_hex_copy(s_pr_buf_t *pr_buf, uint32 u);
static inline void print_format(s_pr_buf_t *pr_buf, char *format, void *param);
static inline void print_format_vga(s_pr_buf_t *pr_buf);
static inline void print_internal(char *format, void *param);
void printf_vga(char *format, ...);
void printf_vga_tk(char *format, ...);

#endif
