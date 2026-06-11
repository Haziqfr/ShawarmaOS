[BITS 32]

extern kernel_main
global _start

_start:
    ; setting up segment registers
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    ; setup stack (AGAIN)
    mov esp, 0x90000    ; set the current stack pointer

    call kernel_main


    jmp .halt



.halt:
    cli
    hlt
    jmp .halt    ; loop forever



times 512-($-$$) db 0
