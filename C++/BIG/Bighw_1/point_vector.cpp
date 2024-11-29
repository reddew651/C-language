#include <iostream>
using namespace std;

// 定义Point结构体
struct Point {
    int x,y;

    // 构造函数
    Point(int x = 0, int y = 0) : x(x), y(y) {}

    // 打印点坐标
    void print() const {
        cout << "(" << x << "," << y << ")";
    }

    // 重载+运算符，实现点的逐元素相加
    Point operator+(const Point& other) const {
        return Point(x + other.x, y + other.y);
    }

    // 重载<<运算符，方便输出Point
    friend ostream& operator<<(ostream& os, const Point& pt) {
        os << "(" << pt.x << "," << pt.y << ")";
        return os;
    }
};

// 定义PointVector类，参考std::vector的一些基本特性
class PointVector {
private:
    Point* data;          // 动态数组指针
    unsigned sz;          // 当前元素个数
    unsigned cap;         // 当前容量

    // 私有方法，扩展容量，动态数组的扩容操作
    void resizeCapacity(unsigned newCap) {
        Point* newData = new Point[newCap]; //定义一个新的数组
        for(unsigned i = 0; i < sz; i++) {//将原数组的元素复制到新数组
            newData[i] = data[i];
        }
        delete[] data;  //删除原数组
        data = newData; //将新数组赋值给原数组
        cap = newCap;
    }

public:
    // 默认构造函数
    PointVector() : data(nullptr), sz(0), cap(0) {}

    // 拷贝构造函数，深度复制
    PointVector(const PointVector& other) : data(nullptr), sz(other.sz), cap(other.cap) {
        if(cap > 0) {
            data = new Point[cap];
            memcpy(data, other.data, sz * sizeof(Point));
        }
    }

    // 赋值运算符，深度赋值
    PointVector& operator=(const PointVector& other) {
        if(this == &other) return *this;
        delete[] data;
        sz = other.sz;
        cap = other.cap;
        if(cap > 0) {
            data = new Point[cap];
            for(unsigned i = 0; i < sz; ++i) {
                data[i] = other.data[i];
            }
        } else {
            data = nullptr;
        }
        return *this;
    }

    // 析构函数
    ~PointVector() {delete[] data;}

    // 清空向量
    void clear() {sz = 0;}

    // 判断向量是否为空
    bool empty() const {return sz == 0;}

    // 返回当前元素个数
    unsigned size() const {return sz;}

    // 返回当前容量
    unsigned capacity() const {return cap;}

    // 添加一个元素到末尾
    void push_back(const Point& pt) {
        if(sz == cap) {
            if (cap == 0) resizeCapacity(1);    // 如果容量为0，初始化为1
            else resizeCapacity(cap * 2);   // 否则扩大为原来的2倍
        }
        data[sz++] = pt;
    }

    // 删除最后一个元素
    void pop_back() {
        if(empty()) throw out_of_range("空");
        sz--;
    }

    // 返回第idx个元素的引用，检查越界
    Point& at(unsigned idx) {
        if(idx >= sz) throw out_of_range("越界");
        return data[idx];
    }

    // 返回第idx个元素的常量引用，检查越界
    const Point& at(unsigned idx) const {
        if(idx >= sz) throw out_of_range("越界");
        return data[idx];
    }

    // 返回头一个元素的引用
    Point& front() {
        if(empty())throw out_of_range("空");
        return data[0];
    }

    // 返回最后一个元素的引用
    Point& back() {
        if(empty()) throw out_of_range("空");
        return data[sz - 1];
    }

    // 重载下标运算符，返回元素的引用
    Point& operator[](unsigned idx) {return data[idx];}

    // 重载下标运算符，返回元素的常量引用
    const Point& operator[](unsigned idx) const {return data[idx];}

    // 在pos之前插入一个Point对象
    bool insert(unsigned pos, const Point &pt) {
        if(pos > sz) return false;
        if(sz == cap) { //判断是否需要扩容
            if (cap == 0) resizeCapacity(1);    // 如果容量为0，初始化为1
            else resizeCapacity(cap * 2);   // 否则扩大为原来的2倍
        }
        for(unsigned i = sz; i > pos; --i) {    //通过循环将pos之后的元素向后移动
            data[i] = data[i - 1];
        }
        data[pos] = pt; //最后将pt插入到pos位置
        ++sz;
        return true;
    }

    // 删除pos位置的对象
    bool erase(unsigned pos) {
        if(pos >= sz) return false; //如果pos越界，返回false
        for(unsigned i = pos; i < sz - 1; i++) {
            data[i] = data[i + 1];  //通过循环将pos后面的元素向前移动
        }
        --sz;
        return true;
    }

    // 重载+运算符，实现PointVector的拼接
    PointVector operator+(const PointVector& other) const {
        PointVector result;
        result.resizeCapacity(sz + other.sz);
        result.sz = sz + other.sz;
        memcpy(result.data, data, sz * sizeof(Point));
        for(unsigned i = 0; i < other.sz; ++i) {
            result.data[sz + i] = other.data[i];
        }
        return result;
    }

    // 重载<<运算符，方便输出PointVector
    friend ostream& operator<<(ostream& os, const PointVector& pvec) {
        os << "[";
        for(unsigned i = 0; i < pvec.sz; i++) {
            os << pvec.data[i];
            if(i != pvec.sz - 1) os << ", ";
        }
        os << "]";
        return os;
    }
};

int main() {
    PointVector pvec;
    if(pvec.empty()) cout << "empty point vector!\n";

    for(int i = 0; i < 20; i++) {
        pvec.push_back(Point(i, i));
        cout << "size = " << pvec.size() << ", capacity = " << pvec.capacity() << endl;
    }

    pvec.front().print();
    cout << endl;
    pvec.back().print();
    cout << endl;

    PointVector pvec1(pvec);
    cout << pvec1 << endl;

    PointVector pvec2;
    pvec2 = pvec1;

    for(unsigned j = 0; j < pvec2.size(); j++)
        cout << pvec2.at(j).x << " " << pvec2[j].y << endl;

    pvec.insert(0, Point(100, 100));
    cout << pvec << endl;

    pvec.erase(pvec.size()/2);
    cout << pvec << endl;

    PointVector pvec3 = pvec1 + pvec2;
    cout << pvec3 << endl;

    return 0;
}