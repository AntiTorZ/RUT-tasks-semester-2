#include "../include/PiecewiseLinearApproximation.h"
#include <algorithm>
#include <stdexcept>
#include <iostream>

namespace miit::approximation {

void PiecewiseLinearApproximation::sortPoints() {
    std::sort(points_.begin(), points_.end());
}

PiecewiseLinearApproximation::PiecewiseLinearApproximation(const std::vector<Point>& pts) 
    : points_(pts) {
    if (points_.size() < 2) {
        throw std::invalid_argument("Требуется минимум 2 точки для аппроксимации");
    }
    sortPoints();
}

PiecewiseLinearApproximation::PiecewiseLinearApproximation(std::initializer_list<Point> pts) 
    : points_(pts) {
    if (points_.size() < 2) {
        throw std::invalid_argument("Требуется минимум 2 точки для аппроксимации");
    }
    sortPoints();
}

void PiecewiseLinearApproximation::addPoint(const Point& p) {
    points_.push_back(p);
    sortPoints();
}

std::vector<Point> PiecewiseLinearApproximation::readPointsFromStream(std::istream& is) {
    std::vector<Point> pts;
    size_t count = 0;
    
    std::cout << "Введите количество опорных точек (минимум 2): ";
    if (!(is >> count) || count < 2) {
        throw std::invalid_argument("Некорректное количество точек");
    }
    
    std::cout << "Введите координаты точек (формат: x y) для каждой:\n";
    for (size_t i = 0; i < count; ++i) {
        Point p;
        std::cout << "Точка #" << (i + 1) << ": ";
        if (!(is >> p)) {
            throw std::invalid_argument("Ошибка чтения координат точки");
        }
        pts.push_back(p);
    }
    return pts;
}

const std::vector<Point>& PiecewiseLinearApproximation::getPoints() const {
    return points_;
}

} // namespace miit::approximation
