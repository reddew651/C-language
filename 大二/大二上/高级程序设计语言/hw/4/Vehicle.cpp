#include <iostream>
using namespace std;

class Vehicle {
public:
    int maxSpeed;
    int weight;

    Vehicle(int mSpeed, int wt) : maxSpeed(mSpeed), weight(wt) {}

    virtual void run() const { cout << "Vehicle is running." << endl; }
    virtual void stop() const { cout << "Vehicle has stopped." << endl; }

    virtual ~Vehicle() {}
};

// Bicycle class derived from Vehicle with virtual inheritance
class Bicycle : virtual public Vehicle {
public:
    int height;

    Bicycle(int mSpeed, int wt, int ht) : Vehicle(mSpeed, wt), height(ht) {}

    void run() const override { cout << "Bicycle is running." << endl; }
    void stop() const override { cout << "Bicycle has stopped." << endl; }
};

// Automobile class derived from Vehicle with virtual inheritance
class Automobile : virtual public Vehicle {
public:
    int seatCount;

    Automobile(int mSpeed, int wt, int seats) : Vehicle(mSpeed, wt), seatCount(seats) {}

    void run() const override { cout << "Automobile is running." << endl; }
    void stop() const override { cout << "Automobile has stopped." << endl; }
};

// Motorcycle class derived from both Bicycle and Automobile
class Motorcycle : public Bicycle, public Automobile {
public:
    Motorcycle(int mSpeed, int wt, int ht, int seats) 
        : Vehicle(mSpeed, wt), Bicycle(mSpeed, wt, ht), Automobile(mSpeed, wt, seats) {}

    void run() const override { cout << "Motorcycle is running with a max speed of " << maxSpeed << " km/h." << endl; }
    void stop() const override { cout << "Motorcycle has stopped." << endl; }
};

int main() {
    Motorcycle m(150, 300, 100, 2);  // maxSpeed, weight, height, seatCount
    cout << "Motorcycle attributes:" << endl;
    cout << "Max Speed: " << m.maxSpeed << endl;
    cout << "Weight: " << m.weight << endl;
    cout << "Height: " << m.height << endl;
    cout << "Seat Count: " << m.seatCount << endl;
    m.run();
    m.stop();
    return 0;
}