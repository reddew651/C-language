#include <iostream>
using namespace std;

class Student{
    private:
        string name;
        int id;
    public:
        Student(const string& name, int id) : name(name), id(id) {} //构造函数

        string getName() const { return name; } //返回姓名

        int getId() const { return id; } //返回学号

        virtual void Display() const {
            cout << "Name: " << name << ", Id: " << id << endl;
        }
};

class ScienceStudent : public Student{
    private:
        int year;
    public:
        ScienceStudent(const string&name, int id, int year) : Student(name, id), year(year) {} //构造函数

        void Display() const override {
            cout << "ScienceStudent Name:" << getName() << ", Id: " << getId() << ", year: " << getyear() << endl;
        }
        
        int getyear() const { return year; } //返回系数
};

class EngineeringStudent : public Student{
    private:
        string major;
    public:
        EngineeringStudent(const string& name, int id, const string& major) : Student(name, id), major(major){}

        void Display() const override {
            cout << "EngineeringStudent Name:" << getName() << ", Id: " << getId() << ", Major: " << getMajor() << endl;
        }

        string getMajor() const { return major; } //返回专业
};

void print(Student* s){
    s->Display();
}

void printMore(Student* s){
    ScienceStudent* scis = dynamic_cast<ScienceStudent*>(s);    // Try to cast the student to a ScienceStudent
    EngineeringStudent* engs = dynamic_cast<EngineeringStudent*>(s);

    if (scis) {  // Check if the student is a ScienceStudent
        cout << "Science Student: " << scis->getName() << ", Year: " << scis->getyear() << endl;
    } else if (engs) {  // Check if the student is an EngineeringStudent
        cout << "Engineering Student: " << engs->getName() << ", Major: " << engs->getMajor() << endl;
    } else {
        s->Display();  // Fallback to basic display if type is unknown
    }
}

int main() {
    ScienceStudent Alice("Alice", 2351111,3);
    ScienceStudent Bob("Bob", 23351112,4);
    EngineeringStudent Carrol("Carrol", 23351113, "CS");
    EngineeringStudent David("David", 23351114, "IT");

    Student* students[] = {&Alice, &Bob, &Carrol, &David};
    for (Student* student : students) {
        printMore(student);
    }
    return 0;


}