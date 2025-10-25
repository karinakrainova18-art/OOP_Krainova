#ifndef TRAPEZE_H
#define TRAPEZE_H

#include "Figure.h"
#include <memory>

class Trapeze : public Figure {
private:
    Point center;
    double topBase, bottomBase, height;

public:
    Trapeze(double x = 0, double y = 0, double top = 1, double bottom = 2, double h = 1);
    
    Trapeze(const Trapeze& other);
    Trapeze(Trapeze&& other) noexcept;
    Trapeze& operator=(const Trapeze& other);
    Trapeze& operator=(Trapeze&& other) noexcept;
    ~Trapeze() override = default;
    
    Point geometricCenter() const override;
    double area() const override;
    void printVertices(std::ostream& os) const override;
    void readFromStream(std::istream& is) override;
    
    std::unique_ptr<Figure> clone() const override;
    bool operator==(const Figure& other) const override;
};

#endif