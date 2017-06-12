#ifndef HAVE_DEFINED_MULTIBOOT_H
#define HAVE_DEFINED_MULTIBOOT_H

typedef struct multiboot_header      s_multiboot_header_t;
typedef struct multiboot_information s_multiboot_info_t;
typedef struct a_out_symbol_table    s_a_out_symbol_table_t;
typedef struct elf_header_table      s_elf_header_table_t;

/*
 * flags specifies feature that OS image request from boot loader, bit [0-15]
 *     bit  0: all boot module loaded along with 4KB boundaries.
 *     bit  1: the information of memory of multiboot information are include.
 *     bit  2: the information of video mode table are include.
 *     bit 16: the following field of address are vaild.
 *         uint32 header_addr;
 *         uint32 load_addr;
 *         uint32 load_end_addr;
 *         uint32 bss_end_addr;
 *         uint32 entry_addr;
 *
 * Machine state when boot loader jump to 32-bits OS
 *     EAX:    magic value 0x2BADB002 indicated OS loaded by multiboot.
 *     EBX:    physical address of s_multiboot_info_t.
 *     A20:    enabled
 *     CR0:    bit 31 PG cleared, bit 0 PE set
 *     EFLAGS: bit 17 VM cleared, bit 9 IF cleared
 *     ESP:    OS image must create its own stack
 *     GDTR:   be invaild
 *     IDTR:   be invaild
 */
struct multiboot_header {
    uint32 magic;         /* identify header 0x1BADB002 */
    uint32 flags;
    uint32 checksum;
    uint32 header_addr;   /* physical address of this header */
    uint32 load_addr;     /* physical address of .text */
    uint32 load_end_addr; /* physical address of the end of .text */
    uint32 bss_end_addr;  /* physical address of .bss end */
    uint32 entry_addr;    /* physical address of boot loader jump to OS */
    uint32 mode_type;
    uint32 width;
    uint32 heigt;
    uint32 depth;
};

struct a_out_symbol_table {
    uint32 table_size;
    uint32 string_size;
    uint32 addr;
    uint32 reserved;
};

struct elf_header_table {
    uint32 number;
    uint32 size;
    uint32 addr;
    uint32 shndx;
};

/*
 * flags indicates the presence and valid of following fields in structure.
 *     bit  0: memory_lower and memory_upper valid, count in KB.
 *     bit  1: boot_device is vaild, indicated the device of OS image.
 *     bit  4 & 5: exclusive.
 *          4: symbol table from a.out kernel
 *          5: section header table from elf kernel
 *     bit  6: mmap is valid, indicate a buffer contains memory map set by BIOS.
 *     bit  9: boot loader name, contains the physical address of boot loader.
 */
struct multiboot_information {
    uint32 flags;
    uint32 memory_lower;
    uint32 memory_upper;
    uint32 boot_device;
    uint32 cmd_line;
    uint32 mods_count;
    uint32 mods_addr;

    union {
        s_a_out_symbol_table_t symbol;
        s_elf_header_table_t   header;
    };

    uint32 mmap_length;
    uint32 mmap_addr;
    uint32 drives_length;
    uint32 drives_addr;
    uint32 config_table;
    uint32 boot_loader_name;
    uint32 apm_table;
    uint32 vbe_control_info;
    uint32 vbe_mode_info;
    uint32 vbe_mode;
    uint32 vbe_interface_seg;
    uint32 vbe_interface_off;
    uint32 vbe_interface_len;
};

#endif

