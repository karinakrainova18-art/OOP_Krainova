#include "Rhombus.h"
#include <cmath>

Rhombus::Rhombus(double x, double y, double d1, double d2)
    : center(x, y), diagonal1(d1), diagonal2(d2) {}

Rhombus::Rhombus(const Rhombus& other)
    : center(other.center), diagonal1(other.diagonal1), diagonal2(other.diagonal2) {}

Rhombus::Rhombus(Rhombus&& other) noexcept
    : center(std::move(other.center)), diagonal1(other.diagonal1), diagonal2(other.diagonal2) {
    other.diagonal1 = 0;
    other.diagonal2 = 0;
}

Rhombus& Rhombus::operator=(const Rhombus& other) {
    if (this != &other) {
        center = other.center;
        diagonal1 = other.diagonal1;
        diagonal2 = other.diagonal2;
    }
    return *this;
}

Rhombus& Rhombus::operator=(Rhombus&& other) noexcept {
    if (this != &other) {
        center = std::move(other.center);
        diagonal1 = other.diagonal1;
        diagonal2 = other.diagonal2;
        other.diagonal1 = 0;
        other.diagonal2 = 0;
    }
    return *this;
}

Point Rhombus::geometricCenter() const {
    return center;
}

double Rhombus::area() const {
    return (diagonal1 * diagonal2) / 2;
}

void Rhombus::printVertices(std::ostream& os) const {
    Point vertices[4] = {
        Point(center.x, center.y + diagonal2/2),
        Point(center.x + diagonal1/2, center.y),
        Point(center.x, center.y - diagonal2/2),
        Point(center.x - diagonal1/2, center.y)
    };
    
    os << "[";
    for (int i = 0; i < 4; ++i) {
        os << "(" << vertices[i].x << ", " << vertices[i].y << ")";
        if (i < 3) os << ", ";
    }
    os << "]";
}

void Rhombus::readFromStream(std::istream& is) {
    is >> center.x >> center.y >> diagonal1 >> diagonal2;
}

std::unique_ptr<Figure> Rhombus::clone() const {
    return std::make_unique<Rhombus>(*this);
}

bool Rhombus::operator==(const Figure& other) const {
    if (const Rhombus* r = dynamic_cast<const Rhombus*>(&other)) {
        return center == r->center && 
               std::abs(diagonal1 - r->diagonal1) < 1e-9 && 
               std::abs(diagonal2 - r->diagonal2) < 1e-9;
    }
    return false;
}