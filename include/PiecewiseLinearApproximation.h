#pragma once
#include "Point.h"
#include <vector>
#include <initializer_list>
#include <iosfwd>

namespace miit::approximation {

class PiecewiseLinearApproximation {
protected:
    std::vector<Point> points_;

    void sortPoints();

public:
    explicit PiecewiseLinearApproximation(const std::vector<Point>& pts);
    PiecewiseLinearApproximation(std::initializer_list<Point> pts);
    virtual ~PiecewiseLinearApproximation() = default;

    void addPoint(const Point& p);
    [[nodiscard]] virtual double calculateY(double x) const = 0;

    static std::vector<Point> readPointsFromStream(std::istream& is);
    [[nodiscard]] const std::vector<Point>& getPoints() const;
};

} // namespace miit::approximation
