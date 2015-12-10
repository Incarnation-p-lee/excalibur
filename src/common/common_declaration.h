#ifndef COMMON_DECLARATION_H
#define COMMON_DECLARATION_H


static inline uint32 memory_set_fill_dword_element(uint8 v);
static inline void memory_set_in_byte(void *base, uint8 v, uint32 len);
static inline void memory_set_in_dword(uint32 *base, uint8 v, uint32 len);
void memory_set_k(void *base, uint8 v, uint32 len);

#endif
