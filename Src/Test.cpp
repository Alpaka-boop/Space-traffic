#include <iostream>
#include <tuple>

#include "Test.h"
#include "Ship.h"
#include "Conditions.h"
#include "Difficulties.h"
#include "Engine.h"
#include "Result.h"

bool Test() {
    Market market;
    DensitySpace densitySpace;

    /* Test 1
     * Маршрут средней длины в туманности повышенной плотности пространства.
     * Обработать два корабля ([Theory]): Прогулочный челнок и Авгур.
     * Первый не имеет прыжковых двигателей, второй имеет недостаточную дальность.
     * Оба не должны завершить маршрут.
     */
    std::cout << "==============Test1==============\n";

    Conditions conditions1(std::make_tuple(800ll, 99999ll, 1200ll), Difficulties(0, 0, 0, 0)
                           , std::make_shared<Market>(market), densitySpace);
    PleasureShuttle pleasureShuttle1;
    Avgur avgur1;

    std::cout << "== Pleasure shuttle\n";
    Result result1 = pleasureShuttle1.Navigate(conditions1);
    result1.Dump(std::cout);
    std::cout << '\n';

    std::cout << "== Avgur\n";
    Result result2 = avgur1.Navigate(conditions1);
    result2.Dump(std::cout);
    std::cout << '\n';

    /* Test 2
     * Вспышка антиматерии в подпространственном канале.
     * Обработать два корабля ([Theory]):  Ваклас и Ваклас с фотонными дефлекторами.
     * В первом случае маршрут не должен быть пройден из-за потери экипажа, во втором – пройден.
     */

    std::cout << "==============Test2==============\n";
    Conditions conditions2(std::make_tuple(800ll, 1000ll, 1200ll), Difficulties(0, 0, 1, 0)
            , std::make_shared<Market>(market), densitySpace);
    Vaclas vaclas1;
    Vaclas vaclas2(true);

    std::cout << "== Vaclas\n";
    Result result3 = vaclas1.Navigate(conditions2);
    result3.Dump(std::cout);
    std::cout << '\n';

    std::cout << "== Vaclas with photonic defl\n";
    Result result4 = vaclas2.Navigate(conditions2);
    result4.Dump(std::cout);
    std::cout << '\n';

    /*
     * Космо-кит в туманности нитринных частиц.
     * Обработать три корабля ([Theory]): Ваклас, Авгур и Мередиан.
     * Первый – уничтожен после столкновения, второй – только потерял щиты, третий – был не тронут.
     */

    std::cout << "==============Test3==============\n";
    NitrineSpace nitrineSpace;
    Conditions conditions3(std::make_tuple(800ll, 1000ll, 1200ll), Difficulties(0, 0, 0, 1)
            , std::make_shared<Market>(market), nitrineSpace);
    Vaclas vaclas3;
    Avgur avgur2;
    Meredian meredian1;

    std::cout << "== Vaclas\n";
    Result result5 = vaclas3.Navigate(conditions3);
    result5.Dump(std::cout);
    std::cout << '\n';

    std::cout << "== Avgur\n";
    Result result6 = avgur2.Navigate(conditions3);
    result6.Dump(std::cout);
    std::cout << '\n';

    std::cout << "== Meredian\n";
    Result result7 = meredian1.Navigate(conditions3);
    result7.Dump(std::cout);
    std::cout << '\n';

    return true;
}