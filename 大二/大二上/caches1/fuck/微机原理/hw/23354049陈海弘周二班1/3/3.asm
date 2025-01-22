data segment
X db 16h, 35h, 18h, 12h, 24h, 30h, 2Eh, 1Ch, 0Fh, 45h, 2Ah, 10h, 20h, 22h, 31h, 17h ; X 段数据
Y db 23h, 40h, 29h, 2Ch, 19h, 11h, 33h, 0Ch, 1Ah, 27h, 3Bh, 14h, 28h, 1Fh, 2Eh, 05h ; Y 段数据
RESULT db 16 dup(0) ;SET ALL DATA TO 0
data ends

code segment
start:
mov ax, data ; PUT THE DATA INTO AX
mov ds, ax ; INITIALIZE THE AX TO DS

lea si, X ; X FIRST ADDRESS TO SI
lea di, Y ; SAME AS UPPER
lea bx, RESULT ; RESULT ADDRESS TO THE BX
mov cx, 16 

process_loop:
mov al, [si] 
add al, [di] 
cmp al, 64h 
ja skip_store ;IF BIGGER THAN 64H, SKIP

mov [bx], al ; IF RIGHT, SMALLER THAN 64H PUT IT INTO BX
inc bx ;TO NEXT

skip_store:
inc si ; X TO THE NEXT
inc di ; SAME AS UPPER
loop process_loop 

hlt 
code ends

end start    

;WRITTEN BY CHENHAIHONG.