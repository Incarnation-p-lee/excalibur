[GLOBAL isr_handler_0]
isr_handler_0:
    cli
    push byte 0x0           ; Push a dummy error code
    push byte 0x0           ; Push the interrupt number
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
    pusha              ; push order eax, ecx, edx, ebx, esp, ebp, esi, edi
    push ds
    push es
    push fs
    push gs

    call  isr_handler_main

    pop  gs
    pop  fs
    pop  es
    pop  ds
    popa 

    add  esp, 8
    sti
    iret               ; When interrupt fires, the processor automatically
                       ; pushed information about the state to the stack,
                       ; include -code segment
                       ;         -instruction pointer
                       ;         -flag register
                       ;         -stack segment
                       ;         -stack pointer
                       ; are pushed with order
                       ;         - ss
                       ;         - esp
                       ;         - flags
                       ;         - cs
                       ;         - ip
                       ; The IRET instruction is specifically designed to
                       ; return from an interrupt. It pops these values off
                       ; the stack and return the processor in orignally.
                       ;

%macro IRQ_HANDLER 2
[GLOBAL irq_handler_%1]
irq_handler_%1:
    cli
    push byte 0
    push byte %2
    jmp  irq_common_handler
%endmacro

[EXTERN irq_handler_main]

IRQ_HANDLER  0, 32
IRQ_HANDLER  1, 33
IRQ_HANDLER  2, 34
IRQ_HANDLER  3, 35
IRQ_HANDLER  4, 36
IRQ_HANDLER  5, 37
IRQ_HANDLER  6, 38
IRQ_HANDLER  7, 39
IRQ_HANDLER  8, 40
IRQ_HANDLER  9, 41
IRQ_HANDLER 10, 42
IRQ_HANDLER 11, 43
IRQ_HANDLER 12, 44
IRQ_HANDLER 13, 45
IRQ_HANDLER 14, 46
IRQ_HANDLER 15, 47

irq_common_handler:
    pusha
    push ds
    push es
    push fs
    push gs

    call irq_handler_main

    pop  gs
    pop  fs
    pop  es
    pop  ds
    popa

    add  esp, 8
    sti
    iret

