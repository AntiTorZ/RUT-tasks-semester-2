#define _USE_MATH_DEFINES
#include <gtest/gtest.h>
#include "../include/ClassZeroOrderExtrapolator.h"
#include <cmath>
#include <float.h>
#include <vector>

TEST(ZeroOrderExtrapolatorTest, BasicCalculation) {
    std::vector<Point> pts = {
        Point(0, 10),
        Point(2, 20),
        Point(4, 5)
    };
    ZeroOrderExtrapolator zoe(pts);

    EXPECT_TRUE(fabs(zoe.calculateY(0.0) - 10.0) < DBL_EPSILON);
    EXPECT_TRUE(fabs(zoe.calculateY(1.9) - 10.0) < DBL_EPSILON);

    EXPECT_TRUE(fabs(zoe.calculateY(2.0) - 20.0) < DBL_EPSILON);
    EXPECT_TRUE(fabs(zoe.calculateY(3.9) - 20.0) < DBL_EPSILON);
}

TEST(ZeroOrderExtrapolatorTest, ShiftLeft) {
    std::vector<Point> pts = {
        Point(10, 100),
        Point(20, 200)
    };
    
    ZeroOrderExtrapolator zoe(pts);
    ZeroOrderExtrapolator shifted = zoe << 5.0;
    
    EXPECT_TRUE(fabs(shifted.calculateY(6.0) - 100.0) < DBL_EPSILON);
}

TEST(SegmentTest, ConstructionAndValue) {
    Point p1(0, 5);
    Point p2(10, 8);
    
    Segment seg(p1, p2);
    
    EXPECT_TRUE(fabs(seg.getLeftPoint().getX() - 0.0) < DBL_EPSILON);
    EXPECT_TRUE(fabs(seg.getLeftPoint().getY() - 5.0) < DBL_EPSILON);
    
    EXPECT_TRUE(fabs(seg.getRightPoint().getX() - 10.0) < DBL_EPSILON);
    EXPECT_TRUE(fabs(seg.getRightPoint().getY() - 5.0) < DBL_EPSILON);
    
    EXPECT_TRUE(fabs(seg.calculateY(5.0) - 5.0) < DBL_EPSILON);
}

TEST(PointTest, StreamOperators) {
    std::stringstream ss("1.5 2.5");
    Point p;
    ss >> p;
    EXPECT_TRUE(fabs(p.getX() - 1.5) < DBL_EPSILON);
    EXPECT_TRUE(fabs(p.getY() - 2.5) < DBL_EPSILON);
    
    std::stringstream out;
    out << p;
    EXPECT_EQ(out.str(), "(1.5, 2.5)");
}

TEST(PointTest, EqualityOperators) {
    Point p1(1.0, 2.0);
    Point p2(1.0, 2.0);
    Point p3(1.0 + DBL_EPSILON/2, 2.0 + DBL_EPSILON/2); // Почти равны
    Point p4(1.1, 2.1); // Не равны
    
    EXPECT_TRUE(p1 == p2);
    EXPECT_TRUE(p1 == p3); // С учётом DBL_EPSILON
    EXPECT_FALSE(p1 == p4);
    EXPECT_TRUE(p1 != p4);
}
