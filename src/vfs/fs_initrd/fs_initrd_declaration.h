#ifndef SRC_VFS_FS_INITRD_DECLARATION_H
#define SRC_VFS_FS_INITRD_DECLARATION_H

s_fs_node_t * fs_initrd_initialize(ptr_t location);
static inline bool fs_initrd_header_legal_p(s_initrd_header_t *header);
static inline s_directory_t * fs_initrd_readdir(s_fs_node_t *fs_node, uint32 index);
static inline s_fs_node_t * fs_initrd_dir_node_create(char *name, f_readdir_t readdir, f_finddir_t finddir);
static inline s_fs_node_t * fs_initrd_file_node_create(char *name, f_read_t read, f_write_t write);
static inline s_fs_node_t * fs_initrd_finddir(s_fs_node_t *fs_node, char *name);
static inline s_fs_node_t * fs_initrd_initialize_i(ptr_t location);
static inline s_initrd_header_t * fs_initrd_header(uint32 i);
static inline uint32 fs_initrd_header_count(ptr_t location);
static inline uint32 fs_initrd_header_length(s_initrd_header_t *header);
static inline uint32 fs_initrd_read(s_fs_node_t *fs_node, uint32 offset, uint32 size, uint8 *buf);
static inline uint32 fs_initrd_write(s_fs_node_t *fs_node, uint32 offset, uint32 size, uint8 *buf);
static inline void fs_initrd_header_set(ptr_t location);

#endif
