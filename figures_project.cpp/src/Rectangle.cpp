#include "Rectangle.h"
#include <cmath>

Rectangle::Rectangle(double x, double y, double w, double h) 
    : center(x, y), width(w), height(h) {}

Rectangle::Rectangle(const Rectangle& other) 
    : center(other.center), width(other.width), height(other.height) {}

Rectangle::Rectangle(Rectangle&& other) noexcept
    : center(std::move(other.center)), width(other.width), height(other.height) {
    other.width = 0;
    other.height = 0;
}

Rectangle& Rectangle::operator=(const Rectangle& other) {
    if (this != &other) {
        center = other.center;
        width = other.width;
        height = other.height;
    }
    return *this;
}

Rectangle& Rectangle::operator=(Rectangle&& other) noexcept {
    if (this != &other) {
        center = std::move(other.center);
        width = other.width;
        height = other.height;
        other.width = 0;
        other.height = 0;
    }
    return *this;
}

Point Rectangle::geometricCenter() const {
    return center;
}

double Rectangle::area() const {
    return width * height;
}

void Rectangle::printVertices(std::ostream& os) const {
    double halfW = width / 2;
    double halfH = height / 2;
    
    Point vertices[4] = {
        Point(center.x - halfW, center.y - halfH),
        Point(center.x + halfW, center.y - halfH),
        Point(center.x + halfW, center.y + halfH),
        Point(center.x - halfW, center.y + halfH)
    };
    
    os << "[";
    for (int i = 0; i < 4; ++i) {
        os << "(" << vertices[i].x << ", " << vertices[i].y << ")";
        if (i < 3) os << ", ";
    }
    os << "]";
}

void Rectangle::readFromStream(std::istream& is) {
    is >> center.x >> center.y >> width >> height;
}

std::unique_ptr<Figure> Rectangle::clone() const {
    return std::make_unique<Rectangle>(*this);
}

bool Rectangle::operator==(const Figure& other) const {
    if (const Rectangle* r = dynamic_cast<const Rectangle*>(&other)) {
        return center == r->center && 
               std::abs(width - r->width) < 1e-9 && 
               std::abs(height - r->height) < 1e-9;
    }
    return false;
}