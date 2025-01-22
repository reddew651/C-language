.model small
.data
num1 db 0x5C
num2 db 0xA1
num3 db 0x86

.code
start:
mov ax, @data
mov ds, ax   

mov al, num1
mov bl, num2
cmp al, bl
jle skip1 
mov al, bl 
  
skip1:
mov bl, num3
cmp al, bl                   
jle skip2 
mov al, bl

skip2:
mov di, 0000H
mov [di], al

mov ah, 4Ch
int 21h
end start