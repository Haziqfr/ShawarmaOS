org 0x7C00
bits 16

start:
  jmp far 0:main


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
  cld    ; clear direction flag so loadsb behaves properly
  
  ; setup data segement
  xor ax, ax     ; we can't write directly to data segement
  mov ds, ax
  mov es, ax

  ; setup stack
  mov ss, ax
  mov sp, 0x9000 ; stack grows downward

  mov [boot_drive], dl    ; save boot drive
  sti


  mov si, msg
  call puts

  mov al, [boot_drive]
  cmp al, 0x80
  jae read


probe_floppy:
  mov si, floppy_selectors

.probe_loop:
  mov cl, [si]
  or cl, cl
  jz error

  push ax
  xor ax, ax
  mov dl, [boot_drive]
  int 0x13
  pop ax

  mov ax, 0x0201
  mov ch, 0
  mov dh, 0
  mov dl, [boot_drive]

  push es
  xor bx, bx
  mov es, bx
  mov bx, 0x7E00
  int 0x13
  pop es

  jnc .probe_success

  inc si
  jmp .probe_loop



.probe_success:
  mov [sectors_per_track], cl
  jmp read



read:

    mov si, 3

.retry:

  mov ax, 0x0000    ; segement
  mov es, ax
  mov ax, 0x0201    ; AH=02h, AL=01h
;  mov al, 1        ; read sector 1
  mov cx, 0x0002
;  mov cl, 2
  mov dl, [boot_drive]    ; Drive = first floppy
  mov dh, 0         ; head number
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
  ;cmp word [0x7E00], 0xBEEF
  ;jne error
  jmp far 0:0x7e00



.halt:
  jmp .halt


error:

  mov si, err_msg
  call puts

boot_drive: db 0
sectors_per_track: db 0
floppy_selectors: db 36, 18, 15, 9, 0

err_msg: db "Not found", 0x0D, 0x0A, 0

.halt:
  jmp .halt
  
msg: db "Booting...", 0x0D, 0x0A, 0


times 510-($-$$) db 0
dw 0xAA55
