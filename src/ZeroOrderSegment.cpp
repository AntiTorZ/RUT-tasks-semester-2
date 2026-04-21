#include "../include/ZeroOrderSegment.h"
#include <iostream>
#include <iomanip>
#include <stdexcept>

namespace miit::approximation {

double ZeroOrderSegment::calculateY(double x) const {
    const auto& pts = getPoints();
    
    if (pts.empty()) {
        throw std::runtime_error("Коллекция точек пуста");
    }
    
    // Экстраполяция слева от первой точки
    if (x < pts.front().getX()) {
        return pts.front().getY();
    }
    
    // Экстраполяция справа от последней точки
    if (x >= pts.back().getX()) {
        return pts.back().getY();
    }
    
    // Поиск интервала [x_i, x_{i+1}) и возврат ординаты левой точки
    // (логика экстраполятора нулевого порядка)
    for (size_t i = 0; i < pts.size() - 1; ++i) {
        if (x >= pts[i].getX() && x < pts[i + 1].getX()) {
            return pts[i].getY();
        }
    }
    
    // Фолбэк (должен быть достигнут только при x == последняя точка)
    return pts.back().getY();
}

std::ostream& operator<<(std::ostream& os, const ZeroOrderSegment& seg) {
    const auto& pts = seg.getPoints();
    os << "=== Экстраполятор нулевого порядка ===\n";
    os << "Опорные точки (" << pts.size() << " шт.):\n";
    
    for (size_t i = 0; i < pts.size(); ++i) {
        os << "  [" << i << "] " << pts[i];
        if (i < pts.size() - 1) {
            os << " -> y = " << std::fixed << std::setprecision(2) << pts[i].getY() 
               << " на интервале [" << pts[i].getX() << ", " << pts[i+1].getX() << ")";
        }
        os << "\n";
    }
    return os;
}

ZeroOrderSegment ZeroOrderSegment::readFromStream(std::istream& is) {
    return ZeroOrderSegment(readPointsFromStream(is));
}

} // namespace miit::approximation
