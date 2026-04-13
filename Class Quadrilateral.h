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

	/**
	* @brief Оператор сравнения на неравенство
	*/
	bool operator!=(const Point& other) const;
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
	* @brief Вычисляет векторное произведение векторов (p1p2 × p1p3)
	* @param p1 - начальная точка первого вектора
	* @param p2 - конечная точка первого вектора
	* @param p3 - конечная точка второго вектора
	* @return Значение векторного произведения
	*/
	double CrossProduct(const Point& p1, const Point& p2, const Point& p3) const;

	/**
	* @brief Вычисляет угол при вершине p2 между векторами p2p1 и p2p3
	* @param p1 - первая точка
	* @param p2 - вершина угла
	* @param p3 - третья точка
	* @return Угол в градусах
	*/
	double GetAngle(const Point& p1, const Point& p2, const Point& p3) const;

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
	* @brief Конструктор, задаёт вершины координатами
	* @param x1, y1 - координаты первой вершины
	* @param x2, y2 - координаты второй вершины
	* @param x3, y3 - координаты третьей вершины
	* @param x4, y4 - координаты четвертой вершины
	*/
	Quadrilateral(const double x1, const double y1, const double x2, const double y2,
		const double x3, const double y3, const double x4, const double y4);

	/**
	* @brief Проверяет является ли четырехугольник выпуклым
	* @return true если четырехугольник выпуклый, false иначе
	*/
	bool IsConvex() const;

	/**
	* @brief Проверяет можно ли описать окружность вокруг четырехугольника
	* @return true если можно описать окружность, false иначе
	*/
	bool CanDescribeCircle() const;

	/**
	* @brief Выводит информацию о четырехугольнике
	*/
	void PrintInfo() const;
};
