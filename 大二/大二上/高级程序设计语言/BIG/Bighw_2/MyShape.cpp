#include <vector> 
#include <iostream>
#include <memory>
#include <cmath>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <algorithm>
using namespace std;
#define PI 3.14

class Point {// Point类定义
private:
    double x_, y_;
public:
    Point(double x = 0, double y = 0) : x_(x), y_(y) {}// 构造函数
    
    void Print() const {cout << "(" << x_ << ", " << y_ << ")";}
    void Move(double x, double y) {x_ += x; y_ += y; }
    
    double GetX() const { return x_; }
    double GetY() const { return y_; }
};

class Edge {// Edge类定义，需要两个点起始和终止
private:
    Point head, tail;
public:
    Edge(const Point& start, const Point& end) : head(start), tail(end) {}// 构造函数
    
    double Length() const { // 计算边长
        double dx = tail.GetX() - head.GetX();
        double dy = tail.GetY() - head.GetY();
        return sqrt(dx * dx + dy * dy);//通过勾股定理计算边长！
    }
    
    void Print() const {
        head.Print();
        cout << " - ";
        tail.Print();
    }
    
    void Move(double x, double y) {//同时移动起始和终止点
        head.Move(x, y);tail.Move(x, y);
    }

    const Point& GetStart() const { return head; }
    const Point& GetEnd() const { return tail; }
};

class Shape {// Shape抽象基类
public:
    static const int UnknownValue = -1;//定义未知值
    
    virtual double Circumference() const = 0;
    virtual double Area() const = 0;
    virtual void Print() const = 0;
    virtual void Move(double x, double y) = 0;
    virtual bool IsValid() const = 0;
    virtual ~Shape() {}
};

class Circle : public Shape {// Circle类定义
private:
    Point center_;
    double radius_;
    
public:
    Circle(const Point& center, double radius) 
        : center_(center), radius_(radius) {}//构造函数 
        
    virtual double Circumference() const override {
        if (!IsValid()) return UnknownValue;
        return 2 * PI * radius_;
    }
    
    virtual double Area() const override {
        if (!IsValid()) return UnknownValue;
        return PI * radius_ * radius_;
    }
    
    virtual void Print() const override {
        cout << "Circle: Center ";
        center_.Print();
        cout << ", Radius: " << radius_;
        if (IsValid()) {
            cout << ", Area: " << Area()<< ", Circumference: " << Circumference();
        }
        cout << endl;
    }
    virtual void Move(double x, double y) override {center_.Move(x, y);}//移动圆心
    virtual bool IsValid() const override {return radius_ > 0;}
    const Point& GetCenter() const { return center_; }//返回圆心
    double GetRadius() const { return radius_; }
};

class Polygon : public Shape {// Polygon类定义，从Shape类继承
private:
    vector<Point> vertices_;//vector存储多边形的顶点
    vector<Edge*> edges_;//vector存储多边形的边，用*是因为边是Edge类的对象
    
public:
    Polygon(const vector<Point>& points) : vertices_(points) {
        if (points.size() < 3) return;//如果顶点数小于3，显然不是多边形
        for (size_t i = 0; i < points.size(); ++i) {
            size_t next = (i + 1) % points.size();//之所以取余是因为最后一个点的下一个点是第一个点
            edges_.push_back(new Edge(points[i], points[next]));//让边的起始点和终止点相邻
        }
    }
    ~Polygon() {for (Edge* edge : edges_) {delete edge;}}//析构函数，释放边的内存
    
    virtual double Circumference() const override {
        if (!IsValid()) return UnknownValue;
        double sum = 0;
        for (const Edge* edge : edges_) sum += edge->Length();
        return sum;
    }
    
    virtual double Area() const override {
        if (!IsValid()) return UnknownValue;
        double area = 0;
        for (size_t i = 0; i < vertices_.size(); ++i) {//通过顶点坐标计算多边形面积
            size_t j = (i + 1) % vertices_.size();
            area += vertices_[i].GetX() * vertices_[j].GetY();//面积等于x1*y2-x2*y1
            area -= vertices_[j].GetX() * vertices_[i].GetY();
        }
        return abs(area) / 2;//注意取绝对值 
    }
    
    virtual void Print() const override {
        cout << "Polygon with edges:" << endl;
        for (const Edge* edge : edges_) {
            cout << "  ";
            edge->Print();
            cout << endl;
        }
        if (IsValid()) {cout << "Area: " << Area() << ", Circumference: " << Circumference();}
        cout << endl;
    }
    
