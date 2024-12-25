#include <iostream>
using namespace std;
class Shape{
    protected:
        double area;
};

class Rectangle : public Shape{
    private:
        double length,width;
    public:
        Rectangle(double l = 0, double w = 0) : length(l), width(w) {}
        double GetArea (){
            area = length * width;
            return area;
        }
        double Getlength(){
            return length;
        }
};

class Circle : public Shape{
    private:
        double radius;
    public:
        Circle (double r = 0) : radius(r) {}
        double GetArea (){
            area = 3.14 * radius * radius;
            return area;
        }
};

class Square : public Rectangle{
    public:
        Square (double side) : Rectangle(side,side) {}
        double GetArea (){
            area = Getlength() * Getlength();
            return area;
        }
};


int main(){
    Rectangle rect(5,10);
    Circle circle(5);
    Square square(5);
    cout << "Area of Rectangle: " << rect.GetArea() << endl;
    cout << "Area of Circle: " << circle.GetArea() << endl;
    cout << "Area of Square: " << square.GetArea() << endl;

}