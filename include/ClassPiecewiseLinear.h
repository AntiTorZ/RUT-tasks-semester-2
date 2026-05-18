#pragma once

#include <vector>
#include <initializer_list>
#include <iostream>
#include "ClassPoint.h"

using namespace std;

/**
* @brief Абстрактный базовый класс "Кусочно-линейная аппроксимация функции"
*/
class PiecewiseLinearApproximation
{
protected:
    /**
    * @param points - коллекция точек, задающих функцию
    */
    vector<Point> points;

public:
    /**
    * @brief Конструктор с вектором точек
    * @param points - вектор точек
    */
    PiecewiseLinearApproximation(vector<Point>& points);

    /**
    * @brief Конструктор со списком инициализации
    * @param points - список точек
    */
    PiecewiseLinearApproximation(initializer_list<Point> points);

    /**
    * @brief Виртуальный деструктор
    */
    virtual ~PiecewiseLinearApproximation() = default;

    /**
    * @brief Добавляет точку в коллекцию
    * @param point - добавляемая точка
    */
    void addPoint(const Point& point);

    /**
    * @brief Получает коллекцию точек
    * @return Вектор точек
    */
    vector<Point> getPoints() const;

    /**
    * @brief Виртуальный метод расчёта ординаты по заданной абсциссе
    * @param x - абсцисса
    * @return Вычисленная ордината
    */
    virtual double calculateY(const double x) const = 0;

    /**
    * @brief Статический метод чтения точек из потока
    * @param is - поток ввода
    * @return Вектор прочитанных точек
    */
    static vector<Point> readPoints(istream& is);
};
