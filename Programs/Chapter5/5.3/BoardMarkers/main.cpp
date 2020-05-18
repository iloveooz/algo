/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 5. Алгоритмы распределения памяти                 *
*          5.3. Распределение памяти блоками переменной длины  *
*                                                              *
*  Автор    : А.Кубенский                                      *
*  Файл     : bilistmemory.cpp                                 *
*  Описание : Тест системы распределения и управления блоками  *
*             памяти переменного размера, организованными с    *
*             помощью метода граничных маркеров                *
***************************************************************/

#include <iostream>

using namespace std;

#include "expression.h"
#include "parser.h"
#include "diff.h"
#include "simplifier.h"
#include "boardmarkers.h"

BoardMarkersMemory * memoryManagement = new BoardMarkersMemory(5000);

int main() {
  // Продифференцируем некоторое выражение...
  Expression * beforeDiff = Parser::parse("(x+1)/(x-1)");
  Diff dasher("x");
  beforeDiff->accept(dasher);
  Expression * afterDiff = dasher.getResult();
  cout << "Before derivative evaluation: " << (string)*beforeDiff << endl
       << "After derivative evaluation: " << (string)*afterDiff << endl;

  // ... и упростим его
  Simplifier simplifier;
  afterDiff->accept(simplifier);
  cout << "after its simplification: " << (string)*simplifier.getResult() << endl;

  return 0;
}
