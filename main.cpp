#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include "vector.h"

template <typename ForwardIt, typename Type>
ForwardIt my_remove(ForwardIt first, ForwardIt last, const Type& value) {

        //1. take range [first, last)
        //2. search for Type value
        //3. return new end of iterator

}

template <typename T>
void PrintVector(const Vector<T>& vector) {
    for (size_t i = 0; i < vector.Size(); ++i) {
        std::cout << vector[i] << ' ';
    }
    std::cout << "\n===================================\n";
}

struct Vector3 {
    float x = 0.0f, y = 0.0f, z = 0.0f;
    int* m_MemoryBlock;

    Vector3() { m_MemoryBlock = new int[5]; }
    
    Vector3(float scalar)
        : x(scalar), y(scalar), z(scalar) {
        m_MemoryBlock = new int[5];
    }
    
    Vector3(float x, float y, float z)
        : x(x), y(y), z(z) {
        m_MemoryBlock = new int[5];
    }
    
    Vector3(const Vector3& other)
        : x(other.x), y(other.y), z(other.z) {
        std::cout << "Copy C'tor\n";
    }
    
    Vector3(Vector3&& other)
        : x(other.x), y(other.y), z(other.z) {
        m_MemoryBlock = other.m_MemoryBlock;
        other.m_MemoryBlock = nullptr;
        std::cout << "Move C'tor\n";
    }
    
    ~Vector3() {
        delete[] m_MemoryBlock;
        std::cout << "Destroyed!\n";
    }

    Vector3& operator=(const Vector3& other) {
        std::cout << "Copy op=\n";
        x = other.x;
        y = other.y;
        z = other.z;
        return *this;
    }
    Vector3& operator=(Vector3&& other) {
        std::cout << "Move op=!\n";
        m_MemoryBlock = other.m_MemoryBlock;
        other.m_MemoryBlock = nullptr;
        x = other.x;
        y = other.y;
        z = other.z;
        return *this;
    }
};
template <>
void PrintVector(const Vector<Vector3>& vector) {
    for (size_t i = 0; i < vector.Size(); ++i) {
        std::cout << vector[i].x << ' ' << vector[i].y << ' ' << vector[i].z << '\n';
    }
    std::cout << "\n===================================\n";
}
int main() {

    Vector<int> vector;
    vector.EmplaceBack(1);
    vector.EmplaceBack(2);
    vector.EmplaceBack(3);
    vector.EmplaceBack(4);
    vector.EmplaceBack(5);

    std::cout << "Not using iterators:\n";
    for(size_t i = 0; i < vector.Size(); ++i) {
        std::cout << vector[i] <<' ';
    }
    std::cout <<"\nRange base for loop:\n";
    for(auto value : vector) {
        std::cout << value << ' ';
    }

    std::cout << "\nIterator:\n";
    for(Vector<int>::Iterator it = vector.begin(); it != vector.end(); ++it) {
        std::cout << *it << ' ';
    }

    std::cout << '\n';
    return 0;
}