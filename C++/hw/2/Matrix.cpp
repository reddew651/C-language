#include <iostream>
#include <cassert>
#include <vector>
using namespace std;

class Matrix {
	private:
		double *data;
		int nRows, nColumns;
	public:
		Matrix(int rows, int cols):nRows(rows),nColumns(cols){
			data = new double[rows*cols]();
			memset(data, 0, size());		//sizeof(double)*rows*cols
		}

		~Matrix(){delete[] data;}

		Matrix(const Matrix& other) : nRows(other.nRows),nColumns(other.nColumns){
			data = new double[nRows * nColumns]();
			nRows = other.nRows;
			nColumns = other.nColumns;
			memcpy(data, other.data, size());	/*for (int i=0; i < nRows * nColumns; i++){data [i] = other.data[i];}*/
		}

		Matrix& operator = (const Matrix& other){
			if (this == &other) return *this;
			delete[] data;
			nRows = other.nRows;
			nColumns = other.nColumns; 
			data = new double [nRows * nColumns];
			memcpy(data, other.data, size());	/*for (int i=0; i < nRows * nColumns;i++){data [i] = other.data[i];}*/
			return *this;
		}

		int nElements(){return nRows * nColumns;}
		
		int size() const{return sizeof(double)*nRows * nColumns;}

		void set(int row, int col, double value){data [row*nColumns + col] = value;}

		double get(int row, int col) const {
			assert (row >= 0 && row < nRows && col >= 0 && col < nColumns);
			return data [row*nColumns + col];
		}

		void printrow(int row,vector<double>& vec) const {
			for (int col = 0; col < nColumns; col++){
				vec.push_back(get(row, col));
				cout << get (row, col) << " "; 
			}
		}

		void printcol (int col,vector<double>& vec) const {
		for (int row = 0; row < nRows; row++){
			vec.push_back(get(row, col));	//cout << get (row, col) << endl;
			}
		}

		void printma () const {
			for (int row =0 ;row< nRows;row++){
				for (int col = 0; col < nColumns; col++){
					cout << get (row, col) << " ";
				}
				cout<<endl;
			}
			cout<<endl;
		}

		void add (const Matrix& other){
			for (int i=0;i<nRows*nColumns;i++){
				data[i]+= other.data[i];
			}
		}

		void sub (const Matrix& other){
			for (int i=0;i<nRows*nColumns;i++){
				data[i]-=other.data[i];
			}
		}

		Matrix operator + (const Matrix& other)const {
			Matrix result (nRows, nColumns);
			memcpy(result.data, data, size());	//for (int i=0;i<nRows*nColumns;i++){result.data[i]=data[i]+other.data[i];}
			return result;
		}
		Matrix operator - (const Matrix& other)const {
			Matrix result (nRows, nColumns);
			memcpy(result.data, data, size());	//for (int i=0;i<nRows*nColumns;i++){result.data[i]=data[i]-other.data[i];}
			return result;
		} 
};

int main(){
	vector<double> vec;
	Matrix m1(2,3);Matrix m2(2,3);
	m1.set(0,0,1);m1.set(0,1,2);m1.set(0,2,3);m1.set(1,0,2);m1.set(1,1,4);m1.set(1,2,6);m1.printma();
	m2=m1;m2.printma();
	m1.add(m2);m1.printma();
	m1=m1+m2;m1.printma();
} 

