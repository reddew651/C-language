#include <iostream>
using namespace std;

// 基类
class Animal {
public:
    void eat() {
        cout << "Animal is eating." << endl;
    }
};

// 派生类，公有继承基类Animal
class Dog : private Animal {
public:
    void bark() {
        eat();
        cout << "Dog is barking." << endl;
    }
};

int main() {
    Dog myDog;
  // 调用基类的方法
    myDog.bark();   // 调用派生类的方法
    return 0;
}