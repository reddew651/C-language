.model small
.data
num db 0x8B 
result db 0 

.code
start:
mov ax, @data
mov ds, ax

mov al, num

mov bl, 80h 
test al, bl
jz not_msb_set 

mov bl, 01h 
test al, bl 
jz not_lsb_set             

mov byte ptr [100h], 1
jmp end_program

not_msb_set:
not_lsb_set:
mov byte ptr [100h], 0

end_program:

mov ah, 4Ch
int 21h
end start