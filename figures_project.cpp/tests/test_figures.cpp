#include <gtest/gtest.h>
#include <sstream>
#include "../include/Figure.h"
#include "../include/Rectangle.h"
#include "../include/Trapeze.h"
#include "../include/Rhombus.h"

class PointTest : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(PointTest, Equality) {
    Point p1(1.0, 2.0);
    Point p2(1.0, 2.0);
    Point p3(3.0, 4.0);
    
    EXPECT_EQ(p1, p2);
    EXPECT_NE(p1, p3);
}

class RectangleTest : public ::testing::Test {
protected:
    void SetUp() override {
        rect = std::make_unique<Rectangle>(0, 0, 4, 2);
    }
    
    void TearDown() override {
        rect.reset();
    }
    
    std::unique_ptr<Rectangle> rect;
};

TEST_F(RectangleTest, Construction) {
    EXPECT_EQ(rect->geometricCenter().x, 0);
    EXPECT_EQ(rect->geometricCenter().y, 0);
    EXPECT_DOUBLE_EQ(rect->area(), 8.0);
}

TEST_F(RectangleTest, CopyConstructor) {
    Rectangle rect2 = *rect;
    EXPECT_TRUE(rect2 == *rect);
}

TEST_F(RectangleTest, MoveConstructor) {
    Rectangle temp_rect(1, 1, 2, 2);
    Rectangle rect3 = std::move(temp_rect);
    EXPECT_EQ(rect3.geometricCenter().x, 1);
}

TEST_F(RectangleTest, StreamOperators) {
    std::stringstream ss;
    rect->printVertices(ss);
    EXPECT_FALSE(ss.str().empty());

    std::stringstream input("1.0 2.0 3.0 4.0");
    Rectangle rect4;
    input >> rect4;
    EXPECT_DOUBLE_EQ(rect4.geometricCenter().x, 1.0);
    EXPECT_DOUBLE_EQ(rect4.geometricCenter().y, 2.0);
}

class TrapezeTest : public ::testing::Test {
protected:
    void SetUp() override {
        trap = std::make_unique<Trapeze>(0, 0, 2, 4, 3);
    }
    
    void TearDown() override {
        trap.reset();
    }
    
    std::unique_ptr<Trapeze> trap;
};

TEST_F(TrapezeTest, Construction) {
    EXPECT_EQ(trap->geometricCenter().x, 0);
    EXPECT_EQ(trap->geometricCenter().y, 0);
    EXPECT_DOUBLE_EQ(trap->area(), 9.0);
}

TEST_F(TrapezeTest, CopyConstructor) {
    Trapeze trap2 = *trap;
    EXPECT_TRUE(trap2 == *trap);
}

TEST_F(TrapezeTest, StreamOperators) {
    std::stringstream ss;
    trap->printVertices(ss);
    EXPECT_FALSE(ss.str().empty());

    std::stringstream input("1.0 2.0 3.0 4.0 5.0");
    Trapeze trap4;
    input >> trap4;
    EXPECT_DOUBLE_EQ(trap4.geometricCenter().x, 1.0);
    EXPECT_DOUBLE_EQ(trap4.geometricCenter().y, 2.0);
}

class RhombusTest : public ::testing::Test {
protected:
    void SetUp() override {
        rhomb = std::make_unique<Rhombus>(0, 0, 4, 2);
    }
    
    void TearDown() override {
        rhomb.reset();
    }
    
    std::unique_ptr<Rhombus> rhomb;
};

TEST_F(RhombusTest, Construction) {
    EXPECT_EQ(rhomb->geometricCenter().x, 0);
    EXPECT_EQ(rhomb->geometricCenter().y, 0);
    EXPECT_DOUBLE_EQ(rhomb->area(), 4.0);
}

TEST_F(RhombusTest, CopyConstructor) {
    Rhombus rhomb2 = *rhomb;
    EXPECT_TRUE(rhomb2 == *rhomb);
}

