#include <iostream>
using namespace std;

// 结构体用于存储非零元素的行、列和值
struct NonzeroElement {
    int row, col;
    double value;

    // 重载 == 运算符，用于比较两个非零元素是否相等
    bool operator==(const NonzeroElement& other) const {
        return row == other.row && col == other.col;
    }
};

// 普通矩阵类
class Matrix {
private:
    int nRows, nColumns;
    double** data;

public:
    // 构造函数，初始化矩阵的行数、列数和数据
    Matrix(int rows, int cols) : nRows(rows), nColumns(cols) {
        data = new double*[nRows];
        for (int i = 0; i < nRows; ++i) {
            data[i] = new double[nColumns]();
        }
    }

    // 析构函数
    ~Matrix() {
        for (int i = 0; i < nRows; ++i) {
            delete[] data[i];
        }
        delete[] data;
    }

    // 设置矩阵中指定位置的元素值
    void set(int row, int col, double value) {
        if (row >= nRows || col >= nColumns || row < 0 || col < 0) {
            throw out_of_range("越界");
        }
        data[row][col] = value;
    }

    // 获取矩阵中指定位置的元素值
    double get(int row, int col) const {
        if (row >= nRows || col >= nColumns || row < 0 || col < 0) {
            throw out_of_range("越界");
        }
        return data[row][col];
    }

    int getRows() const { return nRows; }
    int getCols() const { return nColumns; }

    void printMatrix() const {
        for (int i = 0; i < nRows; ++i) {
            for (int j = 0; j < nColumns; ++j) {
                cout << data[i][j] << " ";
            }
            cout << endl;
        }
    }
};

// 稀疏矩阵类
class SparseMatrix {
private:
    int nRows, nColumns;
    NonzeroElement* data;
    int dataSize;      // 非零元素的数量
    int capacity;      // 动态数组的容量

    void resize() {
        capacity *= 2;
        NonzeroElement* newData = new NonzeroElement[capacity];
        memcpy(newData, data, dataSize * sizeof(NonzeroElement));
        delete[] data;
        data = newData;
    }

public:
    SparseMatrix(int rows, int cols) : nRows(rows), nColumns(cols), dataSize(0), capacity(10) {
        data = new NonzeroElement[capacity];
    }

    // 从普通矩阵构造稀疏矩阵
    SparseMatrix(const Matrix& matrix) : nRows(matrix.getRows()), nColumns(matrix.getCols()), dataSize(0), capacity(10) {
        data = new NonzeroElement[capacity];
        for (int i = 0; i < nRows; ++i) {
            for (int j = 0; j < nColumns; ++j) {
                double value = matrix.get(i, j);
                if (value != 0.0) {
                    if (dataSize == capacity) resize();
                    data[dataSize].row = i;
                    data[dataSize].col = j;
                    data[dataSize].value = value;
                    dataSize++;
                }
            }
        }
    }

    ~SparseMatrix() {
        delete[] data;
    }

    // 复制构造函数
    SparseMatrix(const SparseMatrix& other) : nRows(other.nRows), nColumns(other.nColumns), dataSize(other.dataSize), capacity(other.capacity) {
        data = new NonzeroElement[capacity];
        memcpy(data, other.data, dataSize * sizeof(NonzeroElement));
    }

    // 赋值运算符
    SparseMatrix& operator=(const SparseMatrix& other) {
        if (this == &other) return *this;
        delete[] data;
        nRows = other.nRows;
        nColumns = other.nColumns;
        dataSize = other.dataSize;
        capacity = other.capacity;
        data = new NonzeroElement[capacity];
        memcpy(data, other.data, dataSize * sizeof(NonzeroElement));
        return *this;
    }

    // 设置稀疏矩阵中指定位置的元素值
    void set(int row, int col, double value) {
        for (int i = 0; i < dataSize; ++i) {
            if (data[i].row == row && data[i].col == col) {
                if (value == 0) {   // 如果新值为0，则删除该元素
                    data[i] = data[--dataSize]; // 将最后一个元素移到当前位置，节省空间
                } else {
                    data[i].value = value;  // 否则更新该元素的值
                }
                return;
            }
        }
        if (value != 0) {
            if (dataSize == capacity) resize();
            data[dataSize].row = row;
            data[dataSize].col = col;
            data[dataSize].value = value;
            dataSize++;
        }
    }

    // 获取稀疏矩阵中指定位置的元素值
    double get(int row, int col) const {
        for (int i = 0; i < dataSize; ++i) {
            if (data[i].row == row && data[i].col == col) {
                return data[i].value;
            }
        }
        return 0.0;
    }

    // 打印稀疏矩阵
    void printMatrix() const {
        for (int i = 0; i < nRows; i++) {
            for (int j = 0; j < nColumns; j++) {
                cout << get(i, j) << " ";
            }
            cout << endl;
        }
    }

    void add(const SparseMatrix& other) {
        if (nRows != other.nRows || nColumns != other.nColumns) {
            throw invalid_argument("矩阵不匹配，无法相加");
        }
        for (int i = 0; i < other.dataSize; ++i) {
            set(other.data[i].row, other.data[i].col, get(other.data[i].row, other.data[i].col) + other.data[i].value);
        }
    }

    SparseMatrix operator+(const SparseMatrix& other) const {
        SparseMatrix result(*this);
        result.add(other);
        return result;
    }
};

int main() {
    Matrix matrix1(3, 3);
    matrix1.set(0, 0, 1.0);
    matrix1.set(1, 2, 2.5);
    matrix1.set(2, 1, -3.2);

    cout << "Matrix1:" << endl;
    matrix1.printMatrix();

    SparseMatrix sparseMatrix1(matrix1);
    cout << "Sparse Matrix1:" << endl;
    sparseMatrix1.printMatrix();

    SparseMatrix sparseMatrix2 = sparseMatrix1;
    cout << "Sparse Matrix2 (copy of Sparse Matrix1):" << endl;
    sparseMatrix2.printMatrix();

    sparseMatrix2.set(0, 1, 4.5);
    sparseMatrix2.set(1, 2, 0.0);

    cout << "Sparse Matrix2 (after modification):" << endl;
    sparseMatrix2.printMatrix();

    SparseMatrix sparseMatrix3 = sparseMatrix1 + sparseMatrix2;
    cout << "Sparse Matrix3 (Sparse Matrix1 + Sparse Matrix2):" << endl;
    sparseMatrix3.printMatrix();

    return 0;
}