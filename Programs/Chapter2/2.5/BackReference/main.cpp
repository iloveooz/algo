/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 2. Базовые алгоритмы                              *
*          2.5. Прохождение деревьев                           *
*                                                              *
*  Автор    : A.Koubenski                                      *
*  Файл     : main.cpp                                         *
*  Описание : Функция проверки работы внешнего итератора       *
*             прошитого дерева с обратными ссылками.           *
***************************************************************/

#include "tree.h"
#include "charAnalizer.h"
#include <iostream>

using namespace std;

int main() {
  // Задаем строковое представление дерева из символов в соответствии
  // с тем, как это предписано правилами класса CharAnalizer
  CharAnalizer analizer("(A(B)(C(E)(F(H)(I)(K)))(D(G)))");
  // Строим дерево из символов
  Tree<char> t(analizer);
  // Контрольная печать дерева
  cout << "Tree structure expressed in parantheses (youngest sons marked with dashes):" << endl;
  t.print(cout);
  cout << endl;

  // Печать содержимого узлов дерева в порядке нисходящего обхода "в глубину".
  // Используется итератор BackRefIterator, полученный с помощью метода t.iteratorBR
  cout << "Tree nodes in depth first order (external iterator using back references):" << endl;
  Iterator<char> * iBR = t.iteratorBR();
  for (; iBR->hasMoreElements(); ++*iBR) {
    cout << **iBR;
  }
  cout << endl << endl;
  delete iBR;

  return 0;
}
