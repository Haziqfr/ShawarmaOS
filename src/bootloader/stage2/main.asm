org 0x7E00
bits 16


magic  dw 0xBEEF
version dw 1


entry_headers:
 dw main ; location of main/offset
 dw 0 ; segment



main:
  xor ax, ax
  mov ds, ax
  mov si, msg
  call puts


.halt:
  cli
  hlt
  jmp .halt

msg: db "I am stage2, I am alive", 0

puts:
  push si
  push ax

.loop:
  lodsb       ; loads next char from DS:SI into AL
  or al, al
  jz .done
  mov ah, 0x0E ; BIOS teletype print
  int 0x10
  jmp .loop

.done:
  pop ax
  pop si
  ret

times 512-($-$$) db 0
