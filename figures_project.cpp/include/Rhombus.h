#ifndef RHOMBUS_H
#define RHOMBUS_H

#include "Figure.h"
#include <memory>

class Rhombus : public Figure {
private:
    Point center;
    double diagonal1, diagonal2;

public:
    Rhombus(double x = 0, double y = 0, double d1 = 2, double d2 = 1);
    
    Rhombus(const Rhombus& other);
    Rhombus(Rhombus&& other) noexcept;
    Rhombus& operator=(const Rhombus& other);
    Rhombus& operator=(Rhombus&& other) noexcept;
    ~Rhombus() override = default;
    
    Point geometricCenter() const override;
    double area() const override;
    void printVertices(std::ostream& os) const override;
    void readFromStream(std::istream& is) override;
    
    std::unique_ptr<Figure> clone() const override;
    bool operator==(const Figure& other) const override;
};

#endif