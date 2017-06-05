#ifndef SRC_COMMON_DECLARATION_H
#define SRC_COMMON_DECLARATION_H

bool assert_complain(const char *msg, const char *file, const char *fun, uint32 line, bool exp);
uint32 detect_physical_memory_size(void);
uint32 string_len_k(char *s);
uint64 time_stamp_counter(void);

#endif
