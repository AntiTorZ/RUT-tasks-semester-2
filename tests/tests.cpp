#define _USE_MATH_DEFINES
#include <gtest/gtest.h>
#include <sstream>
#include <cmath>
#include <limits>
#include "../include/Point.h"
#include "../include/ZeroOrderSegment.h"

using namespace miit::approximation;

TEST(PointTest, ConstructorsAndGetters) {
    Point p(3.14, 2.71);
    EXPECT_DOUBLE_EQ(p.getX(), 3.14);
    EXPECT_DOUBLE_EQ(p.getY(), 2.71);
    Point def;
    EXPECT_DOUBLE_EQ(def.getX(), 0.0);
    EXPECT_DOUBLE_EQ(def.getY(), 0.0);
}

TEST(PointTest, Comparisons) {
    Point p1(1.0, 2.0), p2(1.0, 2.0), p3(2.0, 1.0);
    EXPECT_TRUE(p1 == p2);
    EXPECT_FALSE(p1 != p2);
    EXPECT_TRUE(p1 < p3);
    EXPECT_TRUE(p1 <= p2);
}

TEST(PointTest, IOStreams) {
    std::ostringstream out;
    out << Point(12.34, 56.78);
    EXPECT_EQ(out.str(), "(12.34, 56.78)");
    
    std::istringstream in("99.99 -11.11");
    Point p;
    in >> p;
    EXPECT_DOUBLE_EQ(p.getX(), 99.99);
    EXPECT_DOUBLE_EQ(p.getY(), -11.11);
}

TEST(ZeroOrderTest, ConstructionAndSorting) {
    std::vector<Point> unsorted = {{5.0, 10.0}, {1.0, 20.0}, {3.0, 15.0}};
    ZeroOrderSegment seg(unsorted);
    const auto& pts = seg.getPoints();
    EXPECT_DOUBLE_EQ(pts[0].getX(), 1.0);
    EXPECT_DOUBLE_EQ(pts[1].getX(), 3.0);
    EXPECT_DOUBLE_EQ(pts[2].getX(), 5.0);
}

TEST(ZeroOrderTest, AddPoint) {
    ZeroOrderSegment seg({{0.0, 1.0}, {4.0, 2.0}});
    seg.addPoint({2.0, 5.0});
    EXPECT_EQ(seg.getPoints().size(), 3);
    EXPECT_DOUBLE_EQ(seg.getPoints()[1].getX(), 2.0);
}

TEST(ZeroOrderTest, ZeroOrderLogic) {
    ZeroOrderSegment seg({{0.0, 1.0}, {2.0, 3.0}, {4.0, 2.0}});
    EXPECT_DOUBLE_EQ(seg.calculateY(-1.0), 1.0);   // Экстраполяция влево
    EXPECT_DOUBLE_EQ(seg.calculateY(0.5), 1.0);    // [0, 2) -> y=1
    EXPECT_DOUBLE_EQ(seg.calculateY(2.0), 3.0);    // [2, 4) -> y=3
    EXPECT_DOUBLE_EQ(seg.calculateY(3.99), 3.0);
    EXPECT_DOUBLE_EQ(seg.calculateY(4.0), 2.0);    // Правая граница
    EXPECT_DOUBLE_EQ(seg.calculateY(10.0), 2.0);   // Экстраполяция вправо
}

TEST(ZeroOrderTest, OutputStream) {
    ZeroOrderSegment seg({{0.0, 1.5}, {3.0, 2.5}});
    std::ostringstream out;
    out << seg;
    EXPECT_NE(out.str().find("Экстраполятор нулевого порядка"), std::string::npos);
    EXPECT_NE(out.str().find("(0.00, 1.50)"), std::string::npos);
}

TEST(ZeroOrderTest, ReadFromStream) {
    std::istringstream input("2\n0.0 10.0\n5.0 20.0");
    ZeroOrderSegment seg = ZeroOrderSegment::readFromStream(input);
    EXPECT_EQ(seg.getPoints().size(), 2);
    EXPECT_DOUBLE_EQ(seg.getPoints()[0].getY(), 10.0);
    EXPECT_DOUBLE_EQ(seg.getPoints()[1].getY(), 20.0);
}

TEST(ZeroOrderTest, Exceptions) {
    EXPECT_THROW(ZeroOrderSegment({{0.0, 1.0}}), std::invalid_argument);
    EXPECT_THROW(ZeroOrderSegment(std::vector<Point>{}), std::invalid_argument);
}

TEST(ZeroOrderTest, Polymorphism) {
    PiecewiseLinearApproximation* base = new ZeroOrderSegment({{1.0, 10.0}, {3.0, 20.0}});
    EXPECT_DOUBLE_EQ(base->calculateY(1.5), 10.0);
    EXPECT_DOUBLE_EQ(base->calculateY(3.0), 20.0);
    delete base;
}
