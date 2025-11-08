#ifndef TRAPEZE_H
#define TRAPEZE_H

#include "Figure.h"
#include <memory>
#include <cmath>
#include <algorithm>

template<ScalarType T>
class Trapeze : public Figure<T> {
private:
    std::unique_ptr<Point<T>> center_;
    T topBase_;
    T bottomBase_;
    T height_;

public:
    Trapeze() : center_(std::make_unique<Point<T>>(0, 0)), topBase_(0), bottomBase_(0), height_(0) {}
    
    Trapeze(T x, T y, T topBase, T bottomBase, T height)
        : center_(std::make_unique<Point<T>>(x, y)), 
          topBase_(topBase), bottomBase_(bottomBase), height_(height) {}
    
    Trapeze(const Trapeze& other)
        : center_(std::make_unique<Point<T>>(*other.center_)),
          topBase_(other.topBase_), bottomBase_(other.bottomBase_), height_(other.height_) {}
    
    Trapeze& operator=(const Trapeze& other) {
        if (this != &other) {
            center_ = std::make_unique<Point<T>>(*other.center_);
            topBase_ = other.topBase_;
            bottomBase_ = other.bottomBase_;
            height_ = other.height_;
        }
        return *this;
    }
    
    Trapeze(Trapeze&& other) noexcept
        : center_(std::move(other.center_)),
          topBase_(other.topBase_), bottomBase_(other.bottomBase_), height_(other.height_) {
        other.topBase_ = 0;
        other.bottomBase_ = 0;
        other.height_ = 0;
    }
    
    Trapeze& operator=(Trapeze&& other) noexcept {
        if (this != &other) {
            center_ = std::move(other.center_);
            topBase_ = other.topBase_;
            bottomBase_ = other.bottomBase_;
            height_ = other.height_;
            other.topBase_ = 0;
            other.bottomBase_ = 0;
            other.height_ = 0;
        }
        return *this;
    }
    
    std::unique_ptr<Point<T>> geometricCenter() const override {
        return std::make_unique<Point<T>>(*center_);
    }
    
    double area() const override {
        return static_cast<double>(topBase_ + bottomBase_) * static_cast<double>(height_) / 2.0;
    }
    
    void printVertices(std::ostream& os) const override {
        double topOffset = static_cast<double>(topBase_) / 2.0;
        double bottomOffset = static_cast<double>(bottomBase_) / 2.0;
        double h = static_cast<double>(height_) / 2.0;
        double cx = static_cast<double>(center_->x());
        double cy = static_cast<double>(center_->y());
        
        os << "[";
        os << "(" << (cx - bottomOffset) << ", " << (cy - h) << ")";
        os << ", (" << (cx + bottomOffset) << ", " << (cy - h) << ")";
        os << ", (" << (cx + topOffset) << ", " << (cy + h) << ")";
        os << ", (" << (cx - topOffset) << ", " << (cy + h) << ")";
        os << "]";
    }
    
    void readFromStream(std::istream& is) override {
        T x, y;
        is >> x >> y >> topBase_ >> bottomBase_ >> height_;
        center_ = std::make_unique<Point<T>>(x, y);
    }
    
    std::unique_ptr<Figure<T>> clone() const override {
        return std::make_unique<Trapeze<T>>(*this);
    }
    
    bool operator==(const Figure<T>& other) const override {
        if (const Trapeze<T>* t = dynamic_cast<const Trapeze<T>*>(&other)) {
            return *center_ == *t->center_ &&
                   std::abs(static_cast<double>(topBase_ - t->topBase_)) < 1e-9 &&
                   std::abs(static_cast<double>(bottomBase_ - t->bottomBase_)) < 1e-9 &&
                   std::abs(static_cast<double>(height_ - t->height_)) < 1e-9;
        }
        return false;
    }
};

#endif
