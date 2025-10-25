#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Figure.h"
#include <memory>

class Rectangle : public Figure {
private:
    Point center;
    double width, height;

public:
    Rectangle(double x = 0, double y = 0, double w = 1, double h = 1);
    
    Rectangle(const Rectangle& other);
    Rectangle(Rectangle&& other) noexcept;
    Rectangle& operator=(const Rectangle& other);
    Rectangle& operator=(Rectangle&& other) noexcept;
    ~Rectangle() override = default;
    
    Point geometricCenter() const override;
    double area() const override;
    void printVertices(std::ostream& os) const override;
    void readFromStream(std::istream& is) override;
    
    std::unique_ptr<Figure> clone() const override;
    bool operator==(const Figure& other) const override;
};

#endif