#ifndef SRC_BOOT_MULTIBOOT_DECLARATION_H
#define SRC_BOOT_MULTIBOOT_DECLARATION_H

static inline bool multiboot_data_valid_p(uint32 i);
static inline uint32 multiboot_data_info_physical_memory_lower_i(void);
static inline uint32 multiboot_data_info_physical_memory_upper_i(void);
static inline void multiboot_data_header_initialize(s_multiboot_header_t *header);
static inline void multiboot_data_info_initialize(s_multiboot_info_t *info);
static inline void multiboot_data_initialize(void);
static inline void multiboot_data_valid_set(uint32 i);
static inline void multiboot_env_data_detect(s_multiboot_header_t *header, s_multiboot_info_t *info);
static inline void multiboot_env_os_image_detect(void);
static inline void multiboot_env_stack_detect(void);
uint32 multiboot_data_info_physical_memory_lower(void);
uint32 multiboot_data_info_physical_memory_upper(void);
void multiboot_env_cpu_detect(void);
void multiboot_env_detect(uint32 magic, void *boot_header, void *boot_info);

#endif
