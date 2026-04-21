#pragma once
#include "PiecewiseLinearApproximation.h"
#include <iosfwd>

namespace miit::approximation {

/**
 * @brief Класс отрезка для экстраполятора нулевого порядка
 * 
 * Строится по двум точкам. Левая точка задана полностью.
 * У правой точки абсцисса берётся из исходной правой точки,
 * а ордината копируется из левой точки (кусочно-постоянный сигнал).
 */
class ZeroOrderSegment : public PiecewiseLinearApproximation {
public:
    /**
     * @brief Конструктор от вектора точек
     * @param pts Вектор точек
     */
    using PiecewiseLinearApproximation::PiecewiseLinearApproximation;

    /**
     * @brief Расчёт ординаты по заданной абсциссе (экстраполятор нулевого порядка)
     * @param x Абсцисса
     * @return Ордината: значение левой точки интервала [x_i, x_{i+1})
     */
    [[nodiscard]] double calculateY(double x) const override;

    /** @brief Оператор вывода в поток */
    friend std::ostream& operator<<(std::ostream& os, const ZeroOrderSegment& seg);
    
    /**
     * @brief Статический метод чтения отрезка из потока
     * @param is Входной поток
     * @return Созданный объект ZeroOrderSegment
     */
    static ZeroOrderSegment readFromStream(std::istream& is);
};

} // namespace miit::approximation
