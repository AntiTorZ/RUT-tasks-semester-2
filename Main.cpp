#include "Class Quadrilateral.h"

/**
* @brief Считывает значение введённое с клавиатуры
* @return Значение введённое с клавиатуры, если оно считано правильно
*/
const double GetDouble(const string& prompt);

/**
* @brief Точка входа в программу
* @return Возвращает 0, если программа выполнена корректно
*/
int main(void)
{
	system("chcp 1251");
	system("CLS");

	cout << "=== Проверка четырехугольников ===" << endl << endl;

	// Тест 1: Квадрат (выпуклый, можно описать окружность)
	cout << "--- Тест 1: Квадрат ---" << endl;
	Quadrilateral q1(0, 0, 4, 0, 4, 4, 0, 4);
	q1.PrintInfo();
	cout << endl;

	// Тест 2: Прямоугольник (выпуклый, можно описать окружность)
	cout << "--- Тест 2: Прямоугольник ---" << endl;
	Quadrilateral q2(0, 0, 6, 0, 6, 3, 0, 3);
	q2.PrintInfo();
	cout << endl;

	// Тест 3: Произвольный выпуклый четырехугольник
	cout << "--- Тест 3: Произвольный выпуклый ---" << endl;
	Quadrilateral q3(0, 0, 5, 1, 4, 4, 1, 3);
	q3.PrintInfo();
	cout << endl;

	// Тест 4: Равнобедренная трапеция (можно описать окружность)
	cout << "--- Тест 4: Равнобедренная трапеция ---" << endl;
	Quadrilateral q4(0, 0, 6, 0, 4, 3, 2, 3);
	q4.PrintInfo();
	cout << endl;

	// Тест 5: Невыпуклый четырехугольник
	cout << "--- Тест 5: Невыпуклый ---" << endl;
	Quadrilateral q5(0, 0, 4, 0, 2, 1, 2, 4);
	q5.PrintInfo();
	cout << endl;

	// Ввод своих координат
	cout << "=== Ввод своих координат ===" << endl;
	
	double x1 = GetDouble("Введите x1: ");
	double y1 = GetDouble("Введите y1: ");
	double x2 = GetDouble("Введите x2: ");
	double y2 = GetDouble("Введите y2: ");
	double x3 = GetDouble("Введите x3: ");
	double y3 = GetDouble("Введите y3: ");
	double x4 = GetDouble("Введите x4: ");
	double y4 = GetDouble("Введите y4: ");

	try
	{
		Quadrilateral q(x1, y1, x2, y2, x3, y3, x4, y4);
		cout << endl;
		q.PrintInfo();
	}
	catch (...)
	{
		cerr << "Ошибка создания четырехугольника!" << endl;
	}

	return 0;
}

const double GetDouble(const string& prompt)
{
	double number = 0;
	cout << prompt;
	cin >> number;
	if (cin.fail())
	{
		cerr << "Ошибка ввода!" << endl;
		exit(1);
	}
	return number;
}
