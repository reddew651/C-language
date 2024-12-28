#include<iostream>
#include<string>
#include<set>
#include<vector>
#include<memory>
using namespace std;

class Person {
protected:
    string id_;
    string name_;
public:
    Person();
    Person(string id, string name);
    Person(const Person& p);
    ~Person() {}
    virtual void display() const;
};

Person::Person() : id_(""), name_("") {}
Person::Person(string id, string name) : id_(id), name_(name) {}
Person::Person(const Person& p) : id_(p.id_), name_(p.name_) {}
void Person::display() const {
    cout << name_ << "，号码： " << id_ << endl;
}

class Student : public Person {
private:
    string schoolName_;
    double discountRate_;
public:
    Student();
    Student(string id, string name, string schoolName);
    Student(const Student& s);
    ~Student() {}
    void display() const override; //override来覆盖基类的display函数
};

Student::Student() : discountRate_(-1), schoolName_(""), Person("", "") {}//初始化列表
Student::Student(string id, string name, string schoolName) : Person(id, name), schoolName_(schoolName) {}
Student::Student(const Student& s) : Person(s), schoolName_(s.schoolName_), discountRate_(s.discountRate_) {}
void Student::display() const {
    cout << name_ << "，来自" << schoolName_ << "，学号：" << id_ << endl;
}

class Date {
private:
    int year_, month_, day_;
public:
    Date();
    Date(int year, int month, int day);
    Date(const Date& d);
    ~Date() {}
    Date& operator=(const Date&);
    friend ostream& operator<<(ostream& u, const Date& d);//友元函数用来实现重载
};

Date::Date() : year_(0), month_(0), day_(0) {}
Date::Date(int year, int month, int day) : year_(year), month_(month), day_(day) {}
Date::Date(const Date& d) : year_(d.year_), month_(d.month_), day_(d.day_) {}

Date& Date::operator=(const Date& d) {
    if (this != &d) { 
        year_ = d.year_;
        month_ = d.month_;
        day_ = d.day_;
    }
    return *this;
}

ostream& operator<<(ostream& u, const Date& d) {
    u << d.year_ << '.' << d.month_ << '.' << d.day_;
    return u;
}

class Activity {
public:
    Activity();  // 默认构造函数
    Activity(Date date, string place, string activity, set<shared_ptr<Person> > members);  // 带参数的构造函数
    Activity(const Activity& a);  // 拷贝构造函数
    ~Activity() {}
    void print() const;  // 打印活动信息
private:
    Date date_; 
    string place_;  
    string activity_; 
    set<shared_ptr<Person> > members_; 
};

Activity::Activity() : place_(""), activity_(""), date_(), members_() {}
Activity::Activity(Date date, string place, string activity, set<shared_ptr<Person> > members)
    : date_(date), place_(place), activity_(activity), members_(members) {}
Activity::Activity(const Activity& a) : date_(a.date_), place_(a.place_), activity_(a.activity_), members_(a.members_) {}
void Activity::print() const {
    cout << activity_ << ":" << endl;
    cout << date_ << " 举办于" << place_ << endl;
    cout << "成员: " << endl;
    for (const auto& member : members_) {
        member->display();
    }
}

class Club {
protected:
    string name_;  // 俱乐部名称
    set<shared_ptr<Person> > members_;  // 俱乐部成员
    set<shared_ptr<Activity> > activity_;  // 俱乐部活动
public:
    Club() {}
    virtual ~Club() {}
    virtual void displayMembers() const = 0;  // 显示成员信息
    virtual void displayActivities() const = 0;  // 显示活动信息
    virtual void addMember(const Person&) = 0;  // 添加成员
    virtual void addActivity(const Activity&) = 0;  // 添加活动
};

class SportsClub : public Club {
public:
    SportsClub();  // 默认构造函数
    SportsClub(string name, set<shared_ptr<Person> > members, set<shared_ptr<Activity> > activity, string coach);  // 带参数的构造函数
    SportsClub(const SportsClub& sc);  // 拷贝构造函数
    ~SportsClub() {}
    void displayMembers() const override;  // 覆盖基类的displayMembers函数
    void displayActivities() const override;  // 覆盖基类的displayActivities函数
    void addMember(const Person& p) override;  // 覆盖基类的addMember函数
    void addActivity(const Activity& a) override;  // 覆盖基类的addActivity函数
private:
    string coach_;  // 教练名称
};

SportsClub::SportsClub() : coach_(""), Club() {}
SportsClub::SportsClub(string name, set<shared_ptr<Person> > members, set<shared_ptr<Activity> > activity, string coach)
    : coach_(coach), Club() {
    name_ = name;
    members_ = members;
    activity_ = activity;
}
SportsClub::SportsClub(const SportsClub& sc) : Club(sc) {
    coach_ = sc.coach_;
}
void SportsClub::displayMembers() const {
    for (const auto& member : members_) {  // 用auto来自动推断类型
        member->display();
    }
}
void SportsClub::displayActivities() const {
    for (const auto& act : activity_) {
        act->print();
    }
    cout << "主办部门：" << name_ << ", 负责人：" << coach_ << endl;
}
void SportsClub::addMember(const Person& p) {
    members_.insert(make_shared<Person>(p)); 
}
void SportsClub::addActivity(const Activity& a) {
    activity_.insert(make_shared<Activity>(a)); 
}

