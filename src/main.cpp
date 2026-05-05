#include "../include/ClassDeque.h"

/**
* @brief Нумерация объектов выбора
* @param STR - выбор типа данных string
* @param CHR - выбор типа данных char
* @param DBL - выбор типа данных double
* @param INT - выбор типа данных int
* @param BOOL - выбор типа данных bool
*/
enum MyEnum
{
    STR = 1,
    CHR,
    DBL,
    INT,
    BOOL
};

/**
* @brief Считывает число типа int введённое с клавиатуры
* @return Число типа int
*/
int get_choice();

/**
* @brief Выводит ошибку и завершает работу программы
* @param text - текст, выводимый на экран
*/
void ERROR(const string text);

/**
* @brief Область работы с деком
* @param text - тип данных, участвуюший в работе дека
*/
template <typename Type>
void runDeque(const string text);

/**
* @brief Считывает элемент типа type введённое с клавиатуры
* @return Элемент типа type
*/
template <typename Type>
Type get_element();

/**
* @brief Точка входа в программу
* @return Если программа выполнена корректно - 0, иначе 1
*/
int main()
{
    system("chcp 1251");
    system("CLS");

    cout << "Выберите тип данных хранящихся в деке: " << endl <<
        STR << " - слова" << endl <<
        CHR << " - буквы" << endl <<
        DBL << " - вещественные числа" << endl <<
        INT << " - целые числа" << endl <<
        BOOL << " - булевые числа [0,1]" << endl;
    int choice = get_choice();

    system("CLS");

    switch (choice)
    {
    case STR:
        runDeque<string>("string");
        break;
    case CHR:
        runDeque<char>("char");
        break;
    case DBL:
        runDeque<double>("double");
        break;
    case INT:
        runDeque<int>("int");
        break;
    case BOOL:
        runDeque<bool>("bool");
        break;
    default:
        ERROR("Ошибка выбора");
    }

    return 0;
}

int get_choice()
{
    int number = 0;
    cin >> number;
    if (cin.fail())
    {
        ERROR("Ошибка ввода");
    }
    return number;
}

void ERROR(const string text)
{
    cerr << text;
    exit(1);
}

template <typename Type>
void runDeque(const string text)
{
    Deque<Type> First;
    cin >> First;
    system("CLS");

    cout << "Дек: " << First << endl;
    cout << "Размер дека: " << First.size() << endl;
    cout << "Дек пуст? " << (First.empty() ? "да" : "нет") << endl;

    cout << endl << "Первый элемент: " << First.front() << endl;
    cout << "Последний элемент: " << First.back() << endl;

    cout << endl << "Дек после удаления элемента с конца: ";
    First.pop_back();
    cout << First << endl;
    cout << "Размер дека: " << First.size() << endl;

    cout << endl << "Дек после удаления элемента с начала: ";
    First.pop_front();
    cout << First << endl;
    cout << "Размер дека: " << First.size() << endl;

    cout << endl << "Введите элемент (c типом " << text << "), который будет добавлен в конец дека: ";
    Type element = get_element<Type>();
    First.push_back(element);
    cout << "Дек после вставки элемента в конец: " << First << endl;

    cout << endl << "Введите элемент (c типом " << text << "), который будет добавлен в начало дека: ";
    element = get_element<Type>();
    First.push_front(element);
    cout << "Дек после вставки элемента в начало: " << First << endl;

    cout << endl << "Первый элемент: " << First.front() << endl;
    cout << "Последний элемент: " << First.back() << endl;
}

template <typename Type>
Type get_element()
{
    Type element{};
    cin >> element;
    if (cin.fail())
    {
        ERROR("Ошибка ввода");
    }
    return element;
}
