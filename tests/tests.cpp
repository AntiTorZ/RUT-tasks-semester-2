#include <gtest/gtest.h>
#include <sstream>
#include "../include/ClassDeque.h"

/**
* @brief Тест конструкторов
*/
TEST(ClassDeque, TestConstructors)
{
    Deque<int> Zero;
    EXPECT_EQ(Zero.size(), 0);
    EXPECT_TRUE(Zero.empty());

    Deque<int> One{ 1, 2, 3 };
    EXPECT_EQ(One.size(), 3);
    EXPECT_EQ(One[0], 1);
    EXPECT_EQ(One[1], 2);
    EXPECT_EQ(One[2], 3);

    Deque<int> Two(One);
    EXPECT_EQ(Two.size(), 3);
    EXPECT_EQ(Two[0], 1);
    EXPECT_EQ(Two[1], 2);
    EXPECT_EQ(Two[2], 3);

    Deque<int> Original{ 5, 10 };
    Deque<int> Moved(move(Original));
    EXPECT_EQ(Original.size(), 0);
    EXPECT_EQ(Moved.size(), 2);
    EXPECT_EQ(Moved[0], 5);
    EXPECT_EQ(Moved[1], 10);
}

/**
* @brief Тест оператора индекса
*/
TEST(ClassDeque, Index_Operator)
{
    Deque<int> One{ 5, 7, 10, 9 };
    EXPECT_EQ(One[2], 10);
    
    EXPECT_EXIT(One[20], ::testing::ExitedWithCode(1), "Выход за границы дека");
}

/**
* @brief Тест операторов сравнения
*/
TEST(ClassDeque, EQ_Operators)
{
    Deque<int> One{ 1, 2, 3, 4, 5 };
    Deque<int> Two{ 1, 2, 3, 4, 5 };
    Deque<int> Three{ 1, 2, 3, 4 };
    
    EXPECT_TRUE(One == Two);
    EXPECT_TRUE(One != Three);
    EXPECT_FALSE(One == Three);
}

/**
* @brief Тест операторов присваивания
*/
TEST(ClassDeque, Assign_Operators)
{
    Deque<int> One;
    Deque<int> Two{ 1, 2, 3 };
    
    One = Two;
    EXPECT_EQ(One.size(), 3);
    EXPECT_EQ(One[0], 1);
    EXPECT_EQ(One[1], 2);
    EXPECT_EQ(One[2], 3);

    Deque<int> Original{ 5, 10 };
    Deque<int> Target;
    Target = move(Original);
    EXPECT_EQ(Target.size(), 2);
    EXPECT_EQ(Target[0], 5);
    EXPECT_EQ(Target[1], 10);
}

/**
* @brief Тест операторов ввода и вывода
*/
TEST(ClassDeque, IO_Operators)
{
    system("chcp 1251");
    stringstream input("2 10 20");
    Deque<int> One;
    input >> One;

    EXPECT_EQ(One.size(), 2);
    EXPECT_EQ(One[0], 10);
    EXPECT_EQ(One[1], 20);

    stringstream output;
    output << One;
    EXPECT_EQ(output.str(), "{10, 20}");
}

/**
* @brief Тест функций push_back и pop_back
*/
TEST(ClassDeque, Push_Pop_Back)
{
    Deque<int> First;
    
    First.push_back(1);
    First.push_back(2);
    First.push_back(10);
    
    EXPECT_EQ(First.size(), 3);
    EXPECT_EQ(First[0], 1);
    EXPECT_EQ(First[1], 2);
    EXPECT_EQ(First[2], 10);

    First.pop_back();
    EXPECT_EQ(First.size(), 2);
    EXPECT_EQ(First[0], 1);
    EXPECT_EQ(First[1], 2);

    EXPECT_EQ(First.back(), 2);
}

/**
* @brief Тест функций push_front и pop_front
*/
TEST(ClassDeque, Push_Pop_Front)
{
    Deque<int> First;
    
    First.push_front(10);
    First.push_front(2);
    First.push_front(1);
    
    EXPECT_EQ(First.size(), 3);
    EXPECT_EQ(First[0], 1);
    EXPECT_EQ(First[1], 2);
    EXPECT_EQ(First[2], 10);

    First.pop_front();
    EXPECT_EQ(First.size(), 2);
    EXPECT_EQ(First[0], 2);
    EXPECT_EQ(First[1], 10);

    EXPECT_EQ(First.front(), 2);
}

/**
* @brief Тест метода empty
*/
TEST(ClassDeque, Empty_Test)
{
    Deque<int> Empty;
    EXPECT_TRUE(Empty.empty());

    Deque<int> NotEmpty{ 1, 2, 3 };
    EXPECT_FALSE(NotEmpty.empty());

    NotEmpty.pop_back();
    NotEmpty.pop_back();
    NotEmpty.pop_back();
    EXPECT_TRUE(NotEmpty.empty());
}

/**
* @brief Тест комплексной работы с деком
*/
TEST(ClassDeque, Functional)
{
    Deque<int> Deq{ 1, 2, 3 };
    
    Deq.push_back(4);
    Deq.push_front(0);
    
    EXPECT_EQ(Deq.size(), 5);
    EXPECT_EQ(Deq.front(), 0);
    EXPECT_EQ(Deq.back(), 4);
    
    Deq.pop_front();
    EXPECT_EQ(Deq.front(), 1);
    
    Deq.pop_back();
    EXPECT_EQ(Deq.back(), 3);
    
    EXPECT_EQ(Deq.size(), 3);
}
