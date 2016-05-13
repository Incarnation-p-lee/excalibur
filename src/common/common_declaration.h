#ifndef COMMON_DECLARATION_H
#define COMMON_DECLARATION_H


uint32 string_len_k(char *s);
uint64 time_stamp_counter(void);
void assert_complain(const char *msg, const char *file, const char *fun, uint32 line);

#endif
