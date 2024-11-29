// 1. 虚函数练习：
// a) 定义一个Animal类，带有枚举变量type。枚举定义五种动物mammals, birds, fish, reptiles, amphibians。Animal基类里面有SetType, GetType，SetName, GetName，Display等虚函数。
// b) 从Animal派生一个Mammal类，重载Display方法（注意添加override关键词），另外还有一些自己特有的属性和方法。继续派生一个Dog类，重载Display()，添加一些特性，比如NumOfLegs().
// c) 从Animal派生一个Bird类，重载Display方法（注意添加override关键词），另外还有一些特有的属性和方法。
// d) 主函数里，定义2个Dog对象，2个Bird对象，放在一个指针向量vector<Animal*> animals中。遍历每个animal对象，分别调用Display函数.


#include <string>
#include <iostream>
#include <vector>
class Animal {
public:
    // Define enum for animal types
    enum AnimalType {   //enum is a type that can be used to define a set of named values
        MAMMALS,
        BIRDS,
        FISH,
        REPTILES,
        AMPHIBIANS
    };

private:
    AnimalType type;
    std::string name;

public:
    // Constructor
    Animal() : type(MAMMALS), name("") {}

    // Virtual destructor (important for inheritance)
    virtual ~Animal() {}    //virtual destructor is used to ensure that the destructor of the derived class is called when an object of the derived class is destroyed.

    // Set and Get Type
    virtual void SetType(AnimalType newType) {
        type = newType;
    }

    virtual AnimalType GetType() const {
        return type;
    }

    // Set and Get Name
    virtual void SetName(const std::string& newName) {
        name = newName;
    }

    virtual std::string GetName() const {
        return name;
    }

    // Display function
    virtual void Display() const {
        std::string typeStr;
        switch(type) {
            case MAMMALS: typeStr = "Mammals"; break;
            case BIRDS: typeStr = "Birds"; break;
            case FISH: typeStr = "Fish"; break;
            case REPTILES: typeStr = "Reptiles"; break;
            case AMPHIBIANS: typeStr = "Amphibians"; break;
        }
        std::cout << "Name: " << name << "\n";
        std::cout << "Type: " << typeStr << "\n";
    }
};

//here is the mammal class derived from animal
class Mammal : public Animal {
private:
    bool hasHair;
    bool isWarmBlooded;

public:
    Mammal() : hasHair(true), isWarmBlooded(true) {
        SetType(MAMMALS);  // Set type to MAMMALS by default
    }
    //set and get the hasHair and isWarmBlooded
    void SetHasHair(bool hair) { hasHair = hair; }
    bool GetHasHair() const { return hasHair; }

    void SetWarmBlooded(bool warm) { isWarmBlooded = warm; }
    bool GetWarmBlooded() const { return isWarmBlooded; }

    void Display() const override { //override is used to override the base class display function
        Animal::Display();  // Call base class display first
        std::cout << "Has Hair: " << (hasHair ? "Yes" : "No") << "\n";
        std::cout << "Warm Blooded: " << (isWarmBlooded ? "Yes" : "No") << "\n";
    }
};

class Dog : public Mammal {
private:
    int numLegs;
    std::string breed;

public:
    Dog() : numLegs(4), breed("Unknown") {
        SetName("Dog");
    }

    void SetNumLegs(int legs) { numLegs = legs; }
    int GetNumLegs() const { return numLegs; }

    void SetBreed(const std::string& newBreed) { breed = newBreed; }
    std::string GetBreed() const { return breed; }

    void Display() const override {
        Mammal::Display();  // Call parent class display first
        std::cout << "Number of Legs: " << numLegs << "\n";
        std::cout << "Breed: " << breed << "\n";
    }
};


class Bird : public Animal {
private:
    bool canFly;
    double wingspan;  // in centimeters

public:
    Bird() : canFly(true), wingspan(0.0) {
        SetType(BIRDS);  // Set type to BIRDS by default
    }

    void SetCanFly(bool fly) { canFly = fly; }
    bool GetCanFly() const { return canFly; }

    void SetWingspan(double span) { wingspan = span; }
    double GetWingspan() const { return wingspan; }

    void Display() const override {
        Animal::Display();  // Call base class display first
        std::cout << "Can Fly: " << (canFly ? "Yes" : "No") << "\n";
        std::cout << "Wingspan: " << wingspan << " cm\n";
    }
};

int main() {
    // Create a vector to store Animal pointers
    std::vector<Animal*> animals;
    
    // Create and configure Dog objects
    Dog* dog1 = new Dog();
    dog1->SetName("Buddy");
    dog1->SetBreed("Golden Retriever");
    
    Dog* dog2 = new Dog();
    dog2->SetName("Max");
    dog2->SetBreed("German Shepherd");
    
    // Create and configure Bird objects
    Bird* bird1 = new Bird();
    bird1->SetName("Tweety");
    bird1->SetWingspan(15.5);
    
    Bird* bird2 = new Bird();
    bird2->SetName("Eagle");
    bird2->SetWingspan(200.0);
    bird2->SetCanFly(true);
    
    // Add all objects to the vector
    animals.push_back(dog1);
    animals.push_back(dog2);
    animals.push_back(bird1);
    animals.push_back(bird2);
    
    // Display all animals
    std::cout << "Displaying all animals:\n\n";
    for (const Animal* animal : animals) {
        animal->Display();
        std::cout << "------------------------\n";
    }
    
    // Clean up memory
    for (Animal* animal : animals) {
        delete animal;
    }
    
    return 0;
}