.model small
.stack 100h
.data
scores db 56H, 4DH, 5DH, 52H, 64H, 47H, 51H, 5BH, 4FH, 61H ; Initial scores data
.code
main proc
mov ax, @data
mov ds, ax
mov ax, 3100h ; Set segment for storing data
mov es, ax
mov cx, 10 ; Counter for 10 students
mov si, offset scores
mov di, 0
copy_loop: ; Copy scores to memory starting at 3000H
mov al, [si]
mov es:[di], al
inc si
inc di
loop copy_loop
call calculate_ranks ; Call ranking subroutine
mov ax, 4c00h
int 21h
main endp

calculate_ranks proc
push ax ; Save registers
push bx
push cx
push dx
push si
push di
mov ax, 3100h ; Set data segment for ranking
mov ds, ax
mov cx, 10 ; Number of students
mov si, 0
outer_loop: ; Main loop for each student
push cx
mov dx, 1 ; Initial rank = 1
mov cx, 10
mov di, 0
inner_loop: ; Compare with other scores
mov al, es:[si] ; Current student's score
mov bl, es:[di] ; Score to compare with
cmp al, bl ; Compare scores
jae next_compare ; Skip if current score is higher
inc dx ; Increment rank if lower
next_compare:
inc di
loop inner_loop
mov [si+100h], dl ; Store rank at 3100H + offset
inc si
pop cx
loop outer_loop
pop di ; Restore registers
pop si
pop dx
pop cx
pop bx
pop ax
ret
calculate_ranks endp
end main
;written by Chen Haihong
