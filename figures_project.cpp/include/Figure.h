#ifndef FIGURE_H
#define FIGURE_H

#include <iostream>
#include <vector>
#include <memory>
#include <cmath>

class Point {
public:
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}
    
    bool operator==(const Point& other) const {
        return std::abs(x - other.x) < 1e-9 && std::abs(y - other.y) < 1e-9;
    }
    
    bool operator!=(const Point& other) const {
        return !(*this == other);
    }
};

inline std::ostream& operator<<(std::ostream& os, const Point& p) {
    os << "(" << p.x << ", " << p.y << ")";
    return os;
}

class Figure {
public:
    virtual ~Figure() = default;
    
    virtual Point geometricCenter() const = 0;
    virtual double area() const = 0;
    virtual void printVertices(std::ostream& os) const = 0;
    virtual void readFromStream(std::istream& is) = 0;
    
    virtual std::unique_ptr<Figure> clone() const = 0;
    virtual bool operator==(const Figure& other) const = 0;
    
    operator double() const { return area(); }
    
    friend std::ostream& operator<<(std::ostream& os, const Figure& fig) {
        fig.printVertices(os);
        return os;
    }
    
    friend std::istream& operator>>(std::istream& is, Figure& fig) {
        fig.readFromStream(is);
        return is;
    }
};

class FigureArray {
private:
    std::vector<std::unique_ptr<Figure>> figures;

public:
    FigureArray() = default;
    ~FigureArray() = default;
    
    FigureArray(const FigureArray& other) {
        for (const auto& fig : other.figures) {
            figures.push_back(fig->clone());
        }
    }
    
    FigureArray& operator=(const FigureArray& other) {
        if (this != &other) {
            figures.clear();
            for (const auto& fig : other.figures) {
                figures.push_back(fig->clone());
            }
        }
        return *this;
    }
    
    FigureArray(FigureArray&& other) noexcept = default;
    FigureArray& operator=(FigureArray&& other) noexcept = default;
    
    void addFigure(std::unique_ptr<Figure> fig) {
        figures.push_back(std::move(fig));
    }
    
    void removeFigure(size_t index) {
        if (index < figures.size()) {
            figures.erase(figures.begin() + index);
        }
    }
    
    void printAll() const {
        for (size_t i = 0; i < figures.size(); ++i) {
            std::cout << "Figure " << i << ": ";
            std::cout << "Center: (" << figures[i]->geometricCenter().x << ", " 
                      << figures[i]->geometricCenter().y << ") ";
            std::cout << "Area: " << figures[i]->area() << " ";
            std::cout << "Vertices: " << *figures[i] << std::endl;
        }
    }
    
    double totalArea() const {
        double total = 0;
        for (const auto& fig : figures) {
            total += fig->area();
        }
        return total;
    }
    
    size_t size() const {
        return figures.size();
    }
    
    const Figure* getFigure(size_t index) const {
        return index < figures.size() ? figures[index].get() : nullptr;
    }
};

#endif