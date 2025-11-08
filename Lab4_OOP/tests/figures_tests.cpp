#include <gtest/gtest.h>
#include "Point.h"
#include "Figure.h"
#include "Trapeze.h"
#include "Rhombus.h"
#include "Pentagon.h"
#include "Array.h"
#include <memory>
#include <cmath>

TEST(PointTest, DefaultConstructor) {
    Point<int> p;
    EXPECT_EQ(p.x(), 0);
    EXPECT_EQ(p.y(), 0);
}

TEST(PointTest, ParameterizedConstructor) {
    Point<double> p(3.5, 4.2);
    EXPECT_DOUBLE_EQ(p.x(), 3.5);
    EXPECT_DOUBLE_EQ(p.y(), 4.2);
}

TEST(PointTest, CopyConstructor) {
    Point<int> p1(5, 10);
    Point<int> p2(p1);
    EXPECT_EQ(p2.x(), 5);
    EXPECT_EQ(p2.y(), 10);
}

TEST(PointTest, MoveConstructor) {
    Point<int> p1(5, 10);
    Point<int> p2(std::move(p1));
    EXPECT_EQ(p2.x(), 5);
    EXPECT_EQ(p2.y(), 10);
}

TEST(PointTest, EqualityOperator) {
    Point<int> p1(5, 10);
    Point<int> p2(5, 10);
    Point<int> p3(5, 11);
    EXPECT_TRUE(p1 == p2);
    EXPECT_FALSE(p1 == p3);
}

TEST(TrapezeTest, DefaultConstructor) {
    Trapeze<int> t;
    auto center = t.geometricCenter();
    EXPECT_EQ(center->x(), 0);
    EXPECT_EQ(center->y(), 0);
    EXPECT_DOUBLE_EQ(t.area(), 0.0);
}

TEST(TrapezeTest, ParameterizedConstructor) {
    Trapeze<int> t(0, 0, 2, 4, 3);
    EXPECT_DOUBLE_EQ(t.area(), (2.0 + 4.0) * 3.0 / 2.0);
}

TEST(TrapezeTest, CopyConstructor) {
    Trapeze<int> t1(0, 0, 2, 4, 3);
    Trapeze<int> t2(t1);
    EXPECT_TRUE(t1 == t2);
}

TEST(TrapezeTest, MoveConstructor) {
    Trapeze<int> t1(0, 0, 2, 4, 3);
    double area = t1.area();
    Trapeze<int> t2(std::move(t1));
    EXPECT_DOUBLE_EQ(t2.area(), area);
}

TEST(TrapezeTest, ConversionToDouble) {
    Trapeze<int> t(0, 0, 2, 4, 3);
    double area = static_cast<double>(t);
    EXPECT_DOUBLE_EQ(area, 9.0);
}

TEST(RhombusTest, DefaultConstructor) {
    Rhombus<int> r;
    auto center = r.geometricCenter();
    EXPECT_EQ(center->x(), 0);
    EXPECT_EQ(center->y(), 0);
    EXPECT_DOUBLE_EQ(r.area(), 0.0);
}

TEST(RhombusTest, ParameterizedConstructor) {
    Rhombus<int> r(0, 0, 4, 6);
    EXPECT_DOUBLE_EQ(r.area(), 4.0 * 6.0 / 2.0);
}

TEST(RhombusTest, CopyConstructor) {
    Rhombus<int> r1(0, 0, 4, 6);
    Rhombus<int> r2(r1);
    EXPECT_TRUE(r1 == r2);
}

TEST(RhombusTest, ConversionToDouble) {
    Rhombus<int> r(0, 0, 4, 6);
    double area = static_cast<double>(r);
    EXPECT_DOUBLE_EQ(area, 12.0);
}

TEST(PentagonTest, DefaultConstructor) {
    Pentagon<int> p;
    auto center = p.geometricCenter();
    EXPECT_EQ(center->x(), 0);
    EXPECT_EQ(center->y(), 0);
    EXPECT_DOUBLE_EQ(p.area(), 0.0);
}

TEST(PentagonTest, ParameterizedConstructor) {
    Pentagon<int> p(0, 0, 5);
    EXPECT_GT(p.area(), 0.0);
}

TEST(PentagonTest, CopyConstructor) {
    Pentagon<int> p1(0, 0, 5);
    Pentagon<int> p2(p1);
    EXPECT_TRUE(p1 == p2);
}

