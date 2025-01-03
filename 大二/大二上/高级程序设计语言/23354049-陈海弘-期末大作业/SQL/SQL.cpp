// 包含必要的头文件
#include <iostream>
#include <stdio.h>
#include <tuple>
#include <vector>
#include <fstream>
#include <string>
#include <iomanip>
#include <map>
#include <algorithm>

using namespace std;

// 定义基本数据类型
typedef tuple<int, int, int> date;                          // 日期类型(年,月,日)
typedef tuple<int, string, string, date, int, string> Info; // 学生信息(学号,姓名,性别,生日,学年,籍贯)
typedef tuple<int, string, float, int> Course;              // 课程信息(学号,课程名,学分,分数)
typedef pair<int, int> PAIR;

// 用于简化tuple访问的宏定义
#define ID get<0>
#define Courses get<1>
#define Credits get<2>
#define Score get<3>
#define Name get<1>
#define Sex get<2>
#define Birthday get<3>
#define School_year get<4>
#define Birthplace get<5>
#define Year get<0>
#define Month get<1>
#define Day get<2>

// 存储数据的容器
vector<Info> txt1;           // 存储学生信息
vector<Course> txt2;         // 存储课程信息
map<int, int> TotalScore;    // 存储每个学生的总分
map<int, float> TotalCredit; // 存储每个学生的总学分
map<int, int> Count;         // 存储每个学生的课程数量

ostream& operator<<(ostream& u, const date& d) {
    return u << get<0>(d) << '/' << get<1>(d) << '/' << get<2>(d);
}
ostream& operator<<(ostream& u, const Info& d) {
    return u << ID(d) << '\t' << fixed << setw(12) << left << Name(d)
             << fixed << setw(12) << left << Sex(d) << Birthday(d) << '\t'
             << fixed << setw(8) << School_year(d) << '\t' << Birthplace(d);
}
ostream& operator<<(ostream& u, const Course& d) {
    return u << ID(d) << '\t' << setw(25) << setiosflags(ios::left)
             << setfill(' ') << Courses(d) << ' ' << (int)Credits(d)
             << "     " << Score(d);
}
bool operator==(date a, date b) {
    return get<0>(a) == get<0>(b) && get<1>(a) == get<1>(b) && get<2>(a) == get<2>(b);
}
char* Delete(char* a) {
    char* p = a;
    while (*p) p++;
    p[-1] = '\0';
    return a;
}
void PrintInfo(vector<Info> txt1) {
    ofstream out("result.txt", ios::app);
    if (txt1.empty()) return;
    cout << "ID\t" << setw(12) << left << "Name" << setw(12) << left << "Sex"
         << "Birthday\tSchool_year\tBirthplace" << endl;
    for (auto& it : txt1) cout << it << endl;
    out.close();
}
void PrintCourse(vector<Course> txt2) {
    ofstream out("result.txt", ios::app);
    if (txt2.empty()) return;
    cout << "ID\t" << setw(23) << setiosflags(ios::left) << setfill(' ')
         << "Course"
         << "Credits\tScore" << endl;
    for (auto& it : txt2) cout << it << endl;
    out.close();
}
bool cmp_by_value(const PAIR& lhs, const PAIR& rhs) {
    return lhs.second < rhs.second;
}
bool cmpID1(const Info a, const Info b) { return ID(a) < ID(b); }
bool cmpID2(const Course a, const Course b) { return ID(a) < ID(b); }
bool cmpName(const Info a, const Info b) { return Name(a) < Name(b); }
bool cmpScore(const Course a, const Course b) { return Score(a) < Score(b); }
void SortByID1(vector<Info> txt1) {
    sort(txt1.begin(), txt1.end(), cmpID1);
    PrintInfo(txt1);
}
void SortByID2(vector<Course> txt2) {
    sort(txt2.begin(), txt2.end(), cmpID2);
    PrintCourse(txt2);
}
void SortByName(vector<Info> txt1) {
    sort(txt1.begin(), txt1.end(), cmpName);
    PrintInfo(txt1);
}
void SortByScore(vector<Course> txt2) {
    sort(txt2.begin(), txt2.end(), cmpScore);
    PrintCourse(txt2);
}
void SortByTotalScore(map<int, int> TS) {
    vector<PAIR> Vm(TS.begin(), TS.end());
    sort(Vm.begin(), Vm.end(), cmp_by_value);
    ofstream out("result.txt", ios::app);
    for (auto it = Vm.begin(); it != Vm.end(); it++) {
        if (it == Vm.begin()) cout << "ID\tTotalScore" << endl;
        cout << it->first << '\t' << it->second << endl;
    }
    out.close();
}

// 从文件读取并初始化数据
void Create() {
    ifstream in1("./StudentInfo.txt"), in2("./StudentCourse.txt");
    string line;
    if (in1.is_open()) {
        while (getline(in1, line)) {
            if (line[0] == '#') continue;
            int id, school_year, year, month, day;
            char name[20], sex[20], birthday[20] = {}, birthplace[20];
            sscanf(line.c_str(), "%d %s %s %s %d %s", &id, name, sex, birthday, &school_year, birthplace);
            sscanf(birthday, "%4d/%1d/%1d", &year, &month, &day);
            txt1.push_back({id, name, sex, make_tuple(year, month, day), school_year, birthplace});
        }
        sort(txt1.begin(), txt1.end(), cmpID1);
    }
    if (in2.is_open()) {
        while (getline(in2, line)) {
            if (line[0] == '#') continue;
            int id, score;
            float credits;
            char course[25];
            sscanf(line.c_str(), "%d %[^1-9] %f %d", &id, course, &credits, &score);
            TotalCredit[id] += credits;
            TotalScore[id] += score;
            Count[id]++;
            txt2.push_back({id, Delete(course), credits, score});
        }
        sort(txt2.begin(), txt2.end(), cmpID2);
    }
}

