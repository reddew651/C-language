data segment
    SCORES DB 56H, 4DH, 5DH, 52H, 64H, 47H, 51H, 5BH, 4FH, 61H
data ends

MAX_SCORE DB 0 
MAX_ID DB 1 

MIN_SCORE DB 56H 
MIN_ID DB 1 

MOV SI, 3000H
MOV DI, 100H 
MOV BP, 200H

MOV AL, [SI] 
MOV BL, 40H
MOV DL, 66H 
MOV CL, 0 

FIND_MAX_MIN:

CMP AL, BL
JG UPDATE_MAX ; 如果当前成绩更高，更新最高分


CMP AL, DL 
JL UPDATE_MIN ; 如果当前成绩更低，更新最低分

NEXT_STUDENT:
INC SI 
INC CL
MOV AL, [SI] 
CMP CL, 9 
JG DONE ; 如果处理完 10 个学生，跳转到 DONE
JMP FIND_MAX_MIN ; 否则继续处理下一个学生

UPDATE_MAX:
MOV BL, AL ; 更新最高分
MOV [DI], CL ; 存储最高分同学编号
MOV [DI+1], AL ; 存储最高分
JMP NEXT_STUDENT

UPDATE_MIN:
MOV DL, AL 
MOV [BP], CL 
MOV [BP+1], AL 
JMP NEXT_STUDENT

DONE:
HLT