TEST(ArrayTest, DefaultConstructor) {
    Array<int> arr;
    EXPECT_EQ(arr.size(), 0);
    EXPECT_GE(arr.capacity(), 1);
}

TEST(ArrayTest, AddElements) {
    Array<int> arr;
    arr.add(1);
    arr.add(2);
    arr.add(3);
    EXPECT_EQ(arr.size(), 3);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
    EXPECT_EQ(arr[2], 3);
}

TEST(ArrayTest, RemoveElement) {
    Array<int> arr;
    arr.add(1);
    arr.add(2);
    arr.add(3);
    arr.remove(1);
    EXPECT_EQ(arr.size(), 2);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 3);
}

TEST(ArrayTest, ArrayOfFigures) {
    Array<std::shared_ptr<Figure<int>>> figures;
    auto trap = std::make_shared<Trapeze<int>>(0, 0, 2, 4, 3);
    auto rhomb = std::make_shared<Rhombus<int>>(0, 0, 4, 6);
    
    figures.add(trap);
    figures.add(rhomb);
    
    EXPECT_EQ(figures.size(), 2);
    EXPECT_DOUBLE_EQ(figures[0]->area(), 9.0);
    EXPECT_DOUBLE_EQ(figures[1]->area(), 12.0);
}

TEST(ArrayTest, ArrayOfRhombus) {
    Array<std::shared_ptr<Rhombus<int>>> rhombusArray;
    auto rhomb1 = std::make_shared<Rhombus<int>>(0, 0, 4, 6);
    auto rhomb2 = std::make_shared<Rhombus<int>>(5, 5, 8, 10);
    
    rhombusArray.add(rhomb1);
    rhombusArray.add(rhomb2);
    
    EXPECT_EQ(rhombusArray.size(), 2);
    EXPECT_DOUBLE_EQ(rhombusArray[0]->area(), 12.0);
    EXPECT_DOUBLE_EQ(rhombusArray[1]->area(), 40.0);
}

TEST(ArrayTest, MoveSemantics) {
    Array<int> arr1;
    arr1.add(1);
    arr1.add(2);
    
    Array<int> arr2(std::move(arr1));
    EXPECT_EQ(arr2.size(), 2);
    EXPECT_EQ(arr1.size(), 0);
}

TEST(ArrayTest, ResizeWithMove) {
    Array<int> arr;
    for (int i = 0; i < 20; ++i) {
        arr.add(i);
    }
    EXPECT_EQ(arr.size(), 20);
    EXPECT_GE(arr.capacity(), 20);
    
    for (int i = 0; i < 20; ++i) {
        EXPECT_EQ(arr[i], i);
    }
}

TEST(FigureComparisonTest, TrapezeEquality) {
    auto trap1 = std::make_shared<Trapeze<int>>(0, 0, 2, 4, 3);
    auto trap2 = std::make_shared<Trapeze<int>>(0, 0, 2, 4, 3);
    auto trap3 = std::make_shared<Trapeze<int>>(1, 1, 2, 4, 3);
    
    EXPECT_TRUE(*trap1 == *trap2);
    EXPECT_FALSE(*trap1 == *trap3);
}

TEST(FigureComparisonTest, RhombusEquality) {
    auto rhomb1 = std::make_shared<Rhombus<int>>(0, 0, 4, 6);
    auto rhomb2 = std::make_shared<Rhombus<int>>(0, 0, 4, 6);
    auto rhomb3 = std::make_shared<Rhombus<int>>(0, 0, 4, 7);
    
    EXPECT_TRUE(*rhomb1 == *rhomb2);
    EXPECT_FALSE(*rhomb1 == *rhomb3);
}

TEST(TotalAreaTest, CalculateTotalArea) {
    Array<std::shared_ptr<Figure<int>>> figures;
    auto trap = std::make_shared<Trapeze<int>>(0, 0, 2, 4, 3);
    auto rhomb = std::make_shared<Rhombus<int>>(0, 0, 4, 6);
    auto pent = std::make_shared<Pentagon<int>>(0, 0, 5);
    
    figures.add(trap);
    figures.add(rhomb);
    figures.add(pent);
    
    double total = 0.0;
    for (size_t i = 0; i < figures.size(); ++i) {
        total += figures[i]->area();
    }
    
    EXPECT_GT(total, 0.0);
    EXPECT_DOUBLE_EQ(total, trap->area() + rhomb->area() + pent->area());
}
