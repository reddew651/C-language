#include <iostream>
#include <string>
#include <memory>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <deque>

template<typename T>
struct Node {
    T data_;
    Node<T>* pre_;
    Node<T>* next_;
    Node(const T& item = T(), Node* p = nullptr, Node* n = nullptr) : data_(item), pre_(p), next_(n) {}
};

template<typename T>
class Iterator {
public:
    Node<T>* cur_;
    Iterator() : cur_(nullptr) {}
    Iterator(Node<T>* c) : cur_(c) {}
    Iterator(const Iterator& itr) : cur_(itr.cur_) {}

    Iterator& operator++() { cur_ = cur_->next_; return *this; }
    Iterator& operator--() { cur_ = cur_->pre_; return *this; }
    T& operator*() { return cur_->data_; }
    const T& operator*() const { return cur_->data_; }
    bool operator==(const Iterator& itr) { return (cur_ == itr.cur_); }
    bool operator!=(const Iterator& itr) { return (cur_ != itr.cur_); }
};

template<typename T>
class ListQueue {
    Node<T>* head_;
    Node<T>* tail_;
    int size_;
public:
    typedef Iterator<T> iterator;
    typedef const Iterator<T> const_iterator;

    ListQueue() : size_(0), head_(new Node<T>()), tail_(new Node<T>()) {
        head_->next_ = tail_;
        tail_->pre_ = head_;
    }

    ~ListQueue() {
        clear();
        delete head_;
        delete tail_;
    }

    ListQueue(const ListQueue& l) : size_(l.size_), head_(new Node<T>()), tail_(new Node<T>()) {
        head_->next_ = tail_;
        tail_->pre_ = head_;
        for (iterator temp = l.begin(); temp != l.end(); ++temp)
            push_back(*temp);
    }

    void clear() {
        iterator temp = begin();
        while (temp != end())
            temp = erase(temp);
    }

    iterator begin() { return iterator(head_->next_); }
    const_iterator begin() const { return iterator(head_->next_); }
    iterator end() { return iterator(tail_); }
    const_iterator end() const { return iterator(tail_); }

    T& front() { return *begin(); }
    const T& front() const { return *begin(); }
    T& back() { return *(--end()); }
    const T& back() const { return *(--end()); }

    T& at(int idx) const {
        iterator temp = begin();
        if (idx < size_) {
            while (idx--) ++temp;
            return *temp;
        }
        throw std::exception();
    }

    T& operator[](int idx) const {
        return (idx == -1) ? at(rand() % size_) : at(idx);
    }

    void FindforErase(const T& d) {
        iterator it1 = begin();
        iterator it2 = end();
        while (it1 != it2) {
            --it2;
            if (*it1 == d || *it2 == d) {
                erase(*it1 == d ? it1 : it2);
                break;
            }
            ++it1;
        }
    }

    ListQueue& operator=(const ListQueue& l) {
        if (this != &l) {
            clear();
            size_ = l.size_;
            for (iterator temp = l.begin(); temp != l.end(); ++temp)
                push_back(*temp);
        }
        return *this;
    }

    void push_front(const T& item) { insert(begin(), item); }
    void push_back(const T& item) { insert(end(), item); }
    void pop_front() { erase(begin()); }
    void pop_back() { erase(--end()); }

    int size() const { return size_; }
    bool empty() const { return size_ == 0; }

    iterator insert(const iterator itr, const T& item) {
        Node<T>* n = itr.cur_;
        Node<T>* newnode = new Node<T>(item, n->pre_, n);
        n->pre_->next_ = newnode;
        n->pre_ = newnode;
        size_++;
        return iterator(newnode);
    }

    iterator erase(iterator itr) {
        Node<T>* temp = itr.cur_;
        temp->pre_->next_ = temp->next_;
        temp->next_->pre_ = temp->pre_;
        size_--;
        Node<T>* p = temp->next_;
        delete temp;
        return iterator(p);
    }

    friend std::ostream& operator<<(std::ostream& out, const ListQueue<T>& l) {
        for (iterator first = l.begin(), last = l.end(); first != last; ++first)
            out << *first << ' ';
        out << std::endl;
        return out;
    }
};

#pragma warning(disable:6385)
#pragma warning(disable:6386)
#pragma warning(disable:4819)
template <typename T>
class MyVector
{
private:
    T* _items;
    unsigned int _capacity;//分配的空间大小（包括预留空间）
    unsigned int _size;//元素个数
    static const unsigned int _defaultCapacity = 4;//默认容量大小

    void set_capacity(unsigned int newCapacity)//通过ensure_capacity，set_capacity两个私有函数来设置容量大小
    {
        if (newCapacity != this->_capacity)
        {
            if (newCapacity > 0)
            {
                T* newItems = new T[newCapacity];
                for (unsigned int i = 0; i < this->_size; ++i)
                    newItems[i] = _items[i];
                delete[] _items;
                _items = newItems;
                _capacity = newCapacity;
            }
            else
            {
                _items = new T[_defaultCapacity];
                _capacity = _defaultCapacity;
            }
        }
    }

