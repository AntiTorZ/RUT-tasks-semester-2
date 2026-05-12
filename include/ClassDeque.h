#pragma once
#include <iostream>
#include <initializer_list>

using namespace std;

/**
* @brief Класс Дек (двусторонняя очередь)
*/
template<typename Type>
class Deque
{
private:
    /**
    * @param data - элементы дека
    */
    Type* data;

    /**
    * @param count - количество элементов в деке
    */
    size_t count;

    /**
    * @brief Выводит ошибку и завершает работу программы
    * @param text - текст, выводимый на экран
    */
    void ERROR(const string text) const
    {
        cerr << text;
        exit(1);
    }

public:
    /**
    * @brief Конструктор класса по-умолчанию, задаёт пустой дек
    */
    Deque() : data(nullptr), count(0) {}

    /**
    * @brief Конструктор класса, задаёт дек по списку инициализации
    * @param other - список инициализации
    */
    Deque(const initializer_list<Type> other) : data(nullptr), count(other.size())
    {
        if (count > 0)
        {
            data = new Type[count];
            size_t i = 0;
            for (const auto& value : other)
            {
                data[i++] = value;
            }
        }
    }

    /**
    * @brief Конструктор копирования
    * @param other - дек для копирования
    */
    Deque(const Deque& other) : data(nullptr), count(other.count)
    {
        if (count > 0)
        {
            data = new Type[count];
            for (size_t i = 0; i < count; i++)
            {
                data[i] = other.data[i];
            }
        }
    }

    /**
    * @brief Конструктор перемещения
    * @param other - дек для перемещения
    */
    Deque(Deque&& other) noexcept : data(other.data), count(other.count)
    {
        other.data = nullptr;
        other.count = 0;
    }

    /**
    * @brief Добавление элемента в конец дека
    * @param object - объект добавляемый в дек
    */
    void push_back(const Type& object)
    {
        Type* newData = new Type[count + 1];
        
        for (size_t i = 0; i < count; i++)
        {
            newData[i] = data[i];
        }
        
        newData[count] = object;
        
        delete[] data;
        data = newData;
        count++;
    }

    /**
    * @brief Удаление элемента из конца дека
    */
    void pop_back()
    {
        if (count > 0)
        {
            Type* newData = new Type[count - 1];
            
            for (size_t i = 0; i < count - 1; i++)
            {
                newData[i] = data[i];
            }
            
            delete[] data;
            data = newData;
            count--;
        }
        else
        {
            ERROR("Дек пуст, удаление не выполнено\n");
        }
    }

    /**
    * @brief Добавление элемента в начало дека
    * @param object - объект добавляемый в дек
    */
    void push_front(const Type& object)
    {
        Type* newData = new Type[count + 1];
        
        newData[0] = object;
        for (size_t i = 0; i < count; i++)
        {
            newData[i + 1] = data[i];
        }
        
        delete[] data;
        data = newData;
        count++;
    }

    /**
    * @brief Удаление элемента из начала дека
    */
    void pop_front()
    {
        if (count > 0)
        {
            Type* newData = new Type[count - 1];
            
            for (size_t i = 0; i < count - 1; i++)
            {
                newData[i] = data[i + 1];
            }
            
            delete[] data;
            data = newData;
            count--;
        }
        else
        {
            ERROR("Дек пуст, удаление не выполнено\n");
        }
    }

    /**
    * @brief Получение последнего элемента дека
    * @return Последний элемент
    */
    Type& back()
    {
        if (count > 0)
        {
            return data[count - 1];
        }
        ERROR("Дек пуст\n");
    }

    /**
    * @brief Получение последнего элемента дека (константная версия)
    * @return Последний элемент
    */
    const Type& back() const
    {
        if (count > 0)
        {
            return data[count - 1];
        }
        ERROR("Дек пуст\n");
    }

    /**
    * @brief Получение первого элемента дека
    * @return Первый элемент
    */
    Type& front()
    {
        if (count > 0)
        {
            return data[0];
        }
        ERROR("Дек пуст\n");
    }

