#ifndef FIGURE_H
#define FIGURE_H

#include "Point.h"
#include <memory>
#include <iostream>
#include <concepts>

template<ScalarType T>
class Figure {
public:
    virtual ~Figure() = default;
    
    virtual std::unique_ptr<Point<T>> geometricCenter() const = 0;
    virtual double area() const = 0;
    virtual void printVertices(std::ostream& os) const = 0;
    virtual void readFromStream(std::istream& is) = 0;
    virtual std::unique_ptr<Figure<T>> clone() const = 0;
    
    virtual bool operator==(const Figure<T>& other) const = 0;
    virtual bool operator!=(const Figure<T>& other) const {
        return !(*this == other);
    }
    
    explicit operator double() const {
        return area();
    }
    
    friend std::ostream& operator<<(std::ostream& os, const Figure<T>& fig) {
        auto center = fig.geometricCenter();
        os << "Center: " << *center << ", ";
        os << "Vertices: ";
        fig.printVertices(os);
        os << ", Area: " << fig.area();
        return os;
    }
    
    friend std::istream& operator>>(std::istream& is, Figure<T>& fig) {
        fig.readFromStream(is);
        return is;
    }
};

#endif
