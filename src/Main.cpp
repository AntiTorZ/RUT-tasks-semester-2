#include <iostream>
#include <vector>
#include <limits>
#include "../include/ZeroOrderSegment.h"

using namespace miit::approximation;

int main() {
    try {
        std::cout << "Экстраполятор нулевого порядка\n\n";

        std::cout << "[1] Создание через initializer_list:\n";
        ZeroOrderSegment zoh1({ {1.0, 2.0}, {3.0, 4.0}, {5.0, 1.0}, {7.0, 3.0} });
        std::cout << zoh1 << "\n";

        std::vector<double> testX = {0.5, 1.0, 2.0, 3.0, 4.5, 6.0, 7.0, 8.0};
        std::cout << "Расчёт ординат:\n";
        for (double x : testX) {
            std::cout << "  y(" << x << ") = " << zoh1.calculateY(x) << "\n";
        }

        std::cout << "\n[2] Добавление точки {4.0, 5.0}:\n";
        zoh1.addPoint({4.0, 5.0});
        std::cout << zoh1;
        std::cout << "  y(4.5) после добавления = " << zoh1.calculateY(4.5) << "\n";

        // Интерактивный ввод (опционально)
        std::cout << "\n[3] Ввод из потока (нажмите Enter для пропуска):\n";
        std::cout << "Введите 'y' для ручного ввода: ";
        std::string choice;
        std::cin >> choice;
        if (choice == "y" || choice == "Y") {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            ZeroOrderSegment zoh2 = ZeroOrderSegment::readFromStream(std::cin);
            std::cout << "\nСозданный объект:\n" << zoh2;
        }

        std::cout << "\n[4] Полиморфизм (базовый указатель):\n";
        std::vector<PiecewiseLinearApproximation*> vec;
        vec.push_back(new ZeroOrderSegment({{0, 1}, {2, 3}, {4, 2}}));
        vec.push_back(new ZeroOrderSegment({{1, 5}, {3, 1}, {5, 4}}));
        
        for (const auto* obj : vec) {
            std::cout << "  x=2.5 -> y=" << obj->calculateY(2.5) << "\n";
            delete obj;
        }

        std::cout << "\n=== Программа завершена ===\n";
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << "\n";
        return 1;
    }
}
