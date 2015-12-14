[GLOBAL isr_handler_0]
isr_handler_0:
    cli
    push byte 0             ; Push a dummy error code
    push byte 0             ; Push the interrupt number
    jmp  isr_common_handler

%macro ISR_HANDLER_NO_ERRCODE 1
[GLOBAL isr_handler_%1]
isr_handler_%1:
    cli
    push byte 0
    push byte %1
    jmp isr_common_handler
%endmacro

%macro ISR_HANDLER_ERRCODE 1
[GLOBAL isr_handler_%1]
isr_handler_%1:
    cli
    push byte %1
    jmp isr_common_handler
%endmacro

ISR_HANDLER_NO_ERRCODE 1
ISR_HANDLER_NO_ERRCODE 2
ISR_HANDLER_NO_ERRCODE 3
ISR_HANDLER_NO_ERRCODE 4
ISR_HANDLER_NO_ERRCODE 5
ISR_HANDLER_NO_ERRCODE 6
ISR_HANDLER_NO_ERRCODE 7
ISR_HANDLER_ERRCODE    8
ISR_HANDLER_NO_ERRCODE 9
ISR_HANDLER_ERRCODE    10
ISR_HANDLER_ERRCODE    11
ISR_HANDLER_ERRCODE    12
ISR_HANDLER_ERRCODE    13
ISR_HANDLER_ERRCODE    14
ISR_HANDLER_NO_ERRCODE 15
ISR_HANDLER_NO_ERRCODE 16
ISR_HANDLER_NO_ERRCODE 17
ISR_HANDLER_NO_ERRCODE 18
ISR_HANDLER_NO_ERRCODE 19
ISR_HANDLER_NO_ERRCODE 20
ISR_HANDLER_NO_ERRCODE 21
ISR_HANDLER_NO_ERRCODE 22
ISR_HANDLER_NO_ERRCODE 23
ISR_HANDLER_NO_ERRCODE 24
ISR_HANDLER_NO_ERRCODE 25
ISR_HANDLER_NO_ERRCODE 26
ISR_HANDLER_NO_ERRCODE 27
ISR_HANDLER_NO_ERRCODE 28
ISR_HANDLER_NO_ERRCODE 29
ISR_HANDLER_NO_ERRCODE 30
ISR_HANDLER_NO_ERRCODE 31

[EXTERN isr_handler_main]

isr_common_handler:
    pushad             ; push order eax, ecx, edx, ebx, esp, ebp, esi, edi

    mov   ax, ds
    push  eax

    mov   ax, 0x10
    mov   ds, ax
    mov   es, ax
    mov   fs, ax
    mov   gs, ax

    call  isr_handler_main

    pop   eax
    mov   ds, ax
    mov   es, ax
    mov   fs, ax
    mov   gs, ax

    popad
    add esp, 8         ; Cleanup pushed error code and isr number
    sti
    iret               ; When interrupt fires, the processor automatically
                       ; pushed information about the state to the stack,
                       ; include -code segment
                       ;         -instruction pointer
                       ;         -flag register
                       ;         -stack segment
                       ;         -stack pointer
                       ; are pushed.
                       ; The IRET instruction is specifically designed to
                       ; return from an interrupt. It pops these values off
                       ; the stack and return the processor in orignally.
                       ;

