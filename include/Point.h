#pragma once
#include <iosfwd>

namespace miit::approximation {

class Point {
private:
    double x_;
    double y_;

public:
    Point(double x = 0.0, double y = 0.0);

    [[nodiscard]] double getX() const;
    [[nodiscard]] double getY() const;

    bool operator==(const Point& other) const;
    bool operator!=(const Point& other) const;
    bool operator<(const Point& other) const;
    bool operator>(const Point& other) const;
    bool operator<=(const Point& other) const;
    bool operator>=(const Point& other) const;

    friend std::ostream& operator<<(std::ostream& os, const Point& p);
    friend std::istream& operator>>(std::istream& is, Point& p);
};

} // namespace miit::approximation
