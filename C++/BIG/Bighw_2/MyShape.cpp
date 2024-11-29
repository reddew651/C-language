#include <vector>
#include <iostream>
#include <memory>
#include <cmath>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <algorithm>
#include <utility>
#define PI 3.14159265358979323846

// Point类定义
class Point {
private:
    double x_, y_;
public:
    Point(double x = 0, double y = 0) : x_(x), y_(y) {}
    
    void Print() const {
        std::cout << "(" << x_ << ", " << y_ << ")";
    }
    
    void Move(double xoffset, double yoffset) {
        x_ += xoffset;
        y_ += yoffset;
    }
    
    double GetX() const { return x_; }
    double GetY() const { return y_; }
};

// Edge类定义
class Edge {
private:
    Point start_, end_;
public:
    Edge(const Point& start, const Point& end) : start_(start), end_(end) {}
    
    double Length() const {
        double dx = end_.GetX() - start_.GetX();
        double dy = end_.GetY() - start_.GetY();
        return std::sqrt(dx * dx + dy * dy);
    }
    
    void Print() const {
        start_.Print();
        std::cout << " - ";
        end_.Print();
    }
    
    void Move(double xoffset, double yoffset) {
        start_.Move(xoffset, yoffset);
        end_.Move(xoffset, yoffset);
    }

    const Point& GetStart() const { return start_; }
    const Point& GetEnd() const { return end_; }
};

// Shape抽象基类
class Shape {
public:
    static const int UnknownValue = -1;
    
    virtual double Circumference() const = 0;
    virtual double Area() const = 0;
    virtual void Print() const = 0;
    virtual void Move(double xoffset, double yoffset) = 0;
    virtual bool IsValid() const = 0;
    virtual ~Shape() {}
};

// Circle类定义
class Circle : public Shape {
private:
    Point center_;
    double radius_;
    
public:
    Circle(const Point& center, double radius) 
        : center_(center), radius_(radius) {}
        
    virtual double Circumference() const override {
        if (!IsValid()) return UnknownValue;
        return 2 * PI * radius_;
    }
    
    virtual double Area() const override {
        if (!IsValid()) return UnknownValue;
        return PI * radius_ * radius_;
    }
    
    virtual void Print() const override {
        std::cout << "Circle: Center ";
        center_.Print();
        std::cout << ", Radius: " << radius_;
        if (IsValid()) {
            std::cout << ", Area: " << Area()
                     << ", Circumference: " << Circumference();
        }
        std::cout << std::endl;
    }
    
    virtual void Move(double xoffset, double yoffset) override {
        center_.Move(xoffset, yoffset);
    }
    
    virtual bool IsValid() const override {
        return radius_ > 0;
    }

    const Point& GetCenter() const { return center_; }
    double GetRadius() const { return radius_; }
};

// Polygon类定义
class Polygon : public Shape {
private:
    std::vector<Point> vertices_;
    std::vector<Edge*> edges_;
    
public:
    Polygon(const std::vector<Point>& points) : vertices_(points) {
        if (points.size() < 3) return;
        
        for (size_t i = 0; i < points.size(); ++i) {
            size_t next = (i + 1) % points.size();
            edges_.push_back(new Edge(points[i], points[next]));
        }
    }
    
    ~Polygon() {
        for (Edge* edge : edges_) {
            delete edge;
        }
    }
    
    virtual double Circumference() const override {
        if (!IsValid()) return UnknownValue;
        double sum = 0;
        for (const Edge* edge : edges_) {
            sum += edge->Length();
        }
        return sum;
    }
    
    virtual double Area() const override {
        if (!IsValid()) return UnknownValue;
        double area = 0;
        for (size_t i = 0; i < vertices_.size(); ++i) {
            size_t j = (i + 1) % vertices_.size();
            area += vertices_[i].GetX() * vertices_[j].GetY();
            area -= vertices_[j].GetX() * vertices_[i].GetY();
        }
        return std::abs(area) / 2;
    }
    
    virtual void Print() const override {
        std::cout << "Polygon with edges:" << std::endl;
        for (const Edge* edge : edges_) {
            std::cout << "  ";
            edge->Print();
            std::cout << std::endl;
        }
        if (IsValid()) {
            std::cout << "Area: " << Area() 
                     << ", Circumference: " << Circumference();
        }
        std::cout << std::endl;
    }
    