class MusicClub : public Club {
public:
    MusicClub();  // 默认构造函数
    MusicClub(string name, set<shared_ptr<Person> > members, set<shared_ptr<Activity> > activity, string musician);  // 带参数的构造函数
    MusicClub(const MusicClub& mc);  // 拷贝构造函数
    ~MusicClub() {}
    void displayMembers() const override;  // 覆盖基类的displayMembers函数
    void displayActivities() const override;  // 覆盖基类的displayActivities函数
    void addMember(const Person& p) override;  // 覆盖基类的addMember函数
    void addActivity(const Activity& a) override;  // 覆盖基类的addActivity函数
private:
    string musician_;  // 音乐家名称
};

MusicClub::MusicClub() : musician_(""), Club() {}
MusicClub::MusicClub(string name, set<shared_ptr<Person> > members, set<shared_ptr<Activity> > activity, string musician)
    : musician_(musician), Club() {
    name_ = name;
    members_ = members;
    activity_ = activity;
}
MusicClub::MusicClub(const MusicClub& mc) : Club(mc) {
    musician_ = mc.musician_;
}
void MusicClub::displayMembers() const {
    for (const auto& member : members_) {
        member->display();
    }
}
void MusicClub::displayActivities() const {
    for (const auto& act : activity_) {
        act->print();
    }
    cout << "主办部门：" << name_ << ", 负责人：" << musician_ << endl;
}
void MusicClub::addMember(const Person& p) {
    members_.insert(make_shared<Person>(p)); 
}
void MusicClub::addActivity(const Activity& a) {
    activity_.insert(make_shared<Activity>(a)); 
}

enum Instrument { Piano, Violin, Guitar };  // 枚举类型
Instrument instrument_;

class ClubCenter {
public:
    ClubCenter();  // 默认构造函数
    ClubCenter(vector<shared_ptr<Club> > clubs);  // 带参数的构造函数
    ClubCenter(const ClubCenter& cc);  // 拷贝构造函数
    ~ClubCenter() {}
    void displayClub() const;  // 显示俱乐部信息
    void addClub(shared_ptr<Club> c);  // 添加俱乐部
private:
    vector<shared_ptr<Club> > clubs_;  // 俱乐部列表
};

ClubCenter::ClubCenter() : clubs_() {}
ClubCenter::ClubCenter(vector<shared_ptr<Club> > clubs) : clubs_(clubs) {}
ClubCenter::ClubCenter(const ClubCenter& cc) : clubs_(cc.clubs_) {}
void ClubCenter::displayClub() const {
    for (const auto& club : clubs_) {
        club->displayActivities();
        cout << endl;
    }
}
void ClubCenter::addClub(shared_ptr<Club> c) {
    clubs_.push_back(c);
}

int main() {
    set<shared_ptr<Person> > set1, set2, set3, set4;
    // 四个person
    set1.insert(make_shared<Person>("1", "James"));
    set2.insert(make_shared<Person>("2", "Chris"));
    set3.insert(make_shared<Person>("3", "York"));
    set4.insert(make_shared<Person>("4", "Yuki"));
    // 八个student
    set1.insert(make_shared<Student>("5", "Jack", "SYSU"));
    set1.insert(make_shared<Student>("6", "Julie", "SYSU"));
    set2.insert(make_shared<Student>("7", "John", "SYSU"));
    set2.insert(make_shared<Student>("8", "Vim", "SYSU"));
    set3.insert(make_shared<Student>("9", "Mark", "SYSU"));
    set3.insert(make_shared<Student>("10", "Steven", "SYSU"));
    set4.insert(make_shared<Student>("11", "Celnny", "SYSU"));
    set4.insert(make_shared<Student>("12", "Egg", "SYSU"));

    set<shared_ptr<Activity> > set5, set6, set7, set8;

    Date date(2024, 12, 19);  // 活动日期
    // 两个体育活动，两个音乐活动
    set5.insert(make_shared<Activity>(date, "东园篮球场", "篮球赛", set1));
    set6.insert(make_shared<Activity>(date, "体育馆", "健身三大项大赛", set2));
    set7.insert(make_shared<Activity>(date, "东二304", "合唱表演", set3));
    set8.insert(make_shared<Activity>(date, "西三204", "音乐剧", set4));

    ClubCenter clubcenter;
    
    auto ptr17 = make_shared<SportsClub>("篮球俱乐部", set1, set5, "陈老师");
    clubcenter.addClub(ptr17);

    auto ptr18 = make_shared<SportsClub>("健身协会", set2, set6, "Chris Tinder");
    clubcenter.addClub(ptr18);

    auto ptr19 = make_shared<MusicClub>("合唱团", set3, set7, "方老师");
    clubcenter.addClub(ptr19);

    auto ptr20 = make_shared<MusicClub>("话剧社", set4, set8, "赵老师");
    clubcenter.addClub(ptr20);

    clubcenter.displayClub();  // 展示以上所有信息
}