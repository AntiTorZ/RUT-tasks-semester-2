#include "Class Quadrilateral.h"

/**
* @brief Считывает значение координаты с клавиатуры
* @param prompt - сообщение для пользователя
* @return Значение введенной координаты
*/
const double GetCoordinate(const string& prompt);

/**
* @brief Точка входа в программу
* @return Возвращает 0, если программа выполнена корректно
*/
int main(void)
{
	system("chcp 1251");
	system("CLS");

	cout << "=== Проверка четырехугольника ===" << endl << endl;

	// Ввод координат первой точки
	cout << "--- Вершина 1 ---" << endl;
	const double x1 = GetCoordinate("Введите x1: ");
	const double y1 = GetCoordinate("Введите y1: ");
	Point p1(x1, y1);

	// Ввод координат второй точки
	cout << endl << "--- Вершина 2 ---" << endl;
	const double x2 = GetCoordinate("Введите x2: ");
	const double y2 = GetCoordinate("Введите y2: ");
	Point p2(x2, y2);

	// Ввод координат третьей точки
	cout << endl << "--- Вершина 3 ---" << endl;
	const double x3 = GetCoordinate("Введите x3: ");
	const double y3 = GetCoordinate("Введите y3: ");
	Point p3(x3, y3);

	// Ввод координат четвертой точки
	cout << endl << "--- Вершина 4 ---" << endl;
	const double x4 = GetCoordinate("Введите x4: ");
	const double y4 = GetCoordinate("Введите y4: ");
	Point p4(x4, y4);

	// Создание объекта четырехугольника и вывод результата
	try
	{
		Quadrilateral Q(p1, p2, p3, p4);

		cout << endl << "Результаты:" << endl;
		cout << "Четырехугольник выпуклый: " << (Q.IsConvex() ? "ДА" : "НЕТ") << endl;
		cout << "Можно описать окружность: " << (Q.CanDescribeCircle() ? "ДА" : "НЕТ") << endl;
	}
	catch (...)
	{
		cerr << "Произошла ошибка при создании четырехугольника." << endl;
		return 1;
	}

	return 0;
}

const double GetCoordinate(const string& prompt)
{
	double number = 0;
	cout << prompt;
	cin >> number;
	if (cin.fail())
	{
		cerr << "Ошибка ввода! Введено не число." << endl;
		exit(1);
	}
	return number;
}
