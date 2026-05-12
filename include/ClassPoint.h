#pragma once

#include <iostream>

using namespace std;

/**
* @brief Класс "Точка"
*/
class Point
{
private:
    /**
    * @param x - координата точки по горизонтальной оси (абсцисса)
    */
    double x;

    /**
    * @param y - координата точки по вертикальной оси (ордината)
    */
    double y;

public:
    /** 
    * @brief Базовый конструктор класса
    * @param x - координата по оси x (по умолчанию 0)
    * @param y - координата по оси y (по умолчанию 0)
    */
    Point(const double x = 0, const double y = 0);

    /**
    * @brief Получает значение по оси x
    * @return Значение по оси x
    */
    double getX(void) const;

    /**
    * @brief Получает значение по оси y
    * @return Значение по оси y
    */
    double getY(void) const;

    /**
    * @brief Устанавливает значение по оси x
    * @param x - новое значение
    */
    void setX(const double x);

    /**
    * @brief Устанавливает значение по оси y
    * @param y - новое значение
    */
    void setY(const double y);

    /**
    * @brief Оператор равенства
    * @param other - точка для сравнения
    * @return true если координаты равны
    */
    bool operator == (const Point& other) const;

    /**
    * @brief Оператор неравенства
    * @param other - точка для сравнения
    * @return true если координаты не равны
    */
    bool operator != (const Point& other) const;

    /**
    * @brief Оператор меньше (для сортировки)
    * @param other - точка для сравнения
    * @return true если эта точка меньше по x
    */
    bool operator < (const Point& other) const;

    /**
    * @brief Оператор вывода в поток
    * @param os - поток вывода
    * @param point - точка для вывода
    * @return поток вывода
    */
    friend ostream& operator << (ostream& os, const Point& point);

    /**
    * @brief Оператор ввода из потока
    * @param is - поток ввода
    * @param point - точка для ввода
    * @return поток ввода
    */
    friend istream& operator >> (istream& is, Point& point);
};