    virtual void Move(double x, double y) override {
        for (Point& vertex : vertices_) vertex.Move(x, y);
        for (Edge* edge : edges_) edge->Move(x, y);
    }
    
    virtual bool IsValid() const override {return vertices_.size() >= 3;}

    const vector<Point>& GetVertices() const { return vertices_; }
};

class CompositeShape : public Shape {// CompositeShape类表示复合形状，从Shape类继承
public:
    virtual double Circumference() const override { return UnknownValue; }
    virtual double Area() const override { return UnknownValue; }
    virtual bool IsValid() const override { return true; }
    virtual void Move(double x, double y) override {}
    virtual void Print() const override {}
};

shared_ptr<Shape> operator&(const Shape& s1, const Shape& s2) {
    if (typeid(s1) != typeid(s2)) {
        return make_shared<CompositeShape>(); // 不同类型返回复合形状
    }
    if (const Circle* c1 = dynamic_cast<const Circle*>(&s1)) {
        if (const Circle* c2 = dynamic_cast<const Circle*>(&s2)) {
            double dx = c1->GetCenter().GetX() - c2->GetCenter().GetX();
            double dy = c1->GetCenter().GetY() - c2->GetCenter().GetY();
            double distance = sqrt(dx * dx + dy * dy);
            if (distance < c1->GetRadius() + c2->GetRadius() && distance > abs(c1->GetRadius() - c2->GetRadius())) {//相交
                double smallerRadius = min(c1->GetRadius(), c2->GetRadius());
                const Point& center = (c1->GetRadius() < c2->GetRadius()) ? c1->GetCenter() : c2->GetCenter();//三元运算符返回较小半径的圆心
                return make_shared<Circle>(center, smallerRadius);
            }
        }
    }

    if (const Polygon* p1 = dynamic_cast<const Polygon*>(&s1)) {
        if (const Polygon* p2 = dynamic_cast<const Polygon*>(&s2)) {   
            const vector<Point>& vertices1 = p1->GetVertices();
            const vector<Point>& vertices2 = p2->GetVertices();
            for (const Point& v1 : vertices1) {
                for (const Point& v2 : vertices2) {
                    if (abs(v1.GetX() - v2.GetX()) < 1e-10 && abs(v1.GetY() - v2.GetY()) < 1e-10) {//判断两个多边形是否有交点
                        return (p1->Area() < p2->Area()) ? make_shared<Polygon>(vertices1) : make_shared<Polygon>(vertices2);// 返回面积较小的多边形
                    }
                }
            }
        }
    }
    return make_shared<CompositeShape>(); // 没有交集返回复合形状
}

shared_ptr<Shape> operator|(const Shape& s1, const Shape& s2) {
    if (typeid(s1) != typeid(s2)) {return make_shared<CompositeShape>(); }// 不同类型返回复合形状
    if (const Circle* c1 = dynamic_cast<const Circle*>(&s1)) {
        if (const Circle* c2 = dynamic_cast<const Circle*>(&s2)) {
            double dx = c1->GetCenter().GetX() - c2->GetCenter().GetX();
            double dy = c1->GetCenter().GetY() - c2->GetCenter().GetY();
            double distance = sqrt(dx * dx + dy * dy);
            if (distance < c1->GetRadius() + c2->GetRadius()) {// 如果圆相交或包含
                double largerRadius = max(c1->GetRadius(), c2->GetRadius());
                const Point& center = (c1->GetRadius() > c2->GetRadius()) ? c1->GetCenter() : c2->GetCenter();//三元运算符返回较大半径的圆心
                return make_shared<Circle>(center, largerRadius);
            }
        }
    }
    if (const Polygon* p1 = dynamic_cast<const Polygon*>(&s1)) {
        if (const Polygon* p2 = dynamic_cast<const Polygon*>(&s2)) {
            const vector<Point>& vertices1 = p1->GetVertices();//对多边形的定点进行返回
            const vector<Point>& vertices2 = p2->GetVertices();
            for (const Point& v1 : vertices1) {
                for (const Point& v2 : vertices2) {
                    if (abs(v1.GetX() - v2.GetX()) < 1e-10 && abs(v1.GetY() - v2.GetY()) < 1e-10) {//如果两个多边形有交点
                        return (p1->Area() > p2->Area()) ? make_shared<Polygon>(vertices1) : make_shared<Polygon>(vertices2);//返回面积较大的多边形
                    }
                }
            }
        }
    }
    return make_shared<CompositeShape>(); // 没有并集返回复合形状
}

