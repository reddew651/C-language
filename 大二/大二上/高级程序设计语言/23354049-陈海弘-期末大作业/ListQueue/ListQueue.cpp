#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

// 节点结构体，用于双向链表
template<typename T>
struct Node {
    T data_;
    Node<T>* pre_;
    Node<T>* next_;
    Node(const T& item = T(), Node* p = nullptr, Node* n = nullptr) : data_(item), pre_(p), next_(n) {}
};

// 迭代器，用于遍历链表
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
    bool operator==(const Iterator& itr) { return cur_ == itr.cur_; }
    bool operator!=(const Iterator& itr) { return cur_ != itr.cur_; }
};

// 基于双向链表的队列
template<typename T>
class ListQueue {
    Node<T>* head_;
    Node<T>* tail_;
    int size_;
public:
    typedef Iterator<T> iterator;
    typedef const Iterator<T> const_iterator;
    ListQueue() : size_(0), head_(new Node<T>()), tail_(new Node<T>()) {//构造函数
        head_->next_ = tail_;
        tail_->pre_ = head_;
    }
    ~ListQueue() {//析构函数
        clear();
        delete head_;
        delete tail_;
    }
    ListQueue(const ListQueue& l) : size_(l.size_), head_(new Node<T>()), tail_(new Node<T>()) {//拷贝构造函数
        head_->next_ = tail_;
        tail_->pre_ = head_;
        for (iterator temp = l.begin(); temp != l.end(); ++temp)
            push_back(*temp);
    }
    void clear() {//清空
        iterator temp = begin();
        while (temp != end()) temp = erase(temp);
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
    T& operator[](int idx) const {//重载[]
        return (idx == -1) ? at(rand() % size_) : at(idx);
    }
    void FindforErase(const T& d) {//查找删除
        iterator it1 = begin(), it2 = end();
        while (it1 != it2) {
            --it2;
            if (*it1 == d || *it2 == d) {
                erase((*it1 == d) ? it1 : it2);
                break;
            }
            ++it1;
        }
    }
    ListQueue& operator=(const ListQueue& l) {//重载=
        if (this != &l) {
            clear();
            size_ = l.size_;
            for (iterator temp = l.begin(); temp != l.end(); ++temp)
                push_back(*temp);
        }
        return *this;
    }
    void push_front(const T& item) { insert(begin(), item); }//在头部插入
    void push_back(const T& item) { insert(end(), item); }
    void pop_front() { erase(begin()); }//删除头部
    void pop_back() { erase(--end()); }
    int size() const { return size_; }//返回大小
    bool empty() const { return size_ == 0; }
    iterator insert(const iterator itr, const T& item) {//插入
        Node<T>* n = itr.cur_;
        Node<T>* node = new Node<T>(item, n->pre_, n);
        n->pre_->next_ = node;
        n->pre_ = node;
        size_++;
        return iterator(node);
    }
    iterator erase(iterator itr) {//删除
        Node<T>* temp = itr.cur_;
        temp->pre_->next_ = temp->next_;
        temp->next_->pre_ = temp->pre_;
        size_--;
        Node<T>* p = temp->next_;
        delete temp;
        return iterator(p);
    }
    friend std::ostream& operator<<(std::ostream& out, const ListQueue<T>& l) {//friend函数用于
        for (iterator f = l.begin(), e = l.end(); f != e; ++f) out << *f << ' ';
        out << std::endl;
        return out;
    }
};

// 动态数组，自动扩容
template <typename T>
class MyVector {
    T* _items;
    unsigned int _capacity;
    unsigned int _size;
    static const unsigned int _defaultCapacity = 4;
    void set_capacity(unsigned int newCapacity) {//设置容量
        if (newCapacity != _capacity) {
            if (newCapacity > 0) {
                T* n = new T[newCapacity];//新建数组
                for (unsigned int i = 0; i < _size; ++i) n[i] = _items[i];
                delete[] _items;
                _items = n;
                _capacity = newCapacity;
            } else {//默认容量
                _items = new T[_defaultCapacity];
                _capacity = _defaultCapacity;
            }
        }
    }
    void ensure_capacity(unsigned int min) {//确保容量
        if (_capacity < min) {
            unsigned int newCap = (_size == 0 ? _defaultCapacity : _capacity * 2);
            if (newCap < min) newCap = min;
            set_capacity(newCap);
        }
    }
public:
    MyVector() : _capacity(_defaultCapacity), _size(0) {//构造函数
        _items = new T[_defaultCapacity];
    }
    MyVector(int Get_capacity) : _size(0) {
        if (Get_capacity <= _defaultCapacity) Get_capacity = _defaultCapacity;
        _items = new T[Get_capacity];
        _capacity = Get_capacity;
    }
    MyVector(const MyVector<T>& other) { copy_from(other); }//拷贝构造函数
    T& operator[](unsigned int idx) const { return at(idx); }
    void copy_from(const MyVector<T>& other) {
        ensure_capacity(other.Get_size());
        for (unsigned int i = 0; i < other.Get_size(); ++i) _items[i] = other.at(i);
        _size = other.Get_size();
    }
    MyVector<T>& operator=(const MyVector<T>& other) {
        if (this != &other) copy_from(other);
        return *this;
    }
    bool operator==(const MyVector<T>& other) { return (_items == other._items); }
    MyVector<T> operator+(const MyVector<T>& o) {
        MyVector<T> r;
        for (unsigned int i = 0; i < _size; ++i) r.push_back(_items[i]);
        for (unsigned int i = 0; i < o._size; ++i) r.push_back(o.at(i));
        return r;
    }
    unsigned int Get_size() const { return _size; }
    unsigned int Get_capacity() const { return _capacity; }
    void clear() {
        delete[] _items;
        _items = new T[_capacity];
        _size = 0;
    }
    void push_back(const T& item) {
        ensure_capacity(_size + 1);
        _items[_size++] = item;
    }
    T& at(unsigned int idx) const {//返回指定位置的元素
        if (idx < _size) return _items[idx];
        throw std::exception();
    }
    void pop_back() { if (_size > 0) _size--; }
    bool empty() const { return _size == 0; }
    T& front() { if (_size>0) return _items[0]; throw std::exception(); }
    T& back() { if (_size>0) return _items[_size-1]; throw std::exception(); }
    bool insert(unsigned int pos, const T& item) {
        if (pos >= _size) return false;
        ensure_capacity(_size + 1);
        for (unsigned int i = _size; i > pos; --i) _items[i] = _items[i - 1];
        _items[pos] = item;
        ++_size;
        return true;
    }
    bool erase(unsigned int pos) {
        if (pos >= _size || empty()) return false;
        --_size;
        for (unsigned int i = pos; i < _size; ++i) _items[i] = _items[i + 1];
        return true;
    }
    ~MyVector() { delete[] _items; }
    friend std::ostream& operator<<(std::ostream& out, const MyVector<T>& P) {//friend函数用于
        out << "[ ";
        for (unsigned i = 0; i < P.Get_size(); ) {
            out << P.at(i++);
            if (i != P.Get_size()) out << ", ";
        }
        out << " ]" << std::endl;
        return out;
    }
};

// 表示一个人的基类
class Person {
public:
    Person();
    Person(std::string id, std::string name);
    Person(const Person& p);
    virtual void display();
    friend std::ostream& operator<<(std::ostream& out, const Person& P);
protected:
    std::string id_;
    std::string name_;
};

// 学生类，继承自Person
class Student : public Person {
public:
    Student();
    Student(std::string id, std::string name, std::string schoolName);
    Student(const Student& s);
    void display();
    friend std::ostream& operator<<(std::ostream& out, const Student& P);
private:
    std::string schoolName_;
    double discount_ = 0;
};

Person::Person(): id_("\0"), name_("\0") {}//构造函数
Person::Person(std::string id, std::string name) : id_(id), name_(name) {}
Person::Person(const Person& p) : id_(p.id_), name_(p.name_) {}
void Person::display() { std::cout << name_ << ",ID : " << id_ << std::endl; }
std::ostream& operator<<(std::ostream& out, const Person& P) {
    out << P.name_ << ",ID : " << P.id_ << std::endl;
    return out;
}

Student::Student(): schoolName_("\0"), discount_(-1) {
    id_ = '\0'; 
    name_ = '\0';
}
Student::Student(std::string id, std::string name, std::string schoolName)
    : Person(id, name), schoolName_(schoolName) {}
Student::Student(const Student& s)
    : Person(s), schoolName_(s.schoolName_), discount_(s.discount_) {}
void Student::display() {
    std::cout << name_ << ",ID : " << id_ << ", from " << schoolName_ << std::endl;
}
std::ostream& operator<<(std::ostream& out, const Student& P) {
    out << P.name_ << ",ID : " << P.id_ << ", from " << P.schoolName_ << std::endl;
    return out;
}

// 主函数，用于测试以上类
int main() {
    MyVector<Student> mv;
    mv.push_back(Student("123","Reddew","SYSU"));
    mv.push_back(Student("124","Yuki","SYSU"));
    mv.push_back(Student("125","York","SYSU"));
    mv.push_back(Student("126","James","SYSU"));
    mv.insert(2, Student("127","Sarial","SYSU"));
    mv.erase(2);
    mv.push_back(Student("128","Jorze","SYSU"));
    mv.push_back(Student("129","Groize","SYSU"));
    mv.push_back(Student("130","Dada","SYSU"));
    mv.pop_back();
    std::cout << mv << mv.back() << mv.front() << mv.at(2) << std::endl;
    mv.clear();
    if (mv.empty()) std::cout << "It is clear." << std::endl;

    srand(static_cast<unsigned>(time(0)));
    ListQueue<double> ran;
    for (int i = 0; i < 5; i++) {
        ran.push_back(rand());
        ran.push_front(rand());
    }
    std::cout << ran << std::endl;
    ran.clear();
    for (int i = 0; i < 5001; i++) {
        ran.push_back(rand());
        ran.push_front(rand());
    }
    ran.pop_back();
    ran.pop_front();
    ran.insert(ran.end(),3.1415);
    std::cout << ran.at(10000) << "&" << ran[10000] <<"&"<<ran.back() << std::endl;
    ran.erase(ran.begin());
    for (int i = 0; i < 10000; i++) ran.FindforErase(ran[0]);
    if (ran.empty()) std::cout << "It is clear." << std::endl;

    MyVector<ListQueue<int> > list;
    for (int i = 0; i < 1000; i++) {
        ListQueue<int> temp;
        for (int j = 0; j < 10; j++) temp.push_back(i);
        list.push_back(temp);
    }
    std::cout << list;
    list.clear();
    std::cout << list;
    return 0;
}