#pragma once
#include <string>
#include <iostream>
#include <cmath>

using namespace std;

/**
* @brief Структура точки на плоскости
*/
struct Point
{
    /**
    * @param x - абсцисса точки
    */
    double x;

    /**
    * @param y - ордината точки
    */
    double y;

    /**
    * @brief Конструктор точки по умолчанию
    */
    Point();

    /**
    * @brief Конструктор точки с координатами
    * @param x - абсцисса
    * @param y - ордината
    */
    Point(const double x, const double y);

    /**
    * @brief Оператор сравнения на равенство
    */
    bool operator==(const Point& other) const;
};

/**
* @brief Класс четырехугольника
*/
class Quadrilateral
{
private:
    /**
    * @param p1 - первая вершина
    */
    Point p1;

    /**
    * @param p2 - вторая вершина
    */
    Point p2;

    /**
    * @param p3 - третья вершина
    */
    Point p3;

    /**
    * @param p4 - четвертая вершина
    */
    Point p4;

    /**
    * @brief Вычисляет векторное произведение векторов (AB x AC)
    * @param a - начальная точка
    * @param b - конец первого вектора
    * @param c - конец второго вектора
    * @return Знак векторного произведения (z-компонента)
    */
    double CrossProduct(const Point& a, const Point& b, const Point& c) const;

    /**
    * @brief Вычисляет угол при вершине B между векторами BA и BC
    * @param A - первая точка
    * @param B - вершина угла
    * @param C - третья точка
    * @return Угол в градусах
    */
    double GetAngle(const Point& A, const Point& B, const Point& C) const;

    /**
    * @brief Функция проверки корректности задания четырехугольника
    * @param p1 - первая вершина
    * @param p2 - вторая вершина
    * @param p3 - третья вершина
    * @param p4 - четвертая вершина
    */
    void CheckQuadrilateral(const Point& p1, const Point& p2, const Point& p3, const Point& p4);

public:

    /**
    * @brief Конструктор по умолчанию (квадрат 0,0 - 1,0 - 1,1 - 0,1)
    */
    Quadrilateral();

    /**
    * @brief Конструктор, задаёт четыре вершины четырехугольника
    * @param p1 - первая вершина
    * @param p2 - вторая вершина
    * @param p3 - третья вершина
    * @param p4 - четвертая вершина
    */
    Quadrilateral(const Point& p1, const Point& p2, const Point& p3, const Point& p4);

    /**
    * @brief Проверяет является ли четырехугольник выпуклым (Метод диагоналей)
    * @return true если четырехугольник выпуклый, false иначе
    */
    bool IsConvex() const;

    /**
    * @brief Проверяет можно ли описать окружность вокруг четырехугольника
    * @return true если можно описать окружность, false иначе
    */
    bool CanDescribeCircle() const;
};
