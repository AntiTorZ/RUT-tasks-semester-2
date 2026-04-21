#pragma once
#include "Point.h"
#include <vector>
#include <initializer_list>
#include <iosfwd>

namespace miit::approximation {

/**
 * @brief Абстрактный базовый класс кусочно-линейной аппроксимации функции
 */
class PiecewiseLinearApproximation {
protected:
    std::vector<Point> points_;  ///< Коллекция опорных точек

    /** @brief Сортировка точек по абсциссе */
    void sortPoints();

public:
    /**
     * @brief Конструктор от вектора точек
     * @param pts Вектор точек
     */
    explicit PiecewiseLinearApproximation(const std::vector<Point>& pts);
    
    /**
     * @brief Конструктор от списка инициализации
     * @param pts Список точек
     */
    PiecewiseLinearApproximation(std::initializer_list<Point> pts);
    
    /** @brief Виртуальный деструктор */
    virtual ~PiecewiseLinearApproximation() = default;

    /**
     * @brief Добавление точки в коллекцию
     * @param p Добавляемая точка
     */
    void addPoint(const Point& p);

    /**
     * @brief Расчёт ординаты по заданной абсциссе (чисто виртуальный метод)
     * @param x Абсцисса
     * @return Ордината функции в точке x
     */
    [[nodiscard]] virtual double calculateY(double x) const = 0;

    /**
     * @brief Статический метод чтения точек из потока
     * @param is Входной поток
     * @return Вектор прочитанных точек
     */
    static std::vector<Point> readPointsFromStream(std::istream& is);

    /** @return Константная ссылка на коллекцию точек */
    [[nodiscard]] const std::vector<Point>& getPoints() const;
};

} // namespace miit::approximation
