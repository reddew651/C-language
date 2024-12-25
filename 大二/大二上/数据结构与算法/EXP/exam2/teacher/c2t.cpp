#include<iostream>
using namespace std;

struct Node {
    char data;
    int parent, lchild, rchild;
} nodes[101];
int n, lastchild[101];

void buildTree(){
  cin >> n;
  for (int i = 1; i <= n; i++)
	  cin >> nodes[i].data >> nodes[i].parent;
  for (int i = 2; i <= n; i++){
	int f = nodes[i].parent;
	if (lastchild[f] == 0)
		nodes[f].lchild = lastchild[f] = i;
	else{
		int j = lastchild[f]; 
		nodes[j].rchild = lastchild[f] = i;
	}
  }
}

void Preorder(Node &root){ //please finish the following parts
	cout << root.data;
	if (root.lchild != 0) Preorder(nodes[root.lchild]);
	if (root.rchild != 0) Preorder(nodes[root.rchild]);
}
void Midorder(Node &root){ //please finish the following parts
	if (root.lchild != 0) Midorder(nodes[root.lchild]);
	cout << root.data;
	if (root.rchild != 0) Midorder(nodes[root.rchild]);
}

int main(){
  buildTree();
  Preorder(nodes[1]); cout<<"\n";
  Midorder(nodes[1]);
  return 0;
}
