#include <stdio.h>

const int max_n = 100000;
const int max_m = 500000;
const int MAXINT = 100000000;

int heap[max_n+1];
int position[max_n+1];
int lowcost[max_n+1];
int n, m, size;

void decrease_value(int x) {
	int f=x/2; //�õ����ڵ�λ��
	int a;
	a = heap[x]; //�õ���ǰ���

	while(f > 0 && lowcost[a] < lowcost[heap[f]]) 
	{ //��ǰ����lowcost�븸�׽��Ƚ�
		heap[x] = heap[f];
		position[heap[f]] = x;
		x = f;
		f = x/2;
		//add something here  hint�����ȸ��׽���lowcostС����ô����λ��
		
	}
	heap[x] = a; position[heap[x]] = x;//����˫��ӳ��
}

int delete_min() {
	int r,a;
	r = heap[1];
	position[r] = 0;//����ȡ������㣬�޷��ڶ������������r
	a = heap[size]; size--;
	int i = 1,ch = 2;//�Ӹ��ڵ㿪ʼ���µ���
	while (ch <= size) {
		if (ch < size && lowcost[heap[ch]] > lowcost[heap[ch + 1]]) 
		{
			ch++;
				//add something here
		}
		if (lowcost[a] < lowcost[heap[ch]]) {
			break; 
				//add something here
		}
		heap[i] = heap[ch];
		position[heap[i]] = i;
		i = ch;
		ch *= 2;
			//add something here
	}
	heap[i] = a; position[heap[i]] = i;
	return r;
}

int a[max_m + 1]; //��1��ʼ
int b[max_m + 1];
int c[max_m + 1];

int p[max_n + 2];//��n+1��ָ�� ����Ӧ�ô���max_n + 2�Ŀռ�
int linkto[2 * max_m + 1];
int linkcost[2 * max_m + 1];//��

void input_data() {
	scanf("%d %d", &n, &m);
	size = n;
	for (int i = 1; i <= m; i++) {
		scanf("%d %d %d", &a[i], &b[i], &c[i]);
	}
	for (int i = 1; i <= m; i++) {//����ÿ������Ķ�
		p[a[i]]++;
		p[b[i]]++;
	}
	for (int i = 1; i <= n; i++) p[i] = p[i] + p[i - 1];//�൱��ָ�룬�������
	p[n + 1] = p[n];//trick ��һ��ָ��ָ�����һ��Ԫ��
	
	
	for (int i = 1; i <= m; i++) {//�����ڽ�����
		linkto[p[a[i]]] = b[i];
		linkcost[p[a[i]]] = c[i];
		p[a[i]]--;
		linkto[p[b[i]]] = a[i];
		linkcost[p[b[i]]] = c[i];
		p[b[i]]--;

	}
}

void prim() {
	for (int i = 1; i <= n; i++) {
		heap[i] = i; position[i] = i; lowcost[i] = MAXINT;
	}
	lowcost[1] = 0;
	for (int i = 1; i <= n; i++) { //ִ��n�Σ���֤������ÿ������
		int r ;
		r = delete_min();
		//add something here, hint: get r
		if (r > 1) {
			printf("%d\n", lowcost[r]);
		}
		for (int j = p[r] + 1; j <= p[r + 1]; j++) {
			int b = linkto[j];
			if (lowcost[b] > linkcost[j]) {
				lowcost[b] = linkcost[j];//add something here
				if (position[b] > 0) {
				decrease_value(position[b]);//add something here
				}
			}
		}
	}
}

int main() {
	input_data();
	prim();
	return 0;
}
