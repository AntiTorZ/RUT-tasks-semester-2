#define _USE_MATH_DEFINES
#include "../include/ClassPoint.h"
#include <cmath>
#include <float.h>

Point::Point(const double x, const double y) : x(x), y(y) {}

double Point::getX() const {
    return x;
}

double Point::getY() const {
    return y;
}

void Point::setX(const double x) {
    this->x = x;
}

void Point::setY(const double y) {
    this->y = y;
}

bool Point::operator==(const Point& other) const {
    return fabs(this->x - other.x) < DBL_EPSILON && 
           fabs(this->y - other.y) < DBL_EPSILON;
}

bool Point::operator!=(const Point& other) const {
    return !(*this == other);
}

bool Point::operator<(const Point& other) const {
    // Сравниваем с учётом погрешности
    if (fabs(this->x - other.x) < DBL_EPSILON) {
        return false; // Считаем равными
    }
    return this->x < other.x;
}

ostream& operator<<(ostream& os, const Point& point) {
    os << "(" << point.x << ", " << point.y << ")";
    return os;
}

istream& operator>>(istream& is, Point& point) {
    is >> point.x >> point.y;
    return is;
}
