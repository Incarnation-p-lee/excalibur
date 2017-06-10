;
; boot.s kernel start location, also defined multiboot header.
;

BOOT_PAGE_ALIGN   equ 1 << 0     ; Ask GRUB to page-align all kernel sections
BOOT_MEM_INFO     equ 1 << 1     ; Provide kernel with memory info
BOOT_HEADER_MAGIC equ 0x1badb002 ; Mutiboot magic number, identify as multiboot
                                 ; Do not use BOOT_AOUT_KLUDGE, grub does not 
                                 ; pass us a symbol table.
BOOT_STACK_SIZE   equ 4096

BOOT_HEADER_FLAGS equ BOOT_PAGE_ALIGN | BOOT_MEM_INFO
BOOT_CHECKSUM     equ -(BOOT_HEADER_MAGIC + BOOT_HEADER_FLAGS)

[BITS 32]

[GLOBAL boot]                    ; Make boot accessible from C code.
[EXTERN code]                    ; Start of .text section
[EXTERN bss]
[EXTERN end]                     ; End of last location section

boot:
    dd   BOOT_HEADER_MAGIC       ; Grub search this for 4 byte boundary
    dd   BOOT_HEADER_FLAGS       ; Grub load your file / settings
    dd   BOOT_CHECKSUM

    dd   boot                    ; Address of this descriptor
; All below defined by linker, to tell GRUB sections of kernel can be loaded
    dd   code                    ; Start address of .text section
    dd   bss
    dd   end
    dd   start                   ; Kernel entry point, initial eip
    dd   0x0                     ; Mode_type
    dd   0x0                     ; Width
    dd   0x0                     ; Height
    dd   0x0                     ; Depth

stack:
    times BOOT_STACK_SIZE db 0   ; Reserved 4KB for stack

[GLOBAL start]                   ; Kernel entry point
[EXTERN entry]                   ; Entry point of C code

start:
; On bootup, GRUB will set ebx to one multboot information structure.
; and a magic bootloader 0x2badb002 to eax
    mov  esp, stack + BOOT_STACK_SIZE
    push 0                       ; Reset EFLAGS
    popf
    push ebx
    push boot
    push eax

; Start to execute kernel
    cli                          ; Disable interrupts
    call entry                   ; Call main function in C
    jmp $

