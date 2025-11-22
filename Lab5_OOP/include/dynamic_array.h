#pragma once
#include <memory_resource>
#include <iterator>
#include <utility>

template<typename T>
class DynamicArray {
public:
    using allocator_type = std::pmr::polymorphic_allocator<T>;
    
    class Iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        Iterator(pointer ptr) : ptr(ptr) {}

        reference operator*() const { return *ptr; }
        pointer operator->() { return ptr; }

        Iterator& operator++() {
            ++ptr;
            return *this;
        }

        Iterator operator++(int) {
            Iterator tmp = *this;
            ++ptr;
            return tmp;
        }

        friend bool operator==(const Iterator& a, const Iterator& b) {
            return a.ptr == b.ptr;
        }

        friend bool operator!=(const Iterator& a, const Iterator& b) {
            return a.ptr != b.ptr;
        }

    private:
        pointer ptr;
    };

    DynamicArray(allocator_type alloc = {})
        : allocator(alloc), data(nullptr), size_(0), capacity_(0) {}

    ~DynamicArray() {
        clear();
        if (data) {
            for (size_t i = 0; i < capacity_; ++i) {
                allocator.deallocate(&data[i], 1);
            }
            ::operator delete(data);
        }
    }

    void push_back(const T& value) {
        if (size_ >= capacity_) {
            resize_capacity(capacity_ == 0 ? 1 : capacity_ * 2);
        }
        new (&data[size_]) T(value);
        ++size_;
    }

    void push_back(T&& value) {
        if (size_ >= capacity_) {
            resize_capacity(capacity_ == 0 ? 1 : capacity_ * 2);
        }
        new (&data[size_]) T(std::move(value));
        ++size_;
    }

    void pop_back() {
        if (size_ > 0) {
            data[size_ - 1].~T();
            --size_;
        }
    }

    T& operator[](size_t index) { return data[index]; }
    const T& operator[](size_t index) const { return data[index]; }

    Iterator begin() { return Iterator(data); }
    Iterator end() { return Iterator(data + size_); }

    size_t size() const { return size_; }
    bool empty() const { return size_ == 0; }

    T& front() { return data[0]; }
    T& back() { return data[size_ - 1]; }

private:
    void resize_capacity(size_t new_capacity) {
        T* new_data = static_cast<T*>(::operator new(new_capacity * sizeof(T)));
        
        for (size_t i = 0; i < size_; ++i) {
            new (&new_data[i]) T(std::move(data[i]));
            data[i].~T();
        }
        
        if (data) {
            for (size_t i = 0; i < capacity_; ++i) {
                allocator.deallocate(&data[i], 1);
            }
            ::operator delete(data);
        }
        
        for (size_t i = size_; i < new_capacity; ++i) {
            allocator.allocate(&new_data[i], 1);
        }
        
        data = new_data;
        capacity_ = new_capacity;
    }

    void clear() {
        for (size_t i = 0; i < size_; ++i) {
            data[i].~T();
        }
        size_ = 0;
    }

    allocator_type allocator;
    T* data;
    size_t size_;
    size_t capacity_;
};