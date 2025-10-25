#include "Trapeze.h"
#include <cmath>

Trapeze::Trapeze(double x, double y, double top, double bottom, double h)
    : center(x, y), topBase(top), bottomBase(bottom), height(h) {}

Trapeze::Trapeze(const Trapeze& other)
    : center(other.center), topBase(other.topBase), 
      bottomBase(other.bottomBase), height(other.height) {}

Trapeze::Trapeze(Trapeze&& other) noexcept
    : center(std::move(other.center)), topBase(other.topBase),
      bottomBase(other.bottomBase), height(other.height) {
    other.topBase = 0;
    other.bottomBase = 0;
    other.height = 0;
}

Trapeze& Trapeze::operator=(const Trapeze& other) {
    if (this != &other) {
        center = other.center;
        topBase = other.topBase;
        bottomBase = other.bottomBase;
        height = other.height;
    }
    return *this;
}

Trapeze& Trapeze::operator=(Trapeze&& other) noexcept {
    if (this != &other) {
        center = std::move(other.center);
        topBase = other.topBase;
        bottomBase = other.bottomBase;
        height = other.height;
        other.topBase = 0;
        other.bottomBase = 0;
        other.height = 0;
    }
    return *this;
}

Point Trapeze::geometricCenter() const {
    return center;
}

double Trapeze::area() const {
    return (topBase + bottomBase) * height / 2;
}

void Trapeze::printVertices(std::ostream& os) const {
    double topOffset = topBase / 2;
    double bottomOffset = bottomBase / 2;
    
    Point vertices[4] = {
        Point(center.x - bottomOffset, center.y - height/2),
        Point(center.x + bottomOffset, center.y - height/2),
        Point(center.x + topOffset, center.y + height/2),
        Point(center.x - topOffset, center.y + height/2)
    };
    
    os << "[";
    for (int i = 0; i < 4; ++i) {
        os << "(" << vertices[i].x << ", " << vertices[i].y << ")";
        if (i < 3) os << ", ";
    }
    os << "]";
}

void Trapeze::readFromStream(std::istream& is) {
    is >> center.x >> center.y >> topBase >> bottomBase >> height;
}

std::unique_ptr<Figure> Trapeze::clone() const {
    return std::make_unique<Trapeze>(*this);
}

bool Trapeze::operator==(const Figure& other) const {
    if (const Trapeze* t = dynamic_cast<const Trapeze*>(&other)) {
        return center == t->center && 
               std::abs(topBase - t->topBase) < 1e-9 && 
               std::abs(bottomBase - t->bottomBase) < 1e-9 && 
               std::abs(height - t->height) < 1e-9;
    }
    return false;
}