#pragma once
#include "PiecewiseLinearApproximation.h"
#include <iosfwd>

namespace miit::approximation {

class ZeroOrderSegment : public PiecewiseLinearApproximation {
public:
    using PiecewiseLinearApproximation::PiecewiseLinearApproximation;

    [[nodiscard]] double calculateY(double x) const override;

    friend std::ostream& operator<<(std::ostream& os, const ZeroOrderSegment& seg);
    static ZeroOrderSegment readFromStream(std::istream& is);
};

} // namespace miit::approximation