    /**
    * @brief Получение первого элемента дека (константная версия)
    * @return Первый элемент
    */
    const Type& front() const
    {
        if (count > 0)
        {
            return data[0];
        }
        ERROR("Дек пуст\n");
    }

    /**
    * @brief Проверка дека на пустоту
    * @return true если дек пуст, иначе false
    */
    bool empty() const
    {
        return count == 0;
    }

    /**
    * @brief Получение размера дека
    * @return Размер дека
    */
    size_t size() const
    {
        return count;
    }

    /**
    * @brief Оператор присваивания (копирование)
    * @param other - дек для копирования
    * @return Ссылка на текущий дек
    */
    Deque& operator=(const Deque& other)
    {
        if (this != &other)
        {
            delete[] data;
            
            count = other.count;
            
            if (count > 0)
            {
                data = new Type[count];
                for (size_t i = 0; i < count; i++)
                {
                    data[i] = other.data[i];
                }
            }
            else
            {
                data = nullptr;
            }
        }
        return *this;
    }

    /**
    * @brief Оператор присваивания (перемещение)
    * @param other - дек для перемещения
    * @return Ссылка на текущий дек
    */
    Deque& operator=(Deque&& other) noexcept
    {
        if (this != &other)
        {
            delete[] data;
            
            data = other.data;
            count = other.count;
            
            other.data = nullptr;
            other.count = 0;
        }
        return *this;
    }

    /**
    * @brief Оператор доступа по индексу
    * @param index - индекс элемента
    * @return Ссылка на элемент
    */
    Type& operator[](const size_t index)
    {
        if (index >= count)
        {
            ERROR("Выход за границы дека\n");
        }
        return data[index];
    }

    /**
    * @brief Оператор доступа по индексу (константная версия)
    * @param index - индекс элемента
    * @return Ссылка на элемент
    */
    const Type& operator[](const size_t index) const
    {
        if (index >= count)
        {
            ERROR("Выход за границы дека\n");
        }
        return data[index];
    }

    /**
    * @brief Оператор равенства
    * @param other - дек для сравнения
    * @return true если деки равны, иначе false
    */
    bool operator==(const Deque& other) const
    {
        if (count != other.count)
            return false;
        
        for (size_t i = 0; i < count; i++)
        {
            if (data[i] != other.data[i])
                return false;
        }
        
        return true;
    }

    /**
    * @brief Оператор неравенства
    * @param other - дек для сравнения
    * @return true если деки не равны, иначе false
    */
    bool operator!=(const Deque& other) const
    {
        return !(*this == other);
    }

    /**
    * @brief Оператор вывода в поток
    * @param os - поток вывода
    * @param other - дек
    * @return Поток вывода
    */
    friend ostream& operator<<(ostream& os, const Deque& other)
    {
        os << "{";
        for (size_t i = 0; i < other.count; i++)
        {
            os << other.data[i];
            if (i < other.count - 1)
            {
                os << ", ";
            }
        }
        os << "}";
        return os;
    }

    /**
    * @brief Оператор ввода из потока
    * @param is - поток ввода
    * @param deque - дек
    * @return Поток ввода
    */
    friend istream& operator>>(istream& is, Deque& deque)
    {
        size_t count = 0;
        cout << "Введите количество элементов в деке: ";
        is >> count;

        if (is.fail() || count < 0)
        {
            deque.ERROR("Ошибка ввода\n");
        }

        delete[] deque.data;
        deque.data = nullptr;
        deque.count = count;

        if (count > 0)
        {
            deque.data = new Type[count];

            for (size_t i = 0; i < deque.count; ++i)
            {
                cout << "Введите " << i + 1 << " элемент дека: ";
                is >> deque.data[i];

                if (is.fail())
                {
                    deque.ERROR("Ошибка ввода\n");
                }
            }
        }

        return is;
    }

    /**
    * @brief Деструктор класса
    */
    ~Deque()
    {
        delete[] data;
    }
};
