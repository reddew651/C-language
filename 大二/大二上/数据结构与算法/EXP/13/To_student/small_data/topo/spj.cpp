#include<fstream>
#include<iostream>
#include<string>
#include<cstdlib>
#include<cstdio>
using namespace std;
ifstream fin, fout, fstd;
ofstream fscore, freport;

const int maxn = 50000;
const int maxm = 500000;

int n,m;
int score;

int a[maxm + 1];
int b[maxm + 1];
int f[maxn + 2]; //����
int f_in[maxn + 1]; //���
int linkto[maxm + 1];


void get_data() {
	fin >> n >> m;
	for (int i = 1; i <= m; i++) {
		fin >> a[i] >> b[i];
	}
	for (int i = 1; i <= m; i++) {
		f[a[i]]++;
		f_in[b[i]]++;
	}
	for (int i = 1; i <= n; i++) f[i] = f[i] + f[i - 1];

	f[n + 1] = f[n];

	for (int i = 1; i <= m; i++) {
		int x = f[a[i]];
		linkto[x] = b[i];
		f[a[i]]--;
	}
}

void judge()
{
	int flag = 1;
	get_data();
	for (int i = 1; i <= n; i++) 
	{
		int x;
		fstd >> x;
		if (f_in[x] != 0) {
			freport << "Invalid result!"<< "x:"<<x<<endl;
			fscore << 0 << endl;
			flag = 0;
		}
		else {
			for (int j = f[x] + 1; j <= f[x + 1]; j++) {
				f_in[linkto[j]]--;
			}
		}
	}
	if (flag) {
		fscore << score << endl;
		freport << "Success" << endl;
	}

}

int main(int argc, char* argv[])
{

	//put something to fstreams...
/*
argv[1]:�����ļ�
argv[2]:ѡ������ļ�
argv[3]:��׼����ļ�
argv[4]:�������Ե��ֵ
argv[5]:������յ÷ֵ��ļ�
argv[6]:������󱨸���ļ�
*/
	fin.open(argv[1]);
	fout.open(argv[2]);
	fstd.open(argv[3]);
	fscore.open(argv[5]);
	freport.open(argv[6]);
	score = atoi(argv[4]);

	judge();

	fin.close();
	fout.close();
	fstd.close();
	fscore.close();
	freport.close();
	return 0;
}
