#include <iostream>
#include <vector>
#include "../include/ClassZeroOrderExtrapolator.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");

    cout << "Тестирование Экстраполятора нулевого порядка" << endl;

    vector<Point> pts = {
        Point(0, 10),
        Point(2, 20),
        Point(4, 5),
        Point(6, 15)
    };

    ZeroOrderExtrapolator approx(pts);

    cout << "\nИсходные точки:" << endl;
    for (const auto& p : approx.getPoints()) {
        cout << p << " ";
    }
    cout << endl;

    double testX[] = {0.5, 1.5, 3.0, 5.5};
    cout << "\nПроверка значений функции (кусочно-постоянная):" << endl;
    for (double x : testX) {
        try {
            double y = approx.calculateY(x);
            cout << "f(" << x << ") = " << y << endl;
        } catch (const exception& e) {
            cout << "Ошибка при x=" << x << ": " << e.what() << endl;
        }
    }

    cout << "\nСдвиг влево на 1.0" << endl;
    ZeroOrderExtrapolator shifted = approx << 1.0;
    
    cout << "Сдвинутые точки:" << endl;
    for (const auto& p : shifted.getPoints()) {
        cout << p << " ";
    }
    cout << endl;

    cout << "f(0.5) после сдвига = " << shifted.calculateY(0.5) << " (ожидается 10)" << endl;

    cout << "\n--- Тест чтения отрезка ---" << endl;
    cout << "Введите координаты для отрезка (x1 y1 x2 y2): ";
    Segment s = Segment::read(cin);
    cout << "Создан отрезок: Left" << s.getLeftPoint() << ", Right" << s.getRightPoint() << endl;
    cout << "Значение в середине (x=2): " << s.calculateY(2.0) << endl;

    return 0;
}
