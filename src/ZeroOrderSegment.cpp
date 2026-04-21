#include "../include/ZeroOrderSegment.h"
#include <iostream>
#include <iomanip>
#include <stdexcept>

namespace miit::approximation {

double ZeroOrderSegment::calculateY(double x) const {
    const auto& pts = getPoints();
    if (pts.empty()) throw std::runtime_error("Коллекция точек пуста.");

    if (x < pts.front().getX()) return pts.front().getY();
    if (x >= pts.back().getX()) return pts.back().getY();

    for (size_t i = 0; i < pts.size() - 1; ++i) {
        if (x >= pts[i].getX() && x < pts[i + 1].getX()) {
            return pts[i].getY(); // Логика нулевого порядка: ступенька от левой точки
        }
    }
    return pts.back().getY();
}

std::ostream& operator<<(std::ostream& os, const ZeroOrderSegment& seg) {
    const auto& pts = seg.getPoints();
    os << "=== Экстраполятор нулевого порядка ===\n";
    os
