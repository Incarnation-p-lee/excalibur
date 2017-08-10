#ifndef SRC_TEST_DECLARATION_H
#define SRC_TEST_DECLARATION_H

static inline void test_heap(void);
static inline void test_isr(void);
static inline void test_page(void);
static inline void test_vfs(void);
static inline void test_vfs_file_print(s_vfs_node_t *vfs_node);
static inline void test_vfs_initrd(void);
void test_main(void);

#endif
