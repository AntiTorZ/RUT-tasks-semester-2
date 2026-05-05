#include "Class Quadrilateral.h"
#define _USE_MATH_DEFINES
#include <math.h>

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

bool Point::operator!=(const Point& other) const
{
	return !(*this == other);
}

double Quadrilateral::CrossProduct(const Point& p1, const Point& p2, const Point& p3) const
{
	// Векторы: p1p2 и p1p3
	double v1x = p2.x - p1.x;
	double v1y = p2.y - p1.y;
	double v2x = p3.x - p1.x;
	double v2y = p3.y - p1.y;

	// Векторное произведение
	return v1x * v2y - v1y * v2x;
}

double Quadrilateral::GetAngle(const Point& p1, const Point& p2, const Point& p3) const
{
	// Векторы p2p1 и p2p3
	double v1x = p1.x - p2.x;
	double v1y = p1.y - p2.y;
	double v2x = p3.x - p2.x;
	double v2y = p3.y - p2.y;

	double dot = v1x * v2x + v1y * v2y;

	double len1 = sqrt(v1x * v1x + v1y * v1y);
	double len2 = sqrt(v2x * v2x + v2y * v2y);

	if (len1 == 0 || len2 == 0)
	{
		return 0;
	}

	double cosAngle = dot / (len1 * len2);

	if (cosAngle > 1) cosAngle = 1;
	if (cosAngle < -1) cosAngle = -1;

	return acos(cosAngle) * 180.0 / M_PI;
}

void Quadrilateral::CheckQuadrilateral(const Point& p1, const Point& p2, const Point& p3, const Point& p4)
{
	if (p1 == p2 || p1 == p3 || p1 == p4 ||
		p2 == p3 || p2 == p4 ||
		p3 == p4)
	{
		cerr << "Ошибка: некоторые вершины совпадают" << endl;
		exit(1);
	}

	double cp1 = CrossProduct(p1, p2, p3);
	double cp2 = CrossProduct(p2, p3, p4);
	double cp3 = CrossProduct(p3, p4, p1);
	double cp4 = CrossProduct(p4, p1, p2);

	const double EPS = 1e-10;

	if (fabs(cp1) < EPS || fabs(cp2) < EPS || fabs(cp3) < EPS || fabs(cp4) < EPS)
	{
		cerr << "Ошибка: три или более точки лежат на одной прямой" << endl;
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

Quadrilateral::Quadrilateral(const double x1, const double y1, const double x2, const double y2,
	const double x3, const double y3, const double x4, const double y4)
{
	p1 = Point(x1, y1);
	p2 = Point(x2, y2);
	p3 = Point(x3, y3);
	p4 = Point(x4, y4);
	CheckQuadrilateral(p1, p2, p3, p4);
}

bool Quadrilateral::IsConvex() const
{
	double cp1 = CrossProduct(p1, p2, p3);
	double cp2 = CrossProduct(p2, p3, p4);
	double cp3 = CrossProduct(p3, p4, p1);
	double cp4 = CrossProduct(p4, p1, p2);

	bool allPositive = (cp1 > 0) && (cp2 > 0) && (cp3 > 0) && (cp4 > 0);
	bool allNegative = (cp1 < 0) && (cp2 < 0) && (cp3 < 0) && (cp4 < 0);

	return allPositive || allNegative;
}

bool Quadrilateral::CanDescribeCircle() const
{
	if (!IsConvex())
	{
		return false;
	}

	double angle1 = GetAngle(p4, p1, p2); // угол при p1
	double angle2 = GetAngle(p1, p2, p3); // угол при p2
	double angle3 = GetAngle(p2, p3, p4); // угол при p3
	double angle4 = GetAngle(p3, p4, p1); // угол при p4

	const double EPS = 1.0; // допустимая погрешность в градусах

	double sum1 = angle1 + angle3;
	double sum2 = angle2 + angle4;

	return (fabs(sum1 - 180.0) < EPS) && (fabs(sum2 - 180.0) < EPS);
}

void Quadrilateral::PrintInfo() const
{
	cout << "Четырехугольник с вершинами:" << endl;
	cout << "P1(" << p1.x << ", " << p1.y << ")" << endl;
	cout << "P2(" << p2.x << ", " << p2.y << ")" << endl;
	cout << "P3(" << p3.x << ", " << p3.y << ")" << endl;
	cout << "P4(" << p4.x << ", " << p4.y << ")" << endl;
	cout << endl;

	cout << "Выпуклый: " << (IsConvex() ? "ДА" : "НЕТ") << endl;
	cout << "Можно описать окружность: " << (CanDescribeCircle() ? "ДА" : "НЕТ") << endl;

	if (IsConvex())
	{
		double angle1 = GetAngle(p4, p1, p2);
		double angle3 = GetAngle(p2, p3, p4);
		cout << endl << "Углы при противоположных вершинах:" << endl;
		cout << "  При P1: " << angle1 << "°" << endl;
		cout << "  При P3: " << angle3 << "°" << endl;
		cout << "  Сумма: " << (angle1 + angle3) << "°" << endl;
	}
}
