#include <iostream>

ALGraph *Create_Graph(ALGraph * G){
  printf("请输入图的种类标志：") ;
  scanf("%d", &G->kind) ;
  return(G) ; 
}