    virtual void Move(double xoffset, double yoffset) override {
        for (Point& vertex : vertices_) {
            vertex.Move(xoffset, yoffset);
        }
        for (Edge* edge : edges_) {
            edge->Move(xoffset, yoffset);
        }
    }
    
    virtual bool IsValid() const override {
        return vertices_.size() >= 3;
    }

    const std::vector<Point>& GetVertices() const { return vertices_; }
};

// CompositeShape类 - 用于表示复合形状
class CompositeShape : public Shape {
public:
    virtual double Circumference() const override { return UnknownValue; }
    virtual double Area() const override { return UnknownValue; }
    virtual bool IsValid() const override { return true; }
    virtual void Move(double xoffset, double yoffset) override {}
    virtual void Print() const override {
        std::cout << "Composite Shape (Area and Circumference unknown)" << std::endl;
    }
};

// 操作符重载
std::shared_ptr<Shape> operator&(const Shape& s1, const Shape& s2) {
    // 如果类型不同，返回复合形状
    if (typeid(s1) != typeid(s2)) {
        return std::make_shared<CompositeShape>();
    }
    
    // 处理圆的情况
    if (const Circle* c1 = dynamic_cast<const Circle*>(&s1)) {
        if (const Circle* c2 = dynamic_cast<const Circle*>(&s2)) {
            // 计算圆心距离
            double dx = c1->GetCenter().GetX() - c2->GetCenter().GetX();
            double dy = c1->GetCenter().GetY() - c2->GetCenter().GetY();
            double distance = std::sqrt(dx * dx + dy * dy);
            
            // 如果圆相交
            if (distance <= c1->GetRadius() + c2->GetRadius()) {
                // 返回较小的圆
                double smallerRadius = std::min(c1->GetRadius(), c2->GetRadius());
                const Point& center = (c1->GetRadius() < c2->GetRadius()) ? 
                                     c1->GetCenter() : c2->GetCenter();
                return std::make_shared<Circle>(center, smallerRadius);
            }
        }
    }
    
    // 处理多边形的情况
    if (const Polygon* p1 = dynamic_cast<const Polygon*>(&s1)) {
        if (const Polygon* p2 = dynamic_cast<const Polygon*>(&s2)) {
            const std::vector<Point>& vertices1 = p1->GetVertices();
            const std::vector<Point>& vertices2 = p2->GetVertices();
            
            for (const Point& v1 : vertices1) {
                for (const Point& v2 : vertices2) {
                    if (std::abs(v1.GetX() - v2.GetX()) < 1e-10 && 
                        std::abs(v1.GetY() - v2.GetY()) < 1e-10) {
                        return (p1->Area() < p2->Area()) ? 
                               std::make_shared<Polygon>(vertices1) : 
                               std::make_shared<Polygon>(vertices2);
                    }
                }
            }
        }
    }
    
    return std::make_shared<CompositeShape>();
}

std::shared_ptr<Shape> operator|(const Shape& s1, const Shape& s2) {
    // 如果类型不同，返回复合形状
    if (typeid(s1) != typeid(s2)) {
        return std::make_shared<CompositeShape>();
    }
    
    // 处理圆的情况
    if (const Circle* c1 = dynamic_cast<const Circle*>(&s1)) {
        if (const Circle* c2 = dynamic_cast<const Circle*>(&s2)) {
            // 计算圆心距离
            double dx = c1->GetCenter().GetX() - c2->GetCenter().GetX();
            double dy = c1->GetCenter().GetY() - c2->GetCenter().GetY();
            double distance = std::sqrt(dx * dx + dy * dy);
            
            // 如果圆相交或包含
            if (distance <= c1->GetRadius() + c2->GetRadius()) {
                // 返回较大的圆
                double largerRadius = std::max(c1->GetRadius(), c2->GetRadius());
                const Point& center = (c1->GetRadius() > c2->GetRadius()) ? 
                                     c1->GetCenter() : c2->GetCenter();
                return std::make_shared<Circle>(center, largerRadius);
            }
        }
    }
    
    // 处理多边形的情况
    if (const Polygon* p1 = dynamic_cast<const Polygon*>(&s1)) {
        if (const Polygon* p2 = dynamic_cast<const Polygon*>(&s2)) {
            const std::vector<Point>& vertices1 = p1->GetVertices();
            const std::vector<Point>& vertices2 = p2->GetVertices();
            
            for (const Point& v1 : vertices1) {
                for (const Point& v2 : vertices2) {
                    if (std::abs(v1.GetX() - v2.GetX()) < 1e-10 && 
                        std::abs(v1.GetY() - v2.GetY()) < 1e-10) {
                        return (p1->Area() > p2->Area()) ? 
                               std::make_shared<Polygon>(vertices1) : 
                               std::make_shared<Polygon>(vertices2);
                    }
                }
            }
        }
    }
    
    return std::make_shared<CompositeShape>();
}