class ShapeFile {// ShapeFile类定义
private:
    vector<Shape*> shapes_;
    vector<shared_ptr<Shape> > compositeShapes_;
    map<int, Point> points_;

    Point ParsePoint(const string& str) {
        size_t start = str.find('('), comma = str.find(','), end = str.find(')');
        return Point(stod(str.substr(start + 1, comma - start - 1)), stod(str.substr(comma + 1, end - comma - 1)));
    }
    int ParsePointNumber(const string& str) {
        size_t pos = str.find_first_of("0123456789", str.find("Point") + 5);//找到0-9的数字，之后的数字为点的编号
        return stoi(str.substr(pos, str.find_first_not_of("0123456789", pos) - pos));
    }

public:
    ShapeFile(const string& filename) {//构造函数
        ifstream file(filename);//读取文件
        string line;
        while (getline(file, line)) {//当读取到文件末尾时，getline函数返回false
            if (line.empty() || line[0] == '#') continue;//如果是空行或者是注释行，跳过
            istringstream iss(line);
            string type;
            iss >> type;

            if (type == "Point") {
                string coords;
                getline(iss, coords, ':');
                getline(iss, coords);
                points_[ParsePointNumber(line)] = ParsePoint(coords);
            }
            else if (type == "Circle:") {
                string pointPart, radiusStr;
                getline(iss, pointPart, ',');
                iss >> radiusStr;
                shapes_.push_back(new Circle(points_[ParsePointNumber(pointPart)], stod(radiusStr)));
            }
            else if (type == "Polygon:") {
                vector<Point> polyPoints;
                string rest;
                getline(iss, rest);
                size_t pos = 0;
                while ((pos = rest.find("Point")) != string::npos) {
                    size_t endPos = rest.find(",", pos);
                    if (endPos == string::npos) endPos = rest.length();
                    polyPoints.push_back(points_[ParsePointNumber(rest.substr(pos, endPos - pos))]);
                    rest = endPos < rest.length() ? rest.substr(endPos + 1) : "";
                }
                if (polyPoints.size() >= 3) shapes_.push_back(new Polygon(polyPoints));
            }
        } 
        cout << "\nOriginal Shapes:" << endl;
        for (const Shape* shape : shapes_) shape->Print();
    }

    void Generate() {
        for (size_t i = 0; i < shapes_.size(); ++i) {
            for (size_t j = i + 1; j < shapes_.size(); ++j) {
                auto r1 = (*shapes_[i]) & (*shapes_[j]);
                auto r2 = (*shapes_[i]) | (*shapes_[j]);
                if (dynamic_cast<Circle*>(shapes_[i]) && dynamic_cast<Circle*>(shapes_[j])) {
                    double dx = dynamic_cast<Circle*>(shapes_[i])->GetCenter().GetX() - dynamic_cast<Circle*>(shapes_[j])->GetCenter().GetX();
                    double dy = dynamic_cast<Circle*>(shapes_[i])->GetCenter().GetY() - dynamic_cast<Circle*>(shapes_[j])->GetCenter().GetY();
                    double distance = sqrt(dx * dx + dy * dy);
                    double radius1 = dynamic_cast<Circle*>(shapes_[i])->GetRadius();
                    double radius2 = dynamic_cast<Circle*>(shapes_[j])->GetRadius();

                    if (distance < radius1 + radius2) cout << "Circle " << i << " and Circle " << j << " intersect." << endl;//如果圆相交，输出相交
                    else cout << "Circle " << i << " and Circle " << j << " do not intersect." << endl;//如果圆不相交，输出不相交
                }
                if (r1 && r1->IsValid()) compositeShapes_.push_back(r1);
                if (r2 && r2->IsValid()) compositeShapes_.push_back(r2);   
            }
        }
    }
};

int main() {
    try {
        string filename = "shapes.txt"; //直接通过文件名shapes.txt读取文件
        ShapeFile sfile(filename); 
        sfile.Generate(); 
    } catch (const exception& e) {//如果出现异常，输出异常信息
        cerr << "Error: " << e.what() << endl;
        return 1;//不对劲，返回1
    }
    return 0;
}