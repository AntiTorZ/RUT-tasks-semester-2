#include "Class Quadrilateral.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <cstdlib> // Для exit()

// Реализация Point
Point::Point() : x(0), y(0)
{
}

Point::Point(const double x, const double y) : x(x), y(y)
{
}

bool Point::operator==(const Point& other) const
{
	return x == other.x && y == other.y;
}

// Реализация Quadrilateral
double Quadrilateral::CrossProduct(const Point& a, const Point& b, const Point& c) const
{
	// Векторы: ab и ac
	double v1x = b.x - a.x;
	double v1y = b.y - a.y;
	double v2x = c.x - a.x;
	double v2y = c.y - a.y;

	// Векторное произведение (z-компонента)
	return v1x * v2y - v1y * v2x;
}

double Quadrilateral::GetAngle(const Point& A, const Point& B, const Point& C) const
{
	// Векторы BA и BC
	double v1x = A.x - B.x;
	double v1y = A.y - B.y;
	double v2x = C.x - B.x;
	double v2y = C.y - B.y;

	// Скалярное произведение
	double dot = v1x * v2x + v1y * v2y;

	// Длины векторов
	double len1 = sqrt(v1x * v1x + v1y * v1y);
	double len2 = sqrt(v2x * v2x + v2y * v2y);

	if (len1 == 0 || len2 == 0)
	{
		return 0;
	}

	// Косинус угла
	double cosAngle = dot / (len1 * len2);

	// Ограничиваем от -1 до 1
	if (cosAngle > 1) cosAngle = 1;
	if (cosAngle < -1) cosAngle = -1;

	// Возвращаем угол в градусах
	return acos(cosAngle) * 180.0 / M_PI;
}

void Quadrilateral::CheckQuadrilateral(const Point& p1, const Point& p2, const Point& p3, const Point& p4)
{
	// Проверяем, не совпадают ли точки
	if (p1 == p2 || p1 == p3 || p1 == p4 ||
		p2 == p3 || p2 == p4 ||
		p3 == p4)
	{
		cerr << "Ошибка: некоторые вершины совпадают!" << endl;
		exit(1);
	}

	// Проверяем, не лежат ли три точки на одной прямой (коллинарность)
	const double EPS = 1e-10;
	
	double cp1 = CrossProduct(p1, p2, p3);
	double cp2 = CrossProduct(p2, p3, p4);
	double cp3 = CrossProduct(p3, p4, p1);

	if (fabs(cp1) < EPS || fabs(cp2) < EPS || fabs(cp3) < EPS)
	{
		 cerr << "Ошибка: три или более точек лежат на одной прямой!" << endl;
		 exit(1);
	}
}

Quadrilateral::Quadrilateral()
{
	p1 = Point(0, 0);
	p2 = Point(1, 0);
	p3 = Point(1, 1);
	p4 = Point(0, 1);
}

Quadrilateral::Quadrilateral(const Point& p1, const Point& p2, const Point& p3, const Point& p4)
{
	this->p1 = p1;
	this->p2 = p2;
	this->p3 = p3;
	this->p4 = p4;
	CheckQuadrilateral(p1, p2, p3, p4);
}

bool Quadrilateral::IsConvex() const
{
	// Метод пересечения диагоналей:
	// Четырехугольник выпуклый, если его диагонали пересекаются внутри фигуры.
	// Это значит, что концы одной диагонали лежат по разные стороны от прямой, содержащей другую диагональ.

	// Диагональ 1: p1-p3. Проверяем, лежат ли p2 и p4 по разные стороны от этой прямой.
	// Если CrossProduct имеет разные знаки, то точки по разные стороны.
	double cp1 = CrossProduct(p1, p3, p2);
	double cp2 = CrossProduct(p1, p3, p4);
	bool diag1_ok = (cp1 * cp2) < 0;

	// Диагональ 2: p2-p4. Проверяем, лежат ли p1 и p3 по разные стороны от этой прямой.
	double cp3 = CrossProduct(p2, p4, p1);
	double cp4 = CrossProduct(p2, p4, p3);
	bool diag2_ok = (cp3 * cp4) < 0;

	// Если оба условия выполняются, диагонали пересекаются -> фигура выпуклая.
	return diag1_ok && diag2_ok;
}

bool Quadrilateral::CanDescribeCircle() const
{
	// Сначала проверяем, что четырехугольник выпуклый
	if (!IsConvex())
	{
		return false;
	}

	// Вычисляем углы при вершинах
	double angle1 = GetAngle(p4, p1, p2); // угол при p1
	double angle3 = GetAngle(p2, p3, p4); // угол при p3

	// Проверяем сумму противоположных углов
	// Для вписанного четырехугольника: angle1 + angle3 = 180
	const double EPS = 1.0; // допустимая погрешность в градусах

	double sum = angle1 + angle3;

	return (fabs(sum - 180.0) < EPS);
}
