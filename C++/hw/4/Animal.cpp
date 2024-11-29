#include <iostream>
using namespace std;
class Animal {
    public:
        int age;
    public:
        Animal (int a = 0) : age(a) {}
        ~Animal() {}
        void setAge(int a){
            age = a;
        }
        int GetAge() const {
            return age;
        }
};

class Dog : public Animal {
    public:
        Dog(int a = 0) : Animal(a) {}
        void bark() {
            cout << "Woof! Woof!" << endl;
        }
        /*void SetAge(int a) {
            setAge(a);
        }
        */
        void show(){
            cout << "Age: " << GetAge() << endl;
        }
};

int main(){
    Dog mydog(3);
    mydog.bark();
    mydog.show();
    mydog.setAge(5);
    mydog.show();
    return 0;
}