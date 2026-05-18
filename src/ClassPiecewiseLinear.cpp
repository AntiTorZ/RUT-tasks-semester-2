#include "../include/ClassPiecewiseLinear.h"
#include <algorithm>

PiecewiseLinearApproximation::PiecewiseLinearApproximation(vector<Point>& points) : points(points) {
    std::sort(this->points.begin(), this->points.end());
}

PiecewiseLinearApproximation::PiecewiseLinearApproximation(initializer_list<Point> points) : points(points) {
    std::sort(this->points.begin(), this->points.end());
}

void PiecewiseLinearApproximation::addPoint(const Point& point) {
    points.push_back(point);
    std::sort(points.begin(), points.end());
}

vector<Point> PiecewiseLinearApproximation::getPoints() const {
    return points;
}

vector<Point> PiecewiseLinearApproximation::readPoints(istream& is) {
    vector<Point> pts;
    size_t n;
    cout << "Введите количество точек: ";
    if (!(is >> n)) return pts;
    
    for (size_t i = 0; i < n; ++i) {
        Point p;
        cout << "Точка " << i + 1 << " (x y): ";
        is >> p;
        pts.push_back(p);
    }
    return pts;
}
