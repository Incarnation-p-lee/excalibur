#ifndef HAVE_DEFINED_INITRD_DEFINE_H
#define HAVE_DEFINED_INITRD_DEFINE_H

#define INITRD_NAME       "initrd.img"

#define RETURN_IF_TRUE(x) if (x) { return ; }
#define ARRAY_CNT_OF(a)   (sizeof(a) / sizeof(a[0]))

static s_initrd_header_t  header_array[INITRD_HEADER_MAX];

#endif

