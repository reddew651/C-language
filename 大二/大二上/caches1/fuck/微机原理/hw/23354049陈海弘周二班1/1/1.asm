;you should write the data by yourself in the memory
DATA SEGMENT 
MOV SI,1000H ;数据源起始地址
MOV DI,3000H ;数据目标起始地址 
MOV CX,20    ;cycle time

START:
MOV AL,[SI]  ;move now memory data to the al
CMP AL,32H   ;compare whether the data is bigger than 50,so32H
JBE SKIP     ;if not, run skip quickly
MOV [DI],AL  ;if right, then we find the target, move it to the di
ADD DI,1

SKIP:
ADD SI,1
LOOP START

HLT          ;stop

;The English is written by myself not ai. Chenhaihong