// ShapeFile类定义
class ShapeFile {
private:
    std::vector<Shape*> shapes_;
    std::vector<std::shared_ptr<Shape> > compositeShapes_;
    std::map<int, Point> points_;

    Point ParsePoint(const std::string& str) {
        size_t start = str.find('('), comma = str.find(','), end = str.find(')');
        return Point(std::stod(str.substr(start + 1, comma - start - 1)), 
                    std::stod(str.substr(comma + 1, end - comma - 1)));
    }

    int ParsePointNumber(const std::string& str) {
        size_t pos = str.find_first_of("0123456789", str.find("Point") + 5);
        return std::stoi(str.substr(pos, str.find_first_not_of("0123456789", pos) - pos));
    }

public:
    ShapeFile(const std::string& filename) {
        std::ifstream file(filename);
        std::string line;
        while (std::getline(file, line)) {
            if (line.empty() || line[0] == '#') continue;
            std::istringstream iss(line);
            std::string type;
            iss >> type;

            if (type == "Point") {
                std::string coords;
                std::getline(iss, coords, ':');
                std::getline(iss, coords);
                points_[ParsePointNumber(line)] = ParsePoint(coords);
            }
            else if (type == "Circle:") {
                std::string pointPart, radiusStr;
                std::getline(iss, pointPart, ',');
                iss >> radiusStr;
                shapes_.push_back(new Circle(points_[ParsePointNumber(pointPart)], std::stod(radiusStr)));
            }
            else if (type == "Polygon:") {
                std::vector<Point> polyPoints;
                std::string rest;
                std::getline(iss, rest);
                size_t pos = 0;
                while ((pos = rest.find("Point")) != std::string::npos) {
                    size_t endPos = rest.find(",", pos);
                    if (endPos == std::string::npos) endPos = rest.length();
                    polyPoints.push_back(points_[ParsePointNumber(rest.substr(pos, endPos - pos))]);
                    rest = endPos < rest.length() ? rest.substr(endPos + 1) : "";
                }
                if (polyPoints.size() >= 3) shapes_.push_back(new Polygon(polyPoints));
            }
        }
        
        std::cout << "\nOriginal Shapes:" << std::endl;
        for (const Shape* shape : shapes_) shape->Print();
    }

    void Generate() {
        for (size_t i = 0; i < shapes_.size(); ++i) {
            for (size_t j = i + 1; j < shapes_.size(); ++j) {
                auto r1 = (*shapes_[i]) & (*shapes_[j]), r2 = (*shapes_[i]) | (*shapes_[j]);
                if (r1 && r1->IsValid() && typeid(*r1) != typeid(CompositeShape)) 
                    compositeShapes_.push_back(r1);
                if (r2 && r2->IsValid() && typeid(*r2) != typeid(CompositeShape)) 
                    compositeShapes_.push_back(r2);
            }
        }
        
        if (!compositeShapes_.empty()) {
            std::cout << "\nComposite Shapes:" << std::endl;
            for (const auto& shape : compositeShapes_) shape->Print();
        }
    }
};

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }

    try {
        // 创建ShapeFile对象
        std::string filename = argv[1];
        ShapeFile sfile(filename);

        // 生成复合形状并打印
        sfile.Generate();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}