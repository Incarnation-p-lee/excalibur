#ifndef SRC_COMMON_DECLARATION_H
#define SRC_COMMON_DECLARATION_H

bool assert_complain(const char *msg, const char *file, const char *fun, uint32 line, bool exp);
static inline uint32 string_copy_i(char *d, char *s);
static inline uint32 string_len_i(char *s);
uint32 string_copy(char *d, char *s);
uint32 string_len(char *s);
uint64 time_stamp_counter(void);

#endif