// 执行查询测试
void Test() {
    ofstream out("result.txt", ios::app);
    // 测试1: 查找2020级C语言不及格的学生
    out << "(a) 打印2020级选修C语言且成绩小于60分的学生:" << endl;
    for (auto it1 = txt1.begin(); it1 != txt1.end(); it1++) {
        if (School_year(*it1) == 2020) {
            for (auto it2 = txt2.begin(); it2 != txt2.end(); it2++) {
                if (ID(*it1) == ID(*it2) && Courses(*it2) == "C Programming Language" && Score(*it2) < 60)
                    out << *it1 << " ; " << *it2 << endl;
            }
        }
    }
    // 测试2: 查找平均分>80的学生
    out << "(b) 统计课程平均分大于80的学生个人信息并输出:" << endl;
    for (auto it = txt1.begin(); it != txt1.end(); it++) {
        int tmp = TotalScore[ID(*it)] / Count[ID(*it)];
        if (tmp > 80) out << *it << " 平均分：" << tmp << endl;
    }
    // 测试3: 检查学分是否满20
    out << "(c) 查询每个学生是否修满20学分:" << endl;
    for (auto it = TotalCredit.rbegin(); it != TotalCredit.rend(); it++) {
        it->second > 20 ?
            out << "学号为：" << it->first << "的学生修满了20学分" << endl :
            out << "学号为：" << it->first << "的学生未修满20学分" << endl;
    }
    out.close();
}

// 重载比较运算符用于条件查询
bool operator==(Info i, int x) {
    int int1, int2, y, m, d;
    tie(int1, ignore, ignore, ignore, int2, ignore) = i;
    tie(y, m, d) = Birthday(i);
    return int1 == x || int2 == x || y == x || m == x || d == x;
}
bool operator>(Info i, int x) {
    int int1, int2;
    tie(int1, ignore, ignore, ignore, int2, ignore) = i;
    return (int1 > x || int2 > x);
}
bool operator<(Info i, int x) {
    int int1, int2;
    tie(int1, ignore, ignore, ignore, int2, ignore) = i;
    return (int1 < x || int2 < x);
}
bool operator==(Info i, string x) {
    string s1, s2, s3;
    tie(ignore, s1, s2, ignore, ignore, s3) = i;
    return s1 == x || s2 == x || s3 == x;
}
bool operator==(Info i, date x) {
    date d;
    tie(ignore, ignore, ignore, d, ignore, ignore) = i;
    return d == x;
}
bool operator>(Course c, int x) {
    int s; tie(ignore, ignore, ignore, s) = c;
    return s > x;
}
bool operator<(Course c, int x) {
    int s; tie(ignore, ignore, ignore, s) = c;
    return s < x;
}
bool operator==(Course c, int x) {
    int s; tie(ignore, ignore, ignore, s) = c;
    return s == x;
}

// 获取指定学生指定课程的分数
int GetScore(vector<Course> t, string c, int id) {
    for (auto& it : t)
        if (ID(it) == id && Courses(it) == c) return Score(it);
    return -1;
}

// 泛型删除函数,根据条件删除元素
template<typename T1, typename T2>
T1 Erase(T1 txt, T2 cd) {
    for (auto itr = txt.begin(); itr != txt.end();) {
        *itr == cd ? itr = txt.erase(itr) : ++itr;
    }
    return txt;
}

// 基于比较函数的泛型删除
template<typename T1, typename T2>
T1 EraseCmp(bool(*compare)(Course, T2), T1 txt, T2 cd) {
    for (auto itr = txt.begin(); itr != txt.end();) {
        (*compare)(*itr, cd) ? itr = txt.erase(itr) : ++itr;
    }
    return txt;
}
template<typename T1, typename T2>
bool larger(T1 i1, T2 i2) { return i1 > i2; }
template<typename T1, typename T2>
bool smaller(T1 i1, T2 i2) { return i1 < i2; }
template<typename T1, typename T2>
bool equal(T1 i1, T2 i2) { return i1 == i2; }
void Line() {
    for (int i = 0; i < 80; i++) cout << '-';
    cout << endl;
}

// 主函数:测试各项功能
int main() {
    Create();  // 初始化数据
    
    // 测试各种排序方式
    Line(); SortByName(txt1);
    Line(); SortByScore(txt2);
    Line(); SortByID1(txt1);
    Line(); SortByID2(txt2);
    Line(); SortByTotalScore(TotalScore);
    
    // 执行查询测试
    Line(); Test();
    
    // 测试条件查询和删除
    auto sex = "Male", course = "C Programming Language";
    auto birthday_year = 1993, id = 10905, score = 80;
    auto d = make_tuple(1994, 2, 1);
    for (auto it = txt1.begin(); it != txt1.end(); it++) {
        if ((Sex(*it) == sex && Year(Birthday(*it)) > 1900)
             || GetScore(txt2, course, ID(*it)) < 80) {
            cout << *it << endl;
        }
    }
    Line();
    vector<Info> txt3 = Erase(txt1, sex);
    vector<Course> txt4 = EraseCmp(smaller, txt2, score);
    vector<Course> txt5 = EraseCmp(larger, txt2, score);
    PrintInfo(txt3);
    Line(); PrintCourse(txt4);
    Line(); PrintCourse(txt5);
    Line();
    return 0;
}