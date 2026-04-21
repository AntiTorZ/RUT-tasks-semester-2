#pragma once
#include <iosfwd>

namespace miit::approximation {

/**
 * @brief Класс "Точка" на плоскости
 */
class Point {
private:
    double x_;  ///< Абсцисса точки
    double y_;  ///< Ордината точки

public:
    /**
     * @brief Конструктор точки
     * @param x Абсцисса (по умолчанию 0.0)
     * @param y Ордината (по умолчанию 0.0)
     */
    Point(double x = 0.0, double y = 0.0);

    /** @return Абсцисса точки */
    [[nodiscard]] double getX() const;
    /** @return Ордината точки */
    [[nodiscard]] double getY() const;

    /** @brief Оператор равенства */
    bool operator==(const Point& other) const;
    /** @brief Оператор неравенства */
    bool operator!=(const Point& other) const;
    /** @brief Оператор меньше (для сортировки по абсциссе) */
    bool operator<(const Point& other) const;
    /** @brief Оператор больше */
    bool operator>(const Point& other) const;
    /** @brief Оператор меньше или равно */
    bool operator<=(const Point& other) const;
    /** @brief Оператор больше или равно */
    bool operator>=(const Point& other) const;

    /** @brief Оператор вывода в поток */
    friend std::ostream& operator<<(std::ostream& os, const Point& p);
    /** @brief Оператор ввода из потока */
    friend std::istream& operator>>(std::istream& is, Point& p);
};

} // namespace miit::approximation
