/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 5. Алгоритмы распределения памяти                 *
*          5.3. Распределение памяти блоками переменной длины  *
*                                                              *
*  Автор    : А.Кубенский                                      *
*  Файл     : main.cpp                                         *
*  Описание : Тест системы распределения и управления блоками  *
*             памяти переменного размера, организованными с    *
*             помощью метода граничных маркеров                *
***************************************************************/

#include <iostream>
#include "expression.h"
#include "parser.h"
#include "diff.h"
#include "simplifier.h"

using namespace std;

#include "bintwins.h"

BinTwinsMemory * memoryManagement = new BinTwinsMemory(20);

int main() {
  // Продифференцируем некоторое выражение...
  Expression * beforeDiff = Parser::parse("(x+1)/(x-1)+(x*x+x+1)/x");
  Diff dasher("x");
  beforeDiff->accept(dasher);
  Expression * afterDiff = dasher.getResult();
  cout << "Before derivative evaluation: " << (string)*beforeDiff << endl
       << "After derivative evaluation: " << (string)*afterDiff << endl;

  // ... и упростим его
  Simplifier simplifier;
  afterDiff->accept(simplifier);
  cout << "after its simplification: " << (string)*simplifier.getResult() << endl;

  delete beforeDiff;

  // Вывод статистических данных:
  cout << "Memory management statistics: " << BinTwinsMemory::getClaims()
       << " demands; memory needs: " << BinTwinsMemory::getDemanded()
       << " bytes; memory reserved: " << BinTwinsMemory::getReserved()
       << " bytes; percentage of usage: " << (100.0 * BinTwinsMemory::getDemanded() / BinTwinsMemory::getReserved())
       << " %" << endl;

  return 0;
}
