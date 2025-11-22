#include <iostream>
#include "../include/memory_resource.h"
#include "../include/dynamic_array.h"

struct ComplexType {
    int id;
    double value;
    std::string name;

    ComplexType(int i, double v, const std::string& n) 
        : id(i), value(v), name(n) {}
    
    friend std::ostream& operator<<(std::ostream& os, const ComplexType& obj) {
        return os << "{" << obj.id << ", " << obj.value << ", \"" << obj.name << "\"}";
    }
};

int main() {
    {
        HeapTrackingResource resource;
        DynamicArray<int> arr({&resource});

        for (int i = 0; i < 5; ++i) {
            arr.push_back(i * 10);
        }

        std::cout << "Int array: ";
        for (auto it = arr.begin(); it != arr.end(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << "\n";
    }

    {
        HeapTrackingResource resource;
        DynamicArray<ComplexType> arr({&resource});

        arr.push_back({1, 3.14, "first"});
        arr.push_back({2, 2.71, "second"});
        arr.push_back(ComplexType{3, 1.41, "third"});

        std::cout << "Complex array: ";
        for (const auto& item : arr) {
            std::cout << item << " ";
        }
        std::cout << "\n";
    }

    return 0;
}