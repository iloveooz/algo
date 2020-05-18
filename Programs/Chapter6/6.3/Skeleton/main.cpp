/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 6. Алгоритмы обработки сетевой информации         *
*          6.3. Определение остовных деревьев                  *
*                                                              *
*  Автор    : А.Кубенский                                      *
*  Файл     : main.cpp                                         *
*  Описание : Тестовая  функции для проверки нахождения        *
*             минимальных остовных деревьев графа              *
***************************************************************/

#include "ListGraph.h"
#include "graphweight.h"
#include <iostream>

using namespace std;

const double INFINITY = 10000;

int main() {
  // Создаем тестовый пример L-графа.
  ListGraph testGraph(9);
  testGraph.addArc(0, 1);
  testGraph.addArc(0, 4);
  testGraph.addArc(0, 6);
  testGraph.addArc(1, 4);
  testGraph.addArc(1, 7);
  testGraph.addArc(2, 8);
  testGraph.addArc(3, 0);
  testGraph.addArc(4, 6);
  testGraph.addArc(4, 7);
  testGraph.addArc(5, 2);
  testGraph.addArc(6, 3);
  testGraph.addArc(8, 5);

  testGraph.addArc(1, 0);
  testGraph.addArc(4, 0);
  testGraph.addArc(6, 0);
  testGraph.addArc(4, 1);
  testGraph.addArc(7, 1);
  testGraph.addArc(8, 2);
  testGraph.addArc(0, 3);
  testGraph.addArc(6, 4);
  testGraph.addArc(7, 4);
  testGraph.addArc(2, 5);
  testGraph.addArc(3, 6);
  testGraph.addArc(5, 8);

  // Переменная arcsWeight класса TestGraphWeight задает
  // тестовую нагрузку на дуги графа
  class TestGraphWeight : public GraphWeight {
  public :
    double arcLength(int from, int to) const {
      if (from > to) return arcLength(to, from);
      switch (from) {
        case 0: switch (to) { case 1: return 2;
                              case 3: return 1;
                              case 4: return 7;
                              case 6: return 2;
                              default: return INFINITY;
                            }
        case 1: switch (to) { case 4: return 3;
                              case 7: return 5;
                              default: return INFINITY;
                            }
        case 2: switch (to) { case 5: return 1;
                              case 8: return 2;
                              default: return INFINITY;
                            }
        case 3: switch (to) { case 6: return 3;
                              default: return INFINITY;
                            }
        case 4: switch (to) { case 6: return 4;
                              case 7: return 4;
                              default: return INFINITY;
                            }
        case 5: switch (to) { case 8: return 2;
                              default: return INFINITY;
                            }
        default: return INFINITY;
      }
    }
  } arcsWeight;

  cout << testGraph.minSkeleton(cout, arcsWeight) << endl << endl;
  //cout << endl << "Minimal skeleton weight = " << minWeight << endl << endl;

  //minWeight = testGraph.minSkeletonPrim(cout, arcsWeight);
  cout << testGraph.minSkeletonPrim(cout, arcsWeight) << endl << endl;
  //cout << endl << "Minimal skeleton weight = " << minWeight << endl << endl;

  return 0;
}
