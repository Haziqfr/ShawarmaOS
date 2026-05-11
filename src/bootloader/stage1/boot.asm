org 0x7C00
bits 16

start:
  jmp main


puts:
  push si
  push ax

.loop:
  lodsb       ; loads next char in al
  or al, al
  jz .done


  mov ah, 0x0E
  int 0x10

  jmp .loop

.done:
  pop ax
  pop si
  ret



main:


  cli
  ; setup data segement
  xor ax, ax     ; we can't write directly to data segement
  mov ds, ax
  mov es, ax

  ; setup stack
  mov ss, ax
  mov sp, 0x9000 ; stack grows downward

  mov [boot_drive], dl
  sti


  mov si, msg
  call puts

  jmp read



read:

    mov si, 3

.retry:

  mov ax, 0x0000  ; segement
  mov es, ax
  mov ax, 0x0201    ; AX=02h, AL=01h
;  mov al, 1       ; read sector 1
  mov cx, 0x0002
;  mov cl, 2
  mov dl, [boot_drive]    ; Drive = first floppy
  mov dh, 0       ; head number
  mov bx, 0x7E00


  int 13h
  jnc .ok
  jc .fail


.fail:
  dec si
  jnz .retry

  jmp error

.ok:

  ; Validation before jump
  cmp word [0x7E00], 0xBEEF
  jne error
  jmp far [0x7e04]



.halt:
  jmp .halt


error:

  mov si, err_msg
  call puts

boot_drive: db 0
err_msg: db "Not found", 0x0D, 0x0A, 0
.halt:
  jmp .halt
msg: db "Booting...", 0x0D, 0x0A, 0


times 510-($-$$) db 0
dw 0xAA55
