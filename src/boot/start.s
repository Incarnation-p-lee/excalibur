;
; boot.s kernel start location, also defined multiboot header.
;

BOOT_PAGE_ALIGN   equ 1 << 0     ; Ask GRUB to page-align all kernel sections
BOOT_MEM_INFO     equ 1 << 1     ; Provide kernel with memory info
BOOT_HEADER_MAGIC equ 0x1badb002 ; Mutiboot magic number, identify as multiboot
                                 ; Do not use BOOT_AOUT_KLUDGE, grub does not 
                                 ; pass us a symbol table.

BOOT_HEADER_FLAGS equ BOOT_PAGE_ALIGN | BOOT_MEM_INFO
BOOT_CHECKSUM     equ -(BOOT_HEADER_MAGIC + BOOT_HEADER_FLAGS)

[BITS 32]

[GLOBAL boot]                    ; Make boot accessible from C code.
[EXTERN code]                    ; Start of .text section
[EXTERN bss]
[EXTERN end]                     ; End of last location section

boot:
    dd BOOT_HEADER_MAGIC         ; Grub search this for 4 byte boundary
    dd BOOT_HEADER_FLAGS         ; Grub load your file / settings
    dd BOOT_CHECKSUM

    dd boot                      ; Address of this descriptor
; All below defined by linker, to tell GRUB sections of kernel can be loaded
    dd code                      ; Start address of .text section
    dd bss
    dd end
    dd start                     ; Kernel entry point, initial eip

[GLOBAL start]                   ; Kernel entry point
[EXTERN main]                    ; Entry point of C code

start:
; On bootup, GRUB will load a pointer to another information structure into the
; ebx register
    push       ebx               ; Load multiboot header location

    ; Start to execute kernel
    cli                          ; Disable interrupts
    call main                    ; Call main function in C
    jmp $

