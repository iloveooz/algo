/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 1. Способы представления структур данных          *
*          1.5. Графы                                          *
*                                                              *
*  Автор    : А.Кубенский                                      *
*  Файл     : main.cpp                                         *
*  Описание : Функция тестирования представлений и             *
*             преобразований графов                            *
***************************************************************/

#include <iostream>
#include "ListGraph.h"
#include "MatrixGraph.h"
#include "SetGraph.h"
#include "ArcGraph.h"
#include "convert.h"

using namespace std;

//-------------------------------------------------------------
// Данная функция определена только для тестирования
// Она выводит изображение графа в виде матрицы смежности. 
// Осторожно! Функция имеет крайне низкую эффективность для
// большинства представлений графов ввиду своей большой общности.
//-------------------------------------------------------------

void print(const Graph & g) {
  int n = g.vertexCount();
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cout << (g.hasArc(i, j) ? '1' : '0') << ' ';
    }
    cout << endl;
  }
}

//-------------------------------------------------------------
// Основная тестирующая функция создает A-граф и последовательно
// преобразует его сначала в М-граф, потом в S-граф, потом в
// L-граф и, наконец, обратно в А-граф. После каждого преобразования
// Граф выводится в стандартный выходной поток. Граф должен
// оставаться неизменным после каждого преобразования
//-------------------------------------------------------------

int main() {
  ArcGraph arcGraph(5);
  arcGraph.addArc(0, 1);
  arcGraph.addArc(0, 3);
  arcGraph.addArc(1, 2);
  arcGraph.addArc(1, 3);
  arcGraph.addArc(1, 4);
  arcGraph.addArc(3, 2);
  arcGraph.addArc(4, 1);
  cout << "Initial ArcGraph:\n";
  print(arcGraph);
  cout << endl;

  // Преобразование в M-граф
  MatrixGraph & matrixGraph = *convert(arcGraph);
  cout << "Coverted to MatrixGraph:\n";
  print(matrixGraph);
  cout << endl;

  // Преобразование в S-граф
  SetGraph & setGraph = *convert(matrixGraph);
  cout << "Coverted to SetGraph:\n";
  print(setGraph);
  cout << endl;

  // Преобразование в L-граф
  ListGraph & listGraph = *convert(setGraph);
  cout << "Coverted to ListGraph:\n";
  print(listGraph);
  cout << endl;

  // Преобразование обратно в A-граф
  ArcGraph & newArcGraph = *convert(listGraph);
  cout << "Coverted to ArcGraph:\n";
  print(newArcGraph);
  cout << endl;

  return 0;
}