TEST_F(RhombusTest, StreamOperators) {
    std::stringstream ss;
    rhomb->printVertices(ss);
    EXPECT_FALSE(ss.str().empty());

    std::stringstream input("1.0 2.0 3.0 4.0");
    Rhombus rhomb4;
    input >> rhomb4;
    EXPECT_DOUBLE_EQ(rhomb4.geometricCenter().x, 1.0);
    EXPECT_DOUBLE_EQ(rhomb4.geometricCenter().y, 2.0);
}

class FigureArrayTest : public ::testing::Test {
protected:
    void SetUp() override {
        array.addFigure(std::make_unique<Rectangle>(0, 0, 2, 2));
        array.addFigure(std::make_unique<Trapeze>(1, 1, 2, 4, 3));
        array.addFigure(std::make_unique<Rhombus>(2, 2, 4, 2));
    }
    
    FigureArray array;
};

TEST_F(FigureArrayTest, AddFigures) {
    EXPECT_EQ(array.size(), 3);
}

TEST_F(FigureArrayTest, TotalArea) {
    double totalArea = array.totalArea();
    double expectedArea = 4.0 + 9.0 + 4.0;
    EXPECT_NEAR(totalArea, expectedArea, 1e-9);
}

TEST_F(FigureArrayTest, CopyConstructor) {
    FigureArray array2 = array;
    EXPECT_EQ(array2.size(), array.size());
}

TEST_F(FigureArrayTest, RemoveFigure) {
    array.removeFigure(1);
    EXPECT_EQ(array.size(), 2);
}

class PolymorphismTest : public ::testing::Test {
protected:
    void SetUp() override {
        rect = std::make_unique<Rectangle>(0, 0, 2, 2);
        trap = std::make_unique<Trapeze>(0, 0, 2, 4, 3);
        rhomb = std::make_unique<Rhombus>(0, 0, 4, 2);
    }
    
    std::unique_ptr<Figure> rect;
    std::unique_ptr<Figure> trap;
    std::unique_ptr<Figure> rhomb;
};

TEST_F(PolymorphismTest, VirtualFunctions) {
    EXPECT_DOUBLE_EQ(rect->area(), 4.0);
    EXPECT_DOUBLE_EQ(trap->area(), 9.0);
    EXPECT_DOUBLE_EQ(rhomb->area(), 4.0);
}

TEST_F(PolymorphismTest, ConversionOperator) {
    double rectArea = *rect;
    double trapArea = *trap;
    double rhombArea = *rhomb;
    
    EXPECT_DOUBLE_EQ(rectArea, 4.0);
    EXPECT_DOUBLE_EQ(trapArea, 9.0);
    EXPECT_DOUBLE_EQ(rhombArea, 4.0);
}

TEST_F(PolymorphismTest, Cloning) {
    auto rectClone = rect->clone();
    EXPECT_DOUBLE_EQ(rectClone->area(), rect->area());
}

TEST(EdgeCasesTest, ZeroDimensions) {
    Rectangle zeroRect(0, 0, 0, 0);
    EXPECT_DOUBLE_EQ(zeroRect.area(), 0.0);
    
    Trapeze zeroTrap(0, 0, 0, 0, 0);
    EXPECT_DOUBLE_EQ(zeroTrap.area(), 0.0);
    
    Rhombus zeroRhomb(0, 0, 0, 0);
    EXPECT_DOUBLE_EQ(zeroRhomb.area(), 0.0);
}

TEST(EdgeCasesTest, NegativeDimensions) {
    Rectangle negRect(0, 0, -2, -2);
    EXPECT_DOUBLE_EQ(negRect.area(), 4.0);
}

TEST(EdgeCasesTest, EmptyArray) {
    FigureArray emptyArray;
    EXPECT_EQ(emptyArray.size(), 0);
    EXPECT_DOUBLE_EQ(emptyArray.totalArea(), 0.0);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}