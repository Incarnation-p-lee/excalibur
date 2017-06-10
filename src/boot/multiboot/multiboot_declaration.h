#ifndef SRC_BOOT_MULTIBOOT_DECLARATION_H
#define SRC_BOOT_MULTIBOOT_DECLARATION_H

static inline bool multiboot_data_valid_p(uint32 i);
static inline void multiboot_data_valid_set(uint32 i);
void multiboot_data_header_initialize(s_multiboot_header_t *header);
void multiboot_data_info_initialize(s_multiboot_info_t *info);

#endif
