org 0x7E00
bits 16


magic  dw 0xBEEF
version dw 1


entry_headers:
 dw main ; location of main/offset
 dw 0    ; segment



main:
  xor ax, ax
  mov ds, ax
  mov si, msg
  call puts


  call get_a20_state


  cmp ax, 1
  je .halt

  call enable_a20

  jmp .halt


.halt:
  cli
  hlt
  jmp .halt

msg: db "I am stage2, I am alive", 0x0D, 0x0A, 0


;	out:
;		ax - state (0 - disabled, 1 - enabled)
get_a20_state:
	pushf
	push si
	push di
	push ds
	push es
	cli

	mov ax, 0x0000					;	0x0000:0x0500(0x00000500) -> ds:si
	mov ds, ax
	mov si, 0x0500

	not ax						    ;	0xffff:0x0510(0x00100500) -> es:di
	mov es, ax
	mov di, 0x0510

	mov al, [ds:si]					;	save old values
	mov byte [.BufferBelowMB], al
	mov al, [es:di]
	mov byte [.BufferOverMB], al

	mov ah, 1
	mov byte [ds:si], 0
	mov byte [es:di], 1
	mov al, [ds:si]
	cmp al, [es:di]					;	check byte at address 0x0500 != byte at address 0x100500
	jne .exit
	dec ah
.exit:
	mov al, [.BufferBelowMB]
	mov [ds:si], al
	mov al, [.BufferOverMB]
	mov [es:di], al
	shr ax, 8					    ;	move result from ah to al register and clear ah
	pop es
	pop ds
	pop di
	pop si
	popf
	ret

	.BufferBelowMB:	db 0
	.BufferOverMB	db 0




enable_a20:

.bios_int:    ; Try to enable A20 via BIOS interrupts

    mov ax, 0x2401            ; Query A20 gate support
    int 0x15

    jc .fast
    cmp ah, 0
    jne .fast

    call get_a20_state

    cmp ax, 1
    jne .fast

    ret



.fast:
    in al, 0x92
    or al, 00000010b
    and al, 11111110b
    out 0x92, al

    call get_a20_state

    cmp ax, 1
    jne .keyboard

    ret


.keyboard:
pushf
cli                     ; disable interrupts

call    .a20wait
mov     al,0xAD
out     0x64,al         ; disable keyboard

call    .a20wait
mov     al,0xD0
out     0x64,al         ; read controller output port

call    .a20wait2
in      al,0x60         ; save response byte
push    ax

call    .a20wait
mov     al,0xD1
out     0x64,al         ; write next byte into controller output port

call    .a20wait
pop     ax
or      al,2            ; set controller output bit for A20 on
out     0x60,al         ; activate A20

call    .a20wait
mov     al,0xAE
out     0x64,al         ; reactivate keyboard

call    .a20wait

popf
ret

.a20wait:                        ; wait until input buffer is clear
in      al,0x64
test    al,2
jnz     .a20wait
ret


.a20wait2:                       ; wait until response byte has arrived
in      al,0x64
test    al,1
jz      .a20wait2
ret



puts:
 push si
 push ax

 .loop:
 lodsb ; loads next char from DS:SI into AL
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
