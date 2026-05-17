[BITS 32]
[org 0x9000]

protected_mode_start:
    ; setting up segment registers
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    ; setup stack (AGAIN)
    mov esp, 0x90000    ; set the current stack pointer

    mov word [0xB8000], 0x0A32

    
    jmp .halt



.halt:
    cli
    hlt
    jmp .halt    ; loop forever



times 512-($-$$) db 0
