#pragma once

#include "ClassPiecewiseLinear.h"
#include "ClassPoint.h"

/**
* @brief Класс "Отрезок" для экстраполятора нулевого порядка
*/
class Segment
{
private:
    /**
    * @param leftPoint - левая точка отрезка
    */
    Point leftPoint;

    /**
    * @param rightPoint - правая точка отрезка
    *                   (x = x правой точки, y = y левой точки)
    */
    Point rightPoint;

public:
    /**
    * @brief Конструктор отрезка по двум точкам
    * @param left - левая точка
    * @param right - правая точка (используется только её x)
    */
    Segment(const Point& left, const Point& right);

    /**
    * @brief Получает левую точку
    * @return Левая точка
    */
    Point getLeftPoint() const;

    /**
    * @brief Получает правую точку
    * @return Правая точка
    */
    Point getRightPoint() const;

    /**
    * @brief Проверяет, принадлежит ли x отрезку
    * @param x - проверяемая абсцисса
    * @return true если x в пределах отрезка
    */
    bool contains(const double x) const;

    /**
    * @brief Вычисляет ординату на отрезке
    * @param x - абсцисса
    * @return Ордината
    */
    double calculateY(const double x) const;

    /**
    * @brief Оператор сдвига влево
    * @param value - величина сдвига
    * @return Новый сдвинутый отрезок
    */
    Segment operator << (const double value) const;

    /**
    * @brief Статический метод чтения отрезка из потока
    * @param is - поток ввода
    * @return Прочитанный отрезок
    */
    static Segment read(istream& is);
};

/**
* @brief Класс "Экстраполятор нулевого порядка"
*/
class ZeroOrderExtrapolator : public PiecewiseLinearApproximation
{
private:
    /**
    * @param segments - коллекция отрезков
    */
    vector<Segment> segments;

    /**
    * @brief Строит отрезки из точек
    */
    void buildSegments();

public:
    /**
    * @brief Конструктор с вектором точек
    * @param points - вектор точек
    */
    ZeroOrderExtrapolator(const vector<Point>& points);

    /**
    * @brief Конструктор со списком инициализации
    * @param points - список точек
    */
    ZeroOrderExtrapolator(const initializer_list<Point> points);

    /**
    * @brief Метод расчёта ординаты по заданной абсциссе
    * @param x - абсцисса
    * @return Вычисленная ордината (кусочно-постоянная функция)
    */
    double calculateY(const double x) const override;

    /**
    * @brief Оператор сдвига влево для всех отрезков
    * @param value - величина сдвига
    * @return Сдвинутый экстраполятор
    */
    ZeroOrderExtrapolator operator << (const double value) const;

    /**
    * @brief Статический метод чтения отрезка
    * @param is - поток ввода
    * @return Прочитанный отрезок
    */
    static Segment readSegment(istream& is);
};
