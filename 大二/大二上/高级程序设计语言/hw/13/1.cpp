#include <iostream>
#include <string>
#include <algorithm>
#include <numeric> // for std::accumulate
#include <vector>

template <class T, int SIZE>
class Array {
private:
    T elements[SIZE];

public:
    // Constructor to initialize elements
    Array(std::initializer_list<T> list) {
        int i = 0;
        for (auto& item : list) {
            elements[i++] = item;
        }
    }

    // Sort the array
    void sort() {
        std::sort(elements, elements + SIZE);
    }

    // Find an element, return index or -1 if not found
    int find(const T& value) const {
        for (int i = 0; i < SIZE; ++i) {
            if (elements[i] == value) {
                return i;
            }
        }
        return -1;
    }

    // Calculate the sum of the elements
    T sum() const {
        if constexpr (std::is_arithmetic<T>::value) {
            return std::accumulate(elements, elements + SIZE, T(0));
        } else {
            return T(); // Return default for non-numeric types
        }
    }

    // Print the array
    void print() const {
        for (int i = 0; i < SIZE; ++i) {
            std::cout << elements[i] << " ";
        }
        std::cout << std::endl;
    }
};

// Overload << for Score class to print easily
class Score {
public:
    std::string student_id;
    double score;

    Score(const std::string& id = "", double sc = 0.0) : student_id(id), score(sc) {}

    bool operator<(const Score& other) const {
        return score < other.score;
    }

    bool operator==(const Score& other) const {
        return student_id == other.student_id && score == other.score;
    }

    friend std::ostream& operator<<(std::ostream& os, const Score& s) {
        os << "ID: " << s.student_id << ", Score: " << s.score;
        return os;
    }
};

// Test the Array class
int main() {
    // int array
    Array<int, 5> intArray = {5, 2, 8, 1, 9};
    intArray.sort();
    intArray.print();
    std::cout << "Index of 8: " << intArray.find(8) << std::endl;
    std::cout << "Sum: " << intArray.sum() << std::endl;

    // double array
    Array<double, 4> doubleArray = {1.1, 3.3, 2.2, 4.4};
    doubleArray.sort();
    doubleArray.print();
    std::cout << "Sum: " << doubleArray.sum() << std::endl;

    // string array
    Array<std::string, 3> stringArray = {"banana", "apple", "cherry"};
    stringArray.sort();
    stringArray.print();
    std::cout << "Index of 'apple': " << stringArray.find("apple") << std::endl;

    // Score array
    Array<Score, 3> scoreArray = {
        {"S001", 88.5},
        {"S002", 95.0},
        {"S003", 72.5}
    };
    scoreArray.sort();
    scoreArray.print();
    // Note: sum() won't work meaningfully for non-numeric types like Score

    return 0;
}