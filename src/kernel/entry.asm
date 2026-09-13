[BITS 32]

section .entry
extern kernel_main
global _start

;
; Linker script assumes the address 0xC0000000 as the base VMA. To get physical
; address we must subtract that constant
;

VMA equ 0xC0000000

_start:
    ; Set GDT base address dynamically for pre-paging physical execution
    mov eax, (gdt_start - VMA)
    mov dword [gdt_descriptor_phys + 2 - VMA], eax

    ; Reload GDT
    lgdt [gdt_descriptor_phys - VMA]
    jmp 0x08:(.reload_cs - VMA)     ; Far jump to reload CS

.reload_cs:
    ; setting up segment registers
    mov ax, 0x10        ; 0x10 = Data Segment
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    ; setup stack (AGAIN)
    mov esp, 0x90000    ; set the temporary stack pointer

    mov eax, (boot_pd - VMA)
    mov cr3, eax

    ; Enable paging
    mov eax, cr0
    or eax, 0x80000000
    mov cr0, eax

    ; Force EIP into higher-half virtual address
    lea eax, [.higher_half]
    jmp eax

.higher_half:
    ; Move stack pointer to virtual higher half
    mov esp, VMA + 0x90000

    push ebx
    call kernel_main
    add esp, 4

.halt:
    cli
    hlt
    jmp .halt    ; loop forever

;section .data

align 4
gdt_start:

null_descriptor:
    dd 0
    dd 0

code_segment_descriptor:
    dw 0xFFFF        ; Limit (0-15)
    dw 0x0000        ; Base (0-15)
    db 0x00          ; Base (16-23)
    db 10011010b     ; Access Byte (0-7): P=1, DPL=00, S=1, E=1, DC=0(Non-Conforming), RW=1(Read true), A=0
    db 11001111b     ; Flags (0-3)(upper 4 bit) G=1, DB=1, L=not applicable, AVL=0(IDK why) | Limit (16-19) (lower 4 bit)
    db 0x00          ; Base (24-31)

data_segment_descriptor:
    dw 0xFFFF        ; Limit (0-15)
    dw 0x0000        ; Base (0-15)
    db 0x00          ; Base (16-23)
    db 10010010b     ; Access Byte (0-7): P=1, DPL=00, S=1, E=0, DC=0(Direction Up), RW=1(Write true), A=0
    db 11001111b     ; Flags (0-3)(upper 4 bit): G=1, DB=1, L=not applicable, AVL=0(IDK why) | Limit (16-19) (lower 4 bit)
    db 0x00          ; Base (24-31)

gdt_end:

gdt_descriptor_phys:
    dw gdt_end - gdt_start - 1
    dd 0    ; Address will be saved here at runtime dynamically


align 4096

; Page Directory (1024 entries * 4 bytes = 4096 bytes)
boot_pd:
    ; Entry 0: Indentity map lower memory region (0x0 - 4MiB)
    ; boot_pt1 | P (0x1) | RW (0x2)
    dd (boot_pt1 - VMA) + 0x3

    ; Entries 1 - 767: Empty
    times 767 dd 0

    ; Entry 768: Higher-half map (0xC0000000 - 0xC03FFFFF)
    ; Points to the same table
    dd (boot_pt1 - VMA) + 0x3

    ; Entries 769 - 1023: Empty
    times 255 dd 0

; Page Table 1 (Maps physical 0x0 -> 0x3FFFFF)
boot_pt1:
    %assign i 0
    %rep 1024
        dd (i * 0x1000) | 3 ; Present, Writable
        %assign i i+1
    %endrep
