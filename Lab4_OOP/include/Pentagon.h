#ifndef PENTAGON_H
#define PENTAGON_H

#include "Figure.h"
#include <memory>
#include <cmath>
#include <vector>

template<ScalarType T>
class Pentagon : public Figure<T> {
private:
    std::unique_ptr<Point<T>> center_;
    T radius_;

public:
    Pentagon() : center_(std::make_unique<Point<T>>(0, 0)), radius_(0) {}
    
    Pentagon(T x, T y, T radius)
        : center_(std::make_unique<Point<T>>(x, y)), radius_(radius) {}
    
    Pentagon(const Pentagon& other)
        : center_(std::make_unique<Point<T>>(*other.center_)),
          radius_(other.radius_) {}
    
    Pentagon& operator=(const Pentagon& other) {
        if (this != &other) {
            center_ = std::make_unique<Point<T>>(*other.center_);
            radius_ = other.radius_;
        }
        return *this;
    }
    
    Pentagon(Pentagon&& other) noexcept
        : center_(std::move(other.center_)),
          radius_(other.radius_) {
        other.radius_ = 0;
    }
    
    Pentagon& operator=(Pentagon&& other) noexcept {
        if (this != &other) {
            center_ = std::move(other.center_);
            radius_ = other.radius_;
            other.radius_ = 0;
        }
        return *this;
    }
    
    std::unique_ptr<Point<T>> geometricCenter() const override {
        return std::make_unique<Point<T>>(*center_);
    }
    
    double area() const override {
        const double PI = 3.14159265358979323846;
        double r = static_cast<double>(radius_);
        return (5.0 / 2.0) * r * r * std::sin(2.0 * PI / 5.0);
    }
    
    void printVertices(std::ostream& os) const override {
        const double PI = 3.14159265358979323846;
        double r = static_cast<double>(radius_);
        double cx = static_cast<double>(center_->x());
        double cy = static_cast<double>(center_->y());
        
        double startAngle = PI / 2.0;
        double angleStep = 2.0 * PI / 5.0;
        
        os << "[";
        for (int i = 0; i < 5; ++i) {
            double angle = startAngle + i * angleStep;
            double x = cx + r * std::cos(angle);
            double y = cy + r * std::sin(angle);
            os << "(" << x << ", " << y << ")";
            if (i < 4) os << ", ";
        }
        os << "]";
    }
    
    void readFromStream(std::istream& is) override {
        T x, y;
        is >> x >> y >> radius_;
        center_ = std::make_unique<Point<T>>(x, y);
    }
    
    std::unique_ptr<Figure<T>> clone() const override {
        return std::make_unique<Pentagon<T>>(*this);
    }
    
    bool operator==(const Figure<T>& other) const override {
        if (const Pentagon<T>* p = dynamic_cast<const Pentagon<T>*>(&other)) {
            return *center_ == *p->center_ &&
                   std::abs(static_cast<double>(radius_ - p->radius_)) < 1e-9;
        }
        return false;
    }
};

#endif
