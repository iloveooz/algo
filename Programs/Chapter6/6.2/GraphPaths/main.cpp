/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 6. Алгоритмы обработки сетевой информации         *
*          6.2. Поиск кратчайших путей                         *
*                                                              *
*  Автор    : А. Кубенский                                     *
*  Файл     : main.cpp                                         *
*  Описание : Примеры поиска путей в графах                    *
***************************************************************/

#include "ListGraph.h"
#include "MatrixGraph.h"
#include "graphweight.h"
#include <iostream>

using namespace std;

//============================================================
// Вывод вектора номеров вершин в выходной поток
//============================================================

void showPath(int from, int to, const vector<int> & path) {
  cout << endl << "Shortest path from " << from << " to " << to;
  if (path.empty()) {
    cout << " does not exist";
  } else {
    cout << ':' << endl;
    for (vector<int>::const_iterator it = path.begin(); it != path.end(); ++it) {
      cout << *it << "; ";
    }
  }
  cout << endl;
}

//============================================================
// Основная функция
//============================================================

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

  // Переменная arcsWeight класса TestGraphWeight задает
  // тестовую нагрузку на дуги графа
  class TestGraphWeight : public GraphWeight {
  public :
    double arcLength(int from, int to) const {
      switch (from) {
        case 0: switch (to) { case 1: return 2;
                              case 4: return 7;
                              case 6: return 2;
                              default: return INFINITY;
                            }
        case 1: switch (to) { case 4: return 3;
                              case 7: return 5;
                              default: return INFINITY;
                            }
        case 2: switch (to) { case 8: return 2;
                              default: return INFINITY;
                            }
        case 3: switch (to) { case 0: return 1;
                              default: return INFINITY;
                            }
        case 4: switch (to) { case 6: return 4;
                              case 7: return 4;
                              default: return INFINITY;
                            }
        case 5: switch (to) { case 2: return 1;
                              default: return INFINITY;
                            }
        case 6: switch (to) { case 3: return 3;
                              default: return INFINITY;
                            }
        case 8: switch (to) { case 5: return 2;
                              default: return INFINITY;
                            }
        default: return INFINITY;
      }
    }
  } arcsWeight;

  // Поиск кратчайших путей с помощью алгоритма обхода графа в ширину
  showPath(0, 3, testGraph.getShortestPath(0, 3));
  showPath(0, 8, testGraph.getShortestPath(0, 8));

  // Поиск кратчайших путей с помощью алгоритма Дейкстры
  vector<int> path;  
  testGraph.getDijkstraPath(0, 7, arcsWeight, path);
  showPath(0, 7, path);

  testGraph.getDijkstraPath(3, 4, arcsWeight, path);
  showPath(3, 4, path);

  // Создаем тестовый пример M-графа.
  MatrixGraph testMGraph(9);
  testMGraph.addArc(0, 1);
  testMGraph.addArc(0, 4);
  testMGraph.addArc(0, 6);
  testMGraph.addArc(1, 4);
  testMGraph.addArc(1, 7);
  testMGraph.addArc(2, 8);
  testMGraph.addArc(3, 0);
  testMGraph.addArc(4, 6);
  testMGraph.addArc(4, 7);
  testMGraph.addArc(5, 2);
  testMGraph.addArc(6, 3);
  testMGraph.addArc(8, 5);

  // Выводим матрицу смежности графа и его транзитивного замыкания
  cout << endl << testMGraph << endl;
  cout << closure(testMGraph);

  MatrixGraph testCopy = testMGraph;
  // Выводим матрицу смежности графа и его транзитивного замыкания
  cout << endl << testCopy << endl;
  FloydWarshall(testCopy);
  cout << testCopy << endl;

  double ** Path;
  int ** Dir;
  getMinPaths(testMGraph, arcsWeight, Path, Dir);
  cout << endl << "Minimal paths matrix:" << endl;
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      if (Path[i][j] == INFINITY) cout << " -"; else {
        if (Path[i][j] < 10) cout << ' ';
        cout << Path[i][j];
      }
      cout << "  ";
    }
    cout << endl;
  }

  cout << endl << "Directions matrix:" << endl;
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      if (Dir[i][j] == -1) cout << '-'; else cout << Dir[i][j];
      cout << "  ";
    }
    cout << endl;
  }

  return 0;
}
