#include <iostream>
#include <cassert>
#include "../include/memory_resource.h"
#include "../include/dynamic_array.h"

void test_primitive_types() {
    HeapTrackingResource resource;
    DynamicArray<int> arr({&resource});

    assert(arr.empty());
    assert(arr.size() == 0);

    arr.push_back(1);
    arr.push_back(2);
    arr.push_back(3);

    assert(!arr.empty());
    assert(arr.size() == 3);
    assert(arr[0] == 1);
    assert(arr[1] == 2);
    assert(arr[2] == 3);

    arr.pop_back();
    assert(arr.size() == 2);
    assert(arr.back() == 2);

    int sum = 0;
    for (auto it = arr.begin(); it != arr.end(); ++it) {
        sum += *it;
    }
    assert(sum == 3);
}

void test_complex_types() {
    struct TestStruct {
        int a;
        double b;
        TestStruct(int a, double b) : a(a), b(b) {}
    };

    HeapTrackingResource resource;
    DynamicArray<TestStruct> arr({&resource});

    arr.push_back(TestStruct(1, 1.1));
    arr.push_back(TestStruct(2, 2.2));
    arr.push_back(TestStruct(3, 3.3));

    assert(arr.size() == 3);
    assert(arr[0].a == 1);
    assert(arr[1].b == 2.2);
    assert(arr[2].a == 3);

    int count = 0;
    for (auto it = arr.begin(); it != arr.end(); ++it) {
        count += it->a;
    }
    assert(count == 6);
}

void test_iterator_operations() {
    HeapTrackingResource resource;
    DynamicArray<int> arr({&resource});

    arr.push_back(10);
    arr.push_back(20);
    arr.push_back(30);

    auto it1 = arr.begin();
    auto it2 = arr.begin();
    assert(it1 == it2);

    ++it1;
    assert(*it1 == 20);
    assert(it1 != it2);

    auto it3 = it1++;
    assert(*it3 == 20);
    assert(*it1 == 30);
}

void test_memory_reuse() {
    HeapTrackingResource resource;
    DynamicArray<int> arr({&resource});

    for (int i = 0; i < 10; ++i) {
        arr.push_back(i);
    }

    size_t initial_blocks = 0;

    for (int i = 0; i < 5; ++i) {
        arr.pop_back();
    }

    for (int i = 0; i < 5; ++i) {
        arr.push_back(i + 100);
    }
}

void test_forward_iterator_concept() {
    using iterator = DynamicArray<int>::Iterator;
    static_assert(std::is_same_v<typename iterator::iterator_category, std::forward_iterator_tag>);
}

int main() {
    test_primitive_types();
    test_complex_types();
    test_iterator_operations();
    test_memory_reuse();
    test_forward_iterator_concept();

    std::cout << "All tests passed!" << std::endl;
    return 0;
}