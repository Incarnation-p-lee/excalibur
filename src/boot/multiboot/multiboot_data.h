#ifndef HAVE_DEFINED_MULTIBOOT_INFO_H
#define HAVE_DEFINED_MULTIBOOT_INFO_H

typedef enum multiboot_data_type e_multiboot_data_type_t;
typedef struct multiboot_data    s_multiboot_data_t;

enum multiboot_data_type {
    MULTIBOOT_HEADER,
    MULTIBOOT_INFO,
    MULTIBOOT_DATA_TYPE_LIMIT,
};

struct multiboot_data {
    uint32               valid_mask;
    s_multiboot_header_t header;
    s_multiboot_info_t   info;
};

static s_multiboot_data_t multiboot_data = {
    0,
};

#endif

