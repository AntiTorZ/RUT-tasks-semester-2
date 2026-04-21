#include "../include/Point.h"
#include <iostream>
#include <iomanip>

namespace miit::approximation {

Point::Point(double x, double y) : x_(x), y_(y) {}

double Point::getX() const { return x_; }
double Point::getY() const { return y_; }

bool Point::operator==(const Point& other) const { return x_ == other.x_ && y_ == other.y_; }
bool Point::operator!=(const Point& other) const { return !(*this == other); }
bool Point::operator<(const Point& other) const { return x_ < other.x_; }
bool Point::operator>(const Point& other) const { return x_ > other.x_; }
bool Point::operator<=(const Point& other) const { return !(*this > other); }
bool Point::operator>=(const Point& other) const { return !(*this < other); }

std::ostream& operator<<(std::ostream& os, const Point& p) {
    os << std::fixed << std::setprecision(2) << "(" << p.x_ << ", " << p.y_ << ")";
    return os;
}

std::istream& operator>>(std::istream& is, Point& p) {
    return is >> p.x_ >> p.y_;
}

} // namespace miit::approximation