    void ensure_capacity(unsigned int min)
    {
        if (this->_capacity < min)
        {
            unsigned int newCapacity = (this->_size == 0 ? _defaultCapacity : this->_capacity * 2);
            if (newCapacity < min)
                newCapacity = min;
            set_capacity(newCapacity);
        }
    }

public:
    MyVector()
    {
        _items = new T[_defaultCapacity];
        this->_capacity = _defaultCapacity;
        this->_size = 0;//以默认容量开辟空间，元素个数为0
    }

    MyVector(int Get_capacity)
    {
        if (Get_capacity <= _defaultCapacity)//如果参数容量小于等于默认容量 以默认容量开辟空间
            Get_capacity = _defaultCapacity;

        _items = new T[Get_capacity];
        this->_capacity = Get_capacity;
        this->_size = 0;
    }

    MyVector(const MyVector<T>& other)//深度复制构造函数
    {
        copy_from(other);
    }

    T& operator[](unsigned int idx) const
    {
        return at(idx);//利用写好的at函数
    }

    void copy_from(const MyVector<T>& other)
    {
        ensure_capacity(other.Get_size());//通过该函数确认容量大小
        for (unsigned int i = 0; i < other.Get_size(); ++i)
            _items[i] = other.at(i);
        _size = other.Get_size();
    }

    MyVector<T>& operator=(const MyVector<T>& other)
    {
        if (this == &other)//检测自我赋值
            return *this;
        else copy_from(other);
    }
    bool operator==(const MyVector<T>& other)
    {
        if (this->_items == other._items)
            return true;
        else return false;
    }
    MyVector<T> operator+(const MyVector<T>& other)
    {
        MyVector<T> result;//声明一个新的对象来存放结果
        for (unsigned int i = 0; i < this->_size; ++i)
            result.push_back(_items[i]);
        for (unsigned int i = 0; i < other._size; ++i)
            result.push_back(other.at(i));
        return result;
    }
    unsigned int Get_size() const
    {
        return this->_size;
    }
    unsigned int Get_capacity() const
    {
        return this->_capacity;
    }
    void clear()
    {
        delete[] _items;//将原内容清空
        _items = new T[this->_capacity];//开辟新的空间
        this->_size = 0;//现元素为0
    }
    void push_back(const T& item)//向量尾部增加一个元素X
    {
        ensure_capacity(this->_size + 1);
        _items[this->_size++] = item;
    }
    T& at(unsigned int idx) const
    {
        if (idx < this->_size)
            return _items[idx];
        throw std::exception();
    }
    void pop_back()//删除向量中最后一个元素
    {
        if (this->_size > 0)
        {
            this->_size--;
        }
    }
    bool empty()//判断向量是否为空
    {
        return this->_size == 0;
    }
    T& front()//返回首元素的值，否则抛出异常
    {
        if (this->_size > 0)
            return _items[0];
        throw std::exception();
    }
    T& back()//返回末元素的值，否则抛出异常
    {
        if (this->_size > 0)
            return _items[this->_size - 1];
        throw std::exception();
    }
    bool insert(unsigned int pos, const T& item)//在指定位置增加元素
    {
        if (pos >= this->_size)
            return false;

        ensure_capacity(this->_size + 1);
        for (unsigned int i = this->_size; i > pos; --i)
            _items[i] = _items[i - 1];
        _items[pos] = item;
        ++(this->_size);
        return true;
    }
    bool erase(unsigned int pos)//删除指定位置元素
    {
        if (pos >= this->_size || empty())
            return false;
        --(this->_size);
        for (unsigned int i = pos; i < this->_size; ++i)
            _items[i] = _items[i + 1];
        return true;
    }
    ~MyVector()//析构函数，释放内存
    {
        delete[] _items;
    }
    friend std::ostream& operator<<(std::ostream& out, const MyVector<T>& P)
    {
        out << "[ ";
        for (unsigned i = 0; i < P.Get_size(); )
        {
            out << P.at(i++);
            if (i != P.Get_size())
                out << ", ";
        }
        out << " ]" << std::endl;
        return out;
    }
};


class Person
{
public:
    Person();
    Person(std::string id, std::string name);
    Person(const Person& p);
    ~Person() {}
    virtual void display();//虚函数
    friend std::ostream& operator<<(std::ostream& out, const Person& P);
protected:
    std::string id_;
    std::string name_;
};
class Student : public Person
{
public:
    Student();
    Student(std::string id, std::string name, std::string schoolName);
    Student(const Student& s);
    ~Student() {}
    void display();//重写，允许用基类的指针来调用子类的这个函数
    friend std::ostream& operator<<(std::ostream& out, const Student& P);
    //输出流重载，使MyVecter<Student>可以输出
private:
    std::string schoolName_;
    double discount_ = 0; //不明确其含义，后续没有使用
};

