#ifndef SRC_VFS_DECLARATION_H
#define SRC_VFS_DECLARATION_H

bool vfs_node_illegal_p(s_vfs_node_t *vfs_node);
bool vfs_node_legal_p(s_vfs_node_t *vfs_node);
s_vfs_node_t * vfs_dir_node_create(char *name, f_readdir_t readdir, f_finddir_t finddir);
s_vfs_node_t * vfs_file_node_create(char *name, f_read_t read, f_write_t write);
s_vfs_node_t * vfs_readdir(s_vfs_node_t *vfs_node, uint32 index);
static inline bool vfs_node_closable_p(s_vfs_node_t *vfs_node);
static inline bool vfs_node_dir_findable_p(s_vfs_node_t *vfs_node);
static inline bool vfs_node_dir_readable_p(s_vfs_node_t *vfs_node);
static inline bool vfs_node_dir_unfindable_p(s_vfs_node_t *vfs_node);
static inline bool vfs_node_dir_unreadable_p(s_vfs_node_t *vfs_node);
static inline bool vfs_node_directory_p(s_vfs_node_t *vfs_node);
static inline bool vfs_node_illegal_ip(s_vfs_node_t *vfs_node);
static inline bool vfs_node_legal_ip(s_vfs_node_t *vfs_node);
static inline bool vfs_node_not_directory_p(s_vfs_node_t *vfs_node);
static inline bool vfs_node_openable_p(s_vfs_node_t *vfs_node);
static inline bool vfs_node_readable_p(s_vfs_node_t *vfs_node);
static inline bool vfs_node_unclosable_p(s_vfs_node_t *vfs_node);
static inline bool vfs_node_unopenable_p(s_vfs_node_t *vfs_node);
static inline bool vfs_node_unreadable_p(s_vfs_node_t *vfs_node);
static inline bool vfs_node_unwritable_p(s_vfs_node_t *vfs_node);
static inline bool vfs_node_writable_p(s_vfs_node_t *vfs_node);
static inline s_vfs_node_t * vfs_dir_node_create_i(char *name, f_readdir_t readdir, f_finddir_t finddir);
static inline s_vfs_node_t * vfs_file_node_create_i(char *name, f_read_t read, f_write_t write);
static inline uint32 vfs_node_inode_i(s_vfs_node_t *vfs_node);
static inline uint32 vfs_node_length_i(s_vfs_node_t *vfs_node);
static inline void vfs_multiboot_module_initialize(void);
static inline void vfs_node_flags_add(s_vfs_node_t *vfs_node, uint32 flags);
uint32 vfs_close(s_vfs_node_t *vfs_node);
uint32 vfs_node_inode(s_vfs_node_t *vfs_node);
uint32 vfs_node_length(s_vfs_node_t *vfs_node);
uint32 vfs_open(s_vfs_node_t *vfs_node);
uint32 vfs_read(s_vfs_node_t *vfs_node, uint32 offset, uint32 size, uint8 *buf);
uint32 vfs_write(s_vfs_node_t *vfs_node, uint32 offset, uint32 size, uint8 *buf);
void vfs_initialize(void);

#endif
