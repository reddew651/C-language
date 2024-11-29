#include <iostream>
#include <string>
#include <vector>
using namespace std;

static const int maxCourses = 3; // 每个学生最多选3门课程

// 定义学生类，包含学号、姓名、课程名、成绩，我额外加了课程数，用来记录选了几门课
class Student {
private:
    int id; // 学号
    string name; // 姓名
    string courseNames[maxCourses]; // 课程名数组
    double grades[maxCourses]; // 成绩数组
    int courseCount; // 课程数

public:
    int size() const { return sizeof(courseNames); } // 返回课程名数组的大小

    // 默认构造函数,初始化学号为0，姓名为空，课程数为0
    Student() : id(0), name(""), courseCount(0){}

    // 非默认构造函数，初始化学号为id，姓名为name，课程数为0，&name表示引用
    Student(int id, const string &name) : id(id), name(name), courseCount(0) {}

    // 拷贝构造函数,引用m的id，name，courseCount，这里我没有用for循环，而是用memcpy函数，比for循环效率高，简洁
    Student(const Student& m) : id(m.id), name(m.name), courseCount(m.courseCount) {
        memcpy(courseNames, m.courseNames, size()); 
        memcpy(grades, m.grades, sizeof(grades)); 
    }

    int getId() const { return id; } // 获取学号
    void setId(int id) { this->id = id; } // 设置学号

    string getName() const { return name; } // 获取姓名
    void setName(const string &name) { this->name = name; } // 设置姓名

    // 添加课程，返回是否添加成功
    bool AddCourse(const string &courseName, double grade) {
        if (courseCount < maxCourses) { 
            courseNames[courseCount] = courseName; 
            grades[courseCount] = grade; 
            ++courseCount; 
            return true;    
        }
        return false;  
    }

    // 设置课程成绩
    void SetGrade(const string &courseName, double grade) {
        for (int i = 0; i < courseCount; i++) {
            if (courseNames[i] == courseName) {
                grades[i] = grade; 
                return;
            }
        }
    }

    // 获取课程成绩
    double GetGrade(const string& courseName) const {
        for (int i = 0; i < courseCount; i++) {
            if (courseNames[i] == courseName) {
                return grades[i]; 
            }
        }
        return -1; 
    }

    // 计算并输出平均成绩
    double GetAverageGrade() const {
        if (courseCount == 0) return 0; 
        double sum = 0;
        for (int i = 0; i < courseCount; i++) sum += grades[i]; 
        cout  << name << "的平均成绩为: " << sum / courseCount << endl; 
        cout << endl;
    }

    // 显示所有课程成绩
    void ShowGrades() const {
        for (int i = 0; i < courseCount; i++) cout << courseNames[i] << ": " << grades[i] << endl; 
    }

    friend class StudentClass; // StudentClass是Student的友元类
};

class StudentClass {
private:
    static const int maxStudents = 20; // 每个班级最多20个学生
    static int studentCount; // 学生数量
    string code; // 班级代码
    Student* students[maxStudents]; // 学生指针数组

public:
    int size() const { return sizeof(students); } // 返回学生指针数组的大小

    // 默认构造函数,初始化code为空，students为new Student*[maxStudents]，就是指向Student对象的指针数组
    StudentClass() : code("") {memcpy(students, new Student*[maxStudents], size());}

    // 非默认构造函数,初始化code为code，students为new Student*[maxStudents]
    StudentClass(const string& code) : code(code) {memcpy(students, new Student*[maxStudents], size());}

    // 拷贝构造函数
    StudentClass(const StudentClass &m) : code(m.code) {
        memcpy(students, new Student*[maxStudents], size()); // 复制m的students到students
        studentCount = m.studentCount; // 复制m的studentCount到studentCount
    }

    // 析构函数，释放学生指针数组的内存
    ~StudentClass() {
        for (int i = 0; i < studentCount; ++i) {delete students[i];} 
    }

    string getCode() const { return code; } // 获取班级代码
    void setCode(const string &code) { this->code = code; } // 设置班级代码

    // 添加学生，返回是否添加成功
    bool AddStudent(const Student* student) {
        if (studentCount < maxStudents) {
            students[studentCount] = new Student(*student);
            ++studentCount;
            return true; 
        }
        return false;
    }

    // 显示指定学号的学生信息
    void ShowStudent(int id) const {
        for (int i = 0; i < studentCount; i++) {
            if (students[i]->getId() == id) {
                cout << "ID: " << students[i]->getId() << ", Name: " << students[i]->getName() << endl;
                students[i]->ShowGrades();
                cout << endl;
                return;
            }
        }
        cout << "Student not found!" << endl;
    }

    // 选择排序算法，用于按学号排序学生
    void Select_Sort(vector<Student*> &students, int left, int right, bool(*compare)(int,int))const{
        for (int i = left; i < right; i++) { 
            int min = i;
            for (int j = i + 1; j <= right; j++) { 
                if (compare(students[j]->getId(), students[min]->getId())) min = j;
            }
            if (min != i) swap(students[i], students[min]);
        }
    }

    // 按学号顺序显示所有学生信息
    void ShowStudentsByIdOrder(bool (*compare)(int, int)) const {
        vector<Student*> sortedStudents(students, students + studentCount); // 复制students到sortedStudents
        Select_Sort(sortedStudents, 0, studentCount - 1, compare);
        for (const auto& student : sortedStudents) { 
            cout << "ID: " << student->getId() << ", Name: " << student->getName() << endl;
            student->ShowGrades();
            cout << endl;
        }
        cout << endl;
    }

    // 显示学生数量
    static void showStudentCount() {cout << "学生数量: " << studentCount << endl;}
};

int StudentClass::studentCount = 0; // 初始化学生数量

// 比较函数，用于升序排序
bool ascending(int a, int b) {return a < b;}

// 比较函数，用于降序排序
bool descending(int a, int b) {return a > b;}

int main() {
    cout << endl;
    Student s1(1, "Reddew");
    s1.AddCourse("Python", 85.0);s1.AddCourse("C++", 90.0);s1.AddCourse("ConcretMath", 95.0);
    s1.GetAverageGrade();

    Student s2;
    s2.setId(2);s2.setName("Tim");s2.AddCourse("Python", 90.0);s2.AddCourse("C++", 95.0);
    
    Student s3(s1);
    s3.setId(3);s3.setName("Tony");s3.AddCourse("Python", 80.0);s3.SetGrade("Python", 85.0);

    StudentClass sc("sysu2024");
    sc.AddStudent(&s1);sc.AddStudent(&s2);sc.AddStudent(&s3);
    sc.ShowStudent(1);sc.ShowStudent(2); sc.ShowStudent(3);

    cout << "升序显示学生信息:" << endl;
    sc.ShowStudentsByIdOrder(ascending);
    cout << "降序显示学生信息:" << endl;
    sc.ShowStudentsByIdOrder(descending);

    StudentClass ::showStudentCount();
}