Person::Person()
{
    this->id_ = '\0';
    this->name_ = '\0';
}
Person::Person(std::string id, std::string name) : id_(id), name_(name) {} //初始化列表
Person::Person(const Person& p)
{
    this->id_ = p.id_;
    this->name_ = p.name_;
}
void Person::display()
{
    std::cout << name_ << ",ID : " << id_ << std::endl;
}
std::ostream& operator<<(std::ostream& out, const Person& P)
{
    out << P.name_ << ",ID : " << P.id_ << std::endl;
    return out;
}
Student::Student()
{
    this->schoolName_ = '\0';
    this->discount_ = -1;
    this->id_ = '\0';
    this->name_ = '\0';
}
Student::Student(std::string id, std::string name, std::string schoolName) :
    schoolName_(schoolName)
{
    this->id_ = id;
    this->name_ = name;
}
Student::Student(const Student& s)
{
    this->id_ = s.id_;
    this->name_ = s.name_;
    this->schoolName_ = s.schoolName_;
    this->discount_ = s.discount_;
}
void Student::display()
{
    std::cout << name_ << ",ID : " << id_ << ", from " << schoolName_ << std::endl;
}
std::ostream& operator<<(std::ostream& out, const Student& P)
{
    out << P.name_ << ",ID : " << P.id_ << ", from " << P.schoolName_ << std::endl;
    return out;
}//输出流重载与display较为类似，但不能遗漏return


using namespace std;
int main()
{
    MyVector<Student> mv;
    Student s1("4005", "Barbara", "SYSU");
    Student s2("4006", "Vanida", "SYSU");
    Student s3("4007", "Bartola", "SYSU");
    Student s4("4008", "Brielle", "SYSU");
    Student s5("4009", "Garner", "SYSU");
    Student s6("4010", "Franklyn", "SYSU");
    Student s7("4011", "Celestyn", "SYSU");
    Student s8("4012", "Gregg", "SYSU");
    mv.push_back(s1);
    mv.push_back(s2);
    mv.push_back(s3);
    mv.push_back(s4);
    mv.insert(2, s5);
    mv.erase(2);
    mv.push_back(s6);
    mv.push_back(s7);
    mv.push_back(s8);
    mv.pop_back();
    cout << mv << mv.back() << mv.front() << mv.at(2) << endl;
    mv.clear();
    if (mv.empty())
        cout << "It is clear." << endl;//判断是否清空成功
    //int,double,string等也在MyVector中正常运行，不再额外测试
    //以下开始测试ListQueue及各接口
    unsigned seed;//提供不同的种子值，确保随机生成数
    seed = (unsigned)time(0);
    srand(seed);
    ListQueue<double> ran;
    for (int i = 0; i < 5; i++)
    {
        double tmp1 = rand(), tmp2 = rand();
        ran.push_back(tmp1);
        ran.push_front(tmp2);
    }//从前后各插入5个随机值
    cout << ran << endl;
    ran.clear();
    for (int i = 0; i < 5001; i++)
    {
        double tmp1 = rand(), tmp2 = rand();
        ran.push_back(tmp1);
        ran.push_front(tmp2);
    }//从前后各插入5001个值
    ran.pop_back();
    ran.pop_front();
    double pi = 3.1415;
    ran.insert(ran.end(),pi);
    cout << ran.at(10000) << "&" << ran[10000] <<"&"<<ran.back() << endl;
    ran.erase(ran.begin());
    for (int i = 0; i < 10000; i++)
    {
        double temp = ran[0];
        //此处若为ran[-1]则可随机取并删除，但通过阅读资料，"随机访问"不是指随机，而是任意
        ran.FindforErase(temp);
    }//随机访问并删除，直至被清空，类似于clear函数
    if (ran.empty())
        cout << "It is clear." << endl;//判断是否清空成功
    /*static const auto MAX = 10;
    ListQueue<MyVector<int> > list;
    for (int i = 0; i < 10; i++) {
        MyVector<int> temp;
        for (int j = 0; j < MAX; j++) {
            temp.push_back(i);
        }
        list.push_front(temp);
    }//尝试进行类模板嵌套并以MAX为上限组织对象，
    但是会导致权限访问冲突，目前还未想出解决方法
    cout << list;*/
    //反之则可行
    static const auto MAX = 10;
    MyVector<ListQueue<int> > list;
    for (int i = 0; i < 1000; i++) {
        ListQueue<int> temp;
        for (int j = 0; j < MAX; j++) {
            temp.push_back(i);
        }
        list.push_back(temp);
    }
    cout << list;
    list.clear();
    cout << list;
    return 0;
}