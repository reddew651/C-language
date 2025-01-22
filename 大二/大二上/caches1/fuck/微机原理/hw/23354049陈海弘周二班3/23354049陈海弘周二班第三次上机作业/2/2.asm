.model small
.stack 100h

.data
arr db 51h, 3Ah, 95h, 8Dh, 90h, 0A7h, 0C1h, 77h, 24h, 0B1h

.code
main:
mov ax, @data  ;LOAD DATE INTO AX
mov ds, ax

mov cx, 10

outer_loop:
mov si, 0
mov di, cx   ;DI SOTORES THE REMAINING NUMBER
dec di

inner_loop:
mov al, [arr + si]
mov bl, [arr + si + 1]
cmp al, bl
jbe no_swap    ;IF AL <=BL SKIP SWAP

xchg al, bl
mov [arr + si], al
mov [arr + si + 1], bl

no_swap:
inc si
dec di
jnz inner_loop

dec cx
jnz outer_loop

mov si, 0
mov di, 3000h
mov cx, 10
 ;ALL WRITTEN BY CHEN HAIHONG
move_data:
mov al, [arr + si]
mov [di], al
inc si
inc di
loop move_data    ;REPEAT UNTILLCS REACHES 0

mov ah, 4Ch
int 21h     ;CALL DOS INTERRUPT

end main
