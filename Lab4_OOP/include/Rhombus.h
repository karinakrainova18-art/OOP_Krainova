#ifndef RHOMBUS_H
#define RHOMBUS_H

#include "Figure.h"
#include <memory>
#include <cmath>

template<ScalarType T>
class Rhombus : public Figure<T> {
private:
    std::unique_ptr<Point<T>> center_;
    T diagonal1_;
    T diagonal2_;

public:
    Rhombus() : center_(std::make_unique<Point<T>>(0, 0)), diagonal1_(0), diagonal2_(0) {}
    
    Rhombus(T x, T y, T d1, T d2)
        : center_(std::make_unique<Point<T>>(x, y)), diagonal1_(d1), diagonal2_(d2) {}
    
    Rhombus(const Rhombus& other)
        : center_(std::make_unique<Point<T>>(*other.center_)),
          diagonal1_(other.diagonal1_), diagonal2_(other.diagonal2_) {}
    
    Rhombus& operator=(const Rhombus& other) {
        if (this != &other) {
            center_ = std::make_unique<Point<T>>(*other.center_);
            diagonal1_ = other.diagonal1_;
            diagonal2_ = other.diagonal2_;
        }
        return *this;
    }
    
    Rhombus(Rhombus&& other) noexcept
        : center_(std::move(other.center_)),
          diagonal1_(other.diagonal1_), diagonal2_(other.diagonal2_) {
        other.diagonal1_ = 0;
        other.diagonal2_ = 0;
    }
    
    Rhombus& operator=(Rhombus&& other) noexcept {
        if (this != &other) {
            center_ = std::move(other.center_);
            diagonal1_ = other.diagonal1_;
            diagonal2_ = other.diagonal2_;
            other.diagonal1_ = 0;
            other.diagonal2_ = 0;
        }
        return *this;
    }
    
    std::unique_ptr<Point<T>> geometricCenter() const override {
        return std::make_unique<Point<T>>(*center_);
    }
    
    double area() const override {
        return static_cast<double>(diagonal1_) * static_cast<double>(diagonal2_) / 2.0;
    }
    
    void printVertices(std::ostream& os) const override {
        double d1 = static_cast<double>(diagonal1_) / 2.0;
        double d2 = static_cast<double>(diagonal2_) / 2.0;
        double cx = static_cast<double>(center_->x());
        double cy = static_cast<double>(center_->y());
        
        os << "[";
        os << "(" << cx << ", " << (cy + d2) << ")";
        os << ", (" << (cx + d1) << ", " << cy << ")";
        os << ", (" << cx << ", " << (cy - d2) << ")";
        os << ", (" << (cx - d1) << ", " << cy << ")";
        os << "]";
    }
    
    void readFromStream(std::istream& is) override {
        T x, y;
        is >> x >> y >> diagonal1_ >> diagonal2_;
        center_ = std::make_unique<Point<T>>(x, y);
    }
    
    std::unique_ptr<Figure<T>> clone() const override {
        return std::make_unique<Rhombus<T>>(*this);
    }
    
    bool operator==(const Figure<T>& other) const override {
        if (const Rhombus<T>* r = dynamic_cast<const Rhombus<T>*>(&other)) {
            return *center_ == *r->center_ &&
                   std::abs(static_cast<double>(diagonal1_ - r->diagonal1_)) < 1e-9 &&
                   std::abs(static_cast<double>(diagonal2_ - r->diagonal2_)) < 1e-9;
        }
        return false;
    }
};

#endif
