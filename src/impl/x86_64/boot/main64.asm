global long_mode_start
extern kernel_main
extern keyboard_isr

section .text
bits 64
long_mode_start:
    ; load null into all data segment registers
    mov ax, 0
    mov ss, ax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

	call kernel_main
    hlt

global keyboard_handler
keyboard_handler:
    pushaq
    call keyboard_isr
    popaq
    iretq