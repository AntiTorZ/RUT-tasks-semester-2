#define _USE_MATH_DEFINES
#include <gtest/gtest.h>
#include <sstream>
#include <cmath>
#include <limits>

#include "../include/Point.h"
#include "../include/ZeroOrderSegment.h"

using namespace miit::approximation;

// ============================================================================
// Тесты для класса Point
// ============================================================================

/** @brief Тест конструктора и геттеров точки */
TEST(PointTest, ConstructorAndGetters) {
    Point p(3.14, 2.71);
    EXPECT_DOUBLE_EQ(p.getX(), 3.14);
    EXPECT_DOUBLE_EQ(p.getY(), 2.71);
    
    Point defaultPoint;
    EXPECT_DOUBLE_EQ(defaultPoint.getX(), 0.0);
    EXPECT_DOUBLE_EQ(defaultPoint.getY(), 0.0);
}

/** @brief Тест операторов сравнения точек */
TEST(PointTest, ComparisonOperators) {
    Point p1(1.0, 2.0);
    Point p2(1.0, 2.0);
    Point p3(2.0, 1.0);
    Point p4(1.0, 3.0);
    
    EXPECT_TRUE(p1 == p2);
    EXPECT_FALSE(p1 != p2);
    
    EXPECT_TRUE(p1 < p3);   // 1.0 < 2.0 по абсциссе
    EXPECT_FALSE(p1 > p3);
    EXPECT_TRUE(p1 <= p2);
    EXPECT_TRUE(p1 >= p2);
    
    EXPECT_TRUE(p1 < p4);   // одинаковые x, но оператор < сравнивает только x
}

/** @brief Тест операторов ввода/вывода для точки */
TEST(PointTest, IOOperators) {
    Point original(12.34, 56.78);
    
    // Тест вывода
    std::ostringstream out;
    out << original;
    EXPECT_EQ(out.str(), "(12.34, 56.78)");
    
    // Тест ввода
    std::istringstream in("99.99 -11.11");
    Point parsed;
    in >> parsed;
    
    EXPECT_DOUBLE_EQ(parsed.getX(), 99.99);
    EXPECT_DOUBLE_EQ(parsed.getY(), -11.11);
}

// ============================================================================
// Тесты для класса ZeroOrderSegment
// ============================================================================

/** @brief Тест создания отрезка через инициализатор */
TEST(ZeroOrderSegmentTest, ConstructionFromInitializerList) {
    ZeroOrderSegment seg({{0.0, 1.0}, {2.0, 3.0}, {4.0, 2.0}});
    
    const auto& points = seg.getPoints();
    ASSERT_EQ(points.size(), 3);
    
    EXPECT_DOUBLE_EQ(points[0].getX(), 0.0);
    EXPECT_DOUBLE_EQ(points[1].getX(), 2.0);
    EXPECT_DOUBLE_EQ(points[2].getX(), 4.0);
}

/** @brief Тест создания отрезка через вектор */
TEST(ZeroOrderSegmentTest, ConstructionFromVector) {
    std::vector<Point> pts = {{5.0, 10.0}, {1.0, 20.0}, {3.0, 15.0}};
    ZeroOrderSegment seg(pts);
    
    // Точки должны быть отсортированы по абсциссе
    const auto& points = seg.getPoints();
    EXPECT_DOUBLE_EQ(points[0].getX(), 1.0);
    EXPECT_DOUBLE_EQ(points[1].getX(), 3.0);
    EXPECT_DOUBLE_EQ(points[2].getX(), 5.0);
}

/** @brief Тест добавления точки */
TEST(ZeroOrderSegmentTest, AddPoint) {
    ZeroOrderSegment seg({{0.0, 1.0}, {4.0, 2.0}});
    seg.addPoint({2.0, 5.0});
    
    const auto& points = seg.getPoints();
    ASSERT_EQ(points.size(), 3);
    EXPECT_DOUBLE_EQ(points[1].getX(), 2.0);  // новая точка в середине
}

