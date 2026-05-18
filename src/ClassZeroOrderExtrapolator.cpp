#define _USE_MATH_DEFINES
#include "../include/ClassZeroOrderExtrapolator.h"
#include <stdexcept>
#include <cmath>
#include <float.h>

Segment::Segment(const Point& left, const Point& right) {
    this->leftPoint = left;
    this->rightPoint = Point(right.getX(), left.getY());
}

Point Segment::getLeftPoint() const {
    return leftPoint;
}

Point Segment::getRightPoint() const {
    return rightPoint;
}

bool Segment::contains(const double x) const {
    double leftX = leftPoint.getX();
    double rightX = rightPoint.getX();
    
    bool greaterOrEqualLeft = (x > leftX) || (fabs(x - leftX) < DBL_EPSILON);
    bool lessThanRight = (x < rightX) && (fabs(x - rightX) > DBL_EPSILON);
    
    return greaterOrEqualLeft && lessThanRight;
}

double Segment::calculateY(const double x) const {
    if (contains(x)) {
        return leftPoint.getY();
    }
    throw out_of_range("x вне пределов отрезка");
}

Segment Segment::operator<<(const double value) const {
    Point newLeft(leftPoint.getX() - value, leftPoint.getY());
    Point newRight(rightPoint.getX() - value, rightPoint.getY());
    return Segment(newLeft, newRight);
}

Segment Segment::read(istream& is) {
    Point p1, p2;
    cout << "Введите левую точку отрезка (x y): ";
    is >> p1;
    cout << "Введите правую точку отрезка (x y): ";
    is >> p2;
    return Segment(p1, p2);
}

ZeroOrderExtrapolator::ZeroOrderExtrapolator(const vector<Point>& points) : PiecewiseLinearApproximation(const_cast<vector<Point>&>(points)) {
    buildSegments();
}

ZeroOrderExtrapolator::ZeroOrderExtrapolator(const initializer_list<Point> points) : PiecewiseLinearApproximation(points) {
    buildSegments();
}

void ZeroOrderExtrapolator::buildSegments() {
    segments.clear();
    if (points.size() < 2) return;

    for (size_t i = 0; i < points.size() - 1; ++i) {
        segments.emplace_back(points[i], points[i+1]);
    }
}

double ZeroOrderExtrapolator::calculateY(const double x) const {
    for (const auto& seg : segments) {
        if (seg.contains(x)) {
            return seg.getLeftPoint().getY();
        }
    }
    
    if (segments.empty()) throw runtime_error("Нет данных для аппроксимации");

    if (x < segments.front().getLeftPoint().getX() && 
        fabs(x - segments.front().getLeftPoint().getX()) > DBL_EPSILON) {
        return segments.front().getLeftPoint().getY();
    }
    
    if (x >= segments.back().getRightPoint().getX() || 
        fabs(x - segments.back().getRightPoint().getX()) < DBL_EPSILON) {
        return segments.back().getLeftPoint().getY();
    }
    
    return 0.0;
}

ZeroOrderExtrapolator ZeroOrderExtrapolator::operator<<(const double value) const {
    ZeroOrderExtrapolator result(*this);
    result.segments.clear();
    for (const auto& seg : this->segments) {
        result.segments.push_back(seg << value);
    }
    for (auto& p : result.points) {
        p.setX(p.getX() - value);
    }
    return result;
}

Segment ZeroOrderExtrapolator::readSegment(istream& is) {
    return Segment::read(is);
}
