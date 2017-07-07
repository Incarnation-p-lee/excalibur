#ifndef SRC_BOOT_MULTIBOOT_DECLARATION_H
#define SRC_BOOT_MULTIBOOT_DECLARATION_H

ptr_t multiboot_data_info_boot_module_start(uint32 i);
ptr_t multiboot_data_info_modules_addr(void);
ptr_t multiboot_data_info_physical_memory_limit(void);
ptr_t multiboot_data_info_physical_memory_lower(void);
ptr_t multiboot_data_info_physical_memory_upper(void);
static inline bool multiboot_data_info_flag_disabled_p(uint32 flag);
static inline bool multiboot_data_info_flag_enabled_p(uint32 flag);
static inline bool multiboot_data_invalid_p(uint32 i);
static inline bool multiboot_data_valid_p(uint32 i);
static inline ptr_t multiboot_data_info_end_address(void);
static inline ptr_t multiboot_data_info_modules_addr_i(void);
static inline s_boot_module_t * multiboot_data_info_boot_module(uint32 i);
static inline uint32 multiboot_data_info_boot_modules_count_i(void);
static inline uint32 multiboot_data_info_flag(void);
static inline uint32 multiboot_data_info_physical_memory_lower_i(void);
static inline uint32 multiboot_data_info_physical_memory_upper_i(void);
static inline void multiboot_data_header_initialize(s_multiboot_header_t *header);
static inline void multiboot_data_info_initialize(s_multiboot_info_t *info);
static inline void multiboot_data_initialize(void);
static inline void multiboot_data_valid_set(uint32 i);
static inline void multiboot_env_data_detect(s_multiboot_header_t *header, s_multiboot_info_t *info);
static inline void multiboot_env_data_detect_boot_modules(void);
static inline void multiboot_env_data_detect_physical_memory(void);
static inline void multiboot_env_os_image_detect(void);
static inline void multiboot_env_stack_detect(void);
uint32 multiboot_data_info_boot_modules_count(void);
void multiboot_env_cpu_detect(void);
void multiboot_env_detect(uint32 magic, void *boot_header, void *boot_info);

#endif