/** @brief Тест логики экстраполятора нулевого порядка */
TEST(ZeroOrderSegmentTest, ZeroOrderLogic) {
    // Точки: (0,1), (2,3), (4,2)
    // Интервалы: [0,2) -> y=1; [2,4) -> y=3; [4,∞) -> y=2
    ZeroOrderSegment seg({{0.0, 1.0}, {2.0, 3.0}, {4.0, 2.0}});
    
    // Экстраполяция слева
    EXPECT_DOUBLE_EQ(seg.calculateY(-1.0), 1.0);
    
    // Интервал [0, 2): должно возвращать y левой точки = 1.0
    EXPECT_DOUBLE_EQ(seg.calculateY(0.0), 1.0);
    EXPECT_DOUBLE_EQ(seg.calculateY(1.0), 1.0);
    EXPECT_DOUBLE_EQ(seg.calculateY(1.999), 1.0);
    
    // Интервал [2, 4): должно возвращать y левой точки = 3.0
    EXPECT_DOUBLE_EQ(seg.calculateY(2.0), 3.0);
    EXPECT_DOUBLE_EQ(seg.calculateY(3.0), 3.0);
    EXPECT_DOUBLE_EQ(seg.calculateY(3.999), 3.0);
    
    // Экстраполяция справа (включая правую границу)
    EXPECT_DOUBLE_EQ(seg.calculateY(4.0), 2.0);
    EXPECT_DOUBLE_EQ(seg.calculateY(10.0), 2.0);
}

/** @brief Тест оператора вывода для ZeroOrderSegment */
TEST(ZeroOrderSegmentTest, OutputStreamOperator) {
    ZeroOrderSegment seg({{0.0, 1.5}, {3.0, 2.5}});
    
    std::ostringstream out;
    out << seg;
    std::string result = out.str();
    
    EXPECT_NE(result.find("Экстраполятор нулевого порядка"), std::string::npos);
    EXPECT_NE(result.find("(0.00, 1.50)"), std::string::npos);
    EXPECT_NE(result.find("(3.00, 2.50)"), std::string::npos);
}

/** @brief Тест статического метода чтения из потока */
TEST(ZeroOrderSegmentTest, ReadFromStream) {
    std::istringstream input("2\n0.0 10.0\n5.0 20.0");
    
    ZeroOrderSegment seg = ZeroOrderSegment::readFromStream(input);
    const auto& points = seg.getPoints();
    
    ASSERT_EQ(points.size(), 2);
    EXPECT_DOUBLE_EQ(points[0].getX(), 0.0);
    EXPECT_DOUBLE_EQ(points[0].getY(), 10.0);
    EXPECT_DOUBLE_EQ(points[1].getX(), 5.0);
    EXPECT_DOUBLE_EQ(points[1].getY(), 20.0);
}

/** @brief Тест обработки исключений при некорректных данных */
TEST(ZeroOrderSegmentTest, ExceptionHandling) {
    // Слишком мало точек
    EXPECT_THROW(
        ZeroOrderSegment({{0.0, 1.0}}),
        std::invalid_argument
    );
    
    // Пустой вектор
    std::vector<Point> empty;
    EXPECT_THROW(
        ZeroOrderSegment(empty),
        std::invalid_argument
    );
}

/** @brief Тест полиморфного вызова calculateY */
TEST(ZeroOrderSegmentTest, PolymorphicCalculateY) {
    PiecewiseLinearApproximation* base = new ZeroOrderSegment({{1.0, 10.0}, {3.0, 20.0}});
    
    EXPECT_DOUBLE_EQ(base->calculateY(1.5), 10.0);
    EXPECT_DOUBLE_EQ(base->calculateY(3.0), 20.0);
    
    delete base;
}

// ============================================================================
// Интеграционные тесты
// ============================================================================

/** @brief Полный сценарий: создание, расчёт, вывод */
TEST(IntegrationTest, FullWorkflow) {
    // 1. Создаём экстраполятор
    ZeroOrderSegment zoh({
        {0.0, 0.0},
        {1.0, 1.0},
        {2.0, 0.5},
        {3.0, 1.5}
    });
    
    // 2. Проверяем характерную "ступенчатую" форму
    std::vector<std::pair<double, double>> expected = {
        {-1.0, 0.0},    // экстраполяция влево
        {0.0, 0.0},     // начало первого интервала
        {0.5, 0.0},     // внутри [0,1)
        {1.0, 1.0},     // начало второго интервала
        {1.5, 1.0},     // внутри [1,2)
        {2.0, 0.5},     // начало третьего интервала
        {2.5, 0.5},     // внутри [2,3)
        {3.0, 1.5},     // правая граница
        {5.0, 1.5}      // экстраполяция вправо
    };
    
    for (const auto& [x, expectedY] : expected) {
        EXPECT_DOUBLE_EQ(zoh.calculateY(x), expectedY) 
            << "Failed at x = " << x;
    }
    
    // 3. Проверяем вывод
    std::ostringstream out;
    out << zoh;
    EXPECT_NE(out.str().find("Опорные точки"), std::string::npos);
}
