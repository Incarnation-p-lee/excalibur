#ifndef SRC_INITRD_DECLARATION_H
#define SRC_INITRD_DECLARATION_H

int main(char argc, char **argv);
static inline s_initrd_header_t * initrd_header_array_header(uint32 i);
static inline uint32 initrd_file_copy(FILE *fd, FILE *fs, s_initrd_header_t *header);
static inline uint32 initrd_header_size(void);
static inline void initrd_image_make(uint32 argc, char **argv);

#endif
