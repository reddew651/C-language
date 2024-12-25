//  实现如下功能：
// a) 定义一个Shape类，里面有纯虚函数如GetArea，GetLength, Display。
// b) 从Shape派生一个Triangle类，重载Display方法，另外还有一些自己特有的属性和方法。
// c) 从Shape派生一个Circle类，重载Display方法，另外还有一些特有的属性和方法。
// d) 定义一个函数void printa(Shape*)，打印对象的面积和周长。
// e) 主函数里，定义1个Triangle对象，1个Circle，放在一个指针数组Shape* shapes[]中，调用print打印各个Shape对象的信息.
#include <iostream>
using namespace std;

class Shape{
    public:
        virtual double GetArea() const {return 0;};
        virtual double GetLength() const {return 0;};
        virtual void Display() const {return;};
        virtual ~Shape(){}
};

class Triangle : public Shape{
    private:
        double a;
        double b;
        double c;
    public:
        Triangle(double a, double b, double c) : a(a), b(b), c(c){}

        double GetArea() const override {
            double p = (a + b + c) / 2;
            return sqrt(p * (p - a) * (p - b) * (p - c));
        }

        double GetLength() const override {
            return a + b + c;
        }

        void Display() const override{
            cout << "Triangle: ";
            Shape::Display();
            cout << "a: " << a << ", b: " << b << ", c: " << c << endl;
        }
};

class Circle : public Shape{
    private:
        double r;
    public:
        Circle(): r(0){}
        Circle(double r) : r(r){}

        double GetArea() const override {
            return 3.14*r*r;
        }

        double GetLength() const override{
            return 2*3.14*r;
        }

        void Display() const override{
            cout << "Circle: ";
            Shape::Display();
            cout << "r: " << r << endl;
        }
};

class Square : public Shape{
    private:
        double side;
    public:
        Square(double side) : side(side){}

        double GetLength() const override {
            return side*4;
        }

        double GetArea() const override {
            return side*side;
        }

        void Display() const override {
            cout <<"Square: ";
            Shape::Display();
            cout << "side: " << side << endl;
        }
};

void printa(Shape* s){
    s->Display();
    cout << "Area: " << s->GetArea() << ", Length: " << s->GetLength() << endl;
}

int main(){
    Triangle a(3,4,5);
    Circle b(5);
    Square c(9);
    Shape* shapes[] ={ &a, &b,&c};
    for (Shape* shape : shapes) {
        printa(shape);
        cout << endl;
    }
    return 0